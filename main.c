#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
int Green = 10;
int score = 0, drops = 0;
struct node{
    char data;
    short X;
    short Y;
    struct node* prev;
    struct node* next;
};
    struct node* head = NULL;
    struct node* tail = NULL;

int insertVal(){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    if(head == NULL){
        temp->data = rand() % ('A'-'Z')+ 'A';
        temp->X = rand()%80;
        temp->Y = 0;
        temp->next = NULL;
        temp->prev = NULL;
        head = temp;
        tail = temp;
        return;
    }
    else{
        if(numOfnodes()%2 != 0){
            temp->data = rand() % ('z'-'a')+ 'a';
        }
        else if(numOfnodes()%4 == 0){
            char Array[] = {'0', '1','2', '3', '4', '5', '6', '7', '8', '9'};
            temp->data = Array[rand()%10];
        }
        else{
            temp->data = rand() % ('Z'-'A')+ 'A';
        }
        temp->X = rand()%80;
        temp->Y = 0;
        temp->prev = tail;
        tail->next = temp;
        temp->next = NULL;
        tail = temp;
        return;
    }
}
void deleByVal(char val){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    struct node* ptr  = (struct node*)malloc(sizeof(struct node));
    ptr = head;
    while(ptr != NULL){
        if(ptr->data == val){
            if(ptr->prev == NULL){
                temp = head;
                head = temp->next;
                head->prev = NULL;
                free(temp);
                score += 1;
                return;
            }
            else if(ptr->next == NULL){
                temp = tail;
                tail = temp->prev;
                tail->next = NULL;
                free(temp);
                score += 1;
                return;
            }
            else{
                temp = ptr;
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                free(temp);
                score += 1;
                return;
            }
        }
        ptr = ptr->next;
    }
}
void deleVal(){
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    struct node* ptr  = (struct node*)malloc(sizeof(struct node));
    ptr = head;
    if(head == NULL){
        printf("List is empty");
        return;
    }
    else{
        temp = head;
        head = temp->next;
        head->prev = NULL;
        free(temp);
        return;
    }



}
int numOfnodes(){
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr = head;
    int count = 0;
    while(ptr != NULL){
        ptr = ptr->next;
        count++;
    }
    return count;
}
void rulePosition(){
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position = {0, 19};
    SetConsoleTextAttribute(screen, Green);
    SetConsoleCursorPosition(screen, position);
    printf("|_____________________________________________________________________________________|");
    COORD pos = {90, 8};
    SetConsoleCursorPosition(screen, pos);
    printf("Score: %d", score);
    COORD posi = {90, 10};
    SetConsoleCursorPosition(screen, posi);
    printf("Drops: %d", drops);
}
void display(int speed){
    HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position;
    rulePosition();
    SetConsoleTextAttribute(screen, Green);
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    //struct node* temp= (struct node*)malloc(sizeof(struct node));
    ptr = head;
    if(head == NULL)printf("List is empty..!!\n");
    else{
        while(ptr != NULL){
            rulePosition();
            ptr = head;
            for(int i = 0; i < numOfnodes(); i++){
            COORD position = {ptr->X, ptr->Y};
            SetConsoleCursorPosition(screen, position);
            ptr->Y = ptr->Y + 1;
            if(ptr->Y == 20){
            drops += 1;
            deleVal();
            }
            printf("%c", ptr->data);
            ptr = ptr->next;
            //Sleep(100);
            }
        if(drops == 10){
            return;
            }
            Sleep(speed);
            system("cls");
        if(_kbhit()){
            int Val = getch();
            deleByVal(Val);
            }
        }

    }
    return;
}
void end(){
    system("cls");

    printf("\n\t\tGame End...!! :)\t\t\n");
    printf("\t\tScore: %d", score);

    printf("\n\n\n");
    printf("\t\tThank you..!!\n\n");
}
void show(){
    struct node* ptr = (struct node*)malloc(sizeof(struct node));
    ptr = head;
    while(ptr != NULL){
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}
int main()
{
    enum {slow = 1000, fast = 500, expert = 100};
    int speed;
    printf("\n\n\n\t\t**Welcome to Raining Alphabets**\n");
    Sleep(2000);
    printf("\n\t\tPlease select difficulty level..\n\n\t\t1.Slow\n\t\t2.Fast\n\t\t3.Expert\n\t\t");
    scanf("%d",&speed);
    printf("\n\t=====> Ok.. Let's Begin..!!");
    if(speed == 1){
        speed = slow;
    }
    else if(speed == 2){
        speed = fast;
    }
    else if(speed == 3){
        speed = expert;
    }
    else{
        printf("\n\t\tInvalid choice\t\t");
        return 0;
    }
    Sleep(3000);

    while(drops != 10){
        insertVal();
        display(speed);
    }
    end();
    //printf("\nHello world!\n");
    return 0;
}
