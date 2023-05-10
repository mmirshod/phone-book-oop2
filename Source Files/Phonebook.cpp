#include <utility>

#include "iostream"
#include "vector"
#include "iomanip"
#include "../Header Files/SupportiveFunctions.h"

using namespace std;

optional<Country> verify_country_code(string code);

Phonebook::Phonebook() {
    /**
     * Create phonebook object with default filename "contacts.csv"
     */

    this->filename = "contacts.csv";
    fstream fin(filename);
    string line, word;
    vector<string> data;

    if(fin.good()) {
        this->number_of_contacts = get_number_of_records(this->filename);

        while(getline(fin, line)) {
            stringstream ss(line);
            while(getline(ss, word, ','))
                data.push_back(word);

            Contact contact(data[1], data[2], data[3],
                            data[5], stoi(data[0]), stoi(data[4]));
            this->contacts.push_back(contact);
        }
    }
    else {
        ofstream f(filename, ios::trunc);
        f << "ID,first_name,last_name,tel_num,country_id,position\n";
        this->number_of_contacts = 0;
        f.close();
    }
    fin.close();
}


Phonebook::Phonebook(const string& file) {
    /**
     * Create phonebook object with the given filename.
     */
    this->filename = file + ".csv";
    fstream fin(filename, ios::in);
    string line, word;
    vector<string> data;


    if(fin.good()) {
        try {
            this->number_of_contacts = get_number_of_records(this->filename);

            // skip header row
            getline(fin, line);

            // get all contacts
            while (getline(fin, line)) {
                data.clear();

                stringstream ss(line);
                while (getline(ss, word, ',')) {
                    data.push_back(word);
                }
                Contact contact(data[1], data[2], data[3],
                                data[5], stoi(data[0]), stoi(data[4]));
                this->contacts.push_back(contact);
            }
        } catch (invalid_argument&) {
            cout << "INVALID_ARGUMENT_ERROR\n";
            cout << "STOPPING THE PROGRAM...\n";
            exit(1);
        }
    }
    else {
        ofstream f(filename, ios::trunc);
        f << "ID,first_name,last_name,tel_num,country_id,position\n";
        this->number_of_contacts = 0;
        f.close();
    }
    fin.close();
}


[[maybe_unused]] void Phonebook::setContacts(vector<Contact> c) {
    this->contacts = std::move(c);
}


string Phonebook::getFileName() {
    return this->filename;
}


int Phonebook::getNumberOfContacts() const{
    return this->number_of_contacts;
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
    cout << "Input first name of your contact: "; cin >> f_name;
    cout << "Do you want to add last name ?(if yes type Y)"; cin >> trigger;
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
            c = verify_country_code(country_code).value();
            break;
        }
        cout << "\nCountry Code not found!\nTry Again.\n";
    }

    // Get tel number and validate by its length
    while(true) {
        cout << "Input telephone number(with operator code): "; cin >> t_num;
        if(size(to_string(stoull(t_num))) == c.getCountryMaxDigits()) {
            if (not find_contact(country_code + t_num, *this).has_value())
                break;
            else
                cout << "\nNumber already exists! Try to input another number\n";
        }
        else
            cout << "\nIt seems that you entered wrong number!\nTry Again.\n";
    }

    // Entering position
    cout << "Choose position_ to add your contact: ";
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

    // add to local Phonebook object
    try {
        this->contacts.emplace_back(f_name, l_name, country_code + t_num, category, contact_id, c.getCountryId());
    } catch (invalid_argument&) {
        cout << "INVALID_ARGUMENT_ERROR" << endl;
        return;
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

    cout << "New Contact " << f_name << " " << l_name << " Has been added" << endl;

    // increase number of contacts by one
    this->number_of_contacts++;
}


void Phonebook::read_record() {
    string tel_num;
    ifstream fin(this->filename);
    optional<Contact> opt_contact;

    // check if file is open
    if(!fin.is_open())
        cout << "Error! Couldn't Open the file!";

    // get user input
    while(true) {
        cout << "\nInput full telephone number of contact (including country code, but excluding '+' sign): ";
        cin >> tel_num;

        // check if number is valid
        if(tel_num.length() >= 6 and tel_num.length() <= 15) {
            // find contact in phonebook
            opt_contact = find_contact(tel_num, *this);

            // Contact to display
            if (opt_contact.has_value()) {
                cout << opt_contact.value();
                fin.close();
                return;
            }
            else {
                // display error message if desired contact not found
                cout << "Contact Not Found!\n";
                fin.close();
                return;
            }
        }
    }
}


