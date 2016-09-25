#include<iostream>
#include<stdio.h>
#include<string>
#include"Cache.h"

using namespace std;


int main(int argc, char **argv)
{	
	int i,blockSize,l1Size,l1Associativity,l2Size,l2Associativity,replacementPolicy,inclusion;
	string traceFile;
	

	if(argc == 9)
	{

		Cache l1;

		sscanf(argv[1],"%d", &blockSize);
		l1.blockSize = blockSize;
		//Set l2.blockSize
	
		sscanf(argv[2],"%d", &l1Size);
		l1.size = l1Size;

		sscanf(argv[3],"%d", &l1Associativity);
		l1.associativity = l1Associativity;

		sscanf(argv[4],"%d", &l2Size);
		//Set l2.size

		sscanf(argv[5],"%d", &l2Associativity);
		//Set l2.associativity

		sscanf(argv[6],"%d", &replacementPolicy);
		l1.replacementPolicy = replacementPolicy;
		//Set l2.replacementPolicy

		sscanf(argv[7],"%d", &inclusion);
		l1.inclusion = inclusion;
		//Set l2.inclusion


		l1.printCache();
	}
	else
	{
		//Define error method
		Cache::printErrorMessage("Improper arguments.");
	}


	return 0;
}
