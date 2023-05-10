#ifndef PHONE_BOOK_COUNTRY_H
#define PHONE_BOOK_COUNTRY_H

#include "string"
#include "optional"
#include "vector"
#include "fstream"
#include "sstream"

using namespace std;

class Country{
private:
    string name, country_number_code;
    int max_digits, id;
public:
    explicit Country(int = 232);
    string getCountryName() const;
    int getCountryId() const;
    string getCountryCode() const;
    int getCountryMaxDigits() const;
    friend optional<Country> verify_country_code(string code);
    Country& operator=(Country c);
};

#endif //PHONE_BOOK_COUNTRY_H
