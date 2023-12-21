#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <vector>

using namespace std;


enum PhoneType{_FAX, _MAIN, _HOME, _WORK, _OFFICE};

typedef string number;

struct Phone
{
    number number;
    PhoneType phone_type{_MAIN};
};

typedef vector<Phone>PhoneList;

struct Person
{
    int id;
    string firstName;
    string lastName;
    string email;
    PhoneList phone_list;
};

typedef vector<Person> PersonList;


Phone addPhone(number _number, PhoneType _phone_type);
void addPerson(PersonList &list, PhoneList &phone_list, string _firstName, string _lastName, string _email = "");
void showStarterMenu(PersonList &list);
void newPersonHandler(PersonList &list);
void searchPersonHandler(PersonList &list);
PersonList searchPerson(PersonList &list, string query);
string phoneTypeToString(PhoneType type);
void showStudentListHandler(PersonList &list);
void showStudentList(PersonList &list);
void deletePersonHandler(PersonList &list);
void deletePerson(PersonList &list, int index);
void deletePersonListHandler(PersonList &list);
void sortListHandler(PersonList &list);
bool compareFunction(Person a, Person b);
void SaveTofileHandler(PersonList &list);
void readFromFile(PersonList &list);

#endif // PERSON_H
