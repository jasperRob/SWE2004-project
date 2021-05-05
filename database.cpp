#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
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
 * Read in the contents of a file and return it as a vector of maps
 */
vector<map<string, string> > readInFileContents(string columns[], size_t numColumns, string filePath) 
{
	cout << "Opening file " << filePath << endl;
	// Set up a file stream and a vector DB
	ifstream file(filePath);
	vector<map<string, string> > db;
	// Open the file
	if (file.is_open()) {
		string line;
		// Read all lines of the file
		while (getline(file, line)) {
			if (!line.empty()) {
				// Split items by comma and create a map for them
				map<string, string> row;
				stringstream ss(line);
				string item;
				for (int i = 0; i < numColumns; i++) {
					getline(ss, item, ',');
					while (item.back() == '\\') {
						string append;
						getline(ss, append, ',');
						item = item.substr(0, item.length()-1);
						item = item + "," + append;
					}
					row[columns[i]] = item;
				}
				// Push the map to our vector DB
				db.push_back(row);
			}
		}
		file.close();
	} else {
		throw logic_error("Could not open file " + filePath);
	}
	return db;
}

/**
 * Overwrite a file with the current DB contents.
 */
void writeDatabaseToFile(vector<map<string, string> > &db, string columns[], size_t numColumns, string filePath)
{
	ofstream file(filePath, ios::trunc);
	if (file.is_open()) {
		vector<map<string, string> >::iterator rowIt;
		for (rowIt = db.begin(); rowIt != db.end(); rowIt++) {
			map<string, string> row = *rowIt;
			// Write comma seperated values to line
			file << row[columns[0]];
			for (int i = 1; i < numColumns; i++) {
				stringstream ss(row[columns[i]]);
				string item;
				getline(ss, item, ',');
				while (ss.rdbuf()->in_avail()) {
					string append;
					getline(ss, append, ',');
					item = item + "\\," + append;
				}
				file << "," << item;
			}
			file << endl;
		}
		file.close();
	} else {
		throw logic_error("Could not open file " + filePath);
	}
}

/**
 * Insert a row
 */
void insertRow(map<string, string> row, vector<map<string, string> > &db) 
{
	db.push_back(row);
}

/**
 * Update first row using key-value pair
 */
void updateRow(string idColumn, string idValue, map<string, string> row, vector<map<string, string> > &db) 
{
	// Define Iterators
	vector<map<string, string> >::iterator it;
	map<string, string>::iterator rowIt;
	// Iterate through vector DB
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> r = *it;
		// Find row and update it if value checks out
		rowIt = r.find(idColumn);
		if (rowIt != r.end() && rowIt->second == idValue) {
			cout << rowIt->first << " = " << rowIt->second << endl;
			*it = row;
			return;
		}
	}
	// Default to an error if nothing is found
	throw logic_error("No row exists for that key value pair");
}

/**
 * Get first row with a given key-value pair
 */
map<string, string> getRow(string columnName, string value, vector<map<string, string> > &db)
{
	// Define Iterators
	vector<map<string, string> >::iterator it;
	map<string, string>::iterator rowIt;
	// Iterate through vector DB
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		// Find row and return it if value checks out
		rowIt = row.find(columnName);
		if (rowIt != row.end() && rowIt->second == value) {
			return row;
		}
	}
	// Default to an error if nothing is found
	throw logic_error("No row exists for that key value pair");
}

/*
 * Get every value associeted with a column
 */
vector<string> getAllValuesForColumn(string columnName, vector<map<string, string> > &db)
{
	// Define Iterators
	vector<string> values;
	vector<map<string, string> >::iterator it;
	map<string, string>::iterator rowIt;
	// Iterate through vector DB
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		// Find row and return it if value checks out
		rowIt = row.find(columnName);
		if (rowIt != row.end()) {
			values.push_back(rowIt->second);
		}
	}
	if (values.size() > 0) {
		return values;
	}
	// Default to an error if nothing is found
	throw logic_error("No values found for that column");
}

/**
 * Delete first row with a given ID
 */
void deleteRow(string columnName, string value, vector<map<string, string> > &db)
{
	// Define Iterators
	vector<map<string, string> >::iterator it;
	map<string, string>::iterator rowIt;
	// Iterate through vector DB
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		// Find row and remove it if value checks out
		rowIt = row.find(columnName);
		if (rowIt != row.end() && rowIt->second == value) {
			db.erase(it);
			return;
		}
	}
	// Default to an error if nothing is found
	throw logic_error("No row exists for that key value pair");
}

/**
 * List all rows of a db
 * This will format everything
 * Got a bit carried away with this one but oh well.
 */
