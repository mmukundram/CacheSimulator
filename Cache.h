#include"Block.h"
#include<iostream>
#include<string>

using namespace std;

class Cache
{
public:
	Cache()
	{
		hits = misses = reads = writes = 0;
		int i;
		numberOfBlocks = size/blockSize;
		blocks = new Block[numberOfBlocks];
	}
	int hits;
	int misses;
	int reads;
	int writes;
	int size;
	int blockSize;
	int associativity;
	int replacementPolicy;
	int inclusion;
	int numberOfBlocks;
	Block* blocks;    

	void printCache()
	{
		cout<<"CACHE DETAILS"
		<<"\nCache size = "<<size
		<<"\nBlock size = "<<blockSize
		<<"\nAssociativity = "<<associativity
		<<"\nReplacement policy = "<<replacementPolicy<<"\n";
	}

	static void printErrorMessage(string message)
	{
		cout<<"Error :"<<message<<"\n";
	}
};


