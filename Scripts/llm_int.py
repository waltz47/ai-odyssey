import sys
import json
from openai import OpenAI
import os
from tools import *
import re

def log(text):
    print(text)
    open("log.txt",'a').write(text + '\n')

def call_function_by_name(function_name, arguments):
    return globals()[function_name](**arguments)

def main(input_file, output_file):
    with open(input_file, 'r') as f:
        data = f.read()
    log(data)

    client = OpenAI(
            api_key=open('F:/key.txt', 'r').read(), #xai api key TODO: fix this
            base_url="https://api.x.ai/v1",
        )

    messages = [ {"role": "system", "content": f'''You are an NPC in a world called 'the outer world'. Your role is to behave authentically, providing responses that reflect the character's personality, backstory, and the current context of the game world. You have access to one tool:

- **Talk**: This tool allows you to talk to the player as the AI character.
  - Tool Call: `talk(context)`

Guidelines for your operation:

1. **Stay In Character**: Always respond in accordance with your NPC's personality, background, and emotional state.

2. **Context Awareness**: When using `talk`, consider the context provided by the player's actions, the environment, or previous interactions to make your dialogue relevant and engaging.

3. **React to Player**: Use the `talk` tool based on player dialogue or actions to create dynamic conversational exchanges.

4. **Do not be Proactive**: Use `talk` to respond to characters, not to initiate conversations.

5. **Efficiency**: Use the tool when it adds value to the interaction. Sometimes, a simple, direct response from your character's perspective might be sufficient without needing to generate new dialogue.

6: **Only Interact via Tool Calls**: Do not talk directly. Use the tools provided to interact and perform actions.

When you respond, integrate the `talk` tool call naturally into your narrative or dialogue. Here's an example:

Remember, your primary goal is to enrich the player's experience with realistic, engaging dialogue that fits the context of the game or scenario.'''},
        {"role": "user", "content": data }]

    tools = [{'type': "function", "function": f} for f in functions]
    # calling xai api
    response = client.chat.completions.create(
        model='grok-beta',
        messages=messages,
        temperature=0.3,
        tools=tools
    )
    print(response)

    log(response.choices[0].message.content)

    try:
        tool_call = response.choices[0].message.tool_calls[0]
    except:
        log("invalid tool call.")
        sys.exit(1)
    
    id_match = re.search(r'id=\'([^\']+)\'', str(tool_call))
    id_match = id_match.group(1) if id_match else None

    # Extract function name
    function_name = re.search(r'name=\'([^\']+)\'', str(tool_call))
    function_name = function_name.group(1) if function_name else None

    # Extract arguments, handling potential escape characters
    args_match = re.search(r'arguments=\'((?:\\\\|\\\'|[^\'])*)\'', str(tool_call))
    arguments = json.loads(args_match.group(1).replace("\'", "\\'")) if args_match else {}

    # Create a dictionary to represent the JSON structure
    json_data = {
        "id": id_match,
        "type": "function",
        "function": {
            "name": function_name,
            "arguments": arguments
        }
    }

    print(json_data)

    # Write to file
    with open(output_file, 'w') as f:
        json.dump(json_data, f, indent=2)
    # call the tool
    function_name = tool_call.function.name
    arguments = json.loads(tool_call.function.arguments)
    result = call_function_by_name(function_name, arguments)
    function_call_result_message = {
        "role": "tool",
        "content": str(result),
        "tool_call_id": response.choices[0].message.tool_calls[0].id
    }

    # append tool results to the history and repeat
    messages.append(response.choices[0].message)
    messages.append(function_call_result_message)
        
if __name__ == "__main__":
    open("log.txt", 'w')

    if len(sys.argv) != 3:
        print("Usage: python_script.py <input_file> <output_file>")
        sys.exit(1)
    
    input_file, output_file = sys.argv[1], sys.argv[2]
    main(input_file, output_file)





"""
NPC <---> Player
NPC <---> AI
"""