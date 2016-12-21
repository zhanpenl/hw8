#include "SplayTree.h"
#include <iostream>     // std::cout
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand

using namespace std;

int main(int argc, char const *argv[])
{
	SplayTree<int, int> st;
	int count = 100;
	std::srand ( unsigned ( std::time(0) ) );
  	std::vector<int> myvector;

	for (int i=1; i<count; ++i) myvector.push_back(i);
	// using built-in random generator:
	std::random_shuffle ( myvector.begin(), myvector.end() );

	cout << "inserting nodes..." << endl;
	for (int i = 0; i < count; ++i)
	{
		st.insert(myvector[i],0);
		st.print();
		cout << endl;
	}

	std::random_shuffle ( myvector.begin(), myvector.end() );

	cout << endl << "getting nodes..." << endl;
	for (int i = 0; i < count; i++) {
		st.get(myvector[i]);
		st.print();
	}

	std::random_shuffle ( myvector.begin(), myvector.end() );

	cout << endl << "removing nodes..." << endl;

	for (int i = 0; i < count; ++i)
	{
		st.remove(myvector[i]);
		st.print();
		cout << endl;
	}

	return 0;
}