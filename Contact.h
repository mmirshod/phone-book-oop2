//
// Created by ENVY on 4/26/2023.
//

#ifndef PHONE_BOOK_CONTACT_H
#define PHONE_BOOK_CONTACT_H

#include "string"
#include "Country.h"

class Contact {
private:
    string f_name, l_name, tel_num, category;
    int id;
    Country country;
public:
    Contact(
            string f_name,
            string l_name,
            string tel_num,
            string category,
            int contact_id,
            int country_id
    ) : f_name(f_name),
        l_name(l_name),
        tel_num(tel_num),
        category(category),
        id(contact_id),
        country(country_id)
    {}

    friend ostream& operator<<(ostream& out, Contact c);
};


#endif //PHONE_BOOK_CONTACT_H
