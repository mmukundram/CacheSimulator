#include<iostream>
#include<stdio.h>
#include<string>
#include"Cache.h"


using namespace std;


int main(int argc, char **argv)
{	
	int i,blockSize,l1Size,l1Associativity,l2Size,l2Associativity,replacementPolicy,inclusion;
	FILE *traceFile = NULL;
	

	if(argc == 9)
	{

		Cache l1;

		sscanf(argv[1],"%d", &blockSize);
		l1.blockSize = blockSize;
		//Set l2.blockSize
	
		sscanf(argv[2],"%d", &l1Size);
		l1.size = l1Size * 1024;

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

		l1.initializeCache();

		traceFile = fopen(argv[8],"r");

		if(!traceFile)
		{
			Cache::printErrorMessage("Trace file not found.");
		}
		else
		{
			Cache::printMessage("Trace file found.");
		}
		char inputBuffer[100], accessMethod[5], offset[10], index[10], tag[100];
	
		//while(!feof(traceFile))
		{
			fscanf(traceFile,"%s",accessMethod);
			fscanf(traceFile,"%s",inputBuffer);
			string input(inputBuffer);
			input.copy(offset,l1.offsetWidth,input.length()-l1.offsetWidth);
			cout<<"Offset = "<<offset<<endl;
			cout<<accessMethod<<" "<<inputBuffer<<endl;
		}


		l1.printCacheDetails();

		


		
	}
	else
	{
		//Define error method
		Cache::printErrorMessage("Improper arguments.");
	}


	return 0;
}
