#include <iostream>
#include "person.h"

using namespace std;

int main()
{
    PersonList list;
    readFromFile(list);

    // test Person 1
    Phone p1;
    PhoneList phoneList1;
    p1.number = "09118320936";
    phoneList1.push_back(p1);
    addPerson(list, phoneList1, "amir", "hajipoor", "amir@gmail.com");

    // test Person 2
    Phone p2;
    PhoneList phoneList2;
    p2.number = "09304745702";
    phoneList2.push_back(p2);
    addPerson(list, phoneList2, "reza", "bahrami", "amir@gmail.com");

    showStarterMenu(list);

    return 0;
}
