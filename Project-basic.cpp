// SWE20004 Technical Software Development //
// COVID Project //
// Jasper Robison    #102989198 //
// Joel Murphy       #103073746 //
// Samuel Nothnagel  #100601319 //

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;
// #include statement list to include required C++ library functions //

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
						item = item.substr(0, item.length() - 1);
						item = item + "," + append;
					}
					if (i == col && item == value) {
						return true;
					}
				}
			}
		}
		inFile.close();
	}
	else {
		cout << "Could not open file " << filepath << endl;
	}
	return false;
}

/*
 * Check if patient exixts with id
 */
bool patientDoesExist(int id) {
	return doesExist(0, to_string(id), "patients.txt", 9);
}

/*
 * Check if location exixts with name
 */
bool locationDoesExist(string name) {
	return doesExist(0, name, "locations.txt", 1);
}
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
							item = item.substr(0, item.length() - 1);
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
						}
						else {
							fileContents = fileContents + "," + item;
						}
					}
					fileContents = fileContents + "\n";
				}
				else {
					fileContents = fileContents + line + "\n";
				}
			}
		}
		inFile.close();
	}
	else {
		cout << "Could not open file patients.txt" << endl;
	}
	ofstream outFile("patients.txt", ios::trunc);
	if (outFile.is_open()) {
		outFile << fileContents;
		outFile.close();
	}
	else {
		cout << "Could not open file patients.txt" << endl;
	}
}


