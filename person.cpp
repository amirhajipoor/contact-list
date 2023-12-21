#include "person.h"
#include <string>
#include <iostream>
#include <conio.h>
#include <stdlib.h>
#include "table.h"
#include <algorithm>
#include <stdlib.h>
#include <fstream>

int id = 1;
int sort_type = 1;

PersonList list;

using namespace std;

void addPerson(PersonList &list, PhoneList &phone_list, string _firstName, string _lastName, string _email)
{
    Person person;
    person.id = id;
    person.email = _email;
    person.firstName = _firstName;
    person.lastName = _lastName;
    person.phone_list = phone_list;

    list.push_back(person);
    id++;
}

void showStarterMenu(PersonList &list)
{
    system("cls");

    cout << "Welcome to this app. What are you going to do today?" << endl;
    cout << "1) Add new person" << endl;
    cout << "2) Search in list" << endl;
    cout << "3) Delete person" << endl;
    cout << "4) Delete all data" << endl;
    cout << "5) Show all person list" << endl;
    cout << "6) Sort list" << endl;
    cout << "7) Save to File" << endl;
    cout << "8) Exit" << endl;

    short choice;
    cin >> choice;
    cout << endl;

    if (choice < 1 || choice > 8)
    {
        showStarterMenu(list);
    }

    switch (choice)
    {
        case 1:
            newPersonHandler(list);
        break;

        case 2:
            searchPersonHandler(list);
        break;

        case 3:
            deletePersonHandler(list);
        break;

        case 4:
            deletePersonListHandler(list);
        break;

        case 5:
            showStudentListHandler(list);
        break;

        case 6:
            sortListHandler(list);
        break;

        case 7:
             SaveTofileHandler(list);
        break;

        case 8:
            exit(0);
        break;
    }

    getch();
}

Phone newPhoneHandler()
{
    string phone_type;
    number number;

    do {
        cout << "Phone Type (fax, main, home, work, office): ";
        cin >> phone_type;

    } while (phone_type != "fax" && phone_type != "main" && phone_type != "home" && phone_type != "work" && phone_type != "office");

    cout << "Number: ";
    cin >> number;

    Phone phone;
    phone.number = number;

    if (phone_type == "fax") {
        phone.phone_type = PhoneType::_FAX;
    } else if (phone_type == "main") {
        phone.phone_type = PhoneType::_MAIN;
    } else if (phone_type == "home") {
        phone.phone_type = PhoneType::_HOME;
    } else if (phone_type == "work") {
        phone.phone_type = PhoneType::_WORK;
    } else if (phone_type == "office") {
        phone.phone_type = PhoneType::_OFFICE;
    } else {
        //
    }

    return phone;
}

void newPersonHandler(PersonList &list)
{
    system("cls");

    string firstName;
    string lastName;
    string email = "";

    cout << "First name: ";
    cin >> firstName;

    cout << "Last name: ";
    cin >> lastName;

    cout << "do yo want to add email address? (y/n): ";
    char c;
    cin >> c;

    if (c == 'y' || c == 'Y')
    {
        cout << "Email: ";
        cin >> email;
    }

    PhoneList phone_list;

    char q = 'n';

    do {
        auto phone = newPhoneHandler();
        phone_list.push_back(phone);

        cout << "do you want to add another phone for this person? (y/n): ";
        cin >> q;
        cout << endl;

    } while(q == 'y' || q == 'Y');

    addPerson(list, phone_list, firstName, lastName, email);
    showStarterMenu(list);
}

PersonList searchPerson(PersonList &list, string query)
{
    PersonList result;

    for (const auto &person : list)
    {
        if (
            person.firstName.compare(query) >= 0 ||
            person.lastName.compare(query) >= 0 ||
            person.email.compare(query) >= 0
           )
        {
            result.push_back(person);
        }
        else
        {
            for (const auto &phone : person.phone_list)
            {
                if (phone.number.compare(query) >= 0)
                {
                    result.push_back(person);
                    break;
                }
            }
        }
    }

    return result;
}

