#include "STMap.h"

void STMap::add(const std::string& word) {
	int n = this->freqs.get(word);
	if ( n ) {
		this->freqs.insert(word, n + 1);
	}
	else {
		this->freqs.insert(word, 1);
	}
}

void STMap::reportAll(std::ostream& output) {
	this->freqs.report(output);
}
