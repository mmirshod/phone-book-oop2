#include "Phonebook.h"
#include "Employee.h"
#include "SupportiveFunctions.h"
#include "iostream"

using namespace std;

int main() {
    Phonebook p("final_test_3");
    string name, password;
    Employee *employee;
    int choice;

    // get the role in the company
    while(true) {
        choice = make_choice_select_role();
        if (choice != -1) {
            if (choice == 1) {
                // Take user input
                try {
                    cout << "\nInput Your Name: \n";
                    getline(cin, name, '\n');

                    cout << "\nInput a Password:\n";
                    getline(cin, password, '\n');

                    if (check_password(password, "OWNER"))
                        employee = new Owner(name);
                    else
                        throw AuthError("Authentication Error");
                } catch (AuthError& e) {
                    cout << "ERROR: " << e.what() << endl;
                    exit(401);
                }
                break;
            } else if (choice == 2) {try {
                    cout << "\nInput Your Name:\n";
                    getline(cin, name, '\n');

                    cout << "\nInput a Password:\n";
                    getline(cin, password, '\n');

                    if (check_password(password, "MANAGER"))
                        employee = new Manager(name);
                    else
                        throw AuthError("Authentication Error");
                } catch (AuthError& e) {
                    cout << "ERROR: " << e.what() << endl;
                    exit(401);
                }
                break;
            } else if (choice == 3) {
                try {
                    cout << "\nInput Your Name: \n";
                    getline(cin, name, '\n');

                    cout << "\nInput a Password:\n";
                    getline(cin, password, '\n');

                    if (check_password(password, "SPECIALIST"))
                        employee = new Specialist(name);
                    else
                        throw AuthError("Authentication Error");
                } catch (AuthError& e) {
                    cout << "ERROR: " << e.what() << endl;
                    exit(401);
                }
                break;
            } else if (choice == 4) {
                cout << "\nInput Your Name: \n";
                getline(cin, name, '\n');

                employee = new Intern(name);

                system("clear");
                cout << "\nOh, sorry " << name
                     <<  " ... Interns does not have access to our Database.\n";

                delete employee;

                exit(0);
            }
        }
    }

    choice = 1;

    // main menu
    while(choice){
        choice = 1;
        choice = make_choice_main_menu();
        switch (choice) {
            case 0:
                system("clear");
                cout << "\nGoodbye!\n";
                delete employee;
                exit(0);
            case 1:
                system("clear");
                if (employee->verify_permission("CREATE"))
                    p.create_record();
                else
                    cout << "Unfortunately you don't have such permission\n";

                system("pause");
                system("clear");
                break;
            case 2:
                system("clear");
                if (employee->verify_permission("READ"))
                    p.read_record();
                else
                    cout << "Unfortunately you don't have such permission\n";

                system("pause");
                system("clear");
                break;
            case 3:
                system("clear");
                if (employee->verify_permission("READ"))
                    p.read_all_records();
                else
                    cout << "Unfortunately you don't have such permission\n";

                system("pause");
                system("clear");
                break;
            case 5:
                system("clear");
                if (employee->verify_permission("DELETE"))
                    p.delete_record();
                else
                    cout << "Unfortunately you don't have such permission\n";

                system("pause");
                system("clear");
                break;
            case 4:
                system("clear");
                if (employee->verify_permission("UPDATE"))
                    p.update_record();
                else
                    cout << "Unfortunately you don't have such permission\n";

                system("pause");
                system("clear");
                break;
            default:
                system("pause");
                system("clear");
                cout << "\nInvalid Response. Try Again\n";
                break;
        }
    }
}
