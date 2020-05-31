#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <ctype.h>

#include "MeM.h"
#include "main.h"
#include "Book.h"


Book *Books;
Borrow *MyBorrows;
User *MyUsers;

int BooksNumber = 0;
int BorrowsNumber = 0;
int UsersNumber = 0;


void GotoMeM() {

    BooksNumber = GetBooksNumber();
    Books = GetBooks();

    int Select = 0;
    char *CSelect = NULL;

    printf("\n:::::[Members Menu]:::::\n\n");
    printf("1.New Member\n");
    printf("2.Remove Member\n");
    printf("3.Edit Member\n");
    printf("4.Borrow Book\n");
    printf("5.Return Book\n");
    printf("6.Main Menu\n");
    printf("------------------------\n");


    printf("Enter your choice: ");

    /* Validation */

    Here:
    CSelect = GetField();

    while (!IsNumber(CSelect)) { free(CSelect); CSelect = GetField(); }
    sscanf(CSelect, "%d", &Select);
    while (Select <= 0 || Select > 6) { free(CSelect); goto Here; }

    /******************************************************************/

    system("@cls||clear");

    if (Select == 1) NewMember();
    if (Select == 2) RemoveMember();
    if (Select == 3) EditMember();
    if (Select == 4) BorrowBook();
    if (Select == 5) ReturnBook();
    if (Select == 6) main();
}

void NewMember() {

    User U;
    int I = 0;

    printf(":: Add New Member ::\n");
    printf("--------------------\n");

    printf("Enter Last Name:");
    while (!IsString(U.LN = GetField())){ free(U.LN); U.LN = GetField(); }

    printf("\nEnter First Name:");
    while (!IsString(U.FN = GetField())){ free(U.FN); U.FN = GetField(); }

    printf("\nEnter Your Age:");
    while (!IsNumber(U.age = GetField())){ free(U.age); U.age = GetField();}

    //////////Check ID////////////

    printf("\nEnter Unique ID:");

    H1:
    while (!IsNumber(U.ID = GetField())){ free(U.ID); U.ID = GetField();}
    while (UExist(U.ID) == 1) { free(U.ID); goto H1; }

    /////////////////////////////

    printf("\nEnter Your Building Number:");
    while (!IsNumber(U.BN = GetField())){ free(U.BN); U.BN = GetField();}

    printf("\nEnter The Area:");
    while (!IsString(U.Area = GetField())){ free(U.Area); U.Area = GetField(); }

    printf("\nEnter Your City:");
    while (!IsString(U.gov = GetField())){ free(U.gov); U.gov = GetField(); }

    printf("\nEnter Your Phone Number:");

    U.phone = GetField();
    while (!IsNumber(U.phone) || strlen(U.phone) != 11){ free(U.phone); U.phone = GetField();}

    printf("\nEnter Your E_mail:");
    while (!IsEmail(U.email = GetField())){ free(U.email); U.email = GetField(); }

    UsersNumber++;
    MyUsers = (User *) realloc(MyUsers, UsersNumber * sizeof(User));

    MyUsers[UsersNumber - 1].LN = U.LN;
    MyUsers[UsersNumber - 1].FN = U.FN;
    MyUsers[UsersNumber - 1].ID = U.ID;
    MyUsers[UsersNumber - 1].BN = U.BN;
    MyUsers[UsersNumber - 1].Area = U.Area;
    MyUsers[UsersNumber - 1].gov = U.gov;
    MyUsers[UsersNumber - 1].phone = U.phone;
    MyUsers[UsersNumber - 1].age = U.age;
    MyUsers[UsersNumber - 1].email = U.email;


    printf("\n:: Done ::\n\n");
    Redirect();
}

