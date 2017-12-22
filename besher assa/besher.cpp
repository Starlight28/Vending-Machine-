/*************************************
Program: BESHER.cpp
Course: PROGRAMMING FUNDAMENTALS
Year: 2014/15 Trimester 2
Name: MAHMOD BESHER ALREZ
ID: 1131122791
Lecture: TT02
Lab: TT02
EMAil:  m.bashora.s_95@hotmail.com
Phone: 01111372415
*************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string drinkNames[10]; // names of drinks
double drinkPrices[10]; // price of drinks
int drinkUnits[10]; // unit of drinks

int NUMBER_OF_TYPES_OF_DRINKS = 3; // default is 3

int MAX_CANS_OF_DRINKS = 5;

//how many cash and coins (denomination) in the machine
int Ringgit20 = 0;
int Ringgit10 = 0;
int Ringgit5 = 0;
int Ringgit1 = 10;
int Ringgit050 = 10;
int Ringgit020 = 10;
int Ringgit010 = 0;
// for back-up purpose
int bRinggit20;
int bRinggit10;
int bRinggit5;
int bRinggit1;
int bRinggit050;
int bRinggit020;
int bRinggit010;

//how much the user paid
double amountpaid = 0.00;
double balance;
double amounthastobepaid = 0.00;
char choiceofpayment;

// the choise of user
int userdrink; // change from char to int
int howmanycanstobuy;

// denomination to be returned/dispensed to user
int rm20 = 0;
int rm10 = 0;
int rm5 = 0;
int rm1 = 0;
int rm050 = 0;
int rm020 = 0;
int rm010 = 0;

int transactionNumber = 1; // start from 1

// function prototypes
string readPasswordFromFile();
void showAdminMenu();
void showAdminMenu2();
void showMenu();
void showMenu2();
void calculateBalance();
void showDispense();
void clearTransactionLog();
void saveTransaction();
void revertDenomination();

int main()
{
	// default, 3 drinks
	drinkNames[0] = "Soda";
	drinkPrices[0] = 0.80;
	drinkUnits[0] = 0;
	drinkNames[1] = "Orange";
	drinkPrices[1] = 1.00;
	drinkUnits[1] = 4;
	drinkNames[2] = "Lychee";
	drinkPrices[2] = 1.40;
	drinkUnits[2] = 3;

	// to show fractions
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(2);

	showAdminMenu();

	// back-up the number of denomination
	bRinggit20 = Ringgit20; bRinggit10 = Ringgit10;
	bRinggit5 = Ringgit5; bRinggit1 = Ringgit1;
	bRinggit050 = Ringgit050; bRinggit020 = Ringgit020; bRinggit010 = Ringgit010;

	while (1)
	{
		showMenu();
		showMenu2();
		cout << "payment returned RM" << balance << endl << endl;
		calculateBalance();
		showDispense();
		cout << "\nbalance is now = RM" << balance << "\n\n";

		// if balance to user is zero, then the transaction is successful
		if (balance <= 0.0)
		{
		}
		else // transaction is not successful
		{
			revertDenomination();
		}

        saveTransaction();
		transactionNumber++;

		// reset
		rm20 = 0, rm10 = 0, rm5 = 0, rm1 = 0, rm050 = 0, rm020 = 0, rm010 = 0;
		amountpaid = 0.00;
		balance = 0.00;
		amounthastobepaid = 0.00;

	}

	return 0;
}

string readPasswordFromFile()
{
	ifstream ifstream1;
	ifstream1.open("password.txt");

	string thepassword;
	getline(ifstream1, thepassword);

	return thepassword;

}
void writePasswordToFile(string password)
{
	ofstream ofstream1;
	ofstream1.open("password.txt");

	ofstream1 << password;

	return;
}

void showAdminMenu()
{
	string thepassword;
	thepassword = readPasswordFromFile(); // read password from password.txt

	cout << "Enter as admin? (Y/N): ";
	char input;
	cin >> input;
	cin.ignore(100, '\n');

	if (input == 'Y' || input == 'y')
	{
		cout << "Enter password: ";
		string inputpassword;
		cin >> inputpassword;

		if (inputpassword == thepassword)
		{
			showAdminMenu2();
		}
		else
		{
			cout << "Sorry. Wrong password\n";
		}
	}

	return;
}

void showAdminMenu2()
{
	int iMenu = 0;

	while (1)
	{
		cout << "\nAdministrator Menu\n";
		cout << "##################\n\n";
		cout << "1. Set the maximum number of cans which can be bought per transaction\n";
		cout << "2. Set the initial amount of each denomination\n";
		cout << "3. Set drinks names, prices and initial units of cans\n";
		cout << "4. Change password\n";
		cout << "5. Clear the transaction log\n";
		cout << "\nChoose menu (1 - 5) or else to exit: ";
		cin >> iMenu;

		if (iMenu == 1)
		{
			while (1)
			{
				cout << "Set the maximum number of cans which can be bought per transaction (maximum five): ";
				cin >> MAX_CANS_OF_DRINKS;
				if (MAX_CANS_OF_DRINKS > 0 && MAX_CANS_OF_DRINKS < 6)
					break;
			}
		}
		else if (iMenu == 2)
		{
			cout << "Set the initial amount of each denomination as follows: \n";
			cout << "RM20: ";
			cin >> Ringgit20;
			cout << "RM10: ";
			cin >> Ringgit10;
			cout << "RM5: ";
			cin >> Ringgit5;
			cout << "RM1: ";
			cin >> Ringgit1;
			cout << "50cent: ";
			cin >> Ringgit050;
			cout << "20cent: ";
			cin >> Ringgit020;
			cout << "10cent: ";
			cin >> Ringgit010;
		}
		else if (iMenu == 3)
		{
			int iHowManyTypesOfDrinks;
			cout << "How many types of drinks to set? (Max 10) : ";
			cin >> iHowManyTypesOfDrinks;
			for (int i = 0; i<iHowManyTypesOfDrinks; i++)
			{
				cout << "Drink #" << i + 1 << " Name: ";
				cin >> drinkNames[i];

				cout << "Drink #" << i + 1 << " Price (RM): ";
				cin >> drinkPrices[i];

				cout << "Drink #" << i + 1 << " Initial Units: ";
				cin >> drinkUnits[i];

				cout << endl;
			}
		}
		else if (iMenu == 4)
		{
			string password;
			cout << "Set new password: ";
			cin >> password;
			writePasswordToFile(password);
		}
		else if (iMenu == 5)
		{
			char cInput;
			cout << "Are you sure to clear the transaction log? (Y/N): ";
			cin >> cInput;
			if (cInput == 'Y' || cInput == 'y')
				clearTransactionLog();
		}
		else
			break; // break this while(1) loop
	}

	return;
}

void showMenu()
{
	cout << "\n\n";
	cout << "Choice\tDrink Name\t\tPrice\n\n";

	for (int i = 0; i< NUMBER_OF_TYPES_OF_DRINKS; i++)
	{
		cout << i + 1 << "\tMMU " << drinkNames[i] << "\t\tRM" << drinkPrices[i] << endl;
	}
	cout << "\nPurchase (1 to " << NUMBER_OF_TYPES_OF_DRINKS << ") => ";
	cin >> userdrink;
	cout << "How many cans to buy? (Maximum is " << MAX_CANS_OF_DRINKS << ")=> ";
	cin >> howmanycanstobuy;

}

void showMenu2()
{
	while (1)
	{
		amounthastobepaid = drinkPrices[userdrink - 1] * howmanycanstobuy;
		if (drinkUnits[userdrink - 1] == 0)
		{
			cout << "Choice\tDrink Name\t\tPrice\n\n";

			for (int i = 0; i< NUMBER_OF_TYPES_OF_DRINKS; i++)
			{
				cout << i + 1 << "\tMMU " << drinkNames[i] << "\t\tRM" << drinkPrices[i];
				if (drinkUnits[i] == 0)
					cout << "\t[Sold Out]";
				cout << endl;
			}
			cout << "Purchase (1 to " << NUMBER_OF_TYPES_OF_DRINKS << ") => ";
            cin >> userdrink;
            cout << "How many cans to buy? (Maximum is " << MAX_CANS_OF_DRINKS << ")=> ";
            cin >> howmanycanstobuy;
		}
		else
		{
			cout << "Purchase of MMU " << drinkNames[userdrink - 1] << "\tRM" << drinkPrices[userdrink - 1] << " x " << howmanycanstobuy << " = " << "RM" << amounthastobepaid << endl;
			cout << "Amount paid\t\t\t     RM" << amountpaid << endl;
			cout << "Insert" << endl;
			cout << "a) RM20" << endl;
			cout << "b) RM10" << endl;
			cout << "c) RM5" << endl;
			cout << "d) RM1" << endl;
			cout << "e) RM0.50" << endl;
			cout << "f) RM0.20" << endl;
			cout << "g) RM0.10" << endl;
			cout << "pay (a to g) =>";
			cin >> choiceofpayment;

			switch (choiceofpayment)
			{
			case 'a':
				if (Ringgit20<20)
				{
					amountpaid = amountpaid + 20;
					Ringgit20++;
				}
				break;
			case 'b':
				if (Ringgit10<20)
				{
					amountpaid = amountpaid + 10;
					Ringgit10++;
				}
				break;
			case 'c':
				if (Ringgit5<20)
				{
					amountpaid = amountpaid + 5;
					Ringgit5++;
				}
				break;
			case 'd':
				if (Ringgit1<20)
				{
					amountpaid = amountpaid + 1;
					Ringgit1++;
				}
				break;
			case 'e':
				if (Ringgit050<20)
				{
					amountpaid = amountpaid + 0.50;
					Ringgit050++;
				}
				break;
			case 'f':
				if (Ringgit020<20)
				{
					amountpaid = amountpaid + 0.20;
					Ringgit020++;
				}
				break;
			case 'g':
				if (Ringgit010<20)
				{
					amountpaid = amountpaid + 0.10;
					Ringgit010++;
				}
				break;
			}
		}

		if (amountpaid >= amounthastobepaid)
		{
			balance = amountpaid - amounthastobepaid;
			break;
		}

	}
}

void calculateBalance()
{
	while (balance >= 20)
	{
		rm20++;
		balance = balance - 20;
	}
	while (balance >= 10)
	{
		rm10++;
		balance = balance - 10;
	}
	while (balance >= 5)
	{
		rm5++;
		balance = balance - 5;
	}
	while (balance >= 1)
	{
		rm1++;
		balance = balance - 1.00;
	}
	while (balance >= 0.50)
	{
		rm050++;
		balance = balance - 0.50;
	}
	while (balance > 0.19)
	{
		rm020++;
		balance = balance - 0.20;
	}
	while (balance > 0.09)
	{
		rm010++;
		balance = balance - 0.10;
	}
	return;
}

void showDispense()
{
	if (rm20 != 0)
		cout << "RM20.00 x " << rm20 << endl;
	if (rm10 != 0)
		cout << "RM10.00 x " << rm10 << endl;
	if (rm5 != 0)
		cout << "RM5.00 x " << rm5 << endl;
	if (rm1 != 0)
		cout << "RM1.00 x " << rm1 << endl;
	if (rm050 != 0)
		cout << "RM0.50 x " << rm050 << endl;
	if (rm020 != 0)
		cout << "RM0.20 x " << rm020 << endl;
	if (rm010 != 0)
		cout << "RM0.10 x " << rm010 << endl;

	return;
}

void clearTransactionLog()
{
	ofstream ofstream1;
	ofstream1.open("log.csv");
	ofstream1 << "";

	ofstream1.close();

	return;
}

void saveTransaction()
{
	ofstream ofstream1;
	ofstream1.open("log.csv", ios::app);
    ofstream1 << transactionNumber << ",";
	ofstream1 << drinkNames[userdrink - 1] << ",";
	ofstream1 << drinkPrices[userdrink - 1] << ",";
	ofstream1 << howmanycanstobuy << ",";
	ofstream1 << amountpaid << ",";
	// to count number of changes dispensed
	int changedispensed = rm20 + rm10 + rm5 + rm1 + rm050 + rm020 + rm010;
	ofstream1 << changedispensed << ",";
	ofstream1 << Ringgit20 << ",";
	ofstream1 << Ringgit10 << ",";
	ofstream1 << Ringgit5 << ",";
	ofstream1 << Ringgit1 << ",";
	ofstream1 << Ringgit050 << ",";
	ofstream1 << Ringgit020 << ",";
	ofstream1 << Ringgit010 << endl;
	ofstream1.close();

	return;
}

void revertDenomination()
{
	Ringgit20 = bRinggit20; Ringgit10 = bRinggit10;
	Ringgit5 = bRinggit5; Ringgit1 = bRinggit1;
	Ringgit050 = bRinggit050; Ringgit020 = bRinggit020; Ringgit010 = bRinggit010;

	return;
}
