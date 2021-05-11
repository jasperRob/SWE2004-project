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
#include <string>
using namespace std;

/* 
 * Check if a line exists for key val pair
 */
bool doesExist(int col, string value, string filepath, int totalColumns) {
	ifstream inFile(filepath);
	string fileContents;
	// Open the file
	if (inFile.is_open()) {
		string line;
		// Read all lines of the file
		while (getline(inFile, line)) {
			if (!line.empty()) {
				// Split items by comma and create a map for them
				stringstream ss(line);
				for (int i = 0; i < totalColumns; i++) {
					// Accoutn for escaped commas
					string item;
					getline(ss, item, ',');
					while (item.back() == '\\') {
						string append;
						getline(ss, append, ',');
						item = item.substr(0, item.length()-1);
						item = item + "," + append;
					}
					if (i == col && item == value) {
						return true;
					}
				}
			}
		}
		inFile.close();
	} else {
		cout << "Could not open file " << filepath << endl;
	}
	return false;
}

/*
 * Check if patient exixts with a given id
 */
bool patientDoesExist(int id) {
	return doesExist(0, to_string(id), "patients.txt", 9);
}

/*
 * Check if location exixts with a given name
 */
bool locationDoesExist(string name) {
	return doesExist(0, name, "locations.txt", 1);
}

/**
 * This function will update the value of a row column in a file if mathing value is found
 */
void updateColumn(int idIndex, string idVal, int index, string value, string filepath, int totalNumColumns)
{
	ifstream inFile(filepath);
	string fileContents;
	// Open the file
	if (inFile.is_open()) {
		string line;
		// Read all lines of the file
		while (getline(inFile, line)) {
			if (!line.empty()) {
				// Split items by comma
				string updatedLine;
				stringstream ss(line);
				// Check if this is the correct user
				bool hasId = false;
				for (int i = 0; i < totalNumColumns; i++) {
					// Accoutn for unescaped commas
					string item;
					getline(ss, item, ',');
					while (item.back() == '\\') {
						string append;
						getline(ss, append, ',');
						item = item.substr(0, item.length() - 1);
						item = item + "," + append;
					}
					if (i == idIndex && item == idVal) {
						hasId = true;
					}
					// Don't add delim for first item
					if (i > 0) {
						updatedLine = updatedLine + ",";
					}
					// Change the value if at index
					if (i == index) {
						stringstream valstream(value);
						string valItem;
						getline(valstream, valItem, ',');
						while (valstream.rdbuf()->in_avail()) {
							string append;
							getline(ss, append, ',');
							valItem = valItem + "\\," + append;
						}
						updatedLine = updatedLine + valItem;
					} else {
						updatedLine = updatedLine + item;
					}
				}
				if (hasId) {
					fileContents = fileContents + updatedLine + "\n";
				} else {
					fileContents = fileContents + line + "\n";
				}
			}
		}
		inFile.close();
	}
	else {
		cout << "Could not open file " << filepath << endl;
	}
	ofstream outFile(filepath, ios::trunc);
	if (outFile.is_open()) {
		outFile << fileContents;
		outFile.close();
	}
	else {
		cout << "Could not open file " << filepath << endl;
	}
}

/*
 * Update a patient detail using the ID
 */
void updatePatientWithID(int id, int index, string value) {
	updateColumn(0, to_string(id), index, value, "patients.txt", 9);
}

int main() {

	string input, name, dob;
	int id;

	// Ask for the id and name to update
	cout << "Enter a user ID: ";
	getline(cin, input);
	id = stoi(input);
	/* cout << "Enter a new name for this user: "; */
	/* getline(cin, name); */
	/* cout << endl; */
	cout << "Enter a new dob for this user: ";
	getline(cin, dob);
	cout << endl;

	if (doesExist(0, to_string(id), "patients.txt", 9)) {
		cout << "YES" << endl;
	} else {
		cout << "NO" << endl;
	}

	// call this function to set the name of the patient in patients.txt
	// We pass 1 because the name is item 1 after the id
	/* updatePatientWithID(id, 1, name); */
	updatePatientWithID(id, 2, dob);

	return 0;
}
