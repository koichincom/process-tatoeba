import json
import os

def split_json_by_first_letter(input_file, output_folder):
    # Read the input JSON file
    with open(input_file, "r", encoding="utf-8") as f:
        data = json.load(f)
    
    # Dictionary to hold groups
    groups = {}
    
    # Group keys by their first character
    for word, sentences in data.items():
        if not word: 
            continue
        first_char = word[0].lower()
        # If the first character is not a letter, group it under "_"
        group_key = first_char if first_char.isalpha() else "_"
        
        if group_key not in groups:
            groups[group_key] = {}
        groups[group_key][word] = sentences
    
    # Create the output folder if it doesn't exist
    os.makedirs(output_folder, exist_ok=True)
    
    # Write each group to its own JSON file
    for group_key, group_data in groups.items():
        output_file = os.path.join(output_folder, f"{group_key}.json")
        with open(output_file, "w", encoding="utf-8") as f:
            json.dump(group_data, f, indent=4, ensure_ascii=False)
        print(f"Written group '{group_key}' to {output_file}")

if __name__ == "__main__":
    # Change these file names/folders as needed
    input_json = "limited.json"
    output_folder = "final_output"
    split_json_by_first_letter(input_json, output_folder)