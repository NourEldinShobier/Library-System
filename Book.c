#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Book.h"
#include "main.h"
#include "mem.h"


typedef struct {
    char *ISBN;
    int NumOfBorrows;
}BorrowedBook;


Book *MyBooks;
int BooksNum = 0;


void GotoBook() {

    int Select = 0;
    char *CSelect = NULL;

    printf("\n:::[Book Menu]:::\n\n");
    printf("1.Add New Book\n");
    printf("2.Add New Copy\n");
    printf("3.Delete Book\n");
    printf("4.Find Book\n");
    printf("5.Edit Book\n");
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

    if (Select == 1) CreateBook();
    if (Select == 2) AddCpy();
    if (Select == 3) Delete();
    if (Select == 4) Find();
    if (Select == 5) Edit();
    if (Select == 6) main();
}

void CreateBook() {

    Book B;
    int I = 0;

    printf(":: Add New Book ::\n");
    printf("------------------\n");

    printf("Enter Book Title:");
    B.Title = GetField();
    printf("\nEnter Book Author:");
    B.Author = GetField();
    printf("\nEnter Publisher:");
    B.Publisher = GetField();
    //////////Check ISBN////////////
    printf("\nEnter Unique ISBN:");
    B.ISBN = GetField();
    while (BExist(B.ISBN, 'I') == 1) {
        printf("\nRe-Enter Unique ISBN:");
        B.ISBN = GetField();
    }
    ///////////////////////////////
    printf("\nEnter Date Of Publication (dd/mm/yy):");
    B.DOP = GetDate();
    printf("\nEnter Category:");
    B.Ca = GetField();

    B.AC = 1;
    B.NOC = 1;

    BooksNum++;
    MyBooks = (Book *) realloc(MyBooks, BooksNum * sizeof(Book));

    MyBooks[BooksNum - 1].Title = B.Title;
    MyBooks[BooksNum - 1].Author = B.Author;
    MyBooks[BooksNum - 1].Publisher = B.Publisher;
    MyBooks[BooksNum - 1].ISBN = B.ISBN;
    MyBooks[BooksNum - 1].DOP = B.DOP;
    MyBooks[BooksNum - 1].Ca = B.Ca;
    MyBooks[BooksNum - 1].AC = B.AC;
    MyBooks[BooksNum - 1].NOC = B.NOC;

    printf("\n:: Done ::\n\n");
    Redirect();
}

void AddCpy() {

    char *ISBN = NULL, *CNOC = NULL;
    int Results = false, I, NOC;

    printf(":: Add New Copy ::\n");
    printf("------------------\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results) {
        printf("\nEnter number of copies:");

        /* Validation */

        Here:
        CNOC = GetField();
        while (!IsNumber(CNOC)) { free(CNOC); CNOC = GetField(); }
        sscanf(CNOC,"%d",&NOC);
        while (NOC < GetNumOfBorrows(ISBN)) { free(CNOC); goto Here; }

        /********************************************************/

        MyBooks[I].NOC = NOC;
        MyBooks[I].AC = NOC - GetNumOfBorrows(ISBN);

    }
    else
    {
        printf("Book is not found....!!\n\n");
        free(ISBN); free(CNOC);
        Redirect();
    }

    printf(":: Done ::\n\n");
    free(ISBN); free(CNOC);
    Redirect();
}

void Delete() {

    char *ISBN = NULL;
    int Results1 = false, Results2 = false, I;

    printf(":: Delete Book ::\n");
    printf("-----------------\n\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results1 = true;
            break;
        }
    }

    if (Results1)
    {
        /* All copies are returned or not */
        if(MyBooks[I].AC == MyBooks[I].NOC) Results2 = true;

        if(Results2)
        {
            free(MyBooks[I].Title);
            free(MyBooks[I].Author);
            free(MyBooks[I].Publisher);
            free(MyBooks[I].ISBN);
            free(MyBooks[I].DOP);
            free(MyBooks[I].Ca);

            for (; I < BooksNum - 1; I++)
            {
                MyBooks[I].Title = MyBooks[I + 1].Title;
                MyBooks[I].Author = MyBooks[I + 1].Author;
                MyBooks[I].Publisher = MyBooks[I + 1].Publisher;
                MyBooks[I].ISBN = MyBooks[I + 1].ISBN;
                MyBooks[I].DOP = MyBooks[I + 1].DOP;
                MyBooks[I].Ca = MyBooks[I + 1].Ca;
                MyBooks[I].NOC = MyBooks[I + 1].NOC;
                MyBooks[I].AC = MyBooks[I + 1].AC;
            }

            BooksNum--;
            MyBooks = (Book *) realloc(MyBooks, BooksNum * sizeof(Book));
        }
        else
        {
            printf("\nCan't remove book until all copies are returned....!!\n\n");
        }
    }
    else
    {
        printf("\nBook is not found....!!\n\n");
    }

    if (Results1 && Results2) printf("\n:: Done ::\n\n");

    free(ISBN);
    Redirect();
}

