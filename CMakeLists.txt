cmake_minimum_required(VERSION 3.23)
project(phone_book)

set(CMAKE_CXX_STANDARD 20)

add_executable(phone_book Phonebook.cpp Phonebook.h main.cpp SupportiveFunctions.cpp SupportiveFunctions.h Country.cpp Country.h Contact.cpp Contact.h)
