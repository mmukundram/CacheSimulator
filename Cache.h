#include"Block.h"
#include<iostream>
#include<string>
#include<math.h>
#include<map>
#include<vector>
#include<utility>
#define INPUT_SIZE 64

using namespace std;

class Cache
{
public:
	vector<string> setNames;
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

	void displayContent()
	{
		Block *temp = NULL;
		int i;
		for(i=0;i<setNames.size();++i)
		{
			temp = sets[setNames[i]]->next;
			cout<<setNames[i]<<" ";
			while(temp)
			{
				cout<<temp->tag<<" ";
				temp = temp->next;
			}
			cout<<"\n";
		}
	}
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
		<<"\nWrites = "<<writes
		<<"\nMiss rate = "<<(float)(readMisses+writeMisses)/(reads+writes)<<"\n";
	}
	static void printErrorMessage(string message)
	{
		cout<<"Error :"<<message<<"\n";
	}
	static void printMessage(string message)
	{
		cout<<"Message :"<<message<<"\n";
	}
	bool remove(string input)
	{
		char offsetArray[20], indexArray[20], tagArray[100];
		input.copy(offsetArray,offsetWidth,input.length()-offsetWidth);
		offsetArray[offsetWidth] = '\0';
		input.copy(indexArray,indexWidth,input.length()-offsetWidth-indexWidth);
		indexArray[indexWidth] = '\0';
		input.copy(tagArray,input.length()-offsetWidth-indexWidth,0);
		tagArray[input.length()-offsetWidth-indexWidth] = '\0';
		//cout<<"\nOffset = "<<offset<<endl;
		//cout<<"\nIndex = "<<index<<endl;
		//cout<<"\nTag = "<<tag<<endl;
		//cout<<accessMethod<<" "<<inputBuffer<<endl;
		string tag(tagArray);
		string index(indexArray);
		
		Block *temp = NULL;
		if(sets[index] == NULL)
		{
			return false;
		}
		else
		{
			temp = sets[index];
			Block *temp1 = NULL;
			for(temp1 = temp; temp1->next!=NULL; temp1=temp1->next)
			{
				if(temp1->next->tag == tag)
				{
					Block *temp2 = NULL;
					temp2 = temp1->next;
					temp1->next = temp2->next;
					delete temp2;
					return true;
				}
			}
		}
		return false;
	}
	pair<bool,string> write(string input)		
	{
		bool returnValue;
		string returnString = "\0";
		++writes;
		//cout<<"Write called with tag "<<tag<<" and index "<<index<<endl;
		char offsetArray[20], indexArray[20], tagArray[100];
		input.copy(offsetArray,offsetWidth,input.length()-offsetWidth);
		offsetArray[offsetWidth] = '\0';
		input.copy(indexArray,indexWidth,input.length()-offsetWidth-indexWidth);
		indexArray[indexWidth] = '\0';
		input.copy(tagArray,input.length()-offsetWidth-indexWidth,0);
		tagArray[input.length()-offsetWidth-indexWidth] = '\0';
		//cout<<"\nOffset = "<<offset<<endl;
		//cout<<"\nIndex = "<<index<<endl;
		//cout<<"\nTag = "<<tag<<endl;
		//cout<<accessMethod<<" "<<inputBuffer<<endl;
		string tag(tagArray);
		string index(indexArray);
		string offset(offsetArray);	

		Block *temp = NULL;
		if(sets[index] == NULL)
		{
			setNames.push_back(index);
			++writeMisses;
			returnValue = false;
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
					returnValue = true;
					if(replacementPolicy == 0)
					{
						Block *temp2 = temp1->next;
						temp1->next = temp2->next;
						temp2->next = temp->next;
						temp->next = temp2;
					}
					break;
				}
			}
			if(!temp1->next && !returnValue)
			{
				++writeMisses;
				returnValue = false;
				temp1 = new Block();
				temp1->next = NULL;
				temp1->tag = tag;
				temp1->next = temp->next;
				temp->next = temp1;
			}
			if(count == associativity)
			{
				for(temp1 = temp->next; temp1->next->next ; temp1 = temp1->next);
				//cout<<"Tag = "<<temp1->next->tag<<" Index = "<<index<<" Offet = "<<offset<<endl;
				returnString = temp1->next->tag;
				returnString += index;
				returnString += offset;
				delete temp1->next;
				temp1->next = NULL;
			}
		}
		return make_pair(returnValue,returnString);
	}
	pair<bool,string> read(string input)
	{
		bool returnValue;
		string returnString = "\0";
		//cout<<"Read called with tag "<<tag<<" and index "<<index<<endl;
		++reads;
		char offsetArray[20], indexArray[20], tagArray[100];
		input.copy(offsetArray,offsetWidth,input.length()-offsetWidth);
		offsetArray[offsetWidth] = '\0';
		input.copy(indexArray,indexWidth,input.length()-offsetWidth-indexWidth);
		indexArray[indexWidth] = '\0';
		input.copy(tagArray,input.length()-offsetWidth-indexWidth,0);
		tagArray[input.length()-offsetWidth-indexWidth] = '\0';
		//cout<<"\nOffset = "<<offset<<endl;
		//cout<<"\nIndex = "<<index<<endl;
		//cout<<"\nTag = "<<tag<<endl;
		//cout<<accessMethod<<" "<<inputBuffer<<endl;
		string tag(tagArray);
		string index(indexArray);
		string offset(offsetArray);

		Block *temp = NULL;
		temp = sets[index];

		if(!temp)
		{
			setNames.push_back(index);
			++readMisses;
			returnValue = false;
			sets[index] = new Block();
			temp = sets[index];
			temp->next = new Block();
			temp->next->tag = tag;
			returnValue = false;
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
					++readHits;
					returnValue = true;
					if(replacementPolicy == 0)
					{
						Block *temp2 = temp1->next;
						temp1->next = temp2->next;
						temp2->next = temp->next;
						temp->next = temp2;
					}
					break;
				}
			}
			if(!temp1->next && !returnValue)
			{
				++readMisses;
				returnValue = false;
				temp1 = new Block();
				temp1->next = NULL;
				temp1->tag = tag;
				temp1->next = temp->next;
				temp->next = temp1;
			}
			if(count == associativity)
			{
				for(temp1 = temp->next; temp1->next->next ; temp1 = temp1->next);
				//cout<<"Tag = "<<temp1->next->tag<<" Index = "<<index<<" Offet = "<<offset<<endl;
				returnString = temp1->next->tag;
				returnString += index;
				returnString += offset;
				delete temp1->next;
				temp1->next = NULL;
			}
		}
		return make_pair(returnValue,returnString);
	}
};