void RemoveMember() {

    char *ID = NULL;
    int Results = false, I;

    printf(":: Delete Member ::\n");
    printf("-------------------\n\n");

    printf("Enter The ID:");
    ID = GetField();

    printf("\nSearching...");

    for (I = 0; I < UsersNumber; I++) {
        if (strcmp(MyUsers[I].ID, ID) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results)
    {
        for (int J = 0; J < BorrowsNumber; J++)
            if(strcmp(MyBorrows[J].ID,ID) == 0 && strcmp(MyBorrows[J].DateRet,"No") == 0) {Results = false; break;}

        if(Results)
        {
            free(MyUsers[I].LN);
            free(MyUsers[I].FN);
            free(MyUsers[I].ID);
            free(MyUsers[I].Area);
            free(MyUsers[I].age);
            free(MyUsers[I].gov);
            free(MyUsers[I].phone);
            free(MyUsers[I].BN);
            free(MyUsers[I].email);

            for (; I < UsersNumber - 1; I++)
            {
                MyUsers[I].LN = MyUsers[I + 1].LN;
                MyUsers[I].FN = MyUsers[I + 1].FN;
                MyUsers[I].ID = MyUsers[I + 1].ID;
                MyUsers[I].Area = MyUsers[I + 1].Area;
                MyUsers[I].age = MyUsers[I + 1].age;
                MyUsers[I].gov = MyUsers[I + 1].gov;
                MyUsers[I].phone = MyUsers[I + 1].phone;
                MyUsers[I].BN = MyUsers[I + 1].BN;
                MyUsers[I].email = MyUsers[I + 1].email;
            }

            UsersNumber--;
            MyUsers = (User *) realloc(MyUsers, UsersNumber * sizeof(User));
        }
        else
        {
            printf("\n\n Can't Remove Member Until He/She Returns Borrowed Books...!!");
        }
    }
    else
    {
        printf("\nMember is not found....!!\n\n");
    }

    if(Results) printf("\n:: Done ::\n\n");

    free(ID);
    Redirect();
}

void EditMember() {

    char *ID = NULL;
    int Results = false, I;

    printf(":: Edit Member ::\n");
    printf("-----------------\n\n");

    printf("Enter The ID:");
    ID = GetField();

    printf("\nSearching...");

    for (I = 0; I < UsersNumber; I++) {
        if (strcmp(MyUsers[I].ID, ID) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results)
    {
        free(MyUsers[I].LN);
        free(MyUsers[I].FN);
        free(MyUsers[I].BN);
        free(MyUsers[I].Area);
        free(MyUsers[I].gov);
        free(MyUsers[I].phone);
        free(MyUsers[I].age);
        free(MyUsers[I].email);

        printf("Enter Last Name:");
        while (!IsString(MyUsers[I].LN = GetField())){ free(MyUsers[I].LN); MyUsers[I].LN = GetField(); }

        printf("\nEnter First Name:");
        while (!IsString(MyUsers[I].FN = GetField())){ free(MyUsers[I].FN); MyUsers[I].FN = GetField(); }

        printf("\nEnter Your Building Number:");
        while (!IsNumber(MyUsers[I].BN = GetField())){ free(MyUsers[I].BN); MyUsers[I].BN = GetField();}

        printf("\nEnter The Area:");
        while (!IsString(MyUsers[I].Area = GetField())){ free(MyUsers[I].Area); MyUsers[I].Area = GetField(); }

        printf("\nEnter Your City:");
        while (!IsString(MyUsers[I].gov = GetField())){ free(MyUsers[I].gov); MyUsers[I].gov = GetField(); }

        printf("\nEnter Your Phone Number:");

        MyUsers[I].phone = GetField();
        while (!IsNumber(MyUsers[I].phone) || strlen(MyUsers[I].phone) != 11){ free(MyUsers[I].phone); MyUsers[I].phone = GetField();}

        printf("\nEnter Your Age:");
        while (!IsNumber(MyUsers[I].age = GetField())){ free(MyUsers[I].age); MyUsers[I].age = GetField();}

        printf("\nEnter Your E_mail:");
        while (!IsEmail(MyUsers[I].email = GetField())){ free(MyUsers[I].email); MyUsers[I].email = GetField(); }
    }
    else
    {
        printf("\nMember is not found....!!\n\n");
    }

    if(Results) printf("\n:: Done ::\n\n");

    free(ID);
    Redirect();
}

void BorrowBook() {

    char *ID = NULL, *ISBN = NULL;
    int Results1 = false,Results2 = false, Ac = 0, I,J;
    int Borrows = 0, BorrowedBefore = false;

    printf(":: Borrow Book ::\n");
    printf("-----------------\n\n");

    printf("Enter The ID:");
    ID = GetField();

    printf("\nEnter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < UsersNumber; I++) {
        if (strcmp(MyUsers[I].ID, ID) == 0) // Not strcasestr
        {
            Results1 = true;
            break;
        }
    }

    for (J = 0; J < BooksNumber; J++) {
        if (strcmp(Books[J].ISBN, ISBN) == 0) // Not strcasestr
        {
            Ac = Books[J].AC;
            Results2 = true;
            break;
        }
    }

    if(Results1 && Results2)
    {
        if(Ac != 0)
        {
            /* Check Number of borrows per ID */

            for (int K = 0; K < BorrowsNumber; K++)
                if(strcmp(MyBorrows[K].ID, ID) == 0) Borrows++;

            if(Borrows < 3)
            {
                /* Check if want to borrow same book */

                for (int Q = 0; Q < BorrowsNumber; Q++)
                    if(strcmp(MyBorrows[Q].ID, ID) == 0 && strcmp(MyBorrows[Q].ISBN, ISBN) == 0) BorrowedBefore = true;


                if(BorrowedBefore != true)
                {
                    Borrow Temp; bool Later = false;

                    Temp.ISBN = Books[J].ISBN;
                    Temp.ID = MyUsers[I].ID;

                    Temp.DateIss = DateToString(GetToday());
                    Temp.DateRet = "No";

                    printf("\nEnter Return Day (dd/mm/yy):\n");

                    Here:
                    Temp.DateDue = GetDate();

                    /* Compare Dates */
                    Later = CMPDates(StringToDate(Temp.DateDue),GetToday());
                    if(!Later){ free(Temp.DateDue); goto Here;}

                    BorrowsNumber++;
                    MyBorrows = (Borrow *) realloc(MyBorrows, BorrowsNumber * sizeof(Borrow));

                    MyBorrows[BorrowsNumber - 1].ISBN = Temp.ISBN;
                    MyBorrows[BorrowsNumber - 1].ID = Temp.ID;
                    MyBorrows[BorrowsNumber - 1].DateIss = Temp.DateIss;
                    MyBorrows[BorrowsNumber - 1].DateDue = Temp.DateDue;
                    MyBorrows[BorrowsNumber - 1].DateRet = Temp.DateRet;

                    Books[J].AC--;
                }
                else
                {
                    printf("\nCan't borrow same book again...!!\n\n");
                }
            }
            else
            {
                printf("\nCan't borrow more than 3 books...!!\n\n");
            }

        }
        else
        {
            printf("\nThere is no available copies to borrow...!!\n\n");
        }
    }
    else
    {
        printf("\nThe [ISBN] or [ID] you entered is not found....!!\n\n");
    }

    if(Results1 && Results2 && Ac != 0 && Borrows < 3 && BorrowedBefore == false)  printf("\n:: Done ::\n\n");

    free(ISBN); free(ID);
    Redirect();
}

void ReturnBook() {

    char *ID = NULL, *ISBN = NULL;
    int Results1 = false,Results2 = false, I,J,Q;


    printf(":: Return Book ::\n");
    printf("-----------------\n\n");

    printf("Enter The ID:");
    ID = GetField();

    printf("\nEnter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < UsersNumber; I++) {
        if (strcmp(MyUsers[I].ID, ID) == 0) // Not strcasestr
        {
            Results1 = true;
            break;
        }
    }

    for (J = 0; J < BooksNumber; J++) {
        if (strcmp(Books[J].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results2 = true;
            break;
        }
    }

    if(Results1 && Results2)
    {
        /* Search for id and isbn together */

        for (Q = 0; Q < BorrowsNumber; Q++)
            if(strcmp(MyBorrows[Q].ID, ID) == 0 && strcmp(MyBorrows[Q].ISBN, ISBN) == 0) break;

        /* Check if here returend it already */
        if(strcmp(MyBorrows[Q].DateRet,"No") == 0)
        {
            free(MyBorrows[Q].DateRet);
            MyBorrows[Q].DateRet = DateToString(GetToday());
            Books[J].AC++;
        }
        else
        {
            printf("\nThe Book is already returned....!!\n\n");
        }
    }
    else
    {
        printf("\nThe [ISBN] or [ID] you entered is not found....!!\n\n");
    }

    if(Results1 && Results2) printf("\n:: Done ::\n\n");

    free(ISBN); free(ID);
    Redirect();
}

void Load_Borrow(){

    int I = 0, DataRowCount = FileCounter("Borrow.txt");
    char Line[512], *Value = NULL;
    FILE *BorrowFile = fopen("Borrow.txt", "r");

    BorrowsNumber = DataRowCount;
    MyBorrows = malloc(sizeof(Borrow) * (DataRowCount));

    while (fgets(Line, 512, BorrowFile))
    {
        //ISBN
        Value = strtok(Line, ",");
        MyBorrows[I].ISBN = malloc(strlen(Value) + 1);
        strcpy(MyBorrows[I].ISBN, Value);

        //ID
        Value = strtok(NULL, ",");
        MyBorrows[I].ID = malloc(strlen(Value) + 1);
        strcpy(MyBorrows[I].ID, Value);

        //DateIss
        Value = strtok(NULL, ",");
        MyBorrows[I].DateIss = malloc(strlen(Value) + 1);
        strcpy(MyBorrows[I].DateIss, Value);

        //DateDue
        Value = strtok(NULL, ",");
        MyBorrows[I].DateDue = malloc(strlen(Value) + 1);
        strcpy(MyBorrows[I].DateDue, Value);

        //DateRet
        Value = strtok(NULL, "\n");
        MyBorrows[I].DateRet = malloc(strlen(Value) + 1);
        strcpy(MyBorrows[I].DateRet, Value);

        I++;
    }
    free(Value);
    fclose(BorrowFile);
}

void Load_User(){

    int I = 0, DataRowCount = FileCounter("Users.txt");
    char Line[512], *Value = NULL;
    FILE *UserFile = fopen("Users.txt", "r");

    UsersNumber = DataRowCount;
    MyUsers = malloc(sizeof(User) * (DataRowCount));

    while (fgets(Line, 512, UserFile))
    {
        //LN
        Value = strtok(Line, ",");
        MyUsers[I].LN = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].LN, Value);

        //FN
        Value = strtok(NULL, ",");
        MyUsers[I].FN = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].FN, Value);

        //ID
        Value = strtok(NULL, ",");
        MyUsers[I].ID = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].ID, Value);

        //age
        Value = strtok(NULL, ",");
        MyUsers[I].age = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].age, Value);

        //Area
        Value = strtok(NULL, ",");
        MyUsers[I].Area = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].Area, Value);

        //gov
        Value = strtok(NULL, ",");
        MyUsers[I].gov = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].gov, Value);

        //phone
        Value = strtok(NULL, ",");
        MyUsers[I].phone = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].phone, Value);

        //BN
        Value = strtok(NULL, ",");
        MyUsers[I].BN = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].BN, Value);

        //email
        Value = strtok(NULL, "\n");
        MyUsers[I].email = malloc(strlen(Value) + 1);
        strcpy(MyUsers[I].email, Value);

        I++;
    }

    free(Value);
    fclose(UserFile);
}

