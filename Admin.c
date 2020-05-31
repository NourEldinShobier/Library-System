#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "MeM.h"
#include "main.h"
#include "Book.h"
#include "Admin.h"



void GotoAdmin()
{
    int Select = 0;
    char *CSelect = NULL;

    printf("\n:::[Administration Menu]:::\n\n");
    printf("1.Most Popular Books\n");
    printf("2.Overdue Books\n");
    printf("3.Main Menu\n");
    printf("--------------------\n");

    printf("\n\nEnter your choice: ");

    /* Validation */

    Here:
    CSelect = GetField();

    while (!IsNumber(CSelect)) { free(CSelect); CSelect = GetField(); }
    sscanf(CSelect, "%d", &Select);
    while (Select <= 0 || Select > 3) { free(CSelect); goto Here; }

    /******************************************************************/

    system("@cls||clear");

    if (Select == 1) POP();
    if (Select == 2) OverDue();
    if (Select == 3) main();
}