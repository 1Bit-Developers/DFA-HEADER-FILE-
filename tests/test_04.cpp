#include <iostream>
#include "../header_files/DFA.hpp"
using namespace std;

// emptiness check

/* TEST CASES:
1) 
2 1 2
q0 q1
q0
a b
q0 q1
q1 q0

3 2 2
q0 q1 q2
q0 q1
a b
q1 q2
q1 q2
q2 q0



2)
2 1 2
q0 q1
q0
a b
q0 q1
q0 q1

3 2 2
q0 q1 q2
q0 q1
a b
q1 q2
q1 q2
q2 q0
*/


int main() {

	int nos, nof, noa;

	cin >> nos >> nof >> noa;

	DFA d0(nos, nof, noa);

	d0.init();

	d0.display();

	
	cin >> nos >> nof >> noa;

	DFA d1(nos, nof, noa);

	d1.init();

	d1.display();

	cout << "EQUIVALENCE CHECK: " << (d0 == d1) << endl;		// do.is_equivalent_to(d1);

	return 0;

}