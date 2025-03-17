#Imports
from flask import Flask, request, jsonify
import time
from web3 import Web3
import json
from web3.middleware import geth_poa_middleware

app = Flask(__name__)

@app.route('/test', methods=['GET'])
def test():
    return "SUCCESS"

@app.route('/add', methods=['POST'])
def add_bloom_filter():
    data = request.json
    bloomfilter = data.get('bloomfilter')

    print(bloomfilter)
    if geth_poa_middleware in web3.middleware_onion.middlewares:
        web3.middleware_onion.remove(geth_poa_middleware)
    
    web3.middleware_onion.inject(geth_poa_middleware, layer=0)

    transaction = contract.functions.updateBloomFilter(
        bloomfilter
    ).build_transaction({
        'from': account,
        'nonce': web3.eth.get_transaction_count(account)
    })

    # Sign the transaction with the account's private key
    signed_tx = web3.eth.account.sign_transaction(transaction, private_key="0x4f3edf983ac636a65a842ce7c78d9aa706d3b113bce9c46f30d7d21715b23b1d")  # Replace with your private key

    # Send the transaction
    tx_hash = web3.eth.send_raw_transaction(signed_tx.rawTransaction)
    print(f"Transaction sent: {web3.to_hex(tx_hash)}")

    # Wait for the transaction receipt
    receipt = web3.eth.wait_for_transaction_receipt(tx_hash)
    print(f"Transaction receipt: {receipt}")
    # print(len(bloomfilter))
    

    web3.middleware_onion.remove(geth_poa_middleware)
    return "Add Successfully"


@app.route('/get', methods=['GET'])
def get_bloom_filter():
    event_filter = contract.events.bloomFilter.create_filter(fromBlock="latest")
    events = event_filter.get_all_entries()
    if not events:  # Check if events is empty
        return "No Event"
    print(events[0]['args']['bloomFilter'])
    bloomFilter = events[0]['args']['bloomFilter']
    return bloomFilter



if __name__ == '__main__':
    ganache_url = "http://127.0.0.1:8545"
    web3 = Web3(Web3.HTTPProvider(ganache_url))

    with open("VP.json", "r") as f:
        contract_abi = json.load(f)
        contract_abi = contract_abi['abi']

    # contract_address = "0xdE02B5FBA439596A8499462508AB3d9c4b0083d9"
    contract_address = "0xe78A0F7E598Cc8b0Bb87894B0F60dD2a88d6a8Ab"

    contract = web3.eth.contract(address=contract_address, abi=contract_abi)
    account = web3.eth.accounts[0]
    app.run(debug=True)


