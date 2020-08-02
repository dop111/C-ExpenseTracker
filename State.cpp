#include "State.h"
#include "Wallet.h"
#include "Wallet_exception.h"
#include <iostream>
#include <cmath>

HasBalance::HasBalance(Wallet& w) : wallet{ w } {};
void HasBalance::add_money(double amount) const { 
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance += amount; 
}
void HasBalance::spend_money(double amount) const {

	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance -= amount;

	//state transition if needed
	if (wallet.balance <= 80 && wallet.balance > 0) {
		wallet.set_state( wallet.low_balance_state());
		std::cout << "Your balance is now low.\n\n";
	}
	else if (wallet.balance <= 0 && wallet.savings >= abs(wallet.balance)) {
		wallet.savings -= abs(wallet.balance);
		wallet.balance = 0;
		wallet.set_state((wallet.savings > 0) ? wallet.has_saving_no_balance_state() : wallet.no_saving_no_balance_state());

		if (&wallet.get_state() == &wallet.has_saving_no_balance_state()) std::cout << "No balance left.\n\n";
		else std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
	else if (wallet.balance <= 0 && wallet.savings < abs(wallet.balance)) {
		wallet.balance += wallet.savings;
		wallet.savings = 0;
		wallet.debt += abs(wallet.balance);
		wallet.balance = 0;
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "Your debt has been increased. No balance and no savings left.\n\n";
	}

};
void HasBalance::transfer_to_savings(double amount) const
{
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.balance) { wallet.balance -= amount; wallet.savings += amount; }
	else throw Insufficient_funds();

	//state transition if needed
	if (wallet.balance == 0) {
		wallet.set_state( wallet.has_saving_no_balance_state());
		std::cout << "No balance left.\n\n";
		return;
	}
	if (wallet.balance <= 80) {
		wallet.set_state(wallet.low_balance_state());
		std::cout << "Your balance is now low.\n\n";
	}
	
};
void HasBalance::pay_off_debt_with_balance(double amount) const
{
	if (wallet.debt == 0) { throw No_debt(); }
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.balance && amount <=wallet.debt) { wallet.balance -= amount; wallet.debt -= amount; }
	else if (amount > wallet.balance) throw Insufficient_funds();
	else if (amount > wallet.debt) throw Invalid_amount();

	//state transition if needed
	if (wallet.balance <= 80) {
		wallet.set_state( wallet.low_balance_state());
		std::cout << "Your balance is now low.\n\n";
	}
	if (wallet.balance == 0 && wallet.savings > 0) {
		wallet.set_state( wallet.has_saving_no_balance_state());
		std::cout << "No balance left.\n\n";
	}

	if (wallet.balance == 0 && wallet.savings == 0) {
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
};
void HasBalance::pay_off_debt_with_savings(double amount) const
{
	if (wallet.debt == 0) { throw No_debt(); }
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.savings && amount <= wallet.debt) { wallet.savings -= amount; wallet.debt -= amount; }
	else if (amount > wallet.savings) throw Insufficient_funds();
	else if (amount > wallet.debt) throw Invalid_amount();
};