void listFormattedRows(string columns[], size_t numColumns, vector<map<string, string> > &db)
{
	// Define iterators and width vector
	vector<map<string, string> >::iterator it;
	vector<int> columnWidths(numColumns, 0);
	int maxIdWidth = 0;
	// Calculate the column widths
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		for (int c = 0; c < numColumns; c++) {
			columnWidths[c] = max( max( int(columnWidths[c]), int(orNull(row[columns[c]]).length())), int(columns[c].length()));
		}
	}
	// Calulcate the buffer width
	int bufferWidth = accumulate(columnWidths.begin(), columnWidths.end(), 0) + (numColumns * 3) + 1;
	string horizontalBuffer(bufferWidth, '-');
	// Print the header with column tags
	cout << horizontalBuffer << endl;
	for (int i = 0; i < numColumns; i++) {
		cout << "| " << columns[i] << string(columnWidths[i]-columns[i].length(), ' ') << " ";
	}
	cout << "|" << endl << horizontalBuffer << endl;
	// Begin printing each row in the database
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		for (int i = 0; i < numColumns; i++) {
			string value = orNull(row[columns[i]]);
			cout << "| " << value << string(columnWidths[i]-value.length(), ' ') << " ";
		}
		cout << "|" << endl;
	}
	cout << horizontalBuffer << endl;
}

string requestValue(string key)
{
	cout << key << ": ";
	string input;
	getline(cin, input);
	return input;
}

int showMenu()
{
	cout << "Please select one of the following:" << endl;
	cout << "1 - Enter your detail for COVID-Test Recommendation" << endl;
	cout << "2 - Submit Your Covid test status & Update the Location database" << endl;
	cout << "3 - Display the Updated Location (High Risk for COVID) " << endl;
	cout << "4 - Update COVID Patient Details  " << endl;
	cout << "5 - Display the COVID Positive Patient Detail " << endl;
	cout << "6 - Quit" << endl;
	int input = stoi(requestValue("Your Selection"));
	return input;
}

int main() 
{
	// Define a vector of maps for each database
	vector<map<string, string> > patients;
	vector<map<string, string> > symptoms;
	vector<map<string, string> > locations;
	
	// Define an array of columns related to each DB
	string patientColumns[9] = { "id", "name", "dateOfBirth", "address", "visitedLocation", "dateOfEntry", "lastOverseasTravel", "covidTest", "status" };
	string symptomColumns[3] = { "lowRisk", "mediumRisk", "highRisk" };
	string locationsColumns[3] = { "name" };

	// It is neccessary to get the size of these column arrays for use in functions
	size_t patientNumCols = sizeof(patientColumns)/sizeof(patientColumns[0]);
	size_t symptomNumCols = sizeof(symptomColumns)/sizeof(symptomColumns[0]);
	size_t locationsNumCols = sizeof(locationsColumns)/sizeof(locationsColumns[0]);

	// Read file contents into our DBs
	patients = readInFileContents(patientColumns, patientNumCols, "patients.txt");
	symptoms = readInFileContents(symptomColumns, symptomNumCols, "symptoms.txt");
	locations = readInFileContents(locationsColumns, locationsNumCols, "locations.txt");

	int input;
	do {
		// List The Patients
		cout << " Patients Database formatted correctly:" << endl;
		listFormattedRows(patientColumns, patientNumCols, patients);
		cout << endl;

		input = showMenu();
		if (input == 1) { 
			// Ask for the users details
			map<string, string> user;
			user["id"] = requestValue("ID");
			user["name"] = requestValue("Name");
			user["dateOfBirth"] = requestValue("DateOfBirth");
			user["address"] = requestValue("Address");
			user["visitedLocation"] = requestValue("VisitedLocation");
			user["dateOfEntry"] = requestValue("DateOfEntry");
			user["lastOverseasTravel"] = requestValue("LastOverseasTravel");
			user["covidTest"] = requestValue("CovidTest");
			user["status"] = requestValue("Status");
			cout << endl;
			// Insert into the DB and write to file
			insertRow(user, patients);
			writeDatabaseToFile(patients, patientColumns, patientNumCols, "patients.txt");
		}
		if (input == 2) {
			string id = requestValue("ID");
			string covidTest = requestValue("Test Status");
			if (covidTest == "Positive") {
				map<string, string> user;
				try {
					// Get User from DB using the id and set new value
					user = getRow("id", id, patients);
					user["covidTest"] = covidTest;
					// Update their row in the DB
					updateRow("id", id, user, patients);
					// Write contents to file
					writeDatabaseToFile(patients, patientColumns, patientNumCols, "patients.txt");
				} catch (logic_error) {
					cout << "no good" << endl;
				}
				try {
					// Check if location exists and fail if not
					map<string, string> userWithLoc = getRow("name", user["visitedLocation"], locations);
					cout << user["visitedLocation"] << " already in locations database" << endl;
				} catch (logic_error) {
					cout << "Adding " << user["visitedLocation"] << " to locations database" << endl;
					// Create new location
					map<string, string> newLocation;
					string visLoc = user["visitedLocation"];
					newLocation["name"] = visLoc;
					// Add new location to the DB
					insertRow(newLocation, locations);
					// Write this to the file
					writeDatabaseToFile(locations, locationsColumns, locationsNumCols, "locations.txt");
				}
				cout << endl;
			}
		};
	} while (input != 6);

	cout << "Goodbye!" << endl;

	return 0;
}
