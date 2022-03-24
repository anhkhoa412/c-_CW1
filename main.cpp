#include <iostream>
#include <ctime>
#include <vector>
#include <time.h>
#include <sstream>
#include <cstdint>
#include "sha256.h"
#include "sha256.cpp"
#include "Car.h"
#include "Customer.h"
#include "Block.h"
#include "Blockchain.h"
using namespace std ;

//Block 1 with receive the CarData d
Block::Block(int kind, int number, string time, string prevHash, CarData d)
{
    Kind = kind;
    Number = number;
    timestamp = time;
    data1 = d;
    sha256prevHash = prevHash;
    sha256blockHash = calculateHash();
    blockHash = combineHash();
}
//Block 2 with receive the CusData d
Block::Block(int kind, int number, string time, string prevHash, CusData h)
{
    Kind = kind;
    Number = number;
    timestamp = time;
    data2 = h;
    sha256prevHash = prevHash;
    sha256blockHash = calculateHash();
    blockHash = combineHash();
}
//Take the time to mine a block with difficulty 
void Block::MineBlock(int difficulty){
    char cstr[difficulty + 1];
    for (int i = 0; i < difficulty; ++i) {
        cstr[i] = '0';
    }
    cstr[difficulty] = '\0';

    string str(cstr);
    do {
        mineval++;
        sha256blockHash = calculateHash();
    } while (sha256blockHash.substr(0, difficulty) != str);

}

int Block::getMineval(){
    return mineval;
}
// private functions
int Block::getNumber()
{
    return Number;
}
// get kind of block 
int Block::getKind(){
    return Kind;
}
//Get timestamp 
string Block::gettime(){
    time_t now = time(0);
    char*dt = ctime(&now);
    return dt;
}

//Generates hash for current block
size_t Block::combineHash()
{
    // creating string of Car data
    string toHash = data1.Type + data1.Name + data1.Model + to_string(data1.Year) + to_string (data1.Money) + data2.CusName + data2.Identity+ to_string(data2.Age);
   // hashes Car data stringv
    hash<string> DataHash; 
    // combine hashes and get size_t for block hash
    return DataHash(toHash);

}
// Public Functions
size_t Block::getHash()
{
    return (blockHash);
}
// Calculate hash base on sha-256 function
string Block::calculateHash(){
    sha256blockHash = sha256(to_string(blockHash));
    return (sha256blockHash);
}

size_t Block::getPreviousHash()
{
    return previousHash;
}
// Calculate previous hash base on sha-256 function
string Block::calculateprevHash(){
  
     return sha256prevHash;
}

bool Block::isHashValid()
{
    return combineHash() == getHash();
}

// Blockchain Constructor
Blockchain::Blockchain()
{
    Block genesis1 = createGenesisBlock1();
   // Block genesis2 = createGenesisBlock2();
    chain.push_back(genesis1);
     //chain.push_back(genesis2);
    difficulty = 0;
    
}

// Public Chain Getter
vector<Block> Blockchain::getChain() {
    return chain;
}

// Create Genesis Block
Block Blockchain::createGenesisBlock1()
{
    
    // Setup Initial Car Data
    CarData d("Toyota", "Camry", "SE Hybrid Nightshade", 2022, 29.715);
    // Return Genesis Block
    Block genesis(1 ,0,"0","0", d);
    return genesis;
}
/*
Block Blockchain::createGenesisBlock2()
{
    
    // Setup Initial Cus Data
    CusData h("Khoa","371927594",20);
    // Return Genesis Block
    Block genesis(1,"0","123", h);
    return genesis;
}
*/
// We only need pointer here
// to demonstrate manipulation of transaction data
Block *Blockchain::getLatestBlock()
{
    return &chain.back();
}

