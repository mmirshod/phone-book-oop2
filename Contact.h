//
// Created by ENVY on 4/26/2023.
//

#ifndef PHONE_BOOK_CONTACT_H
#define PHONE_BOOK_CONTACT_H

#include "string"
#include "Country.h"

class Contact {
private:
    string f_name, l_name, tel_num, position_;
    int id{};
    Country country;
public:
    Contact();

    Contact(
        string f_name,
        string l_name,
        string tel_num,
        string position,
        int contact_id,
        int country_id
    ) : f_name(f_name),
        l_name(l_name),
        tel_num(tel_num),
        position_(position),
        id(contact_id),
        country(country_id)
    {}

    friend ostream& operator<<(ostream& out, const Contact& c);

    void set_first_name(string name);
    void set_last_name(string surname);
    void set_tel_num(string number);
    void set_position(string position);
    int get_id() const;
    string get_first_name();
    string get_last_name();
    string get_tel_num();
    string get_position() const;
    Country get_country();
};


#endif //PHONE_BOOK_CONTACT_H
