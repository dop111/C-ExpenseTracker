#include <iostream>

class State;

//The "state machine"
class Wallet {

	//states
	const State& has_balance;
	const State& low_balance;
	const State& has_saving_no_balance;
	const State& no_saving_no_balance;

	const State* state;

public:
	double balance;
	double savings;
	double debt;

public:
	Wallet(double balance, double savings, double debt);

	void add_money(double amount);
	void spend_money(double amount);
	void transfer_to_savings(double amount);
	void pay_off_debt_with_balance(double amount);
	void pay_off_debt_with_savings(double amount);

	//get and set State
	const State& get_state() const;
	void set_state(const State&);

	//state getters (making states read only)
	const State& has_balance_state() const;
	const State& low_balance_state() const;
	const State& has_saving_no_balance_state() const;
	const State& no_saving_no_balance_state() const;

	void print_info(std::ostream&) const;

	~Wallet();
};