#ifndef STMAP_H
#define STMAP_H

#include "SplayTree.h"
#include <iostream>

class STMap {
public:	
	void add(const std::string& word);
	void reportAll(std::ostream& output);

private:
	SplayTree<std::string, int> freqs;
};

#endif	