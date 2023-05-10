#include "../Header Files/Country.h"
#include "vector"
#include "sstream"
using namespace std;

optional<Country> verify_country_code(string code) {
    string temp, word;
    vector<string> countries;
    ifstream file(R"(D:\Mirshod\IUT\OOP2\phone-book\Resource Files\countries.csv)");

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

Country::Country(int id) {
    ifstream f(R"(D:\Mirshod\IUT\OOP2\phone-book\Resource Files\countries.csv)");
    vector <string> data;
    string line, word;

    while(getline(f, line)) {
        data.clear();

        stringstream ss(line);
        while(getline(ss, word, ','))
            data.push_back(word);

        if(id == stoi(data[0])) {
            this->id = id;
            this->name = data[1];
            this->country_number_code = data[2];
            this->max_digits = stoi(data[3]);
        }
    }
}

string Country::getCountryName() const {
    return this->name;
}

string Country::getCountryCode() const {
    return this->country_number_code;
}

int Country::getCountryId() const {
    return this->id;
}

int Country::getCountryMaxDigits() const {
    return this->max_digits;
}

Country& Country::operator=(Country c) {
    if (this != &c) {
        this->id = c.id;
        this->name = c.name;
        this->country_number_code = c.country_number_code;
        this->max_digits = c.max_digits;
        return *this;
    }
    else
        return *this;
}
