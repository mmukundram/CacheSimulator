class Block
{
public:
	Block()
	{
		valid = false;
		dirty = false;
	}
	bool valid;
	char *tag;
	bool dirty;
};


