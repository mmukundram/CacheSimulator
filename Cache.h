#include"Block.h"
#include<iostream>
#include<string>
#include<math.h>
#define INPUT_SIZE 64

using namespace std;

class Cache
{
public:
	Cache()
	{
		hits = misses = reads = writes = 0;
	}
	void initializeCache()
	{
		numberOfBlocks = size/blockSize;
		blocks = new Block[numberOfBlocks];	
		offsetWidth = log(blockSize)/log(2);
		int sets = size/(associativity*blockSize);
		indexWidth = log(sets)/log(2);
		tagWidth = INPUT_SIZE - offsetWidth - indexWidth;
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

	int offsetWidth;
	int indexWidth;
	int tagWidth; 

	void printCacheDetails()
	{
		cout<<"CACHE DETAILS"
		<<"\nCache size = "<<size
		<<"\nBlock size = "<<blockSize
		<<"\nAssociativity = "<<associativity
		<<"\nReplacement policy = "<<replacementPolicy
		<<"\nOffset width = "<<offsetWidth
		<<"\nIndex width = "<<indexWidth
		<<"\nTag width = "<<tagWidth<<"\n";
	}

	static void printErrorMessage(string message)
	{
		cout<<"Error :"<<message<<"\n";
	}

	static void printMessage(string message)
	{
		cout<<"Message :"<<message<<"\n";
	}
};


