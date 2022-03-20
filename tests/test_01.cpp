#include <iostream>
#include "../header_files/DFA.hpp"
using namespace std;

// memebership test

/* TEST CASES:
1) 
4 1 2
q0 q1 q2 q3
q3
a b
q1 q0
q1 q2
q3 q0
q3 q3



2)
3 1 2
q0 q1 q2
q2
a b
q0 q1
q1 q1
q2 q1



3)
5 1 2
q0 q1 q2 q3 q4
q2
a b
q1 q3
q3 q2
q1 q1
q3 q3
q2 q1


*/


void generateRandomTest(DFA& D) {
    int tc = rand() % 201 + 100;
    vector<char> symbols(D.ALPHABETS.begin(), D.ALPHABETS.end());

    while(tc--) {
        string INPUT = "";
        int INPUT_STRING_LEN = rand() % 50 + 2;
        for(int i = 0; i < INPUT_STRING_LEN; i++)
            INPUT.push_back(symbols[rand() % D.numOfAlphabets]);
        bool isMem = D[INPUT];	// or D.has_a_member(INPUT);
        cout << "\"" << INPUT << "\""<< (isMem ? " is a member of DFA" : " is not a member of DFA") << endl;
    }
}

int main() {

	int nos, nof, noa;

	cin >> nos >> nof >> noa;

	DFA d0(nos, nof, noa);

	d0.init();

	cout << d0;		// or d0.display()
	
	// empty string acceptance test
	bool res = d0[""];
	cout << "\"" << "\" " << (res ? " is a member of DFA" : " is not a member of DFA") << endl;

	generateRandomTest(d0);

	return 0;

}