from flask import Flask, render_template, request, redirect, url_for, jsonify, Response
import requests
import hashlib
import json
app = Flask(__name__)


api_url = "https://dc0d-158-140-138-91.ngrok-free.app" #change to MFAz address

gateway_id = 8888 #change this for new gateway

caller_info = []

@app.route('/')
def index():
    return render_template('index.html', title="Home Page", gateway_id = gateway_id)


@app.route('/get-api-data', methods=['GET'])
def get_api_data():
    response = requests.get(api_url) #switch this
    api_data = response.text
    print(api_data)
    return api_data

@app.route('/verify', methods=['POST'])
def verify():

    GA = ""
    try:
        # Try to open and read the GA.txt file
        with open('GA.txt', 'r') as file:
            GA = file.read()
    except FileNotFoundError:
        print("Error: GA.txt file not found.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    
    payload ={
        'id' : gateway_id,
        'GA' : GA
    }
    url = api_url + "/verify"
    try:
        # Forward POST request to the external API
        response = requests.post(url, json=payload)
        response_data = response.json()  # Parse JSON response from the external API

        GA = response_data.get("GA")


        if(GA != "Access Denied"): 
            with open("GA.txt","w") as file:
                file.write(GA)
        return response_data

    except requests.exceptions.RequestException as e:
        # Handle errors in the request to the external API
        return "Null"
    
@app.route('/auth', methods=['POST'])
def auth():
    payload ={
        'id' : gateway_id,
    }
    url = f"{api_url}/authrun"
    print(url)
    try:
        # Forward POST request to the external API
        response = requests.post(url, json=payload)
        response_data = response.json()  # Parse JSON response from the external API

        print(response_data.get("GA"))

        GA = response_data.get("GA")

        with open("GA.txt","w") as file:
            file.write(GA)

        return response_data

    except requests.exceptions.RequestException as e:
        # Handle errors in the request to the external API
        return "Null"
    

@app.route('/access_request', methods=['POST'])
def access_request():
    global caller_info
    try:
        data = request.get_json()

        id = data.get('id')
        SGAi = data.get('SGAi')
        payload ={
            'id' : id,
            'GA' : SGAi
        }

        url = api_url + "/verify"


        try:
            # Forward POST request to the external API
            response = requests.post(url, json=payload)
            response_data = response.json()  # Parse JSON response from the external API

            GA = response_data.get("GA")
            
            response_data['from'] = gateway_id
            caller_info = ({
                "caller" : id,
                "GA" : GA
            })

            return response_data

        except requests.exceptions.RequestException as e:
            # Handle errors in the request to the external API
            return "Null"

    except Exception as e:
        print(e)

@app.route('/access-gateway', methods=['POST'])
def access_gateway():

    
    data = request.get_json()
    if not data or 'userInput' not in data or not data['userInput'].strip():
        return jsonify({"error": "Invalid input"}), 400

    user_input = data['userInput']
    print(user_input)

    GA = ""
    try:
        # Try to open and read the GA.txt file
        with open('GA.txt', 'r') as file:
            GA = file.read()
    except FileNotFoundError:
        print("Error: GA.txt file not found.")
    except Exception as e:
        print(f"An unexpected error occurred: {e}")
    
    payload ={
        'id' : gateway_id,
        'SGAi' : GA
    }
    # to_url = "https://f397-158-140-138-91.ngrok-free.app"
    to_url = user_input
    url = to_url + "/access_request"

    print(url)
    try:
        # Forward POST request to the external API
        response = requests.post(url, json=payload)
        response_data = response.json()  # Parse JSON response from the external API

        GA = response_data.get("GA")

        if(GA != "Access Denied"): 
            with open("GA.txt","w") as file:
                file.write(GA)
        
        return response_data

    except requests.exceptions.RequestException as e:
        # Handle errors in the request to the external API
        return "Null"
previous_caller_info_hash = None
@app.route('/stream-caller-info', methods=['GET'])
def stream_caller_info():
    def event_stream():
        global previous_caller_info_hash

        while True:
            # Convert caller_info to JSON and hash it for comparison
            current_caller_info_json = json.dumps(caller_info, sort_keys=True)
            current_caller_info_hash = hashlib.sha256(current_caller_info_json.encode()).hexdigest()

            # Check if the content of caller_info has changed
            if current_caller_info_hash != previous_caller_info_hash:
                # Send the latest caller_info as JSON inside the SSE format (single object)
                yield f"data: {current_caller_info_json}\n\n"
                previous_caller_info_hash = current_caller_info_hash

    return Response(event_stream(), content_type='text/event-stream')
if __name__ == '__main__':
    app.run(debug=True, port = 5000)
