#pragma once
#include <string>

class Wallet_exception {
public:
	virtual std::string what() = 0;
};

class Invalid_amount : public Wallet_exception {
	std::string what() { return "Invalid amount."; }
};

class Insufficient_funds : public Wallet_exception {
	std::string what() { return "Insufficient funds."; }
};

class No_debt : public Wallet_exception {
	std::string what() { return "No debt to pay off."; }
};