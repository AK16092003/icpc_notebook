// Tools -> Build System -> New Build System

{
    "cmd": ["g++", "-std=c++17", "$file_name", "-o", "$file_base_name.exe", "&&", "$file_base_name.exe", "<", "input.txt", ">", "output.txt"],
    "selector": "source.c++",
    "shell": true,
    "working_dir": "$file_path"
}