int main() {

	string symptomlist = "symptoms.txt";
	string locationlist = "location.txt";
	string patient = "patients.txt";
	int userinput, information, ID;
	string overseas, test, status, usersymptom, address, name, symptom, location, dateentered, DOB, check, line, result, needcheck;
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
		cout << "Enter '2' to Display High Risk Locations:" << endl;
		cout << "Enter '4' to Update Patient Details:" << endl;
		cout << "Enter '5' to Display the COVID-19 Positive Patient Details:" << endl;
		cout << "Enter '6' to Quit:" << endl;
		while (true) {
			try {
				getline(cin, check);
				userinput = stoi(check);
				if (userinput > 0 && userinput < 7) {
					break;
				}
				else {
					cout << "Invalid input please try again: ";
				}
			}
			catch (exception) {
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << endl;

		// covid recommendation and patient details //
		if (userinput == 1) {
			cout << "Do You Have Any Symptoms? (yes/no)" << endl;
			getline(cin, usersymptom);
			cout << endl;
			cout << "Are you a New or Existing patient?" << endl;
			cout << "Enter 1 for New or 2 for Exisitng: ";
			while (true) {
				try {
					getline(cin, check);
					userinput = stoi(check);
					if (userinput > 0 && userinput < 3) {
						break;
					}
					else {
						cout << "Invalid input please try again: ";
					}
				}
				catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << endl;
			if (userinput = 1) {

			}

			// below is the input system to search for an existing patient for COVID-19 recommentdation //
			if (userinput = 2) {
				cout << "Please Enter Your Details." << endl;
				cout << "What Detail Will You Enter?" << endl;
				cout << "Enter '1' for Patient ID:" << endl;
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
					}
					catch (exception) {
						cout << "Sorry, that input is invalid, Try Again!" << endl;
						continue;
					}
				}
				cout << endl;
				//takes in user input for which information they will enter//

				//following code takes in whichever information the patient has chosen to supply//
				//and searches through the database to match with an exisitng patient//
				if (information == 1) {
					cout << "Enter Patient ID: ";
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
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(to_string(ID), 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 2) {
					cout << "Enter Name: ";
					getline(cin, name);
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(name, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 3) {
					cout << "Enter Date of Birth (dd/mm/yyyy): ";
					getline(cin, DOB);
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(DOB, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 4) {
					cout << "Enter Address (number street town postcode): ";
					getline(cin, address);
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(address, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 5) {
					cout << "Overseas Travel? (yes/no): ";
					getline(cin, overseas);
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(overseas, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 6) {
					cout << "Enter Symptoms: ";
					getline(cin, symptom);
					cout << endl;
					cout << "Patient Information: ";
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(symptom, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}
				else if (information == 7) {
					cout << "Enter High Risk location Visited: ";
					getline(cin, location);
					cout << endl;
					cout << "Patient Information: ";
					inFile.open(locationlist);
					while (getline(inFile, line)) {
						if (line.find(location, 0) != string::npos) {
							needcheck = "yes";
							// if user has visited will note on whether needs a covid test with whether they have symptoms answered above //
						}
					}
					inFile.close();
					//check to see if then user has visited a high risk location//
					cout << endl;
					cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
					cout << endl;
					inFile.open(patient);
					while (getline(inFile, line)) {
						if (line.find(location, 0) != string::npos) {
							cout << line << endl;
						}
					}
					inFile.close();
					//searches for patient data and prints the data//
				}

				cout << endl;
				if ((needcheck == "yes") || (usersymptom == "yes")) {
					cout << "Recommended that this patient gets a COVID-19 Test Imediately and Isolate until results come back!" << endl;
				}
				//if the patient has visited a high risk area and has symptoms they are recommended to take a test//
				cout << endl;
				cout << endl;
			}
			//returns to main menu//
		}

		// update covid test status and database //
		else if (userinput == 2) {

		cout << "Updating patient COVID-19 Test Results:" << endl;
		cout << "Please enter patient ID: ";
		while (true) {
			try {
				getline(cin, check);
				ID = stoi(check);
			}
			catch (exception) {
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << "Are you updating a COVID-19 Test Result (positive, negative) or Their Status (cured, deceased)?" << endl;
		cout << "Enter 1 for Test Result or 2 for Status: ";
		while (true) {
			try {
				getline(cin, check);
				userinput= stoi(check);
				if (userinput > 0 && userinput < 3) {
					break;
				}
				else {
					cout << "Invalid input please try again: ";
				}
			}
			catch (exception) {
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << endl;
		if (userinput = 1) {
			cout << "Please enter COVID-19 Test Result: ";
			getline(cin, result);
			if ((result != "positive") || (result != "neagtive")) {
				while ((result != "positive") || (result != "neagtive")) {
					cout << "Invalid input please enter positive or negative: ";
					getline(cin, result);
					cout << endl;
				}
			}
			updatePatientWithID(ID, 7, result);
		}

		if (userinput = 2) {
			cout << "Please Enter Patient Status: ";
			getline(cin, result);
			if ((result != "Dead") || (result != "Alive")) {
				while ((result != "Dead") || (result != "Alive")) {
					cout << "Invalid input please enter positive or negative: ";
					getline(cin, result);
					cout << endl;
				}
			}
			updatePatientWithID(ID, 8, result);
		}


			//return to main menu//
		}

		// display high risk locations // 
		else if (userinput == 3) {
			cout << "The High Risk Locations are:" << endl;
			cout << endl;
			cout << endl;

			inFile.open(locationlist);
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
				}
				catch (exception) {
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
				}
				catch (exception) {
					cout << "Sorry, that input is invalid, Try Again!" << endl;
					continue;
				}
			}
			cout << endl;
			//find patient data//
			if (information = 1) {
				cout << "Enter New Name: ";
				getline(cin, check);
				cout << endl;

				// Update name of patient
				updatePatientWithID(ID, 1, check);
			}
			else if (information = 2) {
				cout << "Enter New Date of Birth (dd/mm/yyyy): ";
				getline(cin, check);
				cout << endl;

				// Update DOB of patient
				updatePatientWithID(ID, 2, check);
			}
			else if (information = 3) {
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
			inFile.open(patient);
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

		// quit //
		else if (userinput == 6) {
			cout << "Thank You For Using Our COVID-19 Database Management System!" << endl;
			cout << "Goodbye!" << endl;
		}

	} while (userinput != 6);



	return 0;
}