void Save_Borrows() {

    int I;
    FILE *BorrowFile;

    BorrowFile = fopen("Borrow.txt", "w");

    for (I = 0; I < BorrowsNumber; I++) {
        fprintf(BorrowFile, "%s,%s,%s,%s,%s\n", MyBorrows[I].ISBN, MyBorrows[I].ID, MyBorrows[I].DateIss, MyBorrows[I].DateDue, MyBorrows[I].DateRet);
    }

    fclose(BorrowFile);
}

void Save_Mem() {

    int I;
    FILE *MemFile;

    MemFile = fopen("Users.txt", "w");

    for (I = 0; I < UsersNumber; ++I) {
        fprintf(MemFile, "%s,%s,%s,%s,%s,%s,%s,%s,%s\n", MyUsers[I].LN, MyUsers[I].FN, MyUsers[I].ID, MyUsers[I].age, MyUsers[I].Area, MyUsers[I].gov,
                MyUsers[I].phone, MyUsers[I].BN, MyUsers[I].email);
    }

    fclose(MemFile);
}

int GetNumOfBorrows(char *ISBN) {

    int Borrows = 0;

    for (int I = 0; I < BorrowsNumber; I++)
        if (strcmp(MyBorrows[I].ISBN, ISBN) == 0) Borrows++;

    return Borrows;
}
int UExist(char *Input) {

    int Found = 0;

    for (int I = 0; I < UsersNumber; I++)
    {
        if (strcasestr(MyUsers[I].ID, Input) != NULL) Found++;
    }

    return Found;
}

