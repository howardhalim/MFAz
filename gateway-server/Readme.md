# This is gateway-demo server. 
- Duplicate this as much as required for the demo.
- Each instances refers as a server/client that communicate in a distributed manners

- After duplication:
1. Create a python virtualenv ("python -m venv venv")
2. Start the venv ("source venv/bin/activate" - Linux or ".\venv\Scripts\Activate - windows)
3. install all the required libraries ("pip install -r requirements.txt")
4. start the flask project ("python gateway.py")

- Files Directory
1. [/templates] - holds the [index.html] files that creates the front-end demo on the web
2. [GA.txt] - the historically granted access locally stored in the device - Delete this file when it is a new gateway device (reset it)
3. [gateway.py] - the flask application to start the gateway server demo
    on the [gateway.py] files there are several lines that need to be changed on each individual running system:
    - "api_url" -> change to intended hosted MFAz IP address (cloud/local)
    - "gateway_id" -> represents its own id, change this accordingly to any numbers to shows different gateway representation in the web
    - under the app.run, change the port number accordingly into an unused port (if running multiple gateway server on the same device)
4. "python gateway.py" to run the Flask application



# Ngrok run here after running both gateway.py and MFAz server
- For this "sec" server, we hosted 1 gateway and 1 MFAz using 1 single Ngrok Account.
- update [ngrok.yml] file accordingly (update the authtoken and change any port switch if required)
- After starting both gateway and MFAz server here, run "ngrok start --all --config ngrok.yml" to do port forwarding to ngrok for cross device demo.
- This link only works for 8 hours (can be shutdown manually), and will need to be restart after 8 hours (Free account)
- Save the acquired url by ngrok to represents as the IP address.


# To have the cross-device communication:
1. run multiple gateway-server in multiple device with different "gateway_id" (To identify through webview).
2. Host each gateway-server to the internet using "ngrok" refer to ngrok documentation (change the "ngrok.yml" settings) - You might need multiple emails if you are using free account
3. access all the hosted gateway-server using their respective "hosted urls" in any browser to get the view up.
4. "Access Request" button is to do self authorization to the MFAz server
5. "Dummy Access" button is to do dummy authorization (fix authorized authorization process) - is used to generate dummy historical GA as its first few historical data
6. "URL" refers to "other" gateway-servers URL/IP that this current gateway-server wanted to communicate to. The authorization process will be done by the "other" gateway not on the "current" gateway.
7. Caller Information is provided. This will show the latest access request done by "other" gateway. This is auto update if the "current" gateway received request from "other" gateway.

!!!
The Demo testing mainly uses the URL access gateway to do communication and authorization processes between gateways. Morever, "Dummy access" is provided for new gateway which has not yet have any information stored inside the MFAz server
!!!