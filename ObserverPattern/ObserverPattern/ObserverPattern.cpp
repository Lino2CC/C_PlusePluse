#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Observer
{
public:
	string name;

	virtual void update(string state, string from) {
		cout << "observer update [" << this->name << "], " << state << " " << from << "\n" << endl;
	}

	Observer(string name) {
		this->name = name;
	}
};

class Employee : public Observer
{
public:
	string role;

	virtual void update(string state, string from) override {
		cout << "update status - employee name [" << this->name << "], employee role[" << this->role << "], " << " machine update state: " << state << ", machine name: " << from << "\n" << endl;
	}

	Employee(string name, string role) : Observer(name) {
		this->role = role;
	}
};


class Subject
{
public:
	string state;

	void setState(string s) {
		this->state = s;
	}
	void attach(Observer* o) {
		observers.push_back(o);
	}

	// let inherit instance
	virtual void notifyAllObservers() = 0;
	~Subject() {
		// release memory
		this->observers.clear();
	}
protected:
	std::vector<Observer*> observers;
};

class Machine : public Subject
{
public:
	string name;

	Machine(string name) {
		this->name = name;
	}

	void notifyAllObservers() override {
		// get size to print all machine state & name
		size_t size = this->observers.size();

		for (int idx = 0; idx < size; idx++) {
			this->observers[idx]->update(this->state, this->name);
		}
	}
};


int main(void)
{
	// machine register name
	Machine machine1("machine A");
	Machine machine2("machine B");

	// employee register name & role
	Employee* employee1 = new Employee("John", "A");
	Employee* employee2 = new Employee("Marry", "B");
	Employee* employee3 = new Employee("Ketty", "B");
	Employee* employee4 = new Employee("Andy", "A");
	Employee* employee5 = new Employee("Ryan", "A");

	// employee register machine
	machine1.attach((Observer*)employee1);
	machine1.attach((Observer*)employee4);
	machine1.attach((Observer*)employee5);

	machine2.attach((Observer*)employee2);
	machine2.attach((Observer*)employee3);

	/* Test result */

	// to modify machine 1 state
	machine1.setState("IDLE");
	machine1.notifyAllObservers();

	// to modify machine 1 state
	machine1.setState("PRODUCING");
	machine1.notifyAllObservers();

	// to modify machine 2 state
	machine2.setState("STARVED");
	machine2.notifyAllObservers();

	// to modify machine 2 state
	machine2.setState("PRODUCING");
	machine2.notifyAllObservers();

	return EXIT_SUCCESS;
}
