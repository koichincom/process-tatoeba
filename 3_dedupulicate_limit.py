import json

def process_json(input_file, output_file, limit=100):
    # Load the JSON file
    with open(input_file, 'r', encoding='utf-8') as f:
        data = json.load(f)

    processed_data = {}
    # Process each word key
    for word, sentences in data.items():
        seen = set()
        deduped = []
        # Remove duplicates while preserving order
        for sentence in sentences:
            if sentence not in seen:
                seen.add(sentence)
                deduped.append(sentence)
        # Limit to the first 100 sentences
        processed_data[word] = deduped[:limit]

    # Save the processed data back to a new JSON file
    with open(output_file, 'w', encoding='utf-8') as f:
        json.dump(processed_data, f, indent=4, ensure_ascii=False)

    print(f"Processed JSON saved to {output_file}")

if __name__ == "__main__":
    process_json("eng_sentences.json", "limited.json", limit=100)