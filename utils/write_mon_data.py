import json
import os
import requests
import re

replacements = {
  "smelling-salts" : "SMELLING_SALT",
  "high-jump-kick" : "HI_JUMP_KICK",
}

def try_get_data(file, url):
  data = None
  try:
    with open(file, "r", encoding="utf-8") as datafile:
      data = json.loads(datafile.read())
  except:
    print("Fetching data for %s..." % file)
    response = requests.get(url)
    if response.status_code == 200:
      data = response.json()
      with open(file, "w", encoding="utf-8") as datafile:
        datafile.write(response.text)
  return data

def make_name(append, mname):
  return append + (mname.upper().replace("-", "_") if not mname in replacements else replacements[mname])

mons = {}
with open("../include/constants/species.h", "r") as monfile:
  line_regex = re.compile(r"#define (SPECIES_([^\s]+))")
  for line in monfile:
    line_match = line_regex.match(line)
    if line_match:
      match = line_match[2]
      if match != "NONE" and match != "EGG" and not match.startswith("UNOWN_") and not match.startswith("OLD_UNOWN_"):
        match = match.lower().replace("_", "-")
        mons[line_match[1]] = match

do_egg = False
do_level_up = False
do_machine = False
do_stats = True

mon = None
mons_egg_moves = {}
mons_tm_moves = {}
mons_level_moves = {}
mons_data = {}
max_egg = 0
max_level = 0
for mon_key in mons:
  mon = mons[mon_key]
  file = os.path.join("data/mons", mon + ".json")

  if not os.path.exists(file):
    print(f"Fetching data for {mon}")
    f = mon.replace("deoxys", "deoxys-normal")
    response = requests.get(f"https://pokeapi.co/api/v2/pokemon/{f}")
    if response.status_code == 200:
      data = response.json()
      with open(file, "w", encoding="utf-8") as datafile:
        datafile.write(response.text)
    else:
      print(f"Couldn't get data for {mon}!")

  if os.path.exists(file):
    with open(file, "r") as f:
      mon_data = json.loads(f.read())

      mons_data[mon_key] = mon_data

      mon_name = mon_data["name"]

      egg_moves = []
      tm_moves = []
      level_moves = []
      for move in mon_data["moves"]:
        for vgd in move["version_group_details"]:
          move_name = move["move"]["name"]
          vg_name = vgd["version_group"]["name"]
          vg_learn_method = vgd["move_learn_method"]["name"]

          if do_egg and vg_name == "ultra-sun-ultra-moon" and vg_learn_method == "egg":
            egg_moves.append(make_name("MOVE_", move_name))

          if do_level_up and vg_name == "ultra-sun-ultra-moon" and vg_learn_method == "level-up":
            level_moves.append((vgd["level_learned_at"], make_name("MOVE_", move_name)))

          if do_machine and vg_name == "omega-ruby-alpha-sapphire" and vg_learn_method == "machine":
            mdata = try_get_data(os.path.join("data", "moves", f"{move_name}.json"), move["move"]["url"])
            for machine in mdata["machines"]:
              if machine["version_group"]["name"] == "omega-ruby-alpha-sapphire":
                tmdata = try_get_data(os.path.join("data", "machines", f"{move_name}.json"), machine["machine"]["url"])
                tm_moves.append(make_name("", tmdata["item"]["name"]))

      if (len(egg_moves) > 0):
        max_egg = len(egg_moves) if len(egg_moves) > max_egg else max_egg
        egg_moves.sort()
        egg_moves_str = "egg_moves(" + make_name("", mon_name) + ",\n        " + ",\n        ".join(egg_moves) + "),"
        mons_egg_moves[mon_data["order"]] = egg_moves_str

      if (len(level_moves) > 0):
        max_level = len(level_moves) if len(level_moves) > max_level else max_level
        level_moves.sort(key=lambda x: (x[0], x[1]))
        pascal_case_name = ''.join(x for x in mon_name.title() if not x == "-")
        level_moves_str = f"static const struct LevelUpMove s{pascal_case_name}LevelUpLearnset[] = {{\n    "
        level_moves_str += "\n    ".join(map(lambda x: f"LEVEL_UP_MOVE({x[0]: >2}, {x[1]}),", level_moves))
        level_moves_str += "\n    LEVEL_UP_END\n};"
        mons_level_moves[mon_data["order"]] = level_moves_str

      if do_machine:
        tm_moves_str = f"    [{mon_key}] = {{ 0, 0, 0, 0 }},"
        if (len(tm_moves) > 0):
          tm_moves.sort()
          tm_moves_str = f"    [{mon_key}] =\n    {{"
          for i in range(4):
            tm_moves_str += "\n        " + " | ".join(map(lambda x: f"TMHM({x}, {i})", tm_moves)) + ","
          tm_moves_str += "\n    },"
        mons_tm_moves[mon_data["order"]] = tm_moves_str

