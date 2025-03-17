# usage
## build
This is compile using python:
### windows
- create a new virtualenvironment (python3 -m venv myvenv)
- access the venv (myvenv/Scripts/Activate)
- install all the dependencies (pip install -r requirements.txt)
- run the flask application (python gateway.py)

### linux
- create a new virtualenvironment (python3 -m venv myvenv)
- access the venv (source myvenv/bin/Activate)
- install all the dependencies (pip install -r requirements.txt)
- run the flask application (python gateway.py)


# values: 
url : RPC server url that is being used

contract_address : contract address that is hosting the Smart Contract

contract_abi : Smart Contract abi

private_key : EOA private key used to deploy Smart Contract

# functions:
## add_bloom_filter
invoke add_bloom_filter method from smart contract to create new transaction with the newest bloom_filter value

## get_bloom_filter
return the latest bloom_filter from contract event


# files and folders
[gateway.py] - source code for FLASK server

[VP.json] - contract abi

[requirements.txt] - required library to be installed
