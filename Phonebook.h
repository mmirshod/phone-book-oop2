#include "string"
using namespace std;

class Phonebook {
private:
    string filename;
    int number_of_contacts;
public:
    Phonebook();
    Phonebook(string);
    void create_record();
    void read_record();
    void update_record();
    void delete_record();
    void read_all_records();
    void set_filename(string);
    void export_records(string);
    void import_records(string);
};
