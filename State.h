class Wallet;

class State {
public:
	virtual void add_money(double amount) const = 0;
	virtual void spend_money(double amount) const = 0;
	virtual void transfer_to_savings(double amount) const = 0;
	virtual void pay_off_debt_with_balance(double amount) const = 0;
	virtual void pay_off_debt_with_savings(double amount) const = 0;
};

class HasBalance : public State {
	Wallet& wallet;

public:
	HasBalance(Wallet& w);
	void add_money(double amount) const;
	void spend_money(double amount) const;
	void transfer_to_savings(double amount) const;
	void pay_off_debt_with_balance(double amount) const;
	void pay_off_debt_with_savings(double amount) const;
};

class LowBalance : public State {
	Wallet& wallet;

public:
	LowBalance(Wallet& w);
	void add_money(double amount) const;
	void spend_money(double amount) const;
	void transfer_to_savings(double amount) const;
	void pay_off_debt_with_balance(double amount) const;
	void pay_off_debt_with_savings(double amount) const;
};

class HasSavingNoBalance : public State {
	Wallet& wallet;

public:
	HasSavingNoBalance(Wallet& w);
	void add_money(double amount) const;
	void spend_money(double amount) const;
	void transfer_to_savings(double amount) const;
	void pay_off_debt_with_balance(double amount) const;
	void pay_off_debt_with_savings(double amount) const;
};

class NoSavingNoBalance : public State {
	Wallet& wallet;

public:
	NoSavingNoBalance(Wallet& w);
	void add_money(double amount) const;
	void spend_money(double amount) const;
	void transfer_to_savings(double amount) const;
	void pay_off_debt_with_balance(double amount) const;
	void pay_off_debt_with_savings(double amount) const;
};
