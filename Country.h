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
    Country(int = 232);
    string getCountryName() const;
    int getCountryId() const;
    string getCountryCode() const;
    int getCountryMaxDigits() const;
    friend optional<Country> verify_country_code(string code);
    Country& operator=(optional<Country> c);
};


optional<Country> verify_country_code(string code) {
    string temp, word;
    vector<string> countries;
    ifstream file(R"(D:\Mirshod\IUT\OOP2\phone-book\countries.csv)");

    while(file >> temp) {
        countries.clear();

        stringstream s(temp);
        while(getline(s, word, ','))
            countries.push_back(word);
        if(code == countries[2]) {
            return Country(stoi(countries[0]));
        }
    }
    return nullopt;
}

#endif //PHONE_BOOK_COUNTRY_H
