#include "SplayTree.h"
#include <ctime>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
	SplayTree<int, int> st;
	int count = 1000;
	/*st.insert(1,0);
	st.print();
	st.insert(2,0);
	st.print();*/

	cout << "inserting nodes..." << endl;
	for (int i = 0; i < count; ++i)
	{
		st.insert(i,0);
		st.print();
		cout << endl;
	}

	cout << endl << "getting nodes..." << endl;
	for (int i = 0; i < count; i++) {
		st.get(i);
		st.print();
	}

	cout << endl << "removing nodes..." << endl;

	for (int i = 0; i < count; ++i)
	{
		st.remove(i);
		st.print();
		cout << endl;
	}

	return 0;
}