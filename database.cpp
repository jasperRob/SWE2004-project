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
 * Create a patient map
 */
map<string, string> createPatient(string name, string dateOfBirth, 
							string address, string visitedLocation, 
							string dateOfEntry, string lastOverseasTravel, 
							string covidTest, string status)
{
	map<string, string> patient;
	
	patient["name"] = name;
	patient["dateOfBirth"] = dateOfBirth;
	patient["address"] = address;
	patient["visitedLocation"] = visitedLocation;
	patient["dateOfEntry"] = dateOfEntry;
	patient["lastOverseasTravel"] = lastOverseasTravel;
	patient["covidTest"] = covidTest;
	patient["status"] = status;

	return patient;
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
 * Insert a row
 */
void insertRow(int rowId, map<string, string> row, map<int, map<string, string> > &db) 
{
	db.insert(pair<int, map<string, string> >(rowId, row));
}

/**
 * Update a row using rowId
 */
void updateRow(int rowId, map<string, string> row, map<int, map<string, string> > &db) 
{
	db.erase(rowId);
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
			columnWidths[c] = max( max( int(columnWidths[c]), int(orNull(it->second[columns[c]]).length())), int(columns[c].length()));
			c++;
		}
		// Find Max id width while we are at it
		maxIdWidth = max(maxIdWidth, max(2, int(to_string(it->first).length())));
	}
	// Calulcate the buffer width
	int bufferWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0) + (maxIdWidth) + (numColumns * 2) + (numColumns+1) + 3;
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
	map<int, map<string, string> > patients;
	map<int, map<string, string> > symptoms;
	
	// This will create a new Patient and insert into the DB
	insertRow(
		1, // This is the ID
		createPatient(
			"John Smith",
			"13/02/1994",
			"13 Some Rd, Suburbia",
			"supermarket",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		patients
	);

	insertRow(
		2, // This is the ID
		createPatient(
			"Peter Flint",
			"19/01/1984",
			"25 Another Rd, Somewhere",
			"hospital",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		patients
	);

	insertRow(
		3, // This is the ID
		createPatient(
			"Seargent Pepper",
			"19/01/1984",
			"25 Another Even Longer Rd, Somewhere",
			"hospital",
			"21/4/2021",
			"Yes",
			"Negative",
			"Alive"
		),
		patients
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
	map<string, string> firstPatient = getRow(1, patients);
	
	// This will list all entries in the PATIENTS DB
	// You must tell it what columns to print, how many columns to print, and from which database
	cout << " Patients Database formatted correctly:" << endl;
	string patientColumns[8] = { "name", "dateOfBirth", "address", "visitedLocation", "dateOfEntry", "lastOverseasTravel", "covidTest", "status" };
	listFormattedRows(patientColumns, 8, patients);
	cout << endl;

	// This is how to update a patient in the DB using ID of 3
	map<string, string> patientToChange = getRow(3, patients);
	patientToChange["status"] = "Dead";
	updateRow(3, patientToChange, patients);

	cout << " Patients Database after updating patient:" << endl;
	listFormattedRows(patientColumns, 8, patients);
	cout << endl;

	// This will list all entries in the SYMPTOMS DB
	// You must tell it what columns to print, how many columns to print, and from which database
	cout << " Symptom Database formatted correctly:" << endl;
	string symptomColumns[3] = { "lowRisk", "mediumRisk", "highRisk" };
	listFormattedRows(symptomColumns, 3, symptoms);
	cout << endl;


	return 0;
}
