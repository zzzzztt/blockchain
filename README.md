# blockchain
Pour choisir le difficulter de Miner:  
changer **#define DifficultyNum** dans le fichier Block.h

-------------------------------------------------------------
compiner le fichier main.cpp pour miner sans P2P:  
g++ -std=c++14 main.cpp -o main  

-------------------------------------------------------------

miner avec P2P  
g++ -std=c++14 client.cpp -lpthread -o client  
g++ -std=c++14 server.cpp -lpthread -o server  

