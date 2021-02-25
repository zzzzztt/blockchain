#pragma once
 
 
#include <cstdint>
#include <iostream>


using namespace std;

#define DifficultyNum    5    

class Block {
public:
        //enregistrer le hachage du dernier bloc
    string sPrevHash;            
        //constructeur
    Block(uint32_t nIndexIn, const string &sDataIn);    
        //obtenier le hachage
    string GetHash();            
        //miner et renvoyer sa hachage
    string MineBlock(uint32_t nDifficulty);    
private:
    uint32_t _nIndex;            
    int64_t _nNonce;            
    string _sData;                
    string _sHash;                
    time_t _tTime;                //temps de creation
    string _CalculateHash() const;    //calculer hachage
};