void searchPersonHandler(PersonList &list)
{
    system("cls");
    string query;

    cout << "type something to search: ";
    cin.ignore();
    getline(cin, query);

    PersonList result = searchPerson(list, query);

    if (result.size() == 0)
    {
        cout << endl << "Person not found" << endl;
        showStarterMenu(list);
    } else
    {
        cout << endl << "Search Result:" << endl;

        TextTable t( '-', '|', '+' );

        t.add( "index" );
        t.add( "First name" );
        t.add( "Last name" );
        t.add( "Email" );
        t.endOfRow();

        int index = 1;

        for (const auto &person : result)
        {
            t.add( to_string(index) );
            t.add( person.firstName );
            t.add( person.lastName );
            t.add( person.email );
            t.endOfRow();

            index++;
        }

        t.setAlignment( 2, TextTable::Alignment::RIGHT );
        std::cout << t;

        do {
            cout << endl << "write student index to see more detials: ";
            cin >> index;
        } while(index <= 0);

        cout << endl;
        cout << list[index-1].firstName << "  ";
        cout << list[index-1].lastName << "  ";
        cout << list[index-1].email << "  ";
        cout << endl;

        for (const auto &phone : list[index-1].phone_list)
        {
            cout << "  ->" << phoneTypeToString(phone.phone_type) << " - " << phone.number << endl;
        }
    }
}

string phoneTypeToString(PhoneType type)
{
    string output;

    switch (type)
    {
    case PhoneType::_FAX :
        output = "fax";
        break;
    case PhoneType::_HOME :
        output = "home";
        break;
    case PhoneType::_MAIN :
        output = "main";
        break;
    case PhoneType::_OFFICE :
        output = "office";
        break;
    case PhoneType::_WORK :
        output = "work";
        break;
    }

    return output;
}

void showStudentList(PersonList &list)
{
    system("cls");

    TextTable t2( '-', '|', '+' );

    t2.add( "index" );
    t2.add( "First name" );
    t2.add( "Last name" );
    t2.add( "Email" );
    t2.endOfRow();

    int index = 1;

    for (const auto &person : list)
    {
        t2.add( to_string(index) );
        t2.add( person.firstName );
        t2.add( person.lastName );
        t2.add( person.email );
        t2.endOfRow();

        index++;
    }

    t2.setAlignment( 2, TextTable::Alignment::RIGHT );
    std::cout << t2;
}

void showStudentListHandler(PersonList &list)
{
    showStudentList(list);

    if (list.size() != 0)
    {
        int index;
        cout << endl << "write student index to see more detials: ";
        cin >> index;

        cout << endl;
        cout << list[index-1].firstName << "  ";
        cout << list[index-1].lastName << "  ";
        cout << list[index-1].email << "  ";
        cout << endl;

        if (list[index-1].phone_list.size() != 0)
        {
            for (const auto &phone : list[index-1].phone_list)
            {
                cout << "  ->" << phoneTypeToString(phone.phone_type) << " - " << phone.number << endl;
            }
        }
    }
}

void deletePerson(PersonList &list, int index)
{
    int current = 1;

    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        if (current == index)
        {
            list.erase(iter);
            iter--;
        }

        current++;
    }
}


void deletePersonHandler(PersonList &list)
{
    system("cls");
    string query;

    cout << "type something to search: ";
    cin.ignore();
    getline(cin, query);

    PersonList result = searchPerson(list, query);

    if (result.size() == 0)
    {
        cout << endl << "Person not found" << endl;
        showStarterMenu(list);
    } else
    {
        cout << endl << "Search Result:" << endl;

        TextTable t( '-', '|', '+' );

        t.add( "index" );
        t.add( "First name" );
        t.add( "Last name" );
        t.add( "Email" );
        t.endOfRow();

        int index = 1;

        for (const auto &person : result)
        {
            t.add( to_string(person.id) );
            t.add( person.firstName );
            t.add( person.lastName );
            t.add( person.email );
            t.endOfRow();

            index++;
        }

        t.setAlignment( 2, TextTable::Alignment::RIGHT );
        std::cout << t;

        int deleteUserIndex;
        cout << endl << "which person you want to delete? ";
        cin >> deleteUserIndex;

        cout << deleteUserIndex;

        for (auto iter = list.begin(); iter != list.end(); iter++)
        {
            if (iter->id == deleteUserIndex)
            {
                list.erase(iter);;
                iter--;
            }
        }

        showStarterMenu(list);
    }
}