if do_egg:
  sorted_egg_moves = [x[1] for x in sorted(mons_egg_moves.items(), key=lambda t: t[0])]
  print(f"Maximum number of egg moves on a single mon: {max_egg}")
  with open("egg_moves.h", "w") as f:
    f.write("#define EGG_MOVES_SPECIES_OFFSET 20000\n")
    f.write("#define EGG_MOVES_TERMINATOR 0xFFFF\n")
    f.write("#define egg_moves(species, moves...) (SPECIES_##species + EGG_MOVES_SPECIES_OFFSET), moves\n\n")
    f.write("const u16 gEggMoves[] = {\n    ")
    f.write("\n\n    ".join(sorted_egg_moves))
    f.write("\n\n    EGG_MOVES_TERMINATOR\n};\n")

if do_level_up:
  sorted_level_moves = [x[1] for x in sorted(mons_level_moves.items(), key=lambda t: t[0])]
  print(f"Maximum number of level up moves on a single mon: {max_level}")
  with open("level_up_learnsets.h", "w") as f:
    f.write("#define LEVEL_UP_MOVE(lvl, moveLearned) {.move = moveLearned, .level = lvl}\n\n")
    f.write("\n\n".join(sorted_level_moves))
    f.write("\n")

if do_machine:
  sorted_tm_moves = [x[1] for x in sorted(mons_tm_moves.items(), key=lambda t: t[0])]
  with open("tmhm_learnsets.h", "w") as f:
    f.write("#define TMHM(tmhm, i) ((ITEM_##tmhm - ITEM_TM01) / 32 == i ? (u32)1 << ((ITEM_##tmhm - ITEM_TM01) % 32) : 0)\n\n")
    f.write("const u32 gTMHMLearnsets[][4] =\n{\n")
    f.write("\n\n".join(sorted_tm_moves))
    f.write("\n};\n")

if do_stats:
  output = ""
  with open("../src/data/pokemon/base_stats.h", "r") as statsfile:
    start_regex = re.compile(r"\s+\[(\w+)\]")

    hp_regex = re.compile(r"(\.baseHP[\s=]+)[0-9]+")
    atk_regex = re.compile(r"(\.baseAttack[\s=]+)[0-9]+")
    def_regex = re.compile(r"(\.baseDefense[\s=]+)[0-9]+")
    spd_regex = re.compile(r"(\.baseSpeed[\s=]+)[0-9]+")
    sp_atk_regex = re.compile(r"(\.baseSpAttack[\s=]+)[0-9]+")
    sp_def_regex = re.compile(r"(\.baseSpDefense[\s=]+)[0-9]+")

    exp_regex = re.compile(r"(\.expYield[\s=]+)[0-9]+")

    hp_yield_regex = re.compile(r"(\.evYield_HP[\s=]+)[0-9]+")
    atk_yield_regex = re.compile(r"(\.evYield_Attack[\s=]+)[0-9]+")
    def_yield_regex = re.compile(r"(\.evYield_Defense[\s=]+)[0-9]+")
    spd_yield_regex = re.compile(r"(\.evYield_Speed[\s=]+)[0-9]+")
    sp_atk_yield_regex = re.compile(r"(\.evYield_SpAttack[\s=]+)[0-9]+")
    sp_def_yield_regex = re.compile(r"(\.evYield_SpDefense[\s=]+)[0-9]+")

    mon = None
    for line in statsfile:
      match = start_regex.match(line)
      if match and match[1] in mons_data:
        mon = mons_data[match[1]]
      if mon:
        line = hp_regex.sub(f"\\g<1>{mon['stats'][5]['base_stat']}", line)
        line = atk_regex.sub(f"\\g<1>{mon['stats'][4]['base_stat']}", line)
        line = def_regex.sub(f"\\g<1>{mon['stats'][3]['base_stat']}", line)
        line = sp_atk_regex.sub(f"\\g<1>{mon['stats'][2]['base_stat']}", line)
        line = sp_def_regex.sub(f"\\g<1>{mon['stats'][1]['base_stat']}", line)
        line = spd_regex.sub(f"\\g<1>{mon['stats'][0]['base_stat']}", line)

        line = exp_regex.sub(f"\\g<1>{mon['base_experience']}", line)

        line = hp_yield_regex.sub(f"\\g<1>{mon['stats'][5]['effort']}", line)
        line = atk_yield_regex.sub(f"\\g<1>{mon['stats'][4]['effort']}", line)
        line = def_yield_regex.sub(f"\\g<1>{mon['stats'][3]['effort']}", line)
        line = sp_atk_yield_regex.sub(f"\\g<1>{mon['stats'][2]['effort']}", line)
        line = sp_def_yield_regex.sub(f"\\g<1>{mon['stats'][1]['effort']}", line)
        line = spd_yield_regex.sub(f"\\g<1>{mon['stats'][0]['effort']}", line)

      output += line

  with open("base_stats.h", "w") as f:
    f.write(output)
