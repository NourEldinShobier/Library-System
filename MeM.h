
typedef struct {
    char *LN;        //last name
    char *FN;        //first name
    char *ID;        //ID
    char *Area;      //region
    char *age;       //age
    char *gov;       //Government
    char *phone;     //phone number
    char *BN;        //Building Number
    char *email;     //E_mail
} User;

typedef struct {
    char *ISBN;       //Book ISBN
    char *ID;         //User id
    char *DateIss;    //Date issued
    char *DateDue;    //Date of due
    char *DateRet;    //Date of returning
} Borrow;

typedef struct {

    int dd;
    int mm;
    int yy;

} DateStruct;


void GotoMeM();
void NewMember();
void EditMember();
void RemoveMember();
void BorrowBook();
void ReturnBook();
void Load_Borrow();
void Load_User();
void Save_Borrows();
void Save_Mem();
void OverDue();

int UExist(char *Input);
int GetNumOfBorrows(char *ISBN);

char *GetDate();
char *DateToString(DateStruct InPut);

DateStruct StringToDate(char * Date);
DateStruct GetToday();

bool IsEmail(char *str);
bool CMPDates(DateStruct Date1, DateStruct Date2);