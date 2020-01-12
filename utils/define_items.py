import re

start_cat_regex = re.compile(r"^//\s+(.+)\n")
end_items_regex = re.compile(r"^#define\s+ITEMS_COUNT")
item_regex = re.compile(r"^#define\s+(ITEM_[^\s]+)\s.+(//.+)?")

cur_group = None
output = ""
index = 1
doing = 0

with open("../include/constants/items.h", "r") as f:
  for line in f:
    if doing < 2:
      start_match = start_cat_regex.match(line)
      end_match = end_items_regex.match(line)
      if start_match or end_match:
        if cur_group:
          output += f"#define LAST_{cur_group}_INDEX {index - 1}\n\n"
        if start_match:
          doing = 1
          cur_group = start_match[1].upper().replace(" ", "_")
          output += f"// {start_match[1]}\n"
          output += f"#define FIRST_{cur_group}_INDEX {index}\n"
        if end_match:
          output += f"#define ITEMS_COUNT {index}\n"
          doing = 2
      elif cur_group:
        item_match = item_regex.match(line)
        if item_match:
          comment = "" if not item_match[2] else " " + item_match[2]
          output += f"#define {item_match[1]} {index}{comment}\n"
          index += 1
      elif doing == 0:
        output += line
    else:
      output += line
  
with open("../include/constants/items.h", "w", newline="\n") as f:
  f.write(output)