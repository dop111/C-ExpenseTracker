#pragma once
#include <vector>
#include <string>
#include <iostream>

class Wallet;
class State;

class ICommand {
public:
	virtual void doit() const = 0;
	virtual void undoit() const = 0;
	virtual std::string description() const = 0;
	virtual double get_amount() const = 0;
};

class Add_money : public ICommand {
	double amount;
	Wallet& wallet;
	const State& original_wallet_state; //for undo

public:
	Add_money(double amount, Wallet& wallet);

	void doit() const;
	void undoit() const;
	std::string description() const;
	double get_amount() const;
};

class Spend_money : public ICommand {
	double amount;
	Wallet& wallet;
	const State& original_wallet_state;
	double balance, savings, debt; //for undo
public:
	Spend_money(double amount, Wallet& wallet);

	void doit() const;
	void undoit() const;
	std::string description() const;
	double get_amount() const;
};

class Transfer_to_savings : public ICommand {
	double amount;
	Wallet& wallet;
	const State& original_wallet_state;
public:
	Transfer_to_savings(double amount, Wallet& wallet);

	void doit() const;
	void undoit() const;
	std::string description() const;
	double get_amount() const;
};

class Pay_off_debt_with_balance : public ICommand {
	double amount;
	Wallet& wallet;
	const State& original_wallet_state;
public:
	Pay_off_debt_with_balance(double amount, Wallet& wallet);

	void doit() const;
	void undoit() const;
	std::string description() const;
	double get_amount() const;
};

class Pay_off_debt_with_savings : public ICommand {
	double amount;
	Wallet& wallet;
	const State& original_wallet_state;
public:
	Pay_off_debt_with_savings(double amount, Wallet& wallet);

	void doit() const;
	void undoit() const;
	std::string description() const;
	double get_amount() const;
};

class Account {
	std::string user_name;
	std::vector<const ICommand*> commands;
	std::string prehistory; //previous history (normally from file)

public:
	Account(std::string user_name);

	void execute_command(const ICommand& command);
	void undo_last();
	
	void prepend_history(std::string); //prehistory setter
	void print_history(std::ostream&) const;

	std::string get_user_name() const;

	~Account();
};