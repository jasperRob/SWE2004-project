#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <numeric>
using namespace std;

/*
 * returns value or NULL if empty
 */
string orNull(string value)
{
	if (value.empty()) {
		return "NULL";
	}
	return value;
}

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
void insertRow(int rowId, map<string, string> row, map<int, map<string, string> > &db) 
{
	db.insert(pair<int, map<string, string> >(rowId, row));
}

/**
 * Get a row with a given ID
 */
map<string, string> getRow(int rowId, map<int, map<string, string> > &db)
{
	return db[rowId];
}

/**
 * Delete a row with a given ID
 */
void deleteRow(int rowId, map<int, map<string, string> > &db)
{
	db.erase(rowId);
}

/**
 * List all rows of a db
 * This will format everything
 * Got a bit carried away with this one but oh well.
 */
void listFormattedRows(string columns[], int numColumns, map<int, map<string, string> > &db)
{
	// Define iterators and width vector
	map<int, map<string, string> >::iterator it;
	map<string, string>::iterator it2;
	vector<int> columnWidths(numColumns, 0);
	int maxIdWidth = 0;
	// Calculate the column widths
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = it->second;
		int c = 0;
		for (it2 = row.begin(); it2 != row.end(); it2++) {
			columnWidths[c] = max( max( int(columnWidths[c]), int(it->second[columns[c]].length())), int(columns[c].length()));
			c++;
		}
		// Find Max id width while we are at it
		maxIdWidth = max(maxIdWidth, max(2, int(to_string(it->first).length())));
	}
	// Calulcate the buffer width
	int bufferWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0) + (numColumns * 2) + (numColumns+1) + 5;
	string horizontalBuffer(bufferWidth, '-');
	// Print the header with column tags
	cout << horizontalBuffer << endl << "| ID" << string(maxIdWidth-2, ' ') << " ";
	for (int i = 0; i < numColumns; i++) {
		cout << "| " << columns[i] << string(columnWidths[i]-columns[i].length(), ' ') << " ";
	}
	cout << "|" << endl << horizontalBuffer << endl;
	// Begin printing each row in the database
	for (it = db.begin(); it != db.end(); it++) {
		int rowId = it->first;
		cout << "| " << rowId << string(maxIdWidth-to_string(rowId).length(), ' ') << " ";
		map<string, string> row = it->second;
		for (int i = 0; i < numColumns; i++) {
			string value = orNull(row[columns[i]]);
			cout << "| " << value << string(columnWidths[i]-value.length(), ' ') << " ";
		}
		cout << "|" << endl;
	}
	cout << horizontalBuffer << endl;
}

int main() 
{
	// Define a map for each database
	map<int, map<string, string> > users;
	map<int, map<string, string> > symptoms;
	
	// This will create a new User and insert into the DB
	insertRow(
		1, // This is the userID
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
		2, // This is the userID
		createUser(
			"Peter Flint",
			"19/01/1984",
			"25 Another Rd, Somewhere",
			"hospital",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		users
	);

	insertRow(
		3, // This is the userID
		createUser(
			"Seargent Pepper",
			"19/01/1984",
			"25 Another Even Longer Rd, Somewhere",
			"hospital",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		users
	);

	// This will create a new Symptom and insert into the DB
	insertRow(
		1,
		createSymptom(
			"Fever",
			"",
			""
		),
		symptoms
	);

	insertRow(
		2,
		createSymptom(
			"",
			"Shitting everywhere, on the floors and on the walls",
			""
		),
		symptoms
	);

	// This will get a specific row based on the row ID
	map<string, string> firstUser = getRow(1, users);
	
	// This will list all entries in the USERS DB
	// You must tell it what columns to print, how many columns to print, and from which database
	cout << " Users Database formatted correctly:" << endl;
	string userColumns[8] = { "name", "dateOfBirth", "address", "visitedLocation", "dateOfEntry", "lastOverseasTravel", "covidTest", "status" };
	listFormattedRows(userColumns, 8, users);
	cout << endl;

	// This will list all entries in the SYMPTOMS DB
	// You must tell it what columns to print, how many columns to print, and from which database
	cout << " Symptom Database formatted correctly:" << endl;
	string symptomColumns[3] = { "lowRisk", "mediumRisk", "highRisk" };
	listFormattedRows(symptomColumns, 3, symptoms);
	cout << endl;

	return 0;
}
