// DETERMINISTIC FINITE AUTOMATA TEMPLATES AND RELATED METHODS IN C++

/* 
   	NAME : PRATYUSH MISRA, SWATI KUMARI
   	INSTITUTION : JIIT, NOIDA - 62
   	Implemented DFA library which can store DFA and perform
   	various operations on DFA including membership check, equality, finiteness, emptiness.
*/

#ifndef _DFA_HPP
#define _DFA_HPP

#include <iostream>
#include <map> 
#include <vector>
#include <cassert>
#include <iomanip>
#include <set>
#include <numeric>

using namespace std;

#define MT map<string, int>
#define VT vector<vector<int>>
#define WIDTH 15
#define endl "\n"

// #define NDEBUG
/* 
	To assert in case of errors in errors in DFA
*/

#ifndef NDEBUG
#define __DFA_ASSERT(condition, statement) if (!(condition)) { cout << statement << endl; assert(condition); } 
// else 
// #define __DFA_ASSERT(condition, statement) ((void)0)
#endif


// SLOW DSU (N*LOG(N))

const int V = 100100;
vector<int> par(V);          // USE iota(all(par), 0LL) FIRST %%%%%%%%%%%%%%% NOTE %%%%%%%%%%%%%%%%%%

int comp = V;            // number of components initially = V
int Find(int i) {
    if(par[i] == i) return i;
    return par[i] = Find(par[i]);
}
 
bool unionSet(int i, int j) {
    int set_i = Find(i);
    int set_j = Find(j);
    if(set_i != set_j) {
        par[set_i] = set_j;
        comp--;
        return true;
    }
    else return false;                // cycle present so  ====>  CANT UNION SET
}

// SLOW DSU ENDS


class DFA {
public:

	int numOfStates, numOfFinalStates, numOfAlphabets;
	int INITIAL_STATE = 0;
	string initial_state;
	vector<string> STATES;
	vector<char> ALPHABETS;
	set<string> FINAL_STATES, DEAD, UNREACHABLE;
	vector<vector<string>> TRANSITIONS; 

	DFA():numOfStates(0), numOfFinalStates(0), numOfAlphabets(0){}

	DFA(int numOfStates, int numOfFinalStates, int numOfAlphabets) {
		this -> numOfStates = numOfStates;
		this -> numOfAlphabets = numOfAlphabets;
		this -> numOfFinalStates = numOfFinalStates;

		TRANSITIONS.assign(numOfStates, vector<string>(numOfAlphabets, ""));
	}


	void init() {

		for(int i = 0; i < numOfStates; i++) {
			string s;
			cin >> s;
		 	STATES.push_back(s);
		 	if(i >= 1)	UNREACHABLE.insert(s);		// since i = 0 is initial state and always reachable
		}

		for(int i = 0; i < numOfFinalStates; i++) {
			string s;
			cin >> s;

			FINAL_STATES.insert(s);
		}

		for(int i = 0; i < numOfAlphabets; i++) {
			char s;
			cin >> s;
			ALPHABETS.push_back(s);
		}

		initial_state = STATES[0]; 

		for(int i = 0; i < numOfStates; i++) {
			// cout << 'a';
			bool isDead = true;
			for(int j = 0; j < numOfAlphabets; j++) {
				cin >> TRANSITIONS[i][j];	// state on input -> result state(rs)	
				if(STATES[i] != TRANSITIONS[i][j])	UNREACHABLE.erase(TRANSITIONS[i][j]);
				isDead &= TRANSITIONS[i][j] == STATES[i];
			}

			if(isDead && FINAL_STATES.find(STATES[i]) == FINAL_STATES.end()) 
				DEAD.insert(STATES[i]);

		}

	}	


	void display() {

		cout << "Input Transition Table:" << endl;
	    cout << setw(6) << "State:";
	    
	    for(auto& alf : ALPHABETS)
	    	cout << setw(10) << alf;

	    for (int i = 0; i < numOfStates; i++) {

	    	if(i == 0 && FINAL_STATES.find(STATES[0]) == FINAL_STATES.end())	
	    		cout << endl << setw(4) << "->" << STATES[i];
	    	else if(i == 0 && FINAL_STATES.find(STATES[0]) != FINAL_STATES.end())	
	    		cout << endl << setw(4) << "->*" << STATES[i];
	    	else if(FINAL_STATES.find(STATES[i]) != FINAL_STATES.end())	
	    		cout << endl << setw(4) << '*' << STATES[i];
	    	else 
	    		cout << endl << setw(6) << STATES[i];

	        for (int j = 0; j < numOfAlphabets; j++)
	            cout << setw(10) << TRANSITIONS[i][j];

	    }

	    cout << endl;

	}

