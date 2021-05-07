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
		cout << "Enter '2' to Display High Risk Locations:" << endl;
		cout << "Enter '3' to Display the Symptoms of COVID:" << endl;
		cout << "Enter '4' to Display the COVID-19 Positive Patient Details:" << endl;
		cout << "Enter '5' to Update Patient Details:" << endl;
		cout << "Enter '6' to Quit:" << endl;
		getline(cin, check);
		if ((userinput = stoi(check)) == false) {
			while ((userinput = stoi(check)) == false) {
				cout << "Error please try again: ";
				getline(cin, check);
				cout << endl;
			}
		}
		userinput = stoi(check);
		cout << endl;

		//covid recommendation//
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

		//display high risk locations//
		else if (userinput == 2) {
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

		//display symptoms of covid//
		else if (userinput == 3) {
			cout << "The Symptoms of Covid are:" << endl;
			cout << endl;
			cout << endl;

			inFile.open(symptomlist);
			while (getline(inFile, line)) {
				cout << line << endl;
				cout << endl;
			}
			inFile.close();
			cout << endl;

			cout << "End of symptom list" << endl;

			cout << endl;
			cout << endl;
			//opens respective file and reads contents//

			//return to main menu//
		}

		//display covid positive patient details//
		else if (userinput == 4) {
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

		//update patient details//
		else if (userinput == 5) {

			/*cout << "Which Patient Details Do You Wish To Update?" << endl;
			cout << "Please input Patient ID: ";
			getline(cin, check);
			ID = stoi(check);
			cout << endl;
			//find patient data//
			oFile.open(patient, ios::app);

			cout << "Enter New Name: ";
			getline(cin, name);
			oFile << name << ' ';
			cout << endl;

			cout << "Enter date of birth(dd/mm/yyyy): ";
			getline(cin, name);
			oFile << name << ' ';
			cout << endl;

			cout << "Enter New Address (number street town postcode): ";
			getline(cin, address);
			oFile << address << ' ';
			cout << endl;

			cout << "Change Overseas Travel? (yes/no): ";
			getline(cin, overseas);
			oFile << overseas << ' ';
			cout << endl;

			cout << "Enter New Symptoms: ";
			getline(cin, symptom);
			oFile << symptom << ' ';
			cout << endl;

			cout << "Enter New High Risk location Visited: ";
			getline(cin, location);
			oFile << location << ' ';
			cout << endl;

			cout << "Enter new positive/negative status: ";
			getline(cin, result);
			oFile << result << '\n';
			cout << endl;

			cout << "Updated Patient Information: ";
			cout << "Name: " << name << endl;
			cout << "Address: " << address << endl;
			cout << "Overseas Travel: " << overseas << endl;
			cout << "Symptoms: " << symptom << endl;
			cout << "High risk location visited: " << location << endl;
			cout << "Test result: " << result << endl;
			cout << endl;
			cout << endl;
			cout << endl;

			//return to main menu//
			*/
		}

		//quit//
		else if (userinput == 6) {
			cout << "Thank You For Using Our COVID-19 Database Management System!" << endl;
			cout << "Goodbye!" << endl;
		}

		//invalid integer input//
		else {
			cout << "Invalid Input, Please Try Again: ";
			cin >> userinput;
			cout << endl;
			cout << endl;

			//return to main menu//
		}

	} while (userinput != 6);



	return 0;
}
