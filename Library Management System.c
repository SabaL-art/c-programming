/*
1. Login System: Validate user credentials.
2. Add Books: Enter new book details.
3. Search Books: Find books by title, author, or ISBN.
4. Borrow/Return Books: Manage book borrowing and returning.
5. Exit: Save data and exit.
*/

// ----------------------( NOTE: USERNAME=admin , PASSWORD=password )-----------------------
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>

FILE *fp; //file pointer

struct books{
    char isbn[13];
    char name[25];
    char author[25];
    char isBorrowed[3];
}b[100]; //upto 100 books


void login();
void mainMenu();
void addBook();
void searchBook();
void borrowBook();
// void returnBook();


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
            searchBook();
            break;
            case 3:
            borrowBook();
            break;
            // case 4:
            // returnBook();
            // break;
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
        if (num % 10 == 1 && num != 11)
            printf("Enter the details of %dst book\n", num);
        else if (num % 10 == 2 && num != 12)
            printf("Enter the details of %dnd book\n", num);
        else if (num % 10 == 3 && num != 13)
            printf("Enter the details of %drd book\n", num);
        else
            printf("Enter the details of %dth book\n", num);
        printf("Enter the book name:");
        scanf("%s",b[i].name);
        printf("Enter the book author:");
        scanf("%s",b[i].author);
        printf("Enter the book ISBN:");
        scanf("%s",b[i].isbn);
        strcpy(b[i].isBorrowed,"no");
        fprintf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed);
        printf("\nAdded Book successfully!\n");
    }
    fclose(fp);
}

void searchBook(){
    char Availability[10];
    char search[25];
    printf("\nSearch (by Name of book/Author/ISBN)\n");
    scanf("%s",search);
    fp=fopen("books.txt","r");
    if(fp==NULL){
        printf("Error: Couldn't open the file.\n");
        exit(1);
    }
    int count=0,i=0;
    printf("\n\n%-20s | %-20s | %-13s | Availability","Name","Author","ISBN");
    printf("\n-------------------------------------------------------------------------------\n");
    while(fscanf(fp,"Name:%s Author:%s ISBN:%s Availability:%s\n",b[i].name,b[i].author,b[i].isbn,b[i].isBorrowed)!=EOF){
        if(strcasecmp(b[i].name,search)==0 ||strcasecmp(b[i].author,search)==0 ||strcasecmp(b[i].isbn,search)==0 ){
        if(strcmp(b[i].isBorrowed,"no")) {
            strcpy(Availability,"Borrowed");
        }
        else {
            strcpy(Availability,"Available");
        }
            printf("%-20s | %-20s | %-13s | %-9s\n",b[i].name,b[i].author,b[i].isbn,Availability);
            count=1;
        }
    }
    if(count==0){
        printf("No results found.\n");
    }
    printf("-------------------------------------------------------------------------------\n");
    fclose(fp);
}

void borrowBook(){

}