DateStruct GetToday() {

    DateStruct Temp;
    time_t t = time(NULL);
    struct tm today = *localtime(&t);

    Temp.dd = today.tm_mday;
    Temp.mm = today.tm_mon + 1;
    Temp.yy = today.tm_year + 1900;

    return Temp;
}
DateStruct StringToDate(char *Date) {
    DateStruct Temp;
    char *CTemp = strdup(Date);

    sscanf(strtok(CTemp, "/"), "%d", &Temp.dd);
    sscanf(strtok(NULL, "/"), "%d", &Temp.mm);
    sscanf(strtok(NULL, "\0"), "%d", &Temp.yy);

    free(CTemp);
    return Temp;
}

bool IsEmail(char *str) {

    int At = 0,Dot = 0;
    int NAt = 0, NDot = 0;


    if(isdigit(str[0]) || str[0] == '@' || str[strlen(str) - 1] == '.'|| isdigit(str[strlen(str) - 1])) return false;

    for (int I = 1; str[I] !='\0' ; I++)
    {
        if(!isdigit(str[I]) && !isalpha(str[I]) && str[I] !='_')
        {
            if(str[I] == '@') {NAt++; At = I; continue;}
            if(str[I] == '.') {NDot++; Dot = I; continue;}
            else return false;
        }
    }

    if(NAt != 1 || NDot != 1 || At > Dot || Dot - At == 1 || Dot - At == 2 || (strlen(str) - 1) - Dot == 1 || At - 0 < 2) return false;

    return true;
}
bool CMPDates(DateStruct Date1, DateStruct Date2) {

    if(Date1.yy > Date2.yy)
        return true;

    if(Date1.yy < Date2.yy)
        return false;

    if(Date1.yy == Date2.yy)
    {
        if(Date1.mm > Date2.mm)
            return true;

        if(Date1.mm < Date2.mm)
            return false;

        if(Date1.mm == Date2.mm)
        {
            if(Date1.dd > Date2.dd) return true;
            if(Date1.dd < Date2.dd) return false;
            if(Date1.dd == Date2.dd)return false;
        }
    }
}