	// ================= methods ==================

	// membership test
	bool has_a_member(string INPUT) {
		
		int curr_state = 0;
		for(auto& ch : INPUT) {

			int alf_idx = -1;
			for(int j = 0; j < numOfAlphabets; j++) {
				if(ALPHABETS[j] == ch) {
					alf_idx = j;
					break;
				}
			}

			__DFA_ASSERT(alf_idx != -1, "INPUT CHARACTER NOT IN ALPHABET SET");

			string new_state = TRANSITIONS[curr_state][alf_idx];

			for(int i = 0; i < numOfStates; i++) {
				if(STATES[i] == new_state) {
					curr_state = i;
					break;
				}
			}

			// checking is its a DEAD STATE
			if(DEAD.find(STATES[curr_state]) != DEAD.end()) {
				return false;
			}

		}	

		return FINAL_STATES.find(STATES[curr_state]) != FINAL_STATES.end(); 

	}


	// emptiness check
	bool is_empty() {

		// ignoring all the dead and unreachable state, just check do we a atleast one final state now
		// since dead state cant be final state so just check for unreachable state
		// if we have atleast one final state that is not unreachable...then IS NOT EMPTY

		for(auto& fs : FINAL_STATES)
			if(UNREACHABLE.find(fs) == UNREACHABLE.end()) {	
				return false;
			}

		return true;

	}


	// finiteness check
	bool is_finite() {

		if(is_empty())	return true;		// empty -> cardinality 0 -> finite

		iota(par.begin(), par.end(), 0LL);

		for(int i = 0; i < numOfStates; i++) {

			string st = STATES[i];
			
			if(UNREACHABLE.find(st) != UNREACHABLE.end())	continue;
			if(DEAD.find(st) != DEAD.end())	continue;

			for(int j = 0; j < numOfAlphabets; j++) {

				string nbr = TRANSITIONS[i][j];

				if(UNREACHABLE.find(nbr) != UNREACHABLE.end())	continue;
				if(DEAD.find(nbr) != DEAD.end())	continue;

				bool cycle_present = (unionSet(i, j) == false);		// false i.e. cant union => cycle present 

				if(cycle_present) 
					return false;

			}	

		}

		return true;

	}


	// DFA's equality check
	bool is_equivalent_to(DFA& D) {

		for(int i1 = 0; i1 < numOfStates; i1++)
			for(int i2 = 0; i2 < D.numOfStates; i2++) {
			
			
				string s1 = STATES[i1], s2 = D.STATES[i2];

				if((FINAL_STATES.find(s1) == FINAL_STATES.end()) ^ (D.FINAL_STATES.find(s2) == D.FINAL_STATES.end())) continue;

				for(int j = 0; j < numOfAlphabets; j++) {

					string nbr1 = TRANSITIONS[i1][j];
					string nbr2 = D.TRANSITIONS[i2][j];

					if((FINAL_STATES.find(nbr1) == FINAL_STATES.end()) ^ (D.FINAL_STATES.find(nbr2) == D.FINAL_STATES.end())) 
						return false;

				}
				
			}		

		return true;

	}

	// operator overload for DFA equivalence
	bool operator == (DFA &D) {
        return is_equivalent_to(D);
    }

    // operator overload for string acceptance
    bool operator [](string INPUT) {
    	return has_a_member(INPUT);
    }

	// returns a set of strings of the DEAD STATES in the DFA
	set<string> dead(bool printSet = false) {

		if(printSet) {
			for(auto& val : DEAD)
				cout << val << ' ';
			cout << endl;
		}

		return DEAD; 

	}

	// returns a set of strings of the UNREACHABLE STATES in the DFA
	set<string> unreachable(bool printSet = false) {

		if(printSet) {
			for(auto& val : UNREACHABLE)
				cout << val << ' ';
			cout << endl;
		}

		return UNREACHABLE; 
	}

};

ostream& operator << (ostream &opt, DFA &D) {
	D.display();
    return opt;
}


#endif