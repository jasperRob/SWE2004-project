// SWE20004 Technical Software Development //
// COVID Project //
// Jasper Robison    #102989198 //
// Joel Murphy       #103073746 //
// Samuel Nothnagel  #100601319 //

#include <iostream>
#include <fstream>
#include<string>
using namespace std;
// #include statement list to include required C++ library functions //

int main() {

	string symptomlist = "symptoms.txt";
	string locationlist = "location.txt";
	string patient = "patients.txt";
	int userinput, information;
	string overseas, test, status, usersymptom, address, name, symptom, location, dateentered, DOB, check, line, result, ID, needcheck;
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
		getline(cin, check);
		while (true) {
			try {
				getline(cin, check);
				userinput = stoi(check);
				break;
			}
			catch (exception) {
				cout << "Sorry, that input is invalid, Try Again!" << endl;
				continue;
			}
		}
		cout << endl;

		//covid recommendation and patient details//
		if (userinput == 1) {
			cout << "Do You Have Any Symptoms? (yes/no)" << endl;
			getline(cin, usersymptom);
			cout << endl;
			cout << "Please Enter Your Details." << endl;
			cout << "What Detail Will You Enter?" << endl;
			cout << "Enter '1' for Patient ID:" << endl;
			cout << "Enter '2' for Name:" << endl;
			cout << "Enter '3' for Date of Birth:" << endl;
			cout << "Enter '4' for Address:" << endl;
			cout << "Enter '5' for Overseas Travel:" << endl;
			cout << "Enter '6' for Symptoms:" << endl;
			cout << "Enter '7' for High Risk COVID Area Location:" << endl;
			getline(cin, check);
			information = stoi(check);
			cout << endl;
			//takes in user input for which information they will enter//

			//following code takes in whichever information the patient has chosen to supply//
			//and searches through the database to match with an exisitng patient//
			if (information == 1) {
				cout << "Enter Patient ID: ";
				getline(cin, ID);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
				cout << "ID - Name - Date of Birth - Address - Overseas Travel - Symptoms - High Risk Location Visited - COVID-19 Test Result" << endl;
				cout << endl;
				inFile.open(patient);
				while (getline(inFile, line)) {
					if (line.find(ID, 0) != string::npos) {
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
			else {
				cout << "Invalid Input. Please Try Again" << endl;

			}
			cout << endl;
			if ((needcheck == "yes") || (usersymptom == "yes")) {
				cout << "Recommended that this patient gets a COVID-19 Test Imediately and Isolate until results come back!" << endl;
			}
			//if the patient has visited a high risk area and has symptoms they are recommended to take a test//
			cout << endl;
			cout << endl;

			//returns to main menu//
		}
		
		// update covid test status and database //
		else if (userinput == 2) {
			
			//opens respective file and reads contents//

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
			cout << "Would You Like to Update an Existing Patient or Add a New Patient?" << endl;
			cout << "Enter 1 For Existing Patient and 2 For New Patient" << endl;
			getline(cin, check);
			if(check = 1){
				
			}
			else if(check = 2){
				
			}
			else {
				while((check != 1) || (check != 2)){
					cout << "Invalid input please try again: " ;
					getline(cin, check);
				}
			}
			
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

		//quit//
		else if (userinput == 6) {
			cout << "Thank You For Using Our COVID-19 Database Management System!" << endl;
			cout << "Goodbye!" << endl;
		}

		// invalid integer input //
		else {
			cout << "Invalid Input, Please Try Again: ";
			cout << endl;
			cout << endl;

			//return to main menu//
		}

	} while (userinput != 6);



	return 0;
}
