#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "State.h"
#include "Wallet.h"
#include "Wallet_exception.h"
#include "Wallet_commands.h"

using namespace std;

int main() {
	cout << "Would you like to load previous save? (Type \"yes\" or \"no\".)\n";
	string answer;
	cin >> answer;

	//wallet and account initialization info
	string user_name;
	double income=0;
	double savings=0;
	double debt=0;
	string prehistory; //only needed if loading from file

	if (answer == "yes") {
		ifstream file{ "saved_expenses_data.txt" };

		string line;
		string word_in_line;
		istringstream line_stream;
		
		//deal with previous history
		bool command_flag = false; //set to true if "command" word seen

		//extract wallet and account info from file
		while (getline(file, line)) {

			if (command_flag) {
				prehistory += line + '\n';
				continue;
			}

			line_stream.str(line); //set line_stream to line

			//look at each word in line
			while (line_stream >> word_in_line) {
				if (word_in_line == "balance:") {
					line_stream >> income;
					break;
				}
				if (word_in_line == "savings:") {
					line_stream >> savings;
					break;
				}
				if (word_in_line == "debt:") {
					line_stream >> debt;
					break;
				}
				if (word_in_line == "Username:") {
					line_stream >> user_name;
					break;
				}
				if (word_in_line == "Command") {
					command_flag = true;
					break;
				}
			}
			line_stream.clear();
		}
	}
	else {
		cout << "Please enter your account name: \n";
		cin >> user_name;

		while (std::cout << "Please enter your current balance: \n" && !(cin >> income)) {
			cin.clear(); //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			cout << "Invalid input; please try again.\n\n";
		}

		while (std::cout << "Please enter how much savings you have: \n" && !(cin >> savings)) {
			cin.clear(); //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			cout << "Invalid input; please try again.\n\n";
		}

		while (std::cout << "Please enter how much debt you have: \n" && !(cin >> debt)) {
			cin.clear(); //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			cout << "Invalid input; please try again.\n\n";
		}
	}
	Account my_account(user_name);
	if (answer == "yes") my_account.prepend_history(prehistory);
	Wallet my_wallet(abs(income), abs(savings), abs(debt)); // abs() gets rid of negative values

	while (true) {
		cout << "Please enter your command followed by the amount (type \"help\" for the commands): \n";

		string command;
		cin >> command;
		if (command == "help") {
			cout << "add_money - Adds money to your balance\n"
				<< "spend_money - Subtracts money from your account.\n"
				<< "transfer_to_savings - transfers the specified amount to your savings\n"
				<< "pay_off_debt_with_balance - pays off the specified amount of debt using your balance\n"
				<< "pay_off_debt_with_savings - pays off the specified amount of debt using your savings\n"
				<< "undo - undo last operation\n"
				<< "history - print your past activity\n"
				<< "info - print wallet info\n"
				<< "save - save all information to a file (in the same folder as executable)\n\n";
			continue;
		}
		if (command == "undo") { 
			my_account.undo_last();
			continue;
		}
		if (command == "history") {
			cout << "-----------------------------------\n";
			my_account.print_history(std::cout);
			cout << "-----------------------------------\n\n";
			continue;
		}
		if (command == "info") {
			cout << "-------------------------\n";
			my_wallet.print_info(std::cout);
			cout << "-------------------------\n\n";
			continue;
		}
		if (command == "save") {
			ofstream file("saved_expenses_data.txt");
			my_wallet.print_info(file);
			file << "Username: " << my_account.get_user_name() << '\n';
			my_account.print_history(file);
			continue;
		}
		double amount;
		cin >> amount;
		if (!cin) {
			cin.clear(); //clear bad input flag
			cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //discard input
			cout << "Invalid input\n\n";
			continue;
		}
		if (command == "add_money") my_account.execute_command(*new Add_money(amount, my_wallet));
		if (command == "spend_money")  my_account.execute_command(*new Spend_money(amount,my_wallet));
		if (command == "transfer_to_savings")  my_account.execute_command(*new Transfer_to_savings(amount,my_wallet));
		if (command == "pay_off_debt_with_balance")  my_account.execute_command(*new Pay_off_debt_with_balance(amount,my_wallet));
		if (command == "pay_off_debt_with_savings") my_account.execute_command(*new Pay_off_debt_with_savings(amount, my_wallet));
	}
}