#ifndef STMAP
#define STMAP 

class STMAP
{
public:
	STMAP();
	~STMAP();
	
	void add(const std::string& word);
	void reportAll(std::ostream& output);
};

#endif	