#include "STMap.h"
#include <iostream>
#include <ctime>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {

	char* filename = argv[2];
	cout << "filename: " << filename << endl;
	ifstream ifs (filename, ifstream::in);
	if ( !ifs ) {
		cerr << "error: open file" << endl;
		return -1;
	}

    clock_t start;
    double duration;

    start = clock();

    /* Your algorithm here */
    STMap stmap;
    string word;
    while ( ifs >> word ) {
    	stmap.add(word);
    	cout << word << " ";
    }
    cout << endl;

    duration = ( clock() - start ) / (double) CLOCKS_PER_SEC;

    std::cout << duration << "s" << endl << "reporting..." << endl;

    stmap.reportAll(cout);
}
