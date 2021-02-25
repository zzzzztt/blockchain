#include "BlockChain.h"
 
 
BlockChain::BlockChain() {
   _vChain.emplace_back(Block(0, "Genesis Block"));
   _nDifficulty = DifficultyNum;
}
 
string BlockChain::AddBlock(Block bNew) {
    bNew.sPrevHash = _GetLastBlock().GetHash();
    string hash =  bNew.MineBlock(_nDifficulty);
    _vChain.push_back(bNew);
    return hash;
}
 
Block BlockChain::_GetLastBlock() const {
    return _vChain.back();
}


