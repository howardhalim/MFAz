# Hardhat Project
Make sure device has node.js > v.18.x.x
Step to Compile:
- npm install (installed required package)
- npm install ganache --global (install ganache for local testing)
- run "ganache -d" (to start ganache)
- npx hardhat run scripts/scripts.js (deploy contract to ganache)

# to note:
- [hardhat.config.js](/VP/hardhat.config.js) update this accordingly based on the account private key and network details
- update [contract deployment script](/VP/scripts/scripts.js) accordingly also (account choosing default account[0])


# Smart Contract (Verification Point)
[contract](/VP/contracts/VerificationPoint.sol)
[contract abi](/VP/artifacts/contracts/VerificationPoint.json)
[contract deployment](/VP/scripts/scripts.js)

