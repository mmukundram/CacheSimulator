//g++ ./a.out 64 16 4 32 4 0 0 GCC.t
#include<iostream>
#include<stdio.h>
#include<string>
#include<string.h>
#include"Cache.h"


using namespace std;

string convertHexToBin(string in)
{
	int i,j=0;
	char inputCharArray[100];
	for(i=0;i<in.length();++i)
	{
		switch(in.at(i))
		{
		case '0':
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			break;
		case '1':
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			break;
		case '2':
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';	
			break;
		case '3':
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			break;
		case '4':
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			break;
		case '5':
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			break;
		case '6':
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			break;
		case '7':
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			break;
		case '8':
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			break;
		case '9':
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			break;
		case 'a':
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			break;
		case 'b':
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			break;
		case 'c':
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='0';
			break;
		case 'd':
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			inputCharArray[j++]='1';
			break;
		case 'e':
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='0';
			break;
		case 'f':
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			inputCharArray[j++]='1';
			break;
		default:
			Cache::printErrorMessage("Invalid input.");
		}
	}
	inputCharArray[j] = '\0';
	string input(inputCharArray);
	//cout<<input;
	return input;
}

int main(int argc, char **argv)
{	
	int i,blockSize,l1Size,l1Associativity,l2Size,l2Associativity,replacementPolicy,inclusion;
	FILE *traceFile = NULL;
	

	if(argc == 9)
	{

		Cache l1, l2;

		sscanf(argv[1],"%d", &blockSize);
		l1.blockSize = blockSize;
		l2.blockSize = blockSize;
	
		sscanf(argv[2],"%d", &l1Size);
		l1.size = l1Size;

		sscanf(argv[3],"%d", &l1Associativity);
		l1.associativity = l1Associativity;

		sscanf(argv[4],"%d", &l2Size);
		l2.size = l2Size;

		sscanf(argv[5],"%d", &l2Associativity);
		l2.associativity = l2Associativity;

		sscanf(argv[6],"%d", &replacementPolicy);
		l1.replacementPolicy = replacementPolicy;
		l2.replacementPolicy = replacementPolicy;

		sscanf(argv[7],"%d", &inclusion);
		l1.inclusion = inclusion;
		l2.inclusion = inclusion;

		l1.initializeCache();
		l2.initializeCache();

		traceFile = fopen(argv[8],"r");

		if(!traceFile)
		{
			Cache::printErrorMessage("Trace file not found.");
		}
		else
		{
			//Cache::printMessage("Trace file found.");
		}
		char inputBuffer[100], accessMethod[5];
		
		while(true)
		{
			fscanf(traceFile,"%s",accessMethod);
			if(feof(traceFile))
			{
				break;
			}
			fscanf(traceFile,"%s",inputBuffer);
			string in(inputBuffer);
			//cout<<"Converting "<<in<<" to Bin.\n";
			string input = convertHexToBin(in);
			
			
			if(strcmp(accessMethod,"r") == 0)
			{
				//cout<<"Read "<<tagString<<" from "<<indexString<<"\n";
				//l1.displayContent();
				if(l1.read(input))
				{
					//cout<<"Hit\n";
				}
				else
				{
					//cout<<"Miss\n";
				}
			}
			else if(strcmp(accessMethod,"w") == 0)
			{
				//cout<<"Write "<<tagString<<" into "<<indexString<<"\n";
				//l1.displayContent();
				l1.write(input);			
			}
				

		}
		

		l1.printCacheDetails();
		l1.printCacheStatus();

		


		
	}
	else
	{
		Cache::printErrorMessage("Improper arguments.");
	}


	return 0;
}
