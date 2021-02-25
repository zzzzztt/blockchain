//g++ -std=c++14 main.cpp -o main
#include "BlockChain.h"
#include "BlockChain.cpp"
#include "Block.h"
#include "Block.cpp"
#include "sha256.h"
#include "sha256.cpp"
#include <string>
//#include "client.cpp"
//#include "server.cpp"

using namespace std;
int main() {
  BlockChain bChain = BlockChain();
  
  int i = 1;
  while(true){
	cout << "Mining block "<< i <<"..." << endl;
	const string sBlock = "Block "+ i;
	bChain.AddBlock(Block(i, sBlock));
	i++;

  }
  return 0;
}


