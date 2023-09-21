//
//  main.cpp
//  ПОПЫТКА 5
//
//  Created by Michalis on 22.09.2023.
//


//
//  Slozhno_kapec.cpp
//  Повторение материала 2
//
//  Created by Michalis on 21.09.2023.
//


#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS
#include "main.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <cstdio>


using namespace std;

//errno_t code;

int number = 0;
const int MAX = 25;

void ShowMenu()
{
    cout <<"1. MENU:"<< endl;
    
    cout <<"1. Add Employee"<< endl;

    cout <<"2. Show Employee"<< endl;

    cout <<"3. Delete Employee"<< endl;

    cout <<"4. Sort Last name"<< endl;

    cout <<"5. Search Salary"<< endl;

    cout <<"6. Search Last name"<< endl;
}

bool CheckPhone(char* checkPhone ) {
    int size = 0;
    while (checkPhone[size] != '\0')
    {
        if (!isdigit(checkPhone[size]))
        {
            return false;
        }
        size++;
    }

    if (size == 10)
    {
        return true;
    }
    else {
        return false;
    }


}


void AddPerson(Person* person) {
    if (number < MAX)
    {
        Person newperson;
        cout << "Enter People data:" << endl;
        cout << "Name: ";
        cin.ignore();
        cin.getline(newperson.name, sizeof(newperson.name));
        cout << "Last name: ";
        cin.getline(newperson.last_name, sizeof(newperson.last_name));
        char checkPhone[12];
        do {
            cout << "Phone number (10 symbols): ";
            cin.getline(checkPhone, sizeof(checkPhone));
            if (!CheckPhone(checkPhone))
            {
                cout << "Wrong number" << endl;
            }

        } while (!CheckPhone(checkPhone));
        strcpy(newperson.phone, checkPhone);

        cout << "Salary: ";
        cin >> newperson.salary;

        person[number] = newperson;
        number++;
    }
    else {
        cout << "List Full";
    }

}




void AddToFile(const char* filename, Person* person) {
    FILE* PeopleInfo;
    PeopleInfo = fopen(filename, "w");

    if (PeopleInfo == 0)
    {
        cout << "Error";
    }
    else {
        for (int i = 0; i < number; i++)
        {
            fprintf(PeopleInfo, "Name:  %s \n", person[i].name);
            fprintf(PeopleInfo, "Last name:  %s \n", person[i].last_name);
            fprintf(PeopleInfo, "Phone:  %s \n", person[i].phone);
            fprintf(PeopleInfo, "Salary:  %lf \n", person[i].salary);
        }
        fclose(PeopleInfo);
    }

}

void ShowPersonData(const char* filename, Person* person) {
    FILE* PeopleInfo;
    PeopleInfo=fopen(filename, "r");
    if (!PeopleInfo)
    {
        char buff;
        while ((buff = fgetc(PeopleInfo)) != EOF)
            cout << buff;
    }
    else {
        cout << "Error";

    }
    fclose(PeopleInfo);

}

void ShowPerson(Person* person, int i) {
    cout << "Name: " << person[i].name << endl;
    cout << "Last name: " << person[i].last_name << endl;
    cout << "Phone: " << person[i].phone << endl;
    cout << "Salary: " << person[i].salary << endl << endl;
}
void DeletePerson(Person* person)
{
    char lastName[20];
    int empt = -1;
    cout << "Enter last name: ";
    cin.ignore();
    cin.getline(lastName, sizeof(lastName));

    int unswear;
    cout << "Delete(1), or no Delete(2)";
    cin >> unswear;
    switch (unswear)
    {
    case 1:
        for (int i = 0; i < number; i++)
        {
            if (strcmp(person[i].last_name, lastName) == 0)
            {
                empt = i;
                break;
            }
        }
        if (empt != -1)
        {
            for (int i = empt; i < number - 1; i++)
            {
                person[i] = person[i + 1];
            }
            number--;
            cout << "Data deleted successfully " << endl;
        }
        else {
            cout << "Incorrect last name " << endl;
        }
        break;
    case 2:
        cout << "Stoped delete " << endl;
        break;
    }

}

void SortBySurname(Person* person, const char* filename)
{
    for (size_t i = 0; i < number - 1; i++)
    {
        for (int j = 0; j < number - 1 - i; j++)
        {
            if (strcmp(person[j].last_name, person[j + 1].last_name) > 0)
            {
                Person change = person[j];
                person[j] = person[j + 1];
                person[j + 1] = change;
            }
        }
    }
    AddToFile(filename, person);
}



void SearchSalary(Person* person)
{
    int salary;
    cout << "Enter look for salary" << endl;
    cin >> salary;
    for (int i = 0; i < number; i++)
    {
        if (salary == person[i].salary)
        {
            ShowPerson(person, i);
        }
    }
}
void SearchSurname(Person* person)
{
    char lastName[25];
    cout << "Enter look for surname" << endl;
    cin.ignore();
    cin.getline(lastName, sizeof(lastName));
    for (int i = 0; i < number; i++)
    {
        if (strcmp(lastName,  person[i].last_name) == 0)
        {
            ShowPerson(person, i);
        }
    }
}


int main()
{
    const char* filename = "person.txt";

    Person* person = new Person[MAX];
    int choice;
    ShowMenu();
    bool contin = false;


    do {
        cout << "Enter Choice" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:

            AddPerson(person);
            AddToFile(filename, person);
            break;

        case 2:

            ShowPersonData(filename, person);
            break;

        case 3:

            DeletePerson(person);
            AddToFile(filename, person);
            break;
        case 4:
            SortBySurname(person, filename);
            break;
        case 5:
            SearchSalary(person);
            break;
        case 6:
            SearchSurname(person);
            break;
        }
        cout << "Continue(1)? Stop(0):  ";
        cin >> contin;

    } while (contin);


}