//addBlock1 with CarData 
void Blockchain::addBlock1(CarData d)
{
    time_t now = time(0);
    char*dt = ctime(&now);
    int Number = (int)chain.size();
    size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    string sha256prevHash = sha256(to_string(previousHash));
    int kind = 1;
    Block newBlock(kind ,Number,dt, sha256prevHash, d);
    newBlock.MineBlock(difficulty);
    chain.push_back(newBlock);
}
//addBlock2 with CusData 
void Blockchain::addBlock2(CusData h){
    time_t now = time(0);
    char*dt = ctime(&now);
    int Number = (int)chain.size();
    size_t previousHash = (int)chain.size() > 0 ? getLatestBlock()->getHash() : 0;
    string sha256prevHash = sha256(to_string(previousHash));
    Block newBlock(2,Number,dt, sha256prevHash, h);
     chain.push_back(newBlock);
}
//Check whether the chain is valid or not 
bool Blockchain::isChainValid()
{
    ::vector<Block>::iterator i;
    
    for (i = chain.begin(); i != chain.end(); ++i)
    {
        Block currentBlock = *i;
        if (!currentBlock.isHashValid())
        {
            return false;
        }
        if (i != chain.begin())
        {
            Block previousBlock = *(i - 1);
            if (currentBlock.getPreviousHash() != previousBlock.getHash())
            {
                return false;
            }
        }
    }
    
    return true;
}
//Print content of block 
void Blockchain::printChain() {
    vector<Block>::iterator it;
    
    for (it = chain.begin(); it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        int check = currentBlock.getKind();
    if ( check == 1){
        printf("\n\n===================================");
        cout <<"\nBlock: " << currentBlock.getNumber() <<"\nHash: " << currentBlock.calculateHash() << "\nPrevious Hash: " << currentBlock.calculateprevHash()<<"\nTimestamp: " << currentBlock.gettime() << "mineVal: " << currentBlock.getMineval();
        printf("\n");
        cout<<"\nBrand: "<< currentBlock.data1.Type.c_str()<< "| Name: "<<  currentBlock.data1.Name.c_str() << "| Model: " << currentBlock.data1.Model.c_str()<<"| Year:"<< currentBlock.data1.Year << "| Money: $"<< currentBlock.data1.Money;
        cout<<"\nIs Block Valid?: " << currentBlock.isHashValid();
    
    }
    else if (check == 2) {
        printf("\n\n===================================");
        cout <<"\nBlock: " << currentBlock.getNumber() <<"\nHash: " << currentBlock.calculateHash() << "\nPrevious Hash: " << currentBlock.calculateprevHash()<<"\nTimestamp: " << currentBlock.gettime();
        cout<<"\nCustomer's Name: "<< currentBlock.data2.CusName.c_str()<< "| Identity number: "<<  currentBlock.data2.Identity.c_str() << "| Age: " << currentBlock.data2.Age;
        cout<<"\nIs Block Valid?: " << currentBlock.isHashValid();
    }
    else {
        cout <<"no: " << currentBlock.getKind();
    };
};
};
/*
void Blockchain::printChain2() {
    vector<Block>::iterator it;
    
    for (it = chain.begin()  ; it != chain.end(); ++it)
    {
        Block currentBlock = *it;
        printf("\n\n===================================");
        cout <<"\nBlock: " << currentBlock.getNumber() <<"\nHash: " << currentBlock.calculateHash() << "\nPrevious Hash: " << currentBlock.calculateprevHash()<<"\nTimestamp: " << currentBlock.gettime();
        cout<<"\nCustomer's Name: "<< currentBlock.data2.CusName.c_str()<< "| Identity number: "<<  currentBlock.data2.Identity.c_str() << "| Age: " << currentBlock.data2.Age;
        cout<<"\nIs Block Valid?: " << currentBlock.isHashValid();
    }
}
*/
int main()
{
    // Start Blockchain
    Blockchain Car0;
    cout<<"Mining.."<<endl;

    CusData data02("Khoa", "371907594", 21);
     Car0.addBlock2(data02);
       
     CarData data03("Toyota", "Camry", "LE Hybrid",2022, 27.480);
     Car0.addBlock1(data03);
     CusData data04("Yen", "371907594", 20);
     Car0.addBlock2(data04);
   
    CarData data05("Toyota", "Camry", "SE",2022, 26.935);
     Car0.addBlock1(data05);
     CusData data06("Van", "3719075945", 22);
     Car0.addBlock2(data06);
    
     Car0.printChain();
  /*
    //Data for second block
    CarData data2("Toyota", "Camry", "LE Hybrid",2022, 27.480);
     Car.addBlock(data2);

    //Data for third block
    CarData data3("Toyota", "Camry", "SE",2022, 26.935);
     Car.addBlock(data3);

    //Data for forth block
    CarData data4("Toyota", "Camry", "SE Nightsade",2022, 27.365);
     Car.addBlock(data4);
    
    // Show the content
    Car.printChain();
*/
    printf("\nIs chain still valid? %d\n", Car0.isChainValid());
    system("pause");
    return 0;
}