void Find() {

    Book FindBook;
    int I,T = false, A = false, P = false, IS = false, D = false, C = false;

    printf(":: Find Book ::\n");
    printf("---------------\n");

    printf("Enter Book Title || (--):");
    FindBook.Title = GetField();
    printf("\nEnter Book Author || (--):");
    FindBook.Author = GetField();
    printf("\nEnter Publisher || (--):");
    FindBook.Publisher = GetField();
    printf("\nEnter ISBN || (--):");
    FindBook.ISBN = GetField();
    printf("\nEnter Date Of Publication (dd/mm/yy) || (--):");
    FindBook.DOP = GetField();
    printf("\nEnter Category || (--):");
    FindBook.Ca = GetField();

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(FindBook.Title, "--") != 0)
            if (strcasestr(MyBooks[I].Title, FindBook.Title) != NULL) T = true;

        if (strcmp(FindBook.Author, "--") != 0)
            if (strcasestr(MyBooks[I].Author, FindBook.Author) != NULL) A = true;

        if (strcmp(FindBook.Publisher, "--") != 0)
            if (strcasestr(MyBooks[I].Publisher, FindBook.Publisher) != NULL) P =true;

        if (strcmp(FindBook.ISBN, "--") != 0)
            if (strcasestr(MyBooks[I].ISBN, FindBook.ISBN) != NULL) IS = true;

        if (strcmp(FindBook.DOP, "--") != 0)
            if (strcasestr(MyBooks[I].DOP, FindBook.DOP) != NULL) D = true;

        if (strcmp(FindBook.Ca, "--") != 0)
            if (strcasestr(MyBooks[I].Ca, FindBook.Ca) != NULL) C = true;

        if(T == true || A == true || P == true || IS == true || D == true || C == true)
        {

            printf("- %s, %s, %s, %s, %s, %d, %d, %s\n", MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                    MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
        }
    }

    Redirect();
}

void Edit() {

    char *ISBN = NULL;
    int Results = false, I;

    printf(":: Edit Book ::\n");
    printf("---------------\n\n");

    printf("Enter The ISBN:");
    ISBN = GetField();

    printf("\nSearching...");

    for (I = 0; I < BooksNum; I++) {
        if (strcmp(MyBooks[I].ISBN, ISBN) == 0) // Not strcasestr
        {
            Results = true;
            break;
        }
    }

    if (Results)
    {
        free(MyBooks[I].Title);
        free(MyBooks[I].Author);
        free(MyBooks[I].Publisher);
        free(MyBooks[I].DOP);
        free(MyBooks[I].Ca);

        printf("\n\nEnter Book Title:");
        MyBooks[I].Title = GetField();
        printf("\nEnter Book Author:");
        MyBooks[I].Author = GetField();
        printf("\nEnter Publisher:");
        MyBooks[I].Publisher = GetField();
        printf("\nEnter Date Of Publication (dd/mm/yy):");
        MyBooks[I].DOP = GetDate();
        printf("\nEnter Category:");
        MyBooks[I].Ca = GetField();
    }
    else
    {
        printf("\nBook is not found....!!\n\n");
    }

    if(Results) printf("\n:: Done ::\n\n");
    free(ISBN);
    Redirect();
}

int BExist(char *InPut, char Field) {

    int I;
    int Found = 0;

    for (I = 0; I < BooksNum; I++) {
        switch (Field) {
            case 'T':
                if (strcasestr(MyBooks[I].Title, InPut) != NULL) Found++;
                break;
            case 'A':
                if (strcasestr(MyBooks[I].Author, InPut) != NULL) Found++;
                break;
            case 'P':
                if (strcasestr(MyBooks[I].Publisher, InPut) != NULL) Found++;
                break;
            case 'I':
                if (strcasestr(MyBooks[I].ISBN, InPut) != NULL) Found++;
                break;
            case 'D':
                if (strcasestr(MyBooks[I].DOP, InPut) != NULL) Found++;
                break;
            case 'C':
                if (strcasestr(MyBooks[I].Ca, InPut) != NULL) Found++;
                break;
            default:
                break;
        }
    }

    return Found;
}

