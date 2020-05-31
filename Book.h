
typedef struct {
    char *Title;
    char *Author;
    char *Publisher;
    char *ISBN;
    int NOC, AC; // Num of copies and Available copies
    char *DOP;
    char *Ca;
}Book;

char *GetField();
Book *GetBooks();
int GetBooksNumber();
void GotoBook();
void CreateBook();
void Delete();
void Find();
void Edit();
void POP();
int BExist(char *InPut, char Field);
void Load_Books();
void Save_B();
void AddCpy();