char *GetDate() {

    DateStruct ReturnDate;
    char *DateTime,*DD,*MM,*YY,*Value;
    int CheckDD = true, CheckMM = true, CheckYY = true,Counter = 0;  // Validation for tokens
    int A,B,C;
    int i;

    Here:
    DateTime = GetField();

    /* To make sure he entered two(/) */

    for (i=0; DateTime[i]!= '\0'; i++)
        if ( DateTime[i] == '/') Counter++;

    if(Counter != 2)
    {
        free(DateTime); goto Here;
    }

    /* split (GetDate) into tokens */

    //DD
    Value = strtok(DateTime, "/");
    DD = malloc(strlen(Value) + 1);
    strcpy(DD, Value);

    //MM
    Value = strtok(NULL, "/");
    MM = malloc(strlen(Value) + 1);
    strcpy(MM, Value);

    //YY
    Value = strtok(NULL, "\0");
    YY = malloc(strlen(Value) + 1);
    strcpy(YY, Value);


    if(!IsNumber(DD)) CheckDD = false;
    if (!IsNumber(MM)) CheckMM = false;
    if(!IsNumber(YY)) CheckYY = false;


    if (CheckDD == false && CheckMM == false && CheckYY == false)
    {
        free(DD); free(MM); free(YY); free(Value); free(DateTime); goto Here;
    }

    else
    {

        /* Convert data into int */

        sscanf(DD, "%d", &A);
        sscanf(MM, "%d", &B);
        sscanf(YY, "%d", &C);

        if (A > 0 && A <= 31 && B > 0  && B <= 12 && C > 0) // 31 days per month & 12 months per year
        {
            ReturnDate.dd = A; ReturnDate.mm = B; ReturnDate.yy = C;
            free(DateTime);
            DateTime = DateToString(ReturnDate);
        }
        else
        {
            free(DD); free(MM); free(YY); free(Value); free(DateTime); goto Here;
        }
    }

    free(DD); free(MM); free(YY); free(Value);
    return DateTime;
}
char *DateToString(DateStruct InPut) {

    char *Date = malloc(20);
    sprintf(Date, "%d/%d/%d", InPut.dd, InPut.mm, InPut.yy);
    return Date;
}

void OverDue() {

    printf("\n:: Overdue books ::\n");
    printf("---------------------\n");

    int Found = false;

    if(BorrowsNumber != 0)
    {
        for (int I = 0; I < BorrowsNumber; ++I)
        {
            if(strcmp(MyBorrows[I].DateRet,"No") == 0)
            {
                if(CMPDates(GetToday(),StringToDate(MyBorrows[I].DateDue)))
                {
                    Found = true;
                    printf("- %s, %s, %s, %s, No\n", MyBorrows[I].ISBN, MyBorrows[I].ID, MyBorrows[I].DateIss, MyBorrows[I].DateDue);
                }
            }
        }

        if(!Found) printf("There is no overdue books...!!\n");
    }
    else
    {
        printf("There is no borrows yet...!!");
    }

    Redirect();
}


