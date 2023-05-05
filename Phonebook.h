#ifndef PHONE_BOOK_PHONEBOOK_H
#define PHONE_BOOK_PHONEBOOK_H

// included libraries
#include "string"
#include "vector"
#include "Contact.h"

using namespace std;

class Phonebook {
private:
    string filename;
    int number_of_contacts;
    vector<Contact> contacts;
public:
    Phonebook();
    explicit Phonebook(const string&);
    void setContacts(vector<Contact>);
    string getFileName();
    int getNumberOfContacts() const;
    void create_record();
    void read_record();
    void update_record();
    void delete_record();
    void read_all_records();
};

#endif // PHONE_BOOK_PHONEBOOK_H