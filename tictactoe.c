#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>

void playBot();//  for play with bot mode
void multiplayer();//  for play multiplayer mode
void play(int a[][3], int row, int coln, int turns); //accepts player moves
bool win(int a[][3]); //check win conditions
void display(int a[][3],int turns);// display the board
void convertMoves(int move, int *row,int* coln);// converts move into row & coln
bool validateMove(int row,int coln,int a[][3],bool isBot);//check if the move is valid or not
void botMove(int a[][3]);//gives the bot's move
void delayBotMove();//delays bot move by 2sec


int main() {
    srand(time(NULL));//seed initialization for the rand() function in delayBotMove() function
    int choice;
    while(true){
        printf("<< CHOOSE PLAY MODE >>");
        printf("\n[1]. play multiplayer");
        printf("\n[2]. play with bot");
        printf("\n[3]. exit\n");
        scanf("%d",&choice);
        if(choice!=1 && choice!=2 && choice!=3){
            printf("please chose one among the listed modes (1/2/3)\n");
        }
        else if(choice==1){
        multiplayer();
        }
        else if(choice==2){
            playBot();
        }
        else{
            return 0;
        }
    }
}

void playBot(){
    int a[3][3];
    bool gameOver = false;
    bool isBot=false;
    
    // initialize the board
    for(int row = 0; row < 3; row++) {
        for(int coln = 0; coln < 3; coln++) {
            a[row][coln] = 7;  // 7 = empty boxes
        }
    }

    int turns = 9;  // total no. of turns
    while(turns > 0 && !gameOver) {
        display(a,turns);
        int row, coln, move;

        // check current player
        if(turns % 2 == 0) {
            printf("O (bot) to play\n");
            botMove(a);
            turns--;
            delayBotMove();
        } else {
            isBot=false;
            printf("X to play\n");
            printf("Enter your move: ");
            scanf("%d", &move);
            convertMoves(move,&row,&coln);
            if(!validateMove(row,coln,a,isBot)){
            continue;
            }
            play(a, row, coln, turns);
            turns--; 
        }
        // check winner
        if(win(a)) {
            display(a,turns);
            if(turns % 2 == 0) {
                printf("You win!\n");
            } else {
                printf("Bot wins!\n");
            }
            gameOver = true;
        }
    }

    // draw
    if(!gameOver) {
        printf("The game is a draw.\n");
    }
}

void multiplayer(){
    int a[3][3];
    bool gameOver = false;
    bool isBot=false;

    // initialize board
    for(int row = 0; row < 3; row++) {
        for(int coln = 0; coln < 3; coln++) {
            a[row][coln] = 7;  // 7 = empty boxes
        }
    }

    int turns = 9;  // Total no. of turns
    while(turns > 0 && !gameOver) {
        display(a,turns);

        // check current player
        if(turns % 2 == 0) {
            printf("O to play\n");
        } else {
            printf("X to play\n");
        }

        // accept player input
        int row, coln,move;
        printf("Enter your move : ");
        scanf("%d", &move);
        convertMoves(move,&row,&coln);

        // check input
        if(!validateMove(row,coln,a,isBot)){
            continue;
        }
        // play move
        play(a, row, coln, turns);
        turns--;

        // check winner
        if(win(a)) {
            display(a,turns);
            if(turns % 2 == 0) {
                printf("X wins!\n");
            } else {
                printf("O wins!\n");
            }
            gameOver = true;
        }
    }

    // draw
    if(!gameOver) {
        printf("The game is a draw.\n");
    }
}

void play(int a[][3], int row, int coln, int turns) {
    if(turns % 2 == 0) {
        a[row][coln] = 0;  // O move
    } else {
        a[row][coln] = 1;  // X move
    }
}


bool win(int a[][3]) {
    // Check rows and columns
    for(int i = 0; i < 3; i++) {
        if(a[i][0] == a[i][1] && a[i][1] == a[i][2] && a[i][0] != 7) {
            return true;
        }
        if(a[0][i] == a[1][i] && a[1][i] == a[2][i] && a[0][i] != 7) {
            return true;
        }
    }

    // Check diagonals
    if(a[0][0] == a[1][1] && a[1][1] == a[2][2] && a[0][0] != 7) {
        return true;
    }
    if(a[0][2] == a[1][1] && a[1][1] == a[2][0] && a[0][2] != 7) {
        return true;
    }

    return false;
}

void display(int a[][3],int turns) {
    if(turns==9){
        int n=1;
        printf("\n\t-------------------------------\n");
        for(int i = 0; i < 3; i++) {
            printf("\t|");
            for(int j = 0; j < 3; j++) {
                    printf("    %d    |",n);
                    n++;
            }
            printf("\n\t-------------------------------\n");
        }
        printf("\n");
    }
    else{
        printf("\n\t-------------------------------\n");
        for(int i = 0; i < 3; i++) {
            printf("\t|");
            for(int j = 0; j < 3; j++) {
                if(a[i][j] == 7) {
                    printf("    -    |");
                } else if(a[i][j] == 0) {
                    printf("    O    |");
                } else {
                    printf("    X    |");
                }
            }
            printf("\n\t-------------------------------\n");
        }
        printf("\n");
    }
}

void convertMoves(int move, int *row,int *coln){
    *row=(move-1)/3;
    *coln=(move-1)%3;
}

bool validateMove(int row,int coln,int a[][3],bool isBot){
            if(row < 0 || row >= 3 || coln < 0 || coln >= 3) {
            if(!isBot){
                printf("\n\nInvalid move!!! Choose values between 1 to 9.\n");
            }
            return false;
        }
        if(a[row][coln] != 7) {
            if(!isBot){
            printf("\n\nBox taken!!! Choose again.\n");
            }
            return false;
        }
        return true;
}

void botMove(int a[][3]){
    int row,coln,turns=2;
    bool isBot=true;
    do{
        row=rand()%3;
        coln=rand()%3;
    }while(!validateMove(row,coln,a,isBot));
    play(a, row, coln, turns);
}

void delayBotMove(){
    time_t startTime=time(NULL);
    while((time(NULL)-startTime)<=2){    };
}
