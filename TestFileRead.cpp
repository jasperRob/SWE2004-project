// SWE20004 Technical Software Development //
// COVID Project //
// Jasper Robison    #102989198 //
// Joel Murphy       #103073746 //
// Samuel Nothnagel  #100601319 //

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

/**
 * This function will update the value of a patient column
 * @Param id - the id of the user to update
 * @Param index - the index of the value to update
 * @Param value - the value to replace it with
 */
void updatePatientWithID(int id, int index, string value)
{
	ifstream inFile("patients.txt");
	string fileContents;
	// Open the file
	if (inFile.is_open()) {
		string line;
		// Read all lines of the file
		while (getline(inFile, line)) {
			if (!line.empty()) {
				// Split items by comma and create a map for them
				stringstream ss(line);
				string idStr;
				getline(ss, idStr, ',');
				// Check if this is the correct user
				if (stoi(idStr) == id) {
					fileContents = fileContents + idStr;
					for (int i = 0; i < 8; i++) {
						// Accoutn for unescaped commas
						string item;
						getline(ss, item, ',');
						while (item.back() == '\\') {
							string append;
							getline(ss, append, ',');
							item = item.substr(0, item.length()-1);
							item = item + "," + append;
						}
						// Change the value
						if (i == index) {
							stringstream valstream(value);
							string valItem;
							getline(valstream, valItem, ',');
							while (valstream.rdbuf()->in_avail()) {
								string append;
								getline(ss, append, ',');
								valItem = valItem + "\\," + append;
							}
							fileContents = fileContents + "," + valItem;
						} else {
							fileContents = fileContents + "," + item;
						}
					}
					fileContents = fileContents + "\n";
				} else {
					fileContents = fileContents + line + "\n";
				}
			}
		}
		inFile.close();
	} else {
		cout << "Could not open file patients.txt" << endl;
	}
	ofstream outFile("patients.txt", ios::trunc);
	if (outFile.is_open()) {
		outFile << fileContents;
		outFile.close();
	} else {
		cout << "Could not open file patients.txt" << endl;
	}
}

int main() {

	string input, name;
	int id;

	// Ask for the id and name to update
	cout << "Enter a user ID: ";
	getline(cin, input);
	id = stoi(input);
	cout << "Enter a new name for this user: ";
	getline(cin, name);
	cout << endl;

	// call this function to set the name of the patient in patients.txt
	// We pass 0 because the name is item 0 after the id
	updatePatientWithID(id, 0, name);

	return 0;
}
