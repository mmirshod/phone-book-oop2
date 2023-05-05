//
// Created by ENVY on 4/23/2023.
//

#ifndef PHONE_BOOK_SUPPORTIVEFUNCTIONS_H
#define PHONE_BOOK_SUPPORTIVEFUNCTIONS_H


#include "string"
#include "Phonebook.h"

std::string to_upper(std::string);
int get_number_of_records(const std::string&);
int make_choice_main_menu();
optional <Contact> find_contact(const std::string& number, Phonebook& p);
int make_choice_update_contact();
int make_choice_select_role();
bool check_password(const string& p, const string& r);

#endif //PHONE_BOOK_SUPPORTIVEFUNCTIONS_H
