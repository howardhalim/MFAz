require("@nomicfoundation/hardhat-toolbox");
require("@nomicfoundation/hardhat-ethers");
/** @type import('hardhat/config').HardhatUserConfig */
module.exports = {
  solidity: "0.8.19",
  defaultNetwork:'ganache',
  networks: {
    hardhat:{
      chainID: 1337,
    },
    ganache: {
      url: "http://localhost:8545/", // Ganache default RPC server URL
      chainId: 1337, // Ganache chain ID

      //dev1
      // accounts: [
      //   "0x3b6a23dbc9a7fa04a76ee76beffdd77a5ba9276f235a51d4c7281ffc373ecb57",
      //   "0x36e9c459821aa98178714f7b7b9de927169a3f3f7d3c07d3b7dd8c3ccbaa70e8",
      //   "0x95de92465774985a7329bf07b825cca7f44e4195661ed153e3205adfc678124f",
      //   "0x0ac0f49e95cad6a18515b43bb2a0c2f4fa2ef2b7dba2d347a47e2f095ed037ae",
      //   "0x44fe94f8337229104dbf766ba02864c45148975ad1689ff640ca1855a3c99cc8",
      //   "0x91174cdff69cc57b7d52a15364a538fd970a9457a65f99fe261faa746b727903",
      //   "0x0ea500995e2a4070d7a525451baffe710d3522c9a9931594401bb7c07b1d2246",
      //   "0x89f9f5219b6d74afd8a45122e96d3ddec2035ce87b9df425a1e2f78d51b3d2c3",
      //   "0x53114e7038c86bde2a3e3dc10c70aa94478d4add13760ac7f190f0e570d4fd91",
      //   "0xbf0ad3d5231b873c7983a74c46af11570129daeb8505e96bdfc37010c74abe76"
      // ],

      //dev2
      // accounts:[
      //   "0xb09eeeabadd99d6751065c46d06c2fdb36839c8803a26297918e6a93a4782cbb",
      //   "0xe6044a5c1d5503ac1da5b6b8f02e42ff3d056072dabdbccc748aee4db0cb94a2",
      //   "0x935a13e2db2fee1a7ac6eef9dcdf3a1600842238ff029215c6edad1c018a779c",
      //   "0x37678732c39b7e2bfe83e1f98f97d36b2f6f69042aa2ab640e6bb84fff0dcf9e",
      //   "0xf5d677df8360a6b8d9f9c12bf901216fc9e2ca7e16a794111a2ce33ae21aef54",
      //   "0x22aed919b9bca0e11281a0b68455e201aef41ffea842a24c3d95927f5301e097",
      //   "0x83ada473e422319ef67813b0fb717aea96a0dcd17e728e9c25dc27757f99c161",
      //   "0xb0232c468d4321cd7158cb1e4885f3f87ab4b2b12433d8e4a44e8f59d5129cf0",
      //   "0x85601d6bd102b31ac7c92c2631dc18e1cf4b35449bb9bf0d16f211fedf07acdf",
      //   "0x48efb727d8881a09d362d752dae40fa5b76495ee9c1723d780dff84272da9ef5",
      // ],
      //test
      accounts:[
        "0x4f3edf983ac636a65a842ce7c78d9aa706d3b113bce9c46f30d7d21715b23b1d",
      ],
      gas: 100000000000000
    }
  },
};
