#include "State.h"
#include "Wallet.h"
#include "Wallet_exception.h"

Wallet::Wallet(double balance, double savings, double debt) : has_balance{ *new HasBalance(*this) },
low_balance{ *new LowBalance(*this) }, has_saving_no_balance{ *new HasSavingNoBalance(*this) }, no_saving_no_balance{*new NoSavingNoBalance(*this)} {
	this->balance = balance;
	this->savings = savings;
	this->debt = debt;

	if (balance > 80) state = &has_balance;
	else if (balance <= 80 && balance > 0) state = &low_balance;
	else if (balance == 0 && savings > 0) state = &has_saving_no_balance;
	else state = &no_saving_no_balance;
};

void Wallet::add_money(double amount) {
	state->add_money(amount);
}

void Wallet::spend_money(double amount) {
	state->spend_money(amount);
}

void Wallet::transfer_to_savings(double amount) {
	state->transfer_to_savings(amount);
}

void Wallet::pay_off_debt_with_balance(double amount) {
	state->pay_off_debt_with_balance(amount);
}

void Wallet::pay_off_debt_with_savings(double amount) {
	state->pay_off_debt_with_savings(amount);
}

const State& Wallet::get_state() const{
	return *(this->state);
}

void Wallet::set_state(const State& state) {
	this->state = &state;
}

const State& Wallet::has_balance_state() const {
	return has_balance;
}
const State& Wallet::low_balance_state() const {
	return low_balance;
}
const State& Wallet::has_saving_no_balance_state() const {
	return has_saving_no_balance;
}
const State& Wallet::no_saving_no_balance_state() const {
	return no_saving_no_balance;
}

void Wallet::print_info(std::ostream& os) const{
	os << "Your balance: " << this->balance << '\n'
		<< "Your savings: " << this->savings << '\n'
		<< "Your debt: " << this->debt << '\n';
}

Wallet::~Wallet() {
	delete &has_balance;
	delete &low_balance;
	delete &has_saving_no_balance;
	delete &no_saving_no_balance;
}