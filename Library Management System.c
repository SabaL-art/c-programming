// ----------------------( NOTE: USERNAME=admin , PASSWORD=password )-----------------------
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

FILE *fp; //file pointer

struct books{
    char isbn[14];
    char name[25];
    char author[25];
    char isBorrowed[3];
}b[100]; //upto 100 books


void login();
void mainMenu();
void addBook();
int searchBook(char search[],bool isSearch);
void borrowBook();
void returnBook();


int main(){
    int choice;

    do{
        printf("<==Library Mangement Sysyem==>");
        printf("\n[1] login");
        printf("\n[2] exit\n");
        scanf("%d",&choice);
        switch (choice)
        {
        case 1:
            login();
            break;
        
        case 2:
            exit(0);
        default:
            printf("Invalid choice! try again.");
            break;
        }
    }while(choice!=2);
}

void login(){
    char username[10];
    char password[10];
    printf("\nEnter username:");
    scanf("%s",username);
    printf("Enter password:");
    scanf("%s",password);
    if(!strcmp(username,"") || !strcmp(password,"")){
        printf("Please fill bothe the fields!");
    }
    else if(strcmp(username,"admin") && strcmp(password,"password")) // username=admin and password=password
    {
        printf("Wrong username/password! please try again");
    }
    else{
        printf("\nLogin successful! Welcome admin.\n");
        mainMenu();
    }
}

void mainMenu(){
    int choice;
    while(true){
        printf("\n<==Library Management System==>");
        printf("\n[1] Add Books");
        printf("\n[2] Search Books");
        printf("\n[3] Borrow Book");
        printf("\n[4] Return Book");
        printf("\n[5] exit");
        printf("\n\nEnter your choice:");
        scanf("%d",&choice);
        printf("--------------------------------------\n");

        switch (choice){
            case 1:
            addBook();
            break;
            case 2:
            char search[25];
            printf("\nSearch (by Name of book/Author/ISBN)\n");
            scanf("%s",search);
            searchBook(search,true);
            break;
            case 3:
            borrowBook();
            break;
            case 4:
            returnBook();
            break;
            case 5:
            exit(0);
            default:
            printf("\nPlease enter valid choice");
        }
    }
}

void addBook(){
    int n;
    printf("\nHow many books do you want to add?");
    scanf("%d",&n);
    fp=fopen("books.txt","a");
    if (fp == NULL) {
    printf("Error: Couldn't open the file.\n");
    exit(1);
    }
    for(int i=0;i<n;i++){
        int num=i+1;
        char suffix[3];
        if (num % 10 == 1 && num != 11)
            strcpy(suffix,"st");
        else if (num % 10 == 2 && num != 12)
            strcpy(suffix,"nd");
        else if (num % 10 == 3 && num != 13)
            strcpy(suffix,"rd");
        else
            strcpy(suffix,"th");
        printf("Enter the details of %d%s book\n", num,suffix);
        printf("Enter the book name:");
        scanf("%24s",b[i].name);
        printf("Enter the book author:");
        scanf("%24s",b[i].author);
        printf("Enter the book ISBN:");
        scanf("%13s",b[i].isbn);
        strcpy(b[i].isBorrowed,"no");
        fprintf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed);
        printf("\nAdded Book successfully!\n");
    }
    fclose(fp);
}

int searchBook(char search[],bool isSearch){
    char Availability[10];
    fp=fopen("books.txt","r");
    if(fp==NULL){
        printf("Error: Couldn't open the file.\n");
        exit(1);
    }
    int count=0,i=0;
    printf("\n\n%-20s | %-20s | %-13s | Availability","Name","Author","ISBN");
    printf("\n-------------------------------------------------------------------------------\n");
    while(fscanf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed)!=EOF){
        if (strnlen(b[i].name, sizeof(b[i].name)) == 0 || strnlen(b[i].author, sizeof(b[i].author)) == 0 || strnlen(b[i].isbn, sizeof(b[i].isbn)) == 0) {
            printf("Error: Invalid book data at index %d.\n", i);
            continue;  // Skip this entry and move to the next one
        }
        if(strcasecmp(b[i].name,search)==0 ||strcasecmp(b[i].author,search)==0 ||strcasecmp(b[i].isbn,search)==0 ){
            if(strcmp(b[i].isBorrowed,"no")) {
                strcpy(Availability,"Borrowed");
            }
            else {
                strcpy(Availability,"Available");
            }
            printf("%-20s | %-20s | %-13s | %-9s\n",b[i].name,b[i].author,b[i].isbn,Availability);
            count=1;
            if(!isSearch){  //breaks if called in borrowBook() or returnBook()
                break;
            }
        }
        i++;
    }

    printf("-------------------------------------------------------------------------------\n");
    fclose(fp);
    if(count==0){
        printf("No results found.\n");
        return -1;
    }
    else{
        return i;
    }
}

void borrowBook(){
    char isbn[13];
    int found,i=0,j=0;
    printf("Please enter the ISBN of the book you want to borrow:");
    scanf("%s",isbn);
    found=searchBook(isbn,false);
    if(found!=-1){
        int count=0;
        fp=fopen("books.txt","r");
        if (fp == NULL) {
            printf("Error: Couldn't open the file.\n");
            exit(1);
        }
        while(fscanf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed)!=EOF)
        {
            i++;
        }
        strcpy(b[found].isBorrowed,"yes");
        fclose(fp);
        fp=fopen("books.txt","w");
        if (fp == NULL) {
            printf("Error: Couldn't open the file.\n");
            exit(1);
        }
        for(j=0;j<i;j++){
            fprintf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[j].name,b[j].author,b[j].isbn,b[j].isBorrowed);
        }
        printf("You borrowed the book successfully!");  
        fclose(fp);      
    }
    else{
        printf("No book with isbn %s found.",isbn);
    }
}

void returnBook(){
    char isbn[13];
    int found,i=0,j=0;
    printf("Please enter the ISBN of the book you want to return:");
    scanf("%s",isbn);
    found=searchBook(isbn,false);
    if(found!=-1){
        int count=0;
        fp=fopen("books.txt","r");
        if (fp == NULL) {
            printf("Error: Couldn't open the file.\n");
            exit(1);
        }
        while(fscanf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed)!=EOF)
        {
            i++;
        }
        strcpy(b[found].isBorrowed,"no");
        fclose(fp);
        fp=fopen("books.txt","w");
        if (fp == NULL) {
            printf("Error: Couldn't open the file.\n");
            exit(1);
        }
        for(j=0;j<i;j++){
            fprintf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[j].name,b[j].author,b[j].isbn,b[j].isBorrowed);
        }
        printf("You returned the book successfully!");  
        fclose(fp);      
    }
    else{
        printf("No book with isbn %s found.",isbn);
    }
}
