#include <cstdint>
#ifndef Blockchain_h
#define Blockchain_h

#include <vector>
// Blockchain Class
class Blockchain
{
private:
    Block createGenesisBlock1();
    Block createGenesisBlock2();
    std::vector<Block> chain;
    int difficulty;

public:
    // Constuctor
    Blockchain();

    // Public Functions
    std::vector<Block> getChain();
    Block *getLatestBlock();
    bool isChainValid();
    void addBlock1(CarData data1);
    void addBlock2(CusData data2);
    void printChain();
    void printChain2();
};
#endif