#include <iostream>
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
				file << "," << row[columns[i]];
			}
			file << endl;
		}
		file.close();
	} else {
		throw logic_error("Could not open file " + filePath);
	}
}

/**
 * Create a patient map
 */
map<string, string> createPatient(string id, string name, string dateOfBirth, 
						string address, string visitedLocation, 
						string dateOfEntry, string lastOverseasTravel, 
						string covidTest, string status)
{
	map<string, string> patient;
	
	patient["id"] = id;
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
void insertRow(map<string, string> row, vector<map<string, string> > &db) 
{
	db.push_back(row);
}

/**
 * Update first row using rowId
 */
void updateRow(string columnName, string currentValue, string newValue, vector<map<string, string> > &db) 
{
	// Define Iterators
	vector<map<string, string> >::iterator it;
	map<string, string>::iterator rowIt;
	// Iterate through vector DB
	for (it = db.begin(); it != db.end(); it++) {
		map<string, string> row = *it;
		// Find row and update it if value checks out
		rowIt = row.find(columnName);
		if (rowIt != row.end() && rowIt->second == currentValue) {
			rowIt->second = newValue;
			return;
		}
	}
	// Default to an error if nothing is found
	throw logic_error("No row exists for that key value pair");
}

/**
 * Get first row with a given ID
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

int main() 
{
	// Define a vector of maps for each database
	vector<map<string, string> > patients;
	vector<map<string, string> > symptoms;
	
	// Define an array of columns related to each DB
	string patientColumns[9] = { "id", "name", "dateOfBirth", "address", "visitedLocation", "dateOfEntry", "lastOverseasTravel", "covidTest", "status" };
	string symptomColumns[3] = { "lowRisk", "mediumRisk", "highRisk" };

	// It is neccessary to get the size of these column arrays for use in functions
	size_t patientNumCols = sizeof(patientColumns)/sizeof(patientColumns[0]);
	size_t symptomNumCols = sizeof(symptomColumns)/sizeof(symptomColumns[0]);

	// Read file contents into our DBs
	patients = readInFileContents(patientColumns, patientNumCols, "patients.txt");
	symptoms = readInFileContents(symptomColumns, symptomNumCols, "symptoms.txt");

	cout << endl;

	// List The Patients
	cout << " Patients Database formatted correctly:" << endl;
	listFormattedRows(patientColumns, patientNumCols, patients);
	cout << endl;

	// List The Symptoms
	cout << " Symptom Database formatted correctly:" << endl;
	listFormattedRows(symptomColumns, symptomNumCols, symptoms);
	cout << endl;

	// Get Patient with ID of 1
	// This is how we catch potential errors
	try {
		map<string, string> user = getRow("id", "4", patients);
		cout << "FIRST USER = " << user["name"] << endl << endl;
		// Deleting a row with ID of 1
		deleteRow("id", "4", patients);
	} catch (logic_error){
		cout << "No row for that ID" << endl << endl;
	}

	// Creating a patient and inserting
	insertRow(
		createPatient(
			"4", "James Parker", "17/2/1965", "143 band street OtherTown", "hospital", "2/2/2021", "No", "Negative",  "Alive"
		),
		patients
	);

	cout << " Patients Database formatted correctly:" << endl;
	listFormattedRows(patientColumns, patientNumCols, patients);

	// Make sure this is run every time something is updated
	// It will overwite the file with current DB contents
	writeDatabaseToFile(patients, patientColumns, patientNumCols, "patients.txt");

	try {
		vector<string> locations = getAllValuesForColumn("visitedLocation", patients);
		cout << endl << "Locations: " << endl;
		cout << locations[0] << endl;
		cout << locations[1] << endl;
		cout << locations[2] << endl;
	} catch (logic_error) {
		cout << "nope, couldnt get the locations..." << endl;
	}

	return 0;
}
