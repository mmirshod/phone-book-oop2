#include "string"
#include "optional"
#include "vector"
#include "Contact.h"
using namespace std;

class Phonebook {
private:
    string filename;
    int number_of_contacts;
public:
    /**
     * Creates Phonebook object with default filename "contacts.csv"
     */
    Phonebook();
    vector<Contact> contacts;
    Phonebook(string);
    void setContacts(vector<Contact>);
    void create_record();
    void read_record();
    void update_record();
    void delete_record();
    void read_all_records();
    void export_records(string);
    void import_records(string);
};
