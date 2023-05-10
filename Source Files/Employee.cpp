#include "../Header Files/Employee.h"
#include "iostream"


Employee::Employee() {
    this->role_ = "";   // intern does not have access to database
    this->name_ = ""; // put empty string instead of name_ in order not to get error
}

Employee::Employee (string r, string n) {
    this->role_ = to_upper(std::move(r));
    this->name_ = std::move(n);
}

Employee::~Employee() = default;

Owner::Owner() {
    try {
        if (Owner::num_of_owners_ == 0) {
            this->role_ = "OWNER";
            this->rights_ = {"DELETE", "DELETE_DATABASE", "UPDATE", "CREATE", "READ"};
            Owner::num_of_owners_++;
        }
        else
            throw MalformedOwner("Owner already authorized in the system!");
    }
    catch (MalformedOwner& e) {
        cout << "ERROR: " << e.what() << endl;
        exit(401);
    }
}


Owner::Owner(string n) : Employee("OWNER", std::move(n))
{
    try {
        if (Owner::num_of_owners_ == 0) {
            this->rights_ = {"DELETE", "DELETE_DATABASE", "UPDATE", "CREATE", "READ"};
            Owner::num_of_owners_++;
        }
        else
            throw MalformedOwner("Owner already authorized in the system!");
    }
    catch (MalformedOwner& e) {
        cout << "ERROR: " << e.what() << endl;
        exit(401);
    }
}


int Owner::num_of_owners_ = 0;

bool Owner::verify_permission(std::string p) {
    if(find(this->rights_.begin(), this->rights_.end(), p) == this->rights_.end())
        return false;
    else
        return true;
}

MalformedOwner::MalformedOwner(string errorMessage) : errorMessage_(std::move(errorMessage)) {}

const char *MalformedOwner::what() const noexcept {
    return this->errorMessage_.c_str();
}

Manager::Manager(std::string name) : Employee("MANAGER", std::move(name)) {
    this->rights_ = {"UPDATE", "CREATE", "READ"};
}

bool Manager::verify_permission(std::string p) {
    if(find(this->rights_.begin(), this->rights_.end(), p) == this->rights_.end())
        return false;
    else
        return true;
}


Intern::Intern(std::string name) : Employee("INTERN", std::move(name)) {}


bool Intern::verify_permission(std::string p) {
    return false;
}


Specialist::Specialist(std::string name) : Employee("SPECIALIST", std::move(name)) {
    this->rights_ = {"READ"};
}


bool Specialist::verify_permission(std::string p) {
    if(p == "READ")
        return true;
    return false;
}

const char *AuthError::what() const noexcept {
    return this->errorMessage_.c_str();
}


AuthError::AuthError(std::string errorMessage) {
    this->errorMessage_ = std::move(errorMessage);
}