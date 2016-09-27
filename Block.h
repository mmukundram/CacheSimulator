#include<string>

using namespace std;

class Block
{
public:
	Block()
	{
		valid = false;
		dirty = false;
		next = NULL;
	}
	Block *next;
	bool valid;
	string tag;
	bool dirty;
};


