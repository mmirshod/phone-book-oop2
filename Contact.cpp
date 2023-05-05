#include "Contact.h"

#include <utility>
#include "iomanip"
#include "iostream"

Contact::Contact() = default;

ostream& operator<<(std::ostream &out, const Contact& c) {
    cout << setfill(' ') << left << setw(8) << c.id << "|";
    cout << left << setw(22) << c.f_name << "|";
    cout << left << setw(22) << c.l_name << "|";
    cout << left << setw(31) << c.tel_num << "|";
    cout << left << setw(19) << c.country.getCountryName() << "|";
    cout << left << setw(17) << c.position_ << "|" << endl;
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setw(22) << "" << "|";
    cout << setw(22) << "" << "|";
    cout << setw(31) << "" << "|";
    cout << setw(19) << "" << "|";
    cout << setw(17) << "" << "|" << endl;
    return out;
}


int Contact::get_id() const {
    return this->id;
}

void Contact::set_first_name(std::string name) {
    this->f_name = std::move(name);
}


void Contact::set_last_name(std::string surname) {
    this->l_name = std::move(surname);
}


void Contact::set_tel_num(std::string number) {
    this->tel_num = std::move(number);
}


void Contact::set_position(std::string position) {
    this->position_ = std::move(position);
}


string Contact::get_first_name() {
    return this->f_name;
}

string Contact::get_last_name() {
    return this->l_name;
}


Country Contact::get_country() {
    return this->country;
}


string Contact::get_tel_num() {
    return this->tel_num;
}


string Contact::get_position() const {
    return this->position_;
}
