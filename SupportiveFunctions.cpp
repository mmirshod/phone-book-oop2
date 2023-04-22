#include "string"
#include "fstream"
#include "vector"
#include "sstream"
using namespace std;

string to_upper(string str){
    /**
    Convert a string to upper case.

    @param str The input string to be converted to upper case.
    @return The input string in upper case format.
    */

    for(char & i : str)
        i=toupper(i);

    return str;
}


int get_number_of_records(string filename) {
    /**
     * @brief Returns number of records in the .csv file
     * @param filename A string representing full path to the file (or just filename)
     * @return An integer representing number of records.
     */

    fstream fin(filename, ios::in);
    int i = 0;
    string temp;

    while(getline(fin, temp)) {
        i++;
    }
    fin.close();
    return i - 1;
}


int get_country_id(string code) {
    /**

    @brief Returns the country ID associated with the given country code.
    This function reads a CSV file containing country information and
    searches for a country with a matching country code. If a match is
    found, the function returns the associated country ID as an integer.
    If a match is not found, the function returns 0.
    @param code A string representing the country code to search for.
    @return An integer representing the country ID associated with the given country code.
     Returns 0 if no match is found.
    */

    string temp, word;
    vector<string> country;
    ifstream file(R"(D:\Mirshod\IUT\OOP2\phone-book\countries.csv)");

    while(file >> temp) {
        country.clear();

        stringstream s(temp);
        while(getline(s, word, ','))
            country.push_back(word);

        if(code == country[2])
            return stoi(country[0]);
    }

    return 0;
}


int verify_country_code(string code) {
    string temp, word;
    vector<string> countries;
    ifstream file(R"(D:\Mirshod\IUT\OOP2\phone-book\countries.csv)");


    while(file >> temp) {
        countries.clear();

        stringstream s(temp);
        while(getline(s, word, ','))
            countries.push_back(word);
        if(code == countries[2]) {
            return stoi(countries[3]);
        }
    }
    return 0;
}


bool file_exists(string filename) {
    /**
     * @brief Validate whether file exist or not
     * @param filename A string representing full path to the file (or just filename)
     * @returns True if file exists. False if file does NOT exist
     */

    ifstream fin(filename);
    return fin.good();
}
