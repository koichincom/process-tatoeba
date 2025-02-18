import csv
import json
from collections import defaultdict

def csv_to_grouped_json(csv_file, json_file):
    word_dict = defaultdict(set)  # Using set to avoid duplicate sentences

    with open(csv_file, newline='', encoding='utf-8') as f:
        reader = csv.reader(f)
        next(reader)  # Skip header
        for row in reader:
            if len(row) < 2:
                continue
            word = row[0].strip().strip('"')
            sentence = row[1].strip().strip('"')

            # Add sentence to the word's set
            word_dict[word].add(sentence)

    # Convert sets to lists and write to JSON
    with open(json_file, 'w', encoding='utf-8') as f:
        json.dump({k: list(v) for k, v in word_dict.items()}, f, indent=4, ensure_ascii=False)

    print(f"JSON file created: {json_file}")

if __name__ == '__main__':
    csv_to_grouped_json('eng_sentences.csv', 'eng_sentences.json')