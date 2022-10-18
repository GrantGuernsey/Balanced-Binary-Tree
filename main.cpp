#include <iostream> 
#include <fstream>
#include <string> 
#include "Tree.h"
#include "step2.h"
using namespace std;

char lowerCase(char ch) {
	if (ch > 64 && ch < 91) {
		ch += 32;
	}
	return ch;
}
void words() {
	/* NEW NODE = Tree<int>::Node* y; */
	bool loop = true;
	bool cont = false;
	char ans = ' ';

	while (loop) {
		Tree<step2> x;
		string filename;

		cout << "Enter a file name: ";
		if (cont) cin.ignore();
		getline(cin, filename);
		fstream input(filename, ios::in);

		if (input.fail()) {
			input.close();
			cout << "ERROR, " << filename << " does not exist. Enter a valid filename" << endl << endl;

			cout << "Enter a file name: ";
			getline(cin, filename);
			input.open(filename, ios::in);
		}

		//Set-up file pointer
		char finder;
		input.get(finder);
		while (finder != ':') {
			input.get(finder);
		}

		//Word and tree construction
		char ch;
		string word;
		while (!input.eof()) {

			input.get(ch);

			if ((ch == ' ' || ch == '\n') && word != "") {
				//Make step2 object
				step2 y;
				y.word = word;
				y.freq = 1;

				//Insert object into tree
				x.insert(y);
				word = "";
			}
			else {
				//Build word
				if ((ch > 47 && ch < 58) || (ch > 64 && ch < 91) || (ch > 96 && ch < 123)) {
					word += lowerCase(ch);
				}
			}
		}

		//Display results
		input.close();
		
		cout << "LIST IN ASCENDING ORDER:" << endl;
		x.printInc();

		cout << "LIST IN DESCENDING ORDER:" << endl;
		x.printDec();
		
		//Find
    bool cont = true;
		char c = ' ';
    char repeat = ' ';
		cout << "Would you like to search for a value? Y/n: ";
		cin >> c;
    while (cont == true){
		  if(c == 'y' || c == 'Y'){
			  string word;
			  cout << "What word would you like to search for? ";
			  cin >> word;
			  step2 used;
			  used.word = word;
			  Tree<step2>::Node* found = x.find(used);

			  if (found != nullptr) cout << found->data << endl << endl;
			  else cout << word << " not found" << endl << endl;
			  
      		
      			cout << "Would you like to search for another word? Y/n ";
      			cin >> repeat;
      
			  while (repeat != 'y' && repeat != 'Y' && repeat != 'n' && repeat != 'N') {
				  cout << "ERROR, enter Y or n" << endl << endl;
	
				  cout << "Would you like to search for another word? Y/n: ";
				  cin >> repeat;
			  }
			  if (repeat == 'n' || repeat == 'N') cont = false;
			  }
		else if (c == 'n' || c == 'N') cont = false;
		else {
			cout << "ERROR, enter Y or N" << endl << endl;

			cout << "Would you like to search for a value? Y/n: ";
			cin >> c;
			}
    }
    
		cout << "Would you like to search another file? Y/n: ";
		cin >> ans;

		while (ans != 'y' && ans != 'Y' && ans != 'n' && ans != 'N') {
			cout << "ERROR, enter Y or N" << endl << endl;

			cout << "Would you like to search another file? Y/n: ";
			cin >> ans;
		}

		if (ans == 'n' || ans == 'N') loop = false;
		else cont = true;
		x.~Tree();
	}
}

int main() {
	words();
	return 0;
}