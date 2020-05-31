#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "main.h"
#include "Admin.h"
#include "Book.h"
#include "MeM.h"


int FirstTime = true;

void main() {

    int Select = 0;
    char *CSelect = NULL;

    if(FirstTime)
    {
        Load_Books();
        Load_Borrow();
        Load_User();

        FirstTime = false;
    }

    printf("\n:::[Main Menu]:::\n\n");
    printf("1.Book Management\n");
    printf("2.Member Management\n");
    printf("3.Administrative actions\n");
    printf("4.Save Changes\n");
    printf("5.Exit\n");
    printf("------------------------\n");

    printf("\n\nEnter your choice: ");

    /* Validation */

    Here:
    CSelect = GetField();

    while (!IsNumber(CSelect)) { free(CSelect); CSelect = GetField(); }
    sscanf(CSelect, "%d", &Select);
    while (Select <= 0 || Select > 5) { free(CSelect); goto Here; }

    /******************************************************************/


    system("@cls||clear");

    if (Select == 1) GotoBook();
    if (Select == 2) GotoMeM();
    if (Select == 3) GotoAdmin();
    if (Select == 4) GotoSave();
    if (Select == 5) GotoExit();
}

void GotoSave() {

    Save_B();
    Save_Borrows();
    Save_Mem();
}

void GotoExit() {
    int Select = 0;
    char *CSelect = NULL;

    printf("1. Exit\n");
    printf("2. Save and Exit\n");
    printf("----------------");
    printf("\n\nEnter your choice: ");

    /* Validation */

    Here:
    CSelect = GetField();

    while (!IsNumber(CSelect)) { free(CSelect); CSelect = GetField(); }
    sscanf(CSelect, "%d", &Select);
    while (Select <= 0 || Select > 2) { free(CSelect); goto Here; }

    /******************************************************************/


    if(Select == 1)
    {
        exit(EXIT_SUCCESS);
    }
    if(Select == 2)
    {
        Save_B();
        Save_Borrows();
        Save_Mem();

        exit(EXIT_SUCCESS);
    }
}


// Some Base Methods


bool IsNumber(const char *str) {

    for (int i = 0; str[i] !='\0' ; i++)
        if(isdigit(str[i]) == 0) { return false; }

    return true;
}
bool IsString(const char *str) {

    for (int i = 0; str[i] !='\0' ; i++)
        if(isalpha(str[i]) == 0) { return false; }

    return true;
}

void Redirect() {

    int Choice = 0;
    char *CChoice = NULL;

    printf("\n\n");
    printf("----------\n");
    printf("Move to...\n");
    printf("----------\n");

    printf("1.Book Management\n");
    printf("2.Member Management\n");
    printf("3.Administrative Actions\n");
    printf("4.Main Menu\n");
    printf("------------------------\n");

    /* Validation */

    Here:
    CChoice = GetField();

    while (!IsNumber(CChoice)) { free(CChoice); CChoice = GetField(); }
    sscanf(CChoice, "%d", &Choice);
    while (Choice <= 0 || Choice > 4) { free(CChoice); goto Here; }

    /********************************************************/

    system("@cls||clear");

    if (Choice == 1) GotoBook();
    if (Choice == 2) GotoMeM();
    if (Choice == 3) GotoAdmin();
    if (Choice == 4) main();
}

char *GetString() {

    char *Text, Input;
    size_t CH = 1, Index = 0;

    Text = malloc(sizeof(char) * CH);
    if (!Text) return NULL;


    while ((Input = getchar()) != '\n' && Input != EOF) {

        Text = realloc(Text, CH++ * sizeof(char));
        if (!Text) return NULL;

        Text[Index++] = Input;
    }

    Text[Index] = '\0';

    if (Text[0] == '\0') {
        free(Text);
        return NULL;
    }

    return Text;
}

int FileCounter(char *FileName) {

    FILE *MF = fopen(FileName, "r");

    int ch, Lines = 0;

    do {
        ch = fgetc(MF);
        if (ch == '\n') Lines++;

    } while (ch != EOF);

    fclose(MF);

    return Lines;
}

char *strcasestr(const char *S, const char *Input) {

    size_t i;

    if (!*Input)
        return (char *) S;

    for (; *S; S++) {

        if (toupper(*S) == toupper(*Input)) {
            for (i = 1;; i++) {
                if (!Input[i])
                    return (char *) S;
                if (toupper(S[i]) != toupper(Input[i]))
                    break;
            }
        }
    }

    return NULL;
}



