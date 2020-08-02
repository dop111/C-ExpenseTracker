#include "Wallet_commands.h"
#include "Wallet.h"
#include "Wallet_exception.h"
#include <iostream>
#include <iomanip>
#include <string>

Add_money::Add_money(double amount, Wallet& wallet) : amount{ amount }, wallet{ wallet }, original_wallet_state{wallet.get_state()} 
{};

void Add_money::doit() const{
	wallet.add_money(amount);
}
void Add_money::undoit() const{
	wallet.balance -= amount;
	wallet.set_state(original_wallet_state);
}

std::string Add_money::description() const {
	return "Add money";
}

double Add_money::get_amount() const {
	return amount;
};

Spend_money::Spend_money(double amount, Wallet& wallet) : amount{ amount }, wallet{ wallet }, original_wallet_state{ wallet.get_state() } {
	balance = wallet.balance;
	savings = wallet.savings;
	debt = wallet.debt;
};

void Spend_money::doit() const{
	wallet.spend_money(amount);
}

void Spend_money::undoit() const{
	wallet.balance = balance;
	wallet.savings = savings;
	wallet.debt = debt;
	wallet.set_state(original_wallet_state);
}

std::string Spend_money::description() const {
	return "Spend money";
}

double Spend_money::get_amount() const {
	return amount;
};

Transfer_to_savings::Transfer_to_savings(double amount, Wallet& wallet) : amount{ amount }, wallet{ wallet }, original_wallet_state{ wallet.get_state() } 
{};

void Transfer_to_savings::doit() const{
	wallet.transfer_to_savings(amount);
}
void Transfer_to_savings::undoit() const{
	wallet.balance += amount;
	wallet.savings -= amount;
	wallet.set_state(original_wallet_state);
}

std::string Transfer_to_savings::description() const {
	return "Transfer to savings";
}

double Transfer_to_savings::get_amount() const {
	return amount;
};

Pay_off_debt_with_balance::Pay_off_debt_with_balance(double amount, Wallet& wallet) : amount{ amount }, wallet{ wallet }, original_wallet_state{ wallet.get_state() } 
{};

void Pay_off_debt_with_balance::doit() const{
	wallet.pay_off_debt_with_balance(amount);
}
void Pay_off_debt_with_balance::undoit() const{
	wallet.balance += amount;
	wallet.debt += amount;
	wallet.set_state(original_wallet_state);
}

std::string Pay_off_debt_with_balance::description() const {
	return "Pay off debt with balance";
}

double Pay_off_debt_with_balance::get_amount() const {
	return amount;
};

Pay_off_debt_with_savings::Pay_off_debt_with_savings(double amount, Wallet& wallet) : amount{ amount }, wallet{ wallet }, original_wallet_state{ wallet.get_state() } 
{};

void Pay_off_debt_with_savings::doit() const{
	wallet.pay_off_debt_with_savings(amount);
}
void Pay_off_debt_with_savings::undoit() const{
	wallet.savings += amount;
	wallet.debt += amount;
	wallet.set_state(original_wallet_state);
}

std::string Pay_off_debt_with_savings::description() const {
	return "Pay off debt with savings";
}

double Pay_off_debt_with_savings::get_amount() const {
	return amount;
};

Account::Account(std::string user_name) : user_name{ user_name } {};

void Account::execute_command(const ICommand& command) {
	try {
		command.doit();
		commands.push_back(&command);
	}
	catch (Wallet_exception& e) {
		delete &command;
		std::cerr << "Error: " << e.what() << "\n\n";
	}
}

void Account::prepend_history(std::string s) {
	prehistory += s;
}

void Account::print_history(std::ostream& os) const {
	os << std::setw(26) << std::left << "Command" << "Amount\n";
	os << prehistory;
	for (const ICommand* c : commands) {
		os << std::setw(26) << std::left << c->description()
		<< c->get_amount() << '\n';
	}
}

void Account::undo_last() {
	if (commands.size() > 0) {
		commands.back()->undoit();
		delete commands.back();
		commands.pop_back();
	}
}

std::string Account::get_user_name() const {
	return user_name;
}

Account::~Account() {
	for (const ICommand* c : commands) {
		delete &c;
	}
}