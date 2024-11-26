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
