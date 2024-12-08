import sys
import json

def main(input_file, output_file):
    with open(input_file, 'r') as f:
        data = f.read()
    
    # Example processing
    processed_data = {"processed": f"Processed: {data}"}
    
    with open(output_file, 'w') as f:
        json.dump(processed_data, f)

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python_script.py <input_file> <output_file>")
        sys.exit(1)
    
    input_file, output_file = sys.argv[1], sys.argv[2]
    main(input_file, output_file)

    sys.exit(0)