void deletePersonListHandler(PersonList &list)
{
    for (auto iter = list.begin(); iter != list.end(); iter++)
    {
        list.erase(iter);
        iter--;
    }

    char q;
    cout << "Person list deleted successfuly. back to start menu? (y/n) ";
    cin >> q;

    if (q == 'y' || q == 'Y')
    {
        showStarterMenu(list);
    }
}

bool compareFunction(Person a, Person b)
{
    if (sort_type == 1)
    {
        return a.firstName < a.lastName;
    } else {
        return a.lastName < b.lastName;
    }
}

void sortListHandler(PersonList &list)
{
    system("cls");

    do {
        cout << "Sort by?" << endl;
        cout << "1) First name" << endl;
        cout << "2) Last name" << endl;
        cin >> sort_type;
        cout << endl;

    } while(sort_type != 1 && sort_type != 2);

    sort(list.begin(), list.end(), compareFunction);

    showStudentList(list);
}

void SaveTofileHandler(PersonList &list)
{
    ofstream fout("personList.bin", ios::binary | ios::trunc);
    if (fout)
    {
        for (const auto &person : list)
        {
            // id
            fout.write((char*)&person.id, sizeof(int));

            // firstName
            int firstNameLength = person.firstName.length();
            fout.write((char*)&firstNameLength, sizeof(int));
            fout.write(person.firstName.c_str(), firstNameLength);

            // lastName
            int lastNameLength = person.lastName.length();
            fout.write((char*)&lastNameLength, sizeof(int));
            fout.write(person.lastName.c_str(), lastNameLength);

            // email
            int emailLength = person.email.length();
            fout.write((char*)&emailLength, sizeof(int));
            fout.write(person.email.c_str(), emailLength);

            // phoneNumbers
            int phoneSize = person.phone_list.size();
            fout.write((char*)&phoneSize, sizeof(int));
            for (const auto &phone : person.phone_list)
            {
                int phoneLength = phone.number.length();
                fout.write((char*)&phoneLength, sizeof(int));
                fout.write(phone.number.c_str(), phoneLength);
            }
        }
        fout.close();

        cout << "Person list saved in file successfully!";
    }
}

void readFromFile(PersonList &list)
{
    ifstream fin("personList.bin", ios::binary);
    if (fin)
    {
        int id, firstNameLength, lastNameLength, emailLength, phoneSize;
        while (fin.read((char*)&id, sizeof(int)))
        {
            Person person;
            person.id = id;

            fin.read((char*)&firstNameLength, sizeof(int));
            person.firstName.resize(firstNameLength);
            fin.read(&person.firstName[0], firstNameLength);

            fin.read((char*)&lastNameLength, sizeof(int));
            person.lastName.resize(lastNameLength);
            fin.read(&person.lastName[0], lastNameLength);

            fin.read((char*)&emailLength, sizeof(int));
            person.email.resize(emailLength);
            fin.read(&person.email[0], emailLength);

            fin.read((char*)&phoneSize, sizeof(int));
            person.phone_list.resize(phoneSize);
            for (int j = 0; j < phoneSize; j++)
            {
                int phoneLength;
                fin.read((char*)&phoneLength, sizeof(int));
                person.phone_list[j].number.resize(phoneLength);
                fin.read(&person.phone_list[j].number[0], phoneLength);
            }

            list.push_back(person);
        }

        fin.close();
    }
}

