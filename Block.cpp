#include "Block.h"
#include "sha256.h"
#include <time.h>
#include <sstream>

//constructeur
Block::Block(uint32_t nIndexIn, const string &sDataIn) : _nIndex(nIndexIn), _sData(sDataIn) {
    _nNonce = -1;
    _tTime = time(nullptr);
}

string Block::GetHash() {
    return _sHash;
}

string Block::MineBlock(uint32_t nDifficulty) {
    char cstr[DifficultyNum + 1];
    for (uint32_t i = 0; i < DifficultyNum; ++i) {
        cstr[i] = '0';
    }
    cstr[DifficultyNum] = '\0';
    string str(cstr);
    do {
        _nNonce++;
        _sHash = _CalculateHash();
    } while (_sHash.substr(0, nDifficulty) != str);
    cout << "Block mined: " << _sHash << endl;
    return _sHash;
}


inline string Block::_CalculateHash() const {
    stringstream ss;
    ss << _nIndex << _tTime << _sData << _nNonce << sPrevHash;
    return sha256(ss.str());
}


