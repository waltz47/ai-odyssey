functions = [
    {
        "name": "talk",
        "description": "Print dialogue for a character",
        "parameters": {
            "type": "object",
            "properties": {
                "dialogue": {
                    "type": "string",
                    "description": "The dialogue text",
                    "example_value": "Hello there! How are you doing today?",
                },
            },
            "required": ["dialogue"],
            "optional": [],
        },
    },
]

def talk(dialogue):
    print("Generated dialogue:", dialogue)
    return dialogue