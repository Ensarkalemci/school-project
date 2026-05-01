#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student
{
    int stdId;
    char *name;
} student;

typedef struct stdIDLL
{
    int stdID;
    student *addr;
    struct stdIDLL *next;
} stdIDLL;

typedef struct stdNameLL
{
    char *name;
    student *addr;
    struct stdNameLL *next;
} stdNameLL;

stdIDLL *IDListHEAD = NULL;
stdNameLL *NameListHEAD = NULL;
student *schViaStdID(int id2);
student *schViaStdName(char *name2);

student *createStudent(int id1, char *name1) // create a student
{

    student *newStudent = (student *)malloc(sizeof(student));

    if (newStudent == NULL)
    {
        printf("Memory error\n");
        return NULL;
    }

    newStudent->stdId = id1;
    newStudent->name = (char *)malloc(strlen(name1) + 1);
    if (newStudent->name == NULL)
    {
        printf("Memory error\n");
        free(newStudent);
        return NULL;
    }
    strcpy(newStudent->name, name1);

    return newStudent;
}

int insertIDIndex(student *s) // insert by id
{

    stdIDLL *newNode = (stdIDLL *)malloc(sizeof(stdIDLL));

    if (newNode == NULL)
    {
        printf("Memory error\n");
        return 0;
    }

    newNode->addr = s;
    newNode->next = NULL;
    newNode->stdID = s->stdId;

    if (IDListHEAD == NULL || s->stdId < IDListHEAD->stdID)
    {

        newNode->next = IDListHEAD;
        IDListHEAD = newNode;
        return 1;
    }

    stdIDLL *cur = IDListHEAD;

    while (cur->next != NULL && cur->next->stdID < s->stdId)
    {
        cur = cur->next;
    }
    newNode->next = cur->next;
    cur->next = newNode;
    return 1;
}

int insertNameIndex(student *s) // insert by name
{

    stdNameLL *newNode = (stdNameLL *)malloc(sizeof(stdNameLL));

    if (newNode == NULL)
    {
        printf("Memory error\n");
        return 0;
    }
    newNode->addr = s;
    newNode->name = s->name;
    newNode->next = NULL;
    stdNameLL *cur = NameListHEAD;

    if (NameListHEAD == NULL || strcmp(s->name, NameListHEAD->name) < 0)
    {

        newNode->next = NameListHEAD;
        NameListHEAD = newNode;
        return 1;
    }

    while (cur->next != NULL && strcmp(cur->next->name, s->name) < 0)
    {

        cur = cur->next;
    }

    newNode->next = cur->next;
    cur->next = newNode;

    return 1;
}

void deleteForId(student *s)
{

    stdIDLL *curID = IDListHEAD;
    stdIDLL *prevID = NULL;

    while (curID != NULL)
    {
        if (curID->addr == s)
        {

            if (prevID == NULL)
            {
                IDListHEAD = curID->next;
            }
            else
            {
                prevID->next = curID->next;
            }

            free(curID);
            break;
        }

        prevID = curID;
        curID = curID->next;
    }

    // name delete

    stdNameLL *curName = NameListHEAD;
    stdNameLL *prevName = NULL;

    while (curName != NULL)
    {
        if (curName->addr == s)
        {

            if (prevName == NULL)
            {

                NameListHEAD = curName->next;
            }

            else
            {

                prevName->next = curName->next;
            }
            free(curName);
            break;
        }

        prevName = curName;
        curName = curName->next;
    }
    free(s->name);
    free(s);
}

void addStudent(int id, char *name) // add name
{
    if (schViaStdID(id) != NULL)
    {
        printf("This ID already exists!\n");
        return;
    }

    student *s = createStudent(id, name);

    if (s == NULL)
    {
        printf("basarisiz"); // tekrar kontrol et
        return;
    }

    if (!insertIDIndex(s))
    {
        free(s->name);
        free(s);
        return;
    }

    if (!insertNameIndex(s))
    {
        deleteForId(s);
        return;
    }
}

void dispAllViaStdId() // Printing by id
{
    stdIDLL *cur = IDListHEAD;

    while (cur != NULL)
    {
        printf("ID: %d, Name: %s\n", cur->addr->stdId, cur->addr->name);
        cur = cur->next;
    }
}

void dispAllViaStdName() // Printing by name
{
    stdNameLL *cur = NameListHEAD;

    while (cur != NULL)
    {
        printf("ID: %d, Name: %s\n", cur->addr->stdId, cur->addr->name);
        cur = cur->next;
    }
}

