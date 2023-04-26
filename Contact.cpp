//
// Created by ENVY on 4/26/2023.
//

#include "Contact.h"
#include "iomanip"
#include "iostream"

ostream& operator<<(std::ostream &out, Contact c) {
    cout << setfill(' ') << left << setw(8) << 1 << "|";
    cout << left << setw(22) << c.f_name << "|";
    cout << left << setw(22) << c.l_name << "|";
    cout << left << setw(31) << c.tel_num << "|";
    cout << left << setw(19) << c.country.getCountryName() << "|";
    cout << left << setw(17) << c.category << "|" << endl;
    cout << setfill('-') << setw(8) << "" << "|";
    cout << setw(22) << "" << "|";
    cout << setw(22) << "" << "|";
    cout << setw(31) << "" << "|";
    cout << setw(19) << "" << "|";
    cout << setw(17) << "" << "|" << endl;
}