void Phonebook::update_record() {
    ofstream fout;
    string num_to_find, country_code, new_f_name, new_l_name, new_number, new_country_code, line, word;
    optional<Contact> contact;
    optional<Country> country;
    int choice;

    fout.open(this->filename, ios::trunc);

    if (fout.is_open()) {
        // write header row into contacts file
        fout << "ID,first_name,last_name,tel_num,country_id,position\n";
        fout << "ID,first_name,last_name,tel_num,country_id,position\n";

    } else {
        cout << "\nCould not open the file!\n";
        return;
    }

    // validate country of contact
    while (true) {
        cout << "\nInput country code of phone number: ";
        cin >> country_code;
        country = verify_country_code(country_code);

        if (country.has_value())
            break;
        else
            cout << "\nCountry not found. Try again.\n";
    }

    // validate phone number
    while (true) {
        cout << "\nInput phone number: ";
        cin >> num_to_find;
        contact = find_contact((country_code + num_to_find), *this);

        if (contact.has_value())
            break;
        else
            cout << "\nPhone number not found. Try Again\n";
    }

    // display found data
    cout << "This is the contact we found:\n";
    cout << contact.value() << endl;

    // Change contact object
    while (true) {
        choice = make_choice_update_contact();
        if (choice and choice != -1) {
            if (choice == 1) {

                // update_first_name
                cout << "Input new first name: ";
                cin >> new_f_name;
                contact->set_first_name(new_f_name);
                break;

            } else if (choice == 2) {
                // update_last_name
                cout << "Input new last name: ";
                cin >> new_l_name;
                contact->set_last_name(new_l_name);
                break;

            } else if (choice == 3) {

                // update_number
                // get country code
                while (true) {
                    cout << "\nInput new country code of a number: \n";
                    cin >> new_country_code;

                    country = verify_country_code(new_country_code);

                    if (country.has_value())
                        break;
                    else
                        cout << "\nWrong Country Code!\n";
                }

                // get phone number
                while (true) {
                    cout << "\nInput new telephone number:\n";
                    cin >> new_number;

                    optional<Country> new_country = verify_country_code(new_country_code);

                    if (country->getCountryMaxDigits() == size(to_string(stoull(new_number)))) {
                        contact->set_tel_num(new_country_code + new_number);
                        contact->set_country(country.value());

                        goto end;
                    } else
                        cout << "\nWrong Number!\n";
                }
            }
        } else
            cout << "\nIncorrect input. Try again.\n";
    }

    end:

    // change updated contact in phonebook object
    for (Contact &c: this->contacts)
        if (c.get_id() == contact->get_id()) {
            c = contact.value();
            break;
        }

    for (auto& c : this->contacts) {
        fout << c.get_id() << ","
             << c.get_first_name() << ","
             << c.get_last_name() << ","
             << c.get_tel_num() << ","
             << c.get_country().getCountryId() << ","
             << c.get_position() << "\n";
    }

    // close files
    fout.close();
}

void Phonebook::delete_record() {
    string num_to_delete, line, word;
    fstream fin, fout;
    optional<Contact> contact_to_delete;

    // Take user input
    while(true) {
        cout << "Input whole number to delete: ";
        cin >> num_to_delete;

        // find contact from 'database'
        contact_to_delete = find_contact(num_to_delete, *this);

        // if found contact break the loop
        if (contact_to_delete.has_value())
            break;

        cout << "\nContact not found. Try Again.\n";
    }

    fin.open(this->filename, ios::in);
    fout.open("temp.csv", ios::out);

    // copy header row
    getline(fin, line);
    fout << line << endl;

    try {
        while (getline(fin, line)) {
            vector<string> data;
            stringstream ss(line);

            while (getline(ss, word, ','))
                data.push_back(word);

            try {
                if (stoi(data[0]) == contact_to_delete->get_id())
                    continue;
                else
                    fout << line << endl;
            } catch (invalid_argument &) {
                cout << "INVALID_ARGUMENT_ERROR\n";
                cout << "STOPPING THE PROGRAM\n";
                exit(1);
            }
        }
    } catch (std::exception& e) {
        if(e.what() == "segmentation_fault")
            cout << "SEGMENTATION_FAULT\n";
        else
            cout << "ERROR!\n";

        exit(1);
    }

    // delete contact from local object
    for (auto it = contacts.begin(); it != contacts.end(); it++)
        if (it->get_id() == contact_to_delete->get_id()) {
            this->contacts.erase(it);
            break;
        }

    // close the files
    fin.close();
    fout.close();

    // rename temp file to real one
    remove(this->filename.c_str());
    rename("temp.csv", this->filename.c_str());
}


void Phonebook::read_all_records() {
    ifstream fin(this->filename);

    try {
        // header row
        cout << setfill('-') << setw(8) << "" << "+";
        cout << setw(22) << "" << "+";
        cout << setw(22) << "" << "+";
        cout << setw(31) << "" << "+";
        cout << setw(19) << "" << "+";
        cout << setw(17) << "" << "+" << endl;
        cout << setfill(' ') << left << setw(8) << "| ID" << "|";
        cout << left << setw(22) << "First Name" << "|";
        cout << left << setw(22) << "Last Name" << "|";
        cout << left << setw(31) << "Telephone Number" << "|";
        cout << left << setw(19) << "Country" << "|";
        cout << left << setw(17) << "Position" << "|" << endl;
        cout << setfill('-') << setw(8) << "" << "+";
        cout << setw(22) << "" << "+";
        cout << setw(22) << "" << "+";
        cout << setw(31) << "" << "+";
        cout << setw(19) << "" << "+";
        cout << setw(17) << "" << "+" << endl;

        for (auto it = this->contacts.begin(); it < this->contacts.end(); ++it) {
            cout << *it;
        }
    } catch (invalid_argument&) {
        cout << "INVALID_ARGUMENT\n";
        exit(1);
    } catch (...) {
        cout << "ERROR\n";
        exit(1);
    }
}
