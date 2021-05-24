/**
 * @file Project-basic.cpp
 *
 * SWE20004 Technical Software Development
 * COVID Project
 *
 * @author Jasper Robison    #102989198
 * @author Joel Murphy       #103073746
 * @author Samuel Nothnagel  #100601319
 */

// #include statement list to include required C++ library functions //
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <numeric>
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
				stringstream ss(line);
				for (int i = 0; i < totalColumns; i++) {
					// Split line items by comma
					string item;
					getline(ss, item, ',');
					// Account for escaped commas
					while (item.back() == '\\') {
						string append;
						getline(ss, append, ',');
						item = item.substr(0, item.length() - 1);
						item = item + "," + append;
					}
					// Return true if value exists
					if (i == col && item == value) {
						return true;
					}
				}
			}
		}
		// Finally, close the file
		inFile.close();
	} else {
		// Throw error if file could not be opened
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

/*
 * Check if location exixts with a given name
 */
bool isHighRiskSymptom(string symptom) {
	return doesExist(2, symptom, SYMPTOM_FILEPATH, 3);
}

/**
 * This function will update the value of a row column in a file if idVal is found at idIndex
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
				string updatedLine;
				stringstream ss(line);
				bool hasId = false;
				for (int i = 0; i < totalNumColumns; i++) {
					// Split line items by comma
					string item;
					getline(ss, item, ',');
					// Account for escaped commas
					while (item.back() == '\\') {
						string append;
						getline(ss, append, ',');
						item = item.substr(0, item.length() - 1);
						item = item + "," + append;
					}
					// Check if this is the correct line to update
					if (i == idIndex && item == idVal) {
						hasId = true;
					}
					// Don't add delim for first item
					if (i > 0) {
						updatedLine = updatedLine + ",";
					}
					// Change the value if at index
					stringstream valstream;
					if (i == index) {
						valstream.str(value);
					} else {
						valstream.str(item);
					}
					string valItem;
					getline(valstream, valItem, ',');
					// Account for escaped commas
					while (valstream.rdbuf()->in_avail()) {
						string append;
						getline(valstream, append, ',');
						valItem = valItem + "\\," + append;
					}
					updatedLine = updatedLine + valItem;
				}
				// Only add updated line if it is the line we want to update
				if (hasId) {
					fileContents = fileContents + updatedLine + "\n";
				} else {
					fileContents = fileContents + line + "\n";
				}
			}
		}
		// Finally, close the file
		inFile.close();
	} else {
		// Throw an error if file could not be opened
		cout << "Could not open file " << filepath << endl;
	}
	// Open file again, this time for outputting
	ofstream outFile(filepath, ios::trunc);
	if (outFile.is_open()) {
		outFile << fileContents;
		outFile.close();
	} else {
		// Throw an error if file could not be opened
		cout << "Could not open file " << filepath << endl;
	}
}

/*
 * Update a patient detail using the ID
 */
void updatePatientWithID(int id, int index, string value) {
	updateColumn(0, to_string(id), index, value, PATIENT_FILEPATH, 9);
}

/*
 * Make a string lowercase
 */
string stringToLower(string str) {
	string ret = "";
	for (int i = 0; i < str.size(); i++) {
		ret += tolower(str[i]);
	}
	return ret;
}

/*
 * Helper funtion for escaping commas
 */
string escaped(string str) {
	string ret = "";
	for (int i = 0; i < str.size(); i++) {
		// If we find a comma, add an escape character before it
		if (str[i] == ',') {
			ret += '\\';
		}
		ret += str[i];
	}
	return ret;
}

int main() {

	// Define all the necessary variables
	// All these are to be used in the function of the program
	int userinput, information, ID, existing;
	string overseasTravel, test, status, userSymptoms, address, name, symptom, location, dateentered, DOB, check, line, result, needcheck, dateVisited;
	bool hasVisitedHighRiskLoc;
	ofstream oFile;
	ifstream inFile;

	// Prompt and take in user input regarding what they wish to do
	do {
		cout << "Welcome to the COVID-19 Database Management System!!" << endl;
		cout << endl; cout << "What would you like to do?" << endl;
		cout << "Enter '1' to Enter Your Detail For COVID Test Recommendation:" << endl;
		cout << "Enter '2' to Submit Your COVID-19 Test Status and Update the Location Database:" << endl;
		cout << "Enter '3' to Display High Risk Locations:" << endl;
		cout << "Enter '4' to Update Patient Details:" << endl;
		cout << "Enter '5' to Display the COVID-19 Positive Patient Details:" << endl;
		cout << "Enter '6' to Quit:" << endl;
		// While loop to ensure an integer input
		while (true) {
			try {
				getline(cin, check);
				userinput = stoi(check);
				// Only accept integer within these bounds
				if (userinput > 0 && userinput < 7) {
					break;
				} else {
					cout << "Invalid input please try again: ";
				}
			}
			catch (exception) {
				// Throw error if input is a string
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << endl;

		if (userinput == 1) {
			/* Covid recommendation and patient details */

			hasVisitedHighRiskLoc = false;
			// Ensure user inputs an int
			while (true) {
				try {
					cout << endl << "Enter New Patient ID: ";
					getline(cin, check);
					ID = stoi(check);
					break;
				}
				catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			// Check if patient already exists
			if (!patientDoesExist(ID)) {
				// Takes in all of the patients details and stores in text file
				cout << "Enter New Patient Name: ";
				getline(cin, name);
				cout << "Enter Patient DOB (dd/mm/yyy): ";
				getline(cin, DOB);
				cout << "Enter Patient Address: ";
				getline(cin, address);
				cout << "Enter High Risk Location Visited: ";
				getline(cin, location);
				cout << "Enter Date Visited: ";
				getline(cin, dateVisited);
				cout << "Enter last overseas travel status (yes/no): ";
				getline(cin, overseasTravel);
				overseasTravel = stringToLower(overseasTravel);
				// Ensure yes or no string input
				while ((overseasTravel != "yes") && (overseasTravel != "no")) {
					cout << "Invalid input, please try again (yes/no): ";
					getline(cin, overseasTravel);
					overseasTravel = stringToLower(overseasTravel);
				}
				cout << "Enter COVID-19 Test Result (positive/negative): ";
				getline(cin, result);
				result = stringToLower(result);
				// Ensure positive or negative string input
				while ((result != "positive") && (result != "negative")) {
					cout << "Invalid input, please try again (positive/negative): ";
					getline(cin, result);
					result = stringToLower(result);
				}
				cout << "Enter Status (dead/alive): ";
				getline(cin, status);
				status = stringToLower(status);
				// Ensure dead or alive string input
				while ((status != "dead") && (status != "alive")) {
					cout << "Invalid input, please try again (dead/alive): ";
					getline(cin, status);
					status = stringToLower(status);
				}
				// Opens file in append mode
				oFile.open(PATIENT_FILEPATH, ios::app);
				/*  Output new users data to file and close.
					Also escape any commas that the user might input
				*/
				oFile << ID << "," << escaped(name) << "," << escaped(DOB) << "," << escaped(address) << "," << escaped(stringToLower(location)) << "," 
					<< escaped(dateVisited) << "," << stringToLower(overseasTravel) << "," << stringToLower(result) << "," << stringToLower(status) << "\n";
				oFile.close();
				// Ask for patient symptoms
				cout << "Enter Patient Symptoms: ";
				getline(cin, symptom);
				// Check if they need a test recommended
				if (locationDoesExist(location) || isHighRiskSymptom(stringToLower(symptom))) {
					cout << endl << "Recommended that this patient gets a COVID-19 Test Imediately and Isolate until results come back!" << endl;
				}
			} else {
				// If patient exists prints them out and gives a COVID test recommendation
				cout << endl << "That Patient already exists with that ID" << endl;
				inFile.open(PATIENT_FILEPATH);
				check = to_string(ID);
				cout << "ID - Name - Date of Birth - Address - High Risk Location Visited - Date Visited - Symptoms - COVID-19  Test Result - Status" << endl;
				cout << endl;
				while (getline(inFile, line)) {
					if (line.find(check, 0) != string::npos) {
						cout << line << endl;
						cout << endl;
					}
				}
				inFile.close();
				cout << "Has Patient Visted a High Risk Location? (yes/no): " << endl;
				getline(cin, check);
				cout << "Does Patient Have Symptoms (yes/no): " << endl;
				getline(cin, symptom);
				if ((check == "yes") && (symptom == "yes")) {
					cout << "Recommend That This Patient Gets a COVID-19 Test and Isolates Until Results are Available" << endl;;
				}
			}
			cout << endl << "Press ENTER to continue to menu...";
			cin.ignore();
			cout << endl;
			// Return to main menu
	
		} else if (userinput == 2) {
			/* Submit for COVID test */

			cout << "Please enter patient ID: ";
			while (true) {
				try {
					getline(cin, check);
					ID = stoi(check);
					break;
				}
				catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << "Please enter COVID-19 Test Result (positive/negative): ";
			getline(cin, result);
			result = stringToLower(result);
			while ((result != "positive") && (result != "negative")) {
				cout << "Invalid input, please try again (positive/negative): ";
				getline(cin, result);
				result = stringToLower(result);
			}
			if (result == "positive") {
				// Get new location
				cout << "Please enter most recent visited location: ";
				getline(cin, location);
				location = escaped(stringToLower(location));
				// If not exists, add to DB
				if (!locationDoesExist(location)) {
					oFile.open(LOCATION_FILEPATH, ios::app);
					oFile << location << endl;
					oFile.close();
					cout << location << " added to location database" << endl;
				} else {
					cout << location << " already exists in location database" << endl;
				}
				// Update the users location
				updatePatientWithID(ID, 4, location);
			}
			cout << "Updating patient details..." << endl;
			updatePatientWithID(ID, 7, result);
			// Return to main menu
			cout << endl << "Press ENTER to continue to menu...";
			cin.ignore();
			cout << endl;
			// Return to main menu
		
		} else if (userinput == 3) {
			/* Display high risk locations */

			cout << "The High Risk Locations are:" << endl;
			cout << endl;
			string title = "Location";
			int maxChars = 0;
			// Opens respective file and reads contents
			inFile.open(LOCATION_FILEPATH);
			while (getline(inFile, line)) {
				maxChars = max( int(max(title.length(), line.length())), maxChars);
			}
			inFile.close();
			// Print them with a nicely formatted boundary
			inFile.open(LOCATION_FILEPATH);
			string horizontalBuffer(maxChars + 4, '-');
			cout << horizontalBuffer << endl;
			cout << "| " << title << " |" << endl;
			cout << horizontalBuffer << endl;
			while (getline(inFile, line)) {
				if (!line.empty()) {
					cout << "| " << line << string(maxChars-line.length(), ' ') << " |" << endl;
				}
			}
			cout << horizontalBuffer << endl;
			inFile.close();
			// Return to main menu

		} else if (userinput == 4) {
			/* Update patient details */

			cout << "Which Patient Details Do You Wish To Update?" << endl;
			while (true) {
				try {
					cout << "Please input Patient ID: ";
					getline(cin, check);
					ID = stoi(check);
					break;
				}
				catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			// Check to see if patient actually exists first
			if (!patientDoesExist(ID)) {
				cout << "Sorry, no patient exists with that ID!" << endl;
			} else {
				cout << endl;
				cout << "What Data Would You Like To Update?" << endl;
				cout << "Enter '1' for Name:" << endl;
				cout << "Enter '2' for Date of Birth:" << endl;
				cout << "Enter '3' for Address:" << endl;
				cout << "Enter '4' for New High Risk Location Visited and date visited:" << endl;
				cout << "Enter '5' for Last Overseas Travel" << endl;
				cout << "Enter '6' for New Status" << endl;
				cout << "Enter '7' to EXIT to menu" << endl;
				while (true) {
					try {
						getline(cin, check);
						information = stoi(check);
						// Only except input within these bounds
						if (information < 1 || information > 8) {
							cout << "Sorry, that input is out of bounds!" << endl;
							continue;
						}
						break;
					}
					catch (exception) {
						// Throw an error if user enters a string
						cout << "Sorry, that input is invalid, Try Again!" << endl;
						continue;
					}
				}
				cout << endl;
				// Find patient data
				switch (information)
					/* Each of these options will prompt the user for data
					 * and update the correct value in the db based on the data */
				{
					case 1:
						cout << "Enter New Name: ";
						getline(cin, name);
						// Update name of patient
						updatePatientWithID(ID, 1, name);
						break;
					case 2:
						cout << "Enter New Date of Birth (dd/mm/yyyy): ";
						getline(cin, DOB);
						// Update DOB of patient
						updatePatientWithID(ID, 2, DOB);
						break;
					case 3:
						cout << "Enter New Address: ";
						getline(cin, address);
						// Update address of patient
						updatePatientWithID(ID, 3, address);
						break;
					case 4:
						cout << "Enter New High Risk Location Visited: ";
						getline(cin, location);
						updatePatientWithID(ID, 4, location);
						cout << "Enter Date Visited: ";
						getline(cin, dateVisited);
						// Update location and date visited
						updatePatientWithID(ID, 5, dateVisited);
						break;
					case 5:
						cout << "Enter last overseas travel status (yes/no): ";
						getline(cin, overseasTravel);
						overseasTravel = stringToLower(overseasTravel);
						while ((overseasTravel != "yes") && (overseasTravel != "no")) {
							cout << "Invalid input, please try again (yes/no): ";
							getline(cin, overseasTravel);
							overseasTravel = stringToLower(overseasTravel);
						}
						// Update last overseas travel
						updatePatientWithID(ID, 6, overseasTravel);
						break;
					case 6:
						cout << "Enter Status (dead/alive): ";
						getline(cin, status);
						status = stringToLower(status);
						while ((status != "dead") && (status != "alive")) {
							cout << "Invalid input, please try again (dead/alive): ";
							getline(cin, status);
							status = stringToLower(status);
						}
						// Update patient status
						updatePatientWithID(ID, 8, status);
						break;
					default:
						break;

				}
			}
			cout << endl << "Press ENTER to continue to menu...";
			cin.ignore();
			cout << endl;
			// Return to main menu

		} else if (userinput == 5) {
			/* display covid positive patient details */

			cout << "Covid Positive Patient Details are:" << endl;
			cout << endl;
			string titles[9] = {"ID", "Name", "Date of Birth", "Address", "High Risk Location Visited", "Date Visited" ,"Last Overseas travel","COVID-19 Test Result", "Status"};
			int maxChars[9] = { 0 };
			// Opens patient file and reads contents
			inFile.open(PATIENT_FILEPATH);
			while (getline(inFile, line)) {
				// Only print if they are covid positive patients
				if (line.find("positive", 0) != string::npos) {
					// searches the file for the matching input and takes the position of the matching input //
					stringstream ss(line);
					for (int i = 0; i < 9; i++) {
						string item;
						getline(ss, item, ',');
						// Account for escaped commas
						while (item.back() == '\\') {
							string append;
							getline(ss, append, ',');
							item = item.substr(0, item.length()-1);
							item = item + "," + append;
						}
						// Get the maximum column width for each column
						maxChars[i] = max( int(max(titles[i].length(), item.length())), maxChars[i]);
					}
				}
			}
			inFile.close();
			// Create and print a nice horizontal buffer with correct width
			int bufferWidth = accumulate(begin(maxChars), end(maxChars), 0) + 28;
			string horizontalBuffer(bufferWidth, '-');
			cout << horizontalBuffer << endl;
			// Print the column titles
			for (int i = 0; i < 9; i++) {
				cout << "| " << titles[i] << string(maxChars[i]-titles[i].length(), ' ') << " ";
			}
			cout << "|" << endl;
			cout << horizontalBuffer << endl;
			// Print them with a nicely formatted boundary
			inFile.open(PATIENT_FILEPATH);
			while (getline(inFile, line)) {
				// Only print if they are covid positive patients
				if (line.find("positive", 0) != string::npos) {
					if (!line.empty()) {
						stringstream ss(line);
						for (int i = 0; i < 9; i++) {
							string item;
							getline(ss, item, ',');
							// Account for escaped commas
							while (item.back() == '\\') {
								string append;
								getline(ss, append, ',');
								item = item.substr(0, item.length()-1);
								item = item + "," + append;
							}
							cout << "| " << item << string(maxChars[i]-item.length(), ' ') << " ";
						}
						cout << "|" << endl;
					}
				}
			}
			cout << horizontalBuffer << endl;
			inFile.close();
			cout << endl;
			// Return to main menu
		}

	// Quit if input is 6
	} while (userinput != 6);

	cout << "Thank You For Using Our COVID-19 Database Management System!" << endl << "Goodbye!" << endl;

	return 0;
}
