// SPDX-License-Identifier: UNLICENSED
pragma solidity ^0.8.19;

// Uncomment this line to use console.log
// import "hardhat/console.sol";

contract VerificationPoint{
    // Declare a string variable to hold the bloom filter data
    string public bloom_filter;

    // Event to emit when the bloom filter is updated
    event bloomFilter(string bloomFilter);

    // Method to update the bloom filter and emit the event
    function updateBloomFilter(string memory _bloomFilter) public {
        bloom_filter = _bloomFilter;
        emit bloomFilter(_bloomFilter);
    }
}
