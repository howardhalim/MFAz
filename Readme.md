# MFAz Project
consists of 3 folders:
[/VP] - hardhat project, used to setup the smart contract and deploy it
[/Gateway] - Python FLASK project to connect with the blockchain
[/Gateway_C++] - main MFAz project


# To Start the Project
1. Install all required compiler (node, python, and g++)
    Version used to build this project:
    node: v18.19.1
    python: 3.10.12
    g++: Ubuntu 11.4.0
2. Determine which blockchain wanted to be used (in this PoC, ganache is used, skip to (3) if uses other blockchain)
    - install ganache through npm (npm install ganache --global)
    - start ganache (ganache -d)
3. Based on the blockchain used, update hardhat.config.js files "network" accordingly (code provided is using ganache)
4. Deploy the contract using scripts.js
5. Access [/Gateway], create a new virtual environment (venv), install the required dependencies from requirments.txt and run [gateway.py]
6. Access [/Gateway_C++], for MFAz code and testing.

More information of [/Gateway] and [/Gateway_C++] can be accessed through each respective [readme.md].


## !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! ##
# To run MFAz Demo (MFAZ-server and gateway-server [Demo Purpose] ):
consists of mainly 2 folders - no need to run other folders!!:
[/gateway-server] - a flask application that act as client-server communication devices. (communication between 2 or more "gateway-server")
[/MFAz-server] - a cppcms server that act as a server that authorize using the MFAz system developed

# To Start the Demo
1. Duplicate any amount of gateway-server wanted to be used for the Demo. (Copy and Paste the Whole Folder and see [/gateway-server] Readme.md file for further references)
2. Start the MFAz-server and all the gateway-server application (Refer to individuals Readme.md folder for starting the application).
3. In this Demo, to bring up all the communication up on the internet for cross device demo, "ngrok" has been used
4. After bringing all servers up, we can do the authorization testing through gateway-gateway communication provided on the front-end.

# Ngrok
- Ngrok installation ("https://download.ngrok.com/")
- Setup your own account and get the auth-token required
- For a free account, 1 account can only hosted 1 ngrok.yml file so update .yml file accordingly to add more tunnel if required

# Other Hosting
- Any hosting of the system can be used to do the demo, as long as the host can be accessed by the testing/demo devices
- Setup the hosting according to the hosting platfrom choices.

