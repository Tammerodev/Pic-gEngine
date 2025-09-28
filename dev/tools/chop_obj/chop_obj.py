# take OBJ file and chop it up into invidual stl files - one per object

import sys
import time

# script takes one argument, example: python3 chop_obj.py [path_to_obj]
if len(sys.argv) == 2:
    filepath = sys.argv[1]
    output_path = "dev/tools/chop_obj/output"

    print(f"Opening file {filepath}...")

    with open(filepath, 'r') as file:
        # this stores what object we are reading now
        object_name = ""   
        current_writing_file = open(f"{output_path}/.trash.out", 'w')

        for line in file:
            file_text = line.strip()

            if line[0] == 'o': # beginning of OBJ object declaration
                object_name = line.split(' ')[1].strip()
                current_writing_file = open(f"{output_path}/chop_{object_name}", 'w')

                print(f"Now writing for object: {object_name}")
            
            elif current_writing_file != None: 
                current_writing_file.write(line)

            
else:
    print("Error: script takes one cli argument. ")