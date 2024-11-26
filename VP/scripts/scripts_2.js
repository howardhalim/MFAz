const hre = require("hardhat");

async function main() {
    const accounts = await hre.ethers.getSigners();
    const contracts = await hre.ethers.getContractFactory('VerificationPoint');
    const signer = accounts[0];
    
    const _contract = await contracts.connect(signer).deploy();
    await _contract.waitForDeployment();
    
    console.log("Contract deployed to:", await _contract.getAddress());
}

main()
    .then(() => process.exit(0))
    .catch(error => {
        console.error(error);
        process.exit(1);
    });
