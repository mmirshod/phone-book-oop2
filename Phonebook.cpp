#include "Phonebook.h"
#include <utility>
#include "iostream"
#include "vector"
#include "SupportiveFunctions.h"
#include "iomanip"
#include "Country.h"
#include "fstream"

using namespace std;

Phonebook::Phonebook() {
    /**
     * Create phonebook object with default filename "contacts.csv"
     */

    this->filename = "contacts.csv";
    fstream fin(filename);
    string line, word;
    vector<string> data;

    if(file_exists(this->filename)) {
        this->number_of_contacts = get_number_of_records(this->filename);
        while(getline(fin, line)) {
            stringstream ss(line);
            while(getline(ss, word, ',')) {
                data.push_back(word);
            }
            Contact contact(data[1], data[2], data[3],
                            data[5], stoi(data[0]), stoi(data[4]));
            contacts.push_back(contact);
        }
        setContacts(contacts);
    }
    else {
        ofstream f(filename, ios::trunc);
        f << "ID,first_name,last_name,tel_num,country_id,category\n";
        this->number_of_contacts = 0;
        f.close();
    }
    fin.close();
}


Phonebook::Phonebook(string file) {
    /**
     * Create phonebook object with the given filename.
     */
    this->filename = file + ".csv";
    fstream fin(filename);
    string line, word;
    vector<string> data;

    if(file_exists(this->filename)) {
        this->number_of_contacts = get_number_of_records(this->filename);
        while(getline(fin, line)) {
            stringstream ss(line);
            while(getline(ss, word, ',')) {
                data.push_back(word);
            }
            Contact contact(data[1], data[2], data[3],
                            data[5], stoi(data[0]), stoi(data[4]));
            contacts.push_back(contact);
        }
        setContacts(contacts);
    }
    else {
        ofstream f(filename, ios::trunc);
        f << "ID,first_name,last_name,tel_num,country_id,category\n";
        this->number_of_contacts = 0;
        f.close();
    }
    fin.close();
}


void Phonebook::setContacts(vector<Contact> c) {
    this->contacts = c;
}


void Phonebook::create_record() {
    /**
     * Creates Contact based on given user input.
     */
    // Variables
    string t_num, country_code, f_name, l_name, category, line, word;
    int contact_id;
    Country c;
    char trigger;

    // Entering Personal Info
    cout << "Input first name of your contact?"; cin >> f_name;
    cout << "Do you want to add last name?(if yes type Y)"; cin >> trigger;
    if(trigger == 'y' or trigger == 'Y') {
        cout << "Input Last Name: ";
        cin >> l_name;
    } else {
        l_name = " ";
    }

    // getting country code and finding it in countries.csv file
    while(true) {
        cout << "Input country code of number(without '+'): ";
        cin >> country_code;

        if(verify_country_code(country_code).has_value()) {
            c = verify_country_code(country_code);
            break;
        }
        cout << "\nCountry Code not found!\nTry Again.\n";
    }

    // Get tel number and validate by its length
    while(true) {
        cout << "Input telephone number(with operator code): "; cin >> t_num;
        if(size(to_string(stoull(t_num))) == c.getCountryMaxDigits()) {
            break;
        }
        cout << "\nIt seems that you entered wrong number!\nTry Again.\n";
    }

    // Entering category
    cout << "Choose category to add your contact: ";
    cin >> category;
    category = to_upper(category);

    // giving individual ID number to new contact
    contact_id = this->number_of_contacts + 1;

    // open phonebook file in append mode to add data
    ofstream fout(this->filename, ios::app);

    // check if file has been opened
    if(!fout.is_open()) {
        cout << "Error with Opening File!" << endl;
    }

    // writing to the file, where comma is separator
    fout << contact_id << ","
         << f_name << ","
         << l_name << ","
         << country_code << t_num << ","
         << c.getCountryId() << ","
         << category << endl;

    // closing file
    fout.close();

    cout << "New Contact " << f_name << " " << l_name << "Has been added" << endl;

    this->contacts.emplace_back(f_name, l_name, country_code + t_num, category, contact_id, c.getCountryId());

    // increase number of contacts by one
    this->number_of_contacts++;
}


void Phonebook::read_record() {
    string tel_num;
    ifstream fin(this->filename);

    // check if file is open
    if(!fin.is_open()) {
        cout << "Error! Couldn't Open the file!";
    }

    // get user input
    while(true) {
        cout << "\nInput full telephone number of contact (including country code, but excluding '+' sign): ";
        cin >> tel_num;
        // check if number is valid
        if(tel_num.length() >= 6 and tel_num.length() <= 15)
            break;
    }

    // skip header row
    string temp, field;
    getline(fin, temp);
    // skip to desired position
    for(int i = 0; i < this->number_of_contacts; ++i){
        vector<string> contact;

        getline(fin, temp);  // getting entire record into one string
        stringstream ss(temp);  // giving string 'temp' as an input string to our stringstream

        // parsing stringstream into a 'contact' vector
        while(getline(ss, field, ',')) {
            contact.push_back(field);
        }

        // check if contact has the same number as user inputted
        if(contact[3] == tel_num) {

            // assuming that contact now has right data display it to user
            Contact contact_to_display(contact[1], contact[2], contact[3],
                                       contact[5], stoi(contact[0]),
                                       stoi(contact[4]));

            fin.close(); // close the file
            return; // if yes exit the function
        }
    }

    // exit the function if desired contact not found
    cout << "Contact Not Found!\n";
    fin.close();
}


void Phonebook::update_record() {
    fstream fin(filename), fout("updated.csv");

}


void Phonebook::delete_record() {}


void Phonebook::read_all_records() {}


void Phonebook::export_records(string path) {}


void Phonebook::import_records(string path) {}

