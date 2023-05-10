//
// Created by ENVY on 4/30/2023.
//

#ifndef PHONE_BOOK_EMPLOYEE_H
#define PHONE_BOOK_EMPLOYEE_H

#include "string"
#include "SupportiveFunctions.h"
#include "exception"


using namespace std;

class Employee {
protected:
    string name_;
    string role_;
    vector<string> rights_{};
public:
    Employee ();
    Employee (string r, string n);

    [[maybe_unused]] virtual bool verify_permission(string p) = 0;
    virtual ~Employee();
};

class Owner: public Employee {
private:
    static int num_of_owners_;
public:
    Owner();
    explicit Owner(string n);
    bool verify_permission(string p) override;
};


class MalformedOwner: public exception {
private:
    string errorMessage_;
public:
    explicit MalformedOwner (string errorMessage);
    const char * what() const noexcept override;
};


class AuthError: public exception {
private:
    string errorMessage_;
public:
    explicit AuthError(string errorMessage);
    const char* what() const noexcept override;
};


class Manager : public Employee {
public:
    explicit Manager(string name = " ");
    bool verify_permission(std::string p) override;
};


class Intern : public Employee {
public:
    explicit Intern(string name = " ");
    bool verify_permission(std::string p) override;
};


class Specialist : public Employee {
public:
    explicit Specialist(string name = " ");
    bool verify_permission(std::string p) override;
};

#endif //PHONE_BOOK_EMPLOYEE_H
