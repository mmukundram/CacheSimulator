#include"Block.h"
#include<iostream>
#include<string>
#include<math.h>
#include<map>
#define INPUT_SIZE 64

using namespace std;

class Cache
{
public:
	Cache()
	{
		readHits = writeHits = readMisses = writeMisses = reads = writes = 0;
	}
	void initializeCache()
	{
		numberOfBlocks = size/blockSize;
		//blocks = new Block[numberOfBlocks];	
		offsetWidth = log(blockSize)/log(2);
		numberOfSets = size/(associativity*blockSize);
		indexWidth = log(numberOfSets)/log(2);
		tagWidth = INPUT_SIZE - offsetWidth - indexWidth;
		
	}
	int readHits;
	int readMisses;
	int reads;
	int writeHits;
	int writeMisses;
	int writes;
	int size;
	int blockSize;
	int associativity;
	int replacementPolicy;
	int inclusion;
	int numberOfBlocks;
	int numberOfSets;
	map <string,Block*> sets;			//Has numberOfBlocks/associativity elements

	int offsetWidth;
	int indexWidth;
	int tagWidth; 

	void printCacheDetails()
	{
		cout<<"CACHE DETAILS"
		<<"\nCache size = "<<size
		<<"\nNumber of blocks = "<<numberOfBlocks
		<<"\nBlock size = "<<blockSize
		<<"\nAssociativity = "<<associativity
		<<"\nReplacement policy = "<<replacementPolicy
		<<"\nSets = "<<numberOfSets
		<<"\nOffset width = "<<offsetWidth
		<<"\nIndex width = "<<indexWidth
		<<"\nTag width = "<<tagWidth<<"\n";
	}
	void printCacheStatus()
	{
		cout<<"CACHE STATUS"
		<<"\nRead hits = "<<readHits
		<<"\nRead misses = "<<readMisses
		<<"\nReads = "<<reads
		<<"\nWrite hits = "<<writeHits
		<<"\nWrite misses = "<<writeMisses
		<<"\nWrites = "<<writes<<"\n";
	}
	static void printErrorMessage(string message)
	{
		cout<<"Error :"<<message<<"\n";
	}
	static void printMessage(string message)
	{
		cout<<"Message :"<<message<<"\n";
	}
	void write(string index, string tag)
	{
		++writes;
		//cout<<"Write called with "<<tag<<endl;
		Block *temp = NULL;
		if(sets[index] == NULL)
		{
			++writeMisses;
			sets[index] = new Block();
			temp = sets[index];
			temp->next = new Block();
			temp->next->tag = tag;
		}
		else
		{
			temp = sets[index];
			Block *temp1 = NULL;
			int count = 0;
			//cout<<"\n\n";
			for(temp1 = temp; temp1->next!=NULL; temp1=temp1->next, ++count)
			{
				//cout<<"Count = "<<count<<" "<<temp1->tag<<endl;
				if(temp1->next->tag == tag)
				{
					++writeHits;
					if(replacementPolicy == 1)
					{
						Block *temp2 = temp1->next;
						temp1->next = temp2->next;
						temp2->next = temp->next;
						temp->next = temp2;
					}
					return;
				}
			}
			++writeMisses;
			temp1 = new Block();
			temp1->next = NULL;
			temp1->tag = tag;
			temp1->next = temp->next;
			temp->next = temp1;
			if(count == associativity)
			{
				for(temp1 = temp->next; temp1->next->next ; temp1 = temp1->next);
				delete temp1->next;
				temp1->next = NULL;
			}
		}
	}
	bool read(string index, string tag)
	{
		++reads;
		Block *temp = NULL;
		temp = sets[index];

		if(!temp)
		{
			++readMisses;
			return false;
		}
		else
		{
			Block *temp1 = NULL;
			for(temp1 = temp;temp1->next;temp1 = temp1->next)
			{
				if(temp1->next->tag == tag)
				{
					++readHits;
					if(replacementPolicy == 1)
					{
						Block *temp2 = temp1->next;
						temp1->next = temp2->next;
						temp2->next = temp->next;
						temp->next = temp2;
					}
					return true;
				}
			}
			++readMisses;
			return false;
		}
	}
};


