//
// Created by ENVY on 4/23/2023.
//

#ifndef PHONE_BOOK_SUPPORTIVEFUNCTIONS_H
#define PHONE_BOOK_SUPPORTIVEFUNCTIONS_H

#include "string"
std::string to_upper(std::string);
int get_number_of_records(std::string);
int get_country_id(std::string);
int verify_country_code(std::string);
bool file_exists(std::string);

#endif //PHONE_BOOK_SUPPORTIVEFUNCTIONS_H
