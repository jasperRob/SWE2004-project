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
	int userinput, information, userchange;
	int ID;
	string overseas, test, status, usersymptom, address, name, symptom, location, dateentered, DOB, check, line;
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
				getline(cin, check);
				ID = stoi(check);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else if (information == 2) {
				cout << "Enter Name: ";
				getline(cin, name);
				cout << endl;
				cout << "Patient Information: " << name << endl;
				cout << endl;
			}
			else if (information == 3) {
				cout << "Enter Date of Birth (dd/mm/yyyy): ";
				getline(cin, DOB);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else if (information == 4) {
				cout << "Enter Address (number street town postcode): ";
				getline(cin, address);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else if (information == 5) {
				cout << "Overseas Travel? (yes/no): ";
				getline(cin, overseas);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else if (information == 6) {
				cout << "Enter Symptoms: ";
				getline(cin, symptom);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else if (information == 7) {
				cout << "Enter location Visited: ";
				getline(cin, location);
				cout << "Enter Date Visted: ";
				getline(cin, dateentered);
				cout << endl;
				cout << "Patient Information: ";
				cout << endl;
			}
			else {
				cout << "Invalid Input. Please Try Again" << endl;

			}
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
			//return to main menu//
		}

		//update patient details//
		else if (userinput == 5) {
			cout << "Which Patient Details Do You Wish To Update?" << endl;
			cout << "Please input Patient ID: ";
			getline(cin, check);
			ID = stoi(check);
			cout << endl;
			//find patient data//
			cout << "What Information Do You Wish To Change?" << endl;
			cout << "Enter '1' for Name:" << endl;
			cout << "Enter '2' for Address:" << endl;
			cout << "Enter '3' for Overseas Travel:" << endl;
			cout << "Enter '4' for Symptoms:" << endl;
			cout << "Enter '5' for High Risk COVID Area Location:" << endl;
			getline(cin, check);
			userchange = stoi(check);
			cout << endl;

			if (userchange == 1) {
				cout << "Enter New Name: ";
				getline(cin, name);
				cout << endl;
			}
			else if (userchange == 2) {
				cout << "Enter New Address (number street town postcode): ";
				getline(cin, address);
				cout << endl;
			}
			else if (userchange == 3) {
				cout << "Change Overseas Travel? (yes/no): ";
				getline(cin, overseas);
				cout << endl;
			}
			else if (userchange == 4) {
				cout << "Enter New Symptoms: ";
				getline(cin, symptom);
				cout << endl;
			}
			else if (userchange == 5) {
				cout << "Enter New location Visited: ";
				getline(cin, location);
				cout << endl;
			}
			else {
				cout << "Invalid Input, Goodbye!" << endl;
			}

			cout << "Updated Patient Information: ";
			cout << endl;
			cout << endl;
			cout << endl;

			//return to main menu//
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