student *schViaStdID(int id2) // Finding an address by ID
{

    stdIDLL *cur = IDListHEAD;

    while (cur != NULL)
    {
        if (cur->stdID == id2)
        {
            return cur->addr;
        }

        cur = cur->next;
    }
    return NULL;
}

student *schViaStdName(char *name2) // Finding an address by name
{

    stdNameLL *cur = NameListHEAD;

    while (cur != NULL)
    {

        if (strcmp(cur->name, name2) == 0)
        {

            return cur->addr;
        }

        cur = cur->next;
    }

    return NULL;
}

void updateStudent(int id)       // update
{

    student *s = schViaStdID(id);

    if (s == NULL)
    {

        printf("Student not found\n");
        return;
    }

    int choice;
    printf("1- Update ID\n");
    printf("2- Update Name\n");
    printf("3- Update ID and Name\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice != 1 && choice != 2 && choice != 3)
    {
        printf("Invalid choice\n");
        return;
    }

    if (choice == 1 || choice == 3)
    {

        int newID;
        printf("Enter new ID: ");
        scanf("%d", &newID);

        if (newID != s->stdId && schViaStdID(newID) != NULL)
        {

            printf("This ID already exists!\n");
            return;
        }

        stdIDLL *curID = IDListHEAD;
        stdIDLL *prevID = NULL;

        while (curID != NULL)
        {

            if (curID->addr == s)
            {

                if (prevID == NULL)
                {

                    IDListHEAD = curID->next;
                }

                else
                {

                    prevID->next = curID->next;
                }
                free(curID);
                break;
            }
            prevID = curID;
            curID = curID->next;
        }

        s->stdId = newID;
        insertIDIndex(s);
    }

    if (choice == 2 || choice == 3)
    {

        char newName[100];
        getchar();
        printf("Enter new name: ");
        fgets(newName, 100, stdin);
        newName[strcspn(newName, "\n")] = '\0';

        stdNameLL *curName = NameListHEAD;
        stdNameLL *prevName = NULL;

        while (curName != NULL)
        {

            if (curName->addr == s)
            {

                if (prevName == NULL)
                {

                    NameListHEAD = curName->next;
                }

                else
                {

                    prevName->next = curName->next;
                }

                free(curName);
                break;
            }
            prevName = curName;
            curName = curName->next;
        }

        char *tempName = (char *)malloc(strlen(newName) + 1);
        if (tempName == NULL)
        {
            printf("Memory error\n");
            return;
        }

        strcpy(tempName, newName);

        free(s->name);
        s->name = tempName;

        insertNameIndex(s);
    }
}

int main()
{
    int choice, id, updateChoice;
    char name[100];

    while (1)
    {
        printf("\n--- MENU ---\n");
        printf("1) Add Student\n");
        printf("2) Delete Student\n");
        printf("3) Update Student\n");
        printf("4) Search by Student ID\n");
        printf("5) Search by Student Name\n");
        printf("6) Display by Student ID\n");
        printf("7) Display by Student Name\n");
        printf("8) Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter ID: ");
            scanf("%d", &id);

            printf("Enter Name: ");

            getchar();
            fgets(name, 100, stdin);
            name[strcspn(name, "\n")] = '\0';

            addStudent(id, name);
            break;

        case 2:
        {
            printf("1- Delete by ID :");
            scanf("%d", &id);

            student *s = schViaStdID(id);

            if (s == NULL)
            {
                printf("Student not found\n");
                break;
            }

            deleteForId(s);
            break;
        }

        case 3:
            printf("1-Enter the id for Update Student :");
            scanf("%d", &id);
            updateStudent(id);

            break;

        case 4:
        {
            printf("Enter ID: ");
            scanf("%d", &id);
            student *s = schViaStdID(id);
            if (s)
                printf("ID: %d, Name: %s\n", s->stdId, s->name);
            else
                printf("Student could not found\n");
            break;
        }

        case 5:
        {
            printf("Enter Name: ");

            getchar();
            fgets(name, 100, stdin);
            name[strcspn(name, "\n")] = '\0';

            student *s = schViaStdName(name);
            if (s)
                printf("ID: %d, Name: %s\n", s->stdId, s->name);
            else
                printf("STudent could not found\n");
            break;
        }

        case 6:
            dispAllViaStdId();
            break;

        case 7:
            dispAllViaStdName();
            break;

        case 8:

            return 0;

        default:
            printf("Error your choice is wrong. Please try again!\n");
        }
    }
}