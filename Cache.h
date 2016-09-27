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
		hits = misses = reads = writes = 0;
	}
	void initializeCache()
	{
		numberOfBlocks = size/blockSize;
		//blocks = new Block[numberOfBlocks];	
		offsetWidth = log(blockSize)/log(2);
		int sets = size/(associativity*blockSize);
		indexWidth = log(sets)/log(2) - 1;
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
	map <string,Block*> sets;			//Has numberOfBlocks/associativity elements

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

	void write(string index, string tag)
	{
		//cout<<"Write called with "<<tag<<endl;
		Block *temp = NULL;
		if(sets[index] == NULL)
		{
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
			for(temp1 = temp->next; temp1!=NULL; temp1=temp1->next, ++count)
			{
				//cout<<"Count = "<<count<<" "<<temp1->tag<<endl;
				if(temp1->tag == tag)
				{
					cout<<"Hit";
					break;
				}
			}
			if(!temp1)
			{
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
	}
	bool read(string index, string tag)
	{
		Block *temp = NULL;
		temp = sets[index];

		if(!temp)
		{
			return false;
		}
		else
		{
			Block *temp1 = NULL;
			for(temp1 = temp->next;temp1;temp1 = temp1->next)
			{
				if(temp1->tag == tag)
				{
					return true;
				}
			}
			return false;
		}
	}
};


