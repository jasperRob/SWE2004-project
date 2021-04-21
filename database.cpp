#include <iostream>
#include <vector>
#include <map>
using namespace std;

/**
 * Create a user map
 */
map<string, string> createUser(string name, string dateOfBirth, 
							string address, string visitedLocation, 
							string dateOfEntry, string lastOverseasTravel, 
							string covidTest, string status)
{
	map<string, string> user;
	
	user["name"] = name;
	user["dateOfBirth"] = dateOfBirth;
	user["address"] = address;
	user["visitedLocation"] = visitedLocation;
	user["dateOfEntry"] = dateOfEntry;
	user["lastOverseasTravel"] = lastOverseasTravel;
	user["covidTest"] = covidTest;
	user["status"] = status;

	return user;
}

/**
 * Create a symptom map
 */
map<string, string> createSymptom(string lowRisk, string mediumRisk, string highRisk)
{
	map<string, string> symptom;
	
	symptom["lowRisk"] = lowRisk;
	symptom["mediumRisk"] = mediumRisk;
	symptom["highRisk"] = highRisk;

	return symptom;
}


/**
 * Insert a row and generate a ID for them
 */
void insertRow(map<string, string> row, map<int, map<string, string> > &db)
{
	// Find next highest rowId
	int rowId = 0;
	map<int, map<string, string> >::iterator it;
	for (it = db.begin(); it != db.end(); it++) {
		if (it->first > rowId) {
			rowId = it->first;
		}
	}
	rowId += 1;
	// Insert row into db
	db.insert(pair<int, map<string, string> >(rowId, row));
}

/**
 * Delete a row with a given ID
 */
void deleteRow(int rowId, map<int, map<string, string> > &db)
{
	db.erase(rowId);
}

/**
 * List all rows in a DB and the corresponding ID
 */
void listRows(map<int, map<string, string> > &db)
{
	map<int, map<string, string> >::iterator it;
	for (it = db.begin(); it != db.end(); it++) {
		int rowId = it->first;
		map<string, string> row = it->second;

		cout << " ------------------------------- " << endl;
		cout << "|  " << rowId << "  |  ";
		map<string, string>::iterator rowIter;
		for(rowIter = it->second.begin(); rowIter != it->second.end(); rowIter++) {
			if (rowIter->second.empty()) {
				cout << "NULL";
			} else {
				cout << rowIter->second;
			}
			cout << "  |  ";
		}
		cout << endl;
	}
	cout << "-------------------------------" << endl;
}

int main() 
{
	map<int, map<string, string> > users;
	map<int, map<string, string> > symptoms;
	
	insertRow(
		createUser(
			"John Smith",
			"13/02/1994",
			"13 Some Rd, Suburbia",
			"supermarket",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		users
	);

	insertRow(
		createSymptom(
			"Fever",
			"",
			""
		),
		symptoms
	);

	listRows(users);
	listRows(symptoms);

	return 0;
}
