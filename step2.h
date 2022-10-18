#ifndef STEP2
#define STEP2

#include <iostream> 
#include <fstream>
#include <string> 
using namespace std;

class step2 {
public:
	string word;
	int freq;

	//Operator Overloads
	bool operator == (step2 const& obj) {
		return this->word == obj.word;
	}
	bool operator != (step2 const& obj) {
		return !(this->word == obj.word);
	}
	bool operator < (step2 const& obj) {
		string first = this->word;
		string second = obj.word;
		if (first[0] == second[0]) {
			int count;
			if (first.length() < second.length()) {
				count = second.length();
			}
			else {
				count = first.length();
			}
			for (int x = 1; x < count; x++) {
				if (first[x] != second[x]) {
					return first[x] < second[x];
				}
			}
			return true;
		}
		else {
			return first[0] < second[0];
		}

	}
	bool operator > (step2 const& obj) {
		string first = this->word;
		string second = obj.word;
		if (first[0] == second[0]) {
			int count;
			if (first.length() < second.length()) {
				count = second.length();
			}
			else {
				count = first.length();
			}
			for (int x = 1; x < count; x++) {
				if (first[x] != second[x]) {
					return first[x] > second[x];
				}
			}
			return true;
		}
		else {
			return first[0] > second[0];
		}
	}
	void operator++(int) {
		freq += 1;
	}
	friend ostream& operator << (ostream& os, const step2& s) {
		os << s.word << " = " << s.freq;
		return os;
	}
};

#endif