LowBalance::LowBalance(Wallet& w) : wallet{ w } {};
void LowBalance::add_money(double amount) const {
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance += amount;

	//state transition if needed
	if (wallet.balance > 80) {
		wallet.set_state( wallet.has_balance_state());
		std::cout << "Your balance is no longer low.Hooray!\n\n";
	}

}
void LowBalance::spend_money(double amount) const
{
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance -= amount;
	if (wallet.balance > 0) { std::cout << "Warning: Your balance is low.\n\n"; return; }

	//state transition if needed
	if (wallet.balance <= 0 && wallet.savings >= abs(wallet.balance)) {
		wallet.savings -= abs(wallet.balance);
		wallet.balance = 0;
		wallet.set_state((wallet.savings > 0) ? wallet.has_saving_no_balance_state() : wallet.no_saving_no_balance_state());

		if (&wallet.get_state() == &wallet.has_saving_no_balance_state()) std::cout << "No balance left.\n\n";
		else std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
	else if (wallet.balance <= 0 && wallet.savings < abs(wallet.balance)) {
		wallet.balance += wallet.savings;
		wallet.savings = 0;
		wallet.debt += abs(wallet.balance);
		wallet.balance = 0;
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "Your debt has been increased. No balance and no savings left.\n\n";
	}
};
void LowBalance::transfer_to_savings(double amount) const
{
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.balance) {
		std::cout << "Warning: Your balance is low.\n\n";
		wallet.balance -= amount;
		wallet.savings += amount;
	}
	else throw Insufficient_funds();

	//state transition if needed
	if (wallet.balance == 0) {
		wallet.set_state(wallet.has_saving_no_balance_state());
		std::cout << "No balance left.\n\n";
	}
};
void LowBalance::pay_off_debt_with_balance(double amount) const
{
	if (wallet.debt == 0) { throw No_debt(); }
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.balance && amount <= wallet.debt) { 
		std::cout << "Warning: Your balance is low.\n\n";
		wallet.balance -= amount; 
		wallet.debt -= amount; 
	}
	else if (amount > wallet.balance) throw Insufficient_funds();
	else if (amount > wallet.debt) throw Invalid_amount();

	//state transition if needed
	if (wallet.balance == 0 && wallet.savings > 0) {
		wallet.set_state( wallet.has_saving_no_balance_state());
		std::cout << "No balance left.\n\n";
	}

	if (wallet.balance == 0 && wallet.savings == 0) {
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
};
void LowBalance::pay_off_debt_with_savings(double amount) const
{
	if (wallet.debt == 0) { throw No_debt(); }
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.savings && amount <= wallet.debt) { wallet.savings -= amount; wallet.debt -= amount; }
	else if (amount > wallet.savings) throw Insufficient_funds();
	else if (amount > wallet.debt) throw Invalid_amount();
};

HasSavingNoBalance::HasSavingNoBalance(Wallet& w) : wallet{ w } {};
void HasSavingNoBalance::add_money(double amount) const {
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance += amount;
	
	//state transition if needed
	if (amount > 80) wallet.set_state (wallet.has_balance_state());
}
void HasSavingNoBalance::spend_money(double amount) const
{
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.savings -= amount;

	//state transition if needed
	if (wallet.savings == 0) {
		wallet.set_state(wallet.no_saving_no_balance_state());
		std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
	else if (wallet.savings < 0) {
		wallet.debt += abs(wallet.savings);
		wallet.savings = 0;
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "No balance and no savings left. Your debt has been increased.\n\n";
	}
};
void HasSavingNoBalance::transfer_to_savings(double amount) const
{
	throw Insufficient_funds();
};
void HasSavingNoBalance::pay_off_debt_with_balance(double amount) const
{
	throw Insufficient_funds();
};
void HasSavingNoBalance::pay_off_debt_with_savings(double amount) const
{
	if (wallet.debt == 0) { throw No_debt(); }
	if (amount <= 0) { throw Invalid_amount(); }

	if (amount <= wallet.savings && amount <= wallet.debt) { wallet.savings -= amount; wallet.debt -= amount; }
	else if (amount > wallet.savings) throw Insufficient_funds();
	else if (amount > wallet.debt) throw Invalid_amount();

	//state transition if needed
	if (wallet.savings == 0) {
		wallet.set_state( wallet.no_saving_no_balance_state());
		std::cout << "No balance and no savings left. Spending money will result in debt.\n\n";
	}
};

NoSavingNoBalance::NoSavingNoBalance(Wallet& w) : wallet{ w } {};
void NoSavingNoBalance::add_money(double amount) const {
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.balance += amount;
	
	//state transition if needed
	if (amount <= 80) {
		wallet.set_state(wallet.low_balance_state());
	}
	else wallet.set_state(wallet.has_balance_state());

	std::cout << "You have increased your balance! Woohoo!\n\n";
}
void NoSavingNoBalance::spend_money(double amount) const
{
	if (amount <= 0) { throw Invalid_amount(); }
	wallet.debt += amount;
	std::cout << "No balance and no savings left. Your debt has been increased.\n\n";
};
void NoSavingNoBalance::transfer_to_savings(double amount) const
{
	throw Insufficient_funds();
};
void NoSavingNoBalance::pay_off_debt_with_balance(double amount) const
{
	throw Insufficient_funds();
};
void NoSavingNoBalance::pay_off_debt_with_savings(double amount) const
{
	throw Insufficient_funds();
};