#include <iostream>
#include "../header_files/DFA.hpp"
using namespace std;

// emptiness test

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
1 0 2
q0
a b
q0 q0



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

int main() {

	int nos, nof, noa;

	cin >> nos >> nof >> noa;

	DFA d0(nos, nof, noa);

	d0.init();

	cout << d0;		// or d0.display()
	
	cout << "DFA IS FINITE: " << d0.is_finite() << endl;

	return 0;

}