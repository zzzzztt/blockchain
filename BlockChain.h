#pragma once
 
#include <cstdint>
#include <vector>
#include "Block.h"

using namespace std;
 
class BlockChain {
public:
    BlockChain();                    //constructeur de BlockChain
    string AddBlock(Block bNew);        
private:
    uint32_t _nDifficulty;            //difficulte
    vector<Block> _vChain;            //Enregister le BlockChain
    Block _GetLastBlock() const;    //obtenir le dernier bloc
};


