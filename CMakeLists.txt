cmake_minimum_required(VERSION 3.23)
project(phone_book)

set(CMAKE_CXX_STANDARD 20)

add_executable(phone_book "Source Files/Phonebook.cpp" "Header Files/Phonebook.h" main.cpp "Source Files/SupportiveFunctions.cpp" "Header Files/SupportiveFunctions.h" "Source Files/Country.cpp" "Header Files/Country.h" "Source Files/Contact.cpp" "Header Files/Contact.h" "Source Files/Employee.cpp" "Header Files/Employee.h")
