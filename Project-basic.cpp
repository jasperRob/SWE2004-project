// SWE20004 Technical Software Development //
// COVID Project //
// Jasper Robison    #102989198 //
// Joel Murphy       #103073746 //
// Samuel Nothnagel  #100601319 //

// #include statement list to include required C++ library functions //
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Define locations of db files with macros
string PATIENT_FILEPATH = "patients.txt";
string LOCATION_FILEPATH = "locations.txt";
string SYMPTOM_FILEPATH = "symptoms.txt";

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
	return doesExist(0, to_string(id), PATIENT_FILEPATH, 9);
}

/*
 * Check if location exixts with a given name
 */
bool locationDoesExist(string name) {
	return doesExist(0, name, LOCATION_FILEPATH, 1);
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
	} else {
		cout << "Could not open file " << filepath << endl;
	}
	ofstream outFile(filepath, ios::trunc);
	if (outFile.is_open()) {
		outFile << fileContents;
		outFile.close();
	} else {
		cout << "Could not open file " << filepath << endl;
	}
}

/*
 * Update a patient detail using the ID
 */
void updatePatientWithID(int id, int index, string value) {
	updateColumn(0, to_string(id), index, value, PATIENT_FILEPATH, 9);
}

int main() {

	int userinput, information, ID, existing;
	string overseas, test, status, userSymptoms, address, name, symptom, location, dateentered, DOB, check, line, result, needcheck;
	bool hasVisitedHighRiskLoc;
	ofstream oFile;
	ifstream inFile;
	//user input variables//

	//variables to enable the use of the database//
	//declare all variables before proceeding to code//

	//prompts and takes in user input for what they wish to do//
	do {
		cout << "Welcome to the COVID-19 Database Management System!!" << endl;
		cout << endl;
		cout << "What would you like to do?" << endl;
		cout << "Enter '1' to Enter Your Detail For COVID Test Recommendation:" << endl;
		cout << "Enter '2' to Submit Your COVID-19 Test Status and Update the Location Database:" << endl;
		cout << "Enter '3' to Display High Risk Locations:" << endl;
		cout << "Enter '4' to Update Patient Details:" << endl;
		cout << "Enter '5' to Display the COVID-19 Positive Patient Details:" << endl;
		cout << "Enter '6' to Quit:" << endl;
		while (true) {
			try {
				getline(cin, check);
				userinput = stoi(check);
				if (userinput > 0 && userinput < 7) {
					break;
				} else {
					cout << "Invalid input please try again: ";
				}
			}
			catch (exception) {
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << endl;

		// Covid recommendation and patient details
		if (userinput == 1) {
			hasVisitedHighRiskLoc = false;

			// Ensure user inputs an int
			while (true) {
				try {
					cout << endl << "Enter New Patient ID: ";
					getline(cin, check);
					ID = stoi(check);
					break;
				} catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			// Check if patient already exists
			if (!patientDoesExist(ID)) {
				// Opens file in append mode
				oFile.open(PATIENT_FILEPATH, ios::app);
				oFile << check << ",";
				// Takes in all of the patients details and stores in text file
				cout << "Enter New Patient Name: ";
				getline(cin, check);
				oFile << check << ",";
				cout << "Enter Patient DOB (dd/mm/yyy): ";
				getline(cin, check);
				oFile << check << ",";
				cout << "Enter Patient Address: ";
				getline(cin, check);
				oFile << check << ",";
				cout << "Enter High Risk Location Visited: ";
				getline(cin, check);
				oFile << check << ",";
				cout << endl;
				cout << "Enter Date Visited: ";
				getline(cin, check);
				oFile << check << ",";
				cout << endl;
				cout << "Does Patients Have Symptoms: ";
				getline(cin, check);
				oFile << check << ",";
				cout << endl;
				cout << "Enter COVID-19 Test Result: ";
				getline(cin, check);
				oFile << check << ",";
				cout << endl;
				cout << "Enter Status: ";
				getline(cin, check);
				oFile << check << "\n";
				// Close the opened file
				oFile.close();
				cout << endl << "Do You Have Any Symptoms? (yes/no): ";
				getline(cin, userSymptoms);
				cout << "Which location have you visited recently?: ";
				getline(cin, check);

				if (locationDoesExist(check)) {
					hasVisitedHighRiskLoc = true;
				}
				if (hasVisitedHighRiskLoc && userSymptoms == "yes") {
					cout << endl << "Recommended that this patient gets a COVID-19 Test Imediately and Isolate until results come back!" << endl;
				}
			} else {
				cout << endl << "Sorry, a Patient already exists with that ID" << endl;
			}
			cout << endl << "Press ENTER to continue to menu...";
			cin.ignore();
			cout << endl;

		// Update covid test status and database
		} else if (userinput == 2) {

			cout << "Please enter patient ID: ";
			while (true) {
				try {
					getline(cin, check);
					ID = stoi(check);
					break;
				} catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << "Please enter COVID-19 Test Result (Positive/Negative): ";
			getline(cin, status);
			if ((status != "Positive") && (status != "Negative")) {
				while ((status != "Positive") && (status != "Negative")) {
					cout << "Invalid input, please try again (Positive/Negative): ";
					getline(cin, status);
					cout << endl;
				}
			}
			if (status == "Positive") {
				// Get new location
				cout << "Please enter most recent visited location: ";
				getline(cin, location);
				// If not exists, add to DB
				if (!locationDoesExist(location)) {
					oFile.open(LOCATION_FILEPATH, ios::app);
					oFile << location << endl;
					oFile.close();
					cout << location << " added to location database";
				} else {
					cout << location << " already exists in location database";
				}
			}
			updatePatientWithID(ID, 7, status);
			cout << endl << endl << "Press ENTER to continue to menu...";
			cin.ignore();
			cout << endl;

		// Display high risk locations
		} else if (userinput == 3) {
			cout << "The High Risk Locations are:" << endl;
			cout << endl;
			cout << endl;

			inFile.open(LOCATION_FILEPATH);
			while (getline(inFile, line)) {
				cout << line << endl;
				cout << endl;
			}
			inFile.close();
			cout << endl;
			cout << "End of High Risk Location List" << endl;
			cout << endl;
			cout << endl;
			//opens respective file and reads contents//

			//return to main menu//
		}

		// update patient details //
		else if (userinput == 4) {

			cout << "Which Patient Details Do You Wish To Update?" << endl;
			cout << "Please input Patient ID: ";
			while (true) {
				try {
					getline(cin, check);
					ID = stoi(check);
					break;
				} catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << endl;

			cout << "What Data Would You Like To Update?" << endl;
			cout << "Enter '2' for Name:" << endl;
			cout << "Enter '3' for Date of Birth:" << endl;
			cout << "Enter '4' for Address:" << endl;
			cout << "Enter '5' for Overseas Travel:" << endl;
			cout << "Enter '6' for Symptoms:" << endl;
			cout << "Enter '7' for High Risk COVID Area Location:" << endl;
			while (true) {
				try {
					getline(cin, check);
					information = stoi(check);
					break;
				} catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << endl;
			//find patient data//
			if (information == 1) {
				cout << "Enter New Name: ";
				getline(cin, check);
				cout << endl;

				// Update name of patient
				updatePatientWithID(ID, 1, check);
			}
			else if (information == 2) {
				cout << "Enter New Date of Birth (dd/mm/yyyy): ";
				getline(cin, check);
				cout << endl;

				// Update DOB of patient
				updatePatientWithID(ID, 2, check);
			}
			else if (information == 3) {
				cout << "Enter New Address: ";
				getline(cin, check);
				cout << endl;

				// Update address of patient
				updatePatientWithID(ID, 3, check);
			}
			//return to main menu//
		}

		// display covid positive patient details //
		else if (userinput == 5) {
			cout << "Covid Positive Patient Details are:" << endl;
			cout << endl;
			cout << endl;
			result = "positive";
			inFile.open(PATIENT_FILEPATH);
			cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
			cout << endl;
			while (getline(inFile, line)) {
				if (line.find(result, 0) != string::npos) {
					cout << line << endl;
					cout << endl;
				}
			}
			inFile.close();
			//searches for patient data and prints the data//
			cout << endl;
			cout << endl;
			//return to main menu//
		}
	// Quit if input is 6
	} while (userinput != 6);

	cout << "Thank You For Using Our COVID-19 Database Management System!" << endl << "Goodbye!" << endl;

	return 0;
}
