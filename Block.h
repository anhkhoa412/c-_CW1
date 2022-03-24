#include <cstdint>
#ifndef Block_h
#define Block_h
#include "Car.h"
#include "Customer.h"
//Block class
class Block
{
private:
    int Kind;
    int Number;
    std::string timestamp;
    size_t blockHash;
    std::string sha256blockHash;
    std::string sha256prevHash;
    size_t previousHash;
    size_t combineHash();
    int mineval;

public:
    // Constuctor
    Block(int Kind, int number, std::string time,  std::string sha256prevHash, CarData d);
    Block(int Kind, int number, std::string time,  std::string sha256prevHash, CusData d);
    
    //Indentify the data in block whether it receive Car data or Cusdata.
    int getKind();
    // Get Block number
    int getNumber();
    //Get time
    std::string gettime();
    // Get Original Hash
    size_t getHash();
    
    // Get Previous Hash
    size_t getPreviousHash();
    
    // Car Data
    CarData data1;
    CusData data2;
    // Validate Hash
    bool isHashValid();

    //The nunmber of hashing time to get the correct hash
    void MineBlock(int difficulty);
    int getMineval();

    //Calculate hash with sha-256 algorithm
    std::string calculateHash();
    std::string calculateprevHash();
};
#endif