int GetBooksNumber(){
    return BooksNum;
}

Book *GetBooks() {
    return MyBooks;
}

char *GetField() {

    size_t I = 0;
    char *P;

    Here:
    P = GetString();
    while (P == NULL) P = GetString();

    bool Accept = false;

    while (P[I] != '\0') {
        if (P[I] != ' ') {
            Accept = true;
            break;
        }
        I++;
    }

    if (!Accept) {
        Accept = false;
        I = 0;
        free(P);
        goto Here;
    }

    return P;
}

void Load_Books() {

    int I = 0, DataRowCount = FileCounter("Books.txt");
    char Line[512], *Value = NULL;
    FILE *BookFile = fopen("Books.txt", "r");

    BooksNum = DataRowCount;
    MyBooks = malloc(sizeof(Book) * (DataRowCount));

    while (fgets(Line, 512, BookFile)) {

        //Title
        Value = strtok(Line, ",");
        MyBooks[I].Title = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Title, Value);

        //Author
        Value = strtok(NULL, ",");
        MyBooks[I].Author = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Author, Value);

        //Publisher
        Value = strtok(NULL, ",");
        MyBooks[I].Publisher = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Publisher, Value);

        //ISBN
        Value = strtok(NULL, ",");
        MyBooks[I].ISBN = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].ISBN, Value);

        //DOP
        Value = strtok(NULL, ",");
        MyBooks[I].DOP = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].DOP, Value);

        //NOC
        sscanf(strtok(NULL, ","), "%d", &MyBooks[I].NOC);

        //AC
        sscanf(strtok(NULL, ","), "%d", &MyBooks[I].AC);

        //Ca
        Value = strtok(NULL, "\n");
        MyBooks[I].Ca = malloc(strlen(Value) + 1);
        strcpy(MyBooks[I].Ca, Value);

        I++;
    }


    free(Value);
    fclose(BookFile);
}

void Save_B() {

    int I;
    FILE *BookFile;

    BookFile = fopen("Books.txt", "w");

    for (I = 0; I < BooksNum; ++I) {
        fprintf(BookFile, "%s,%s,%s,%s,%s,%d,%d,%s\n", MyBooks[I].Title, MyBooks[I].Author, MyBooks[I].Publisher,
                MyBooks[I].ISBN, MyBooks[I].DOP, MyBooks[I].NOC, MyBooks[I].AC, MyBooks[I].Ca);
    }

    fclose(BookFile);
}

void POP() {

    printf("\n:: Most Popular Books ::\n");
    printf("--------------------------\n");

    int I,J;
    BorrowedBook Books[BooksNum], Temp;

    for (I = 0; I < BooksNum; I++)
    {
        Books[I].ISBN = MyBooks[I].ISBN;
        Books[I].NumOfBorrows = GetNumOfBorrows(Books[I].ISBN); /* Loops in Borrow array to get num of borrow */
    }

    /* Bubble Sorting */
    for (I = 0; I < BooksNum; I++)
    {
        for (J = 0; J < BooksNum - I; J++)
        {
            if (Books[J].NumOfBorrows < Books[J + 1].NumOfBorrows)
            {
                Temp.ISBN = Books[J + 1].ISBN;
                Temp.NumOfBorrows = Books[J + 1].NumOfBorrows;

                Books[J + 1].ISBN = Books[J].ISBN;
                Books[J + 1].NumOfBorrows = Books[J].NumOfBorrows;

                Books[J].ISBN = Temp.ISBN;
                Books[J].NumOfBorrows = Temp.NumOfBorrows;
            }

        }
    }

    if(BooksNum >= 5)
    {
        if(Books[4].NumOfBorrows != 0)
        {
            for (I = 0; I < 5; I++)
            {
                for (J = 0; J < BooksNum; J++)
                {
                    if(strcmp(Books[I].ISBN, MyBooks[J].ISBN) == 0)
                    {
                        printf("- %s\n", MyBooks[J].Title);
                        break;
                    }
                }
            }
        }
        else
        {
            printf("There are some book not borrowed yet...!!\n");
        }
    }
    else
    {
        printf("Number of books is less than 5...!!\n");
    }


    Redirect();
}






