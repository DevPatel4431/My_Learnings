// Hello Programmers
// I am author of this code Dev Patel
// this is open source code of Sutdent Data Management System
// Time: November 2024
// Assignment of Computer Programming Subject of 1st Sem in Nirma University
// Feel Free to Use this Code 

#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<ctype.h>

#define ERROR_COLOR "\033[1;31m" // Bold Red
#define HEADER_COLOR "\033[96m" // Bright Cyan
#define OPTIONS_COLOR "\033[92m" // Light Green
#define INPUT_COLOR "\033[93m" // Bright Yellow
#define BRIGHT_MAGENTA "\033[95m" // Magenta
#define RESET "\033[0m" 
#define PASS "77777789"

int user_type = 0;

typedef struct DoB{
    int date;
    int month;
    int year;
}DoB;

typedef struct student{
    char RollNo[10];
    char name[20];
    char gender[10];
    DoB dob;
    char phonenum[11];
    char address[50];
}student;

void Menu();
void Menu_student();
void Menu_admin();
void add();
void view();
void search();
void edit();
void statistics();

void add(){

    student s;
    system("cls");
    printf(HEADER_COLOR "\n\t<---Enter New Student Data--->\n\n" RESET);

    printf(INPUT_COLOR "Enter the Roll No. of Student: " RESET);
    scanf("%[^\n]",s.RollNo);
    getchar();
    printf(INPUT_COLOR "Enter the Name of Student: " RESET);
    scanf("%[^\n]",s.name);
    getchar();
    printf(INPUT_COLOR "Enter Gender of Student: " RESET);
    scanf("%[^\n]",s.gender);
    getchar();
    printf(INPUT_COLOR "Enter the Date of Birth of Student (dd mm yyyy): " RESET);
    scanf("%d %d %d", &s.dob.date, &s.dob.month, &s.dob.year);
    getchar();
    printf(INPUT_COLOR "Enter the Phone No. of Student: " RESET);
    scanf("%[^\n]",s.phonenum);
    getchar();
    printf(INPUT_COLOR "Enter Address of Student: " RESET);
    scanf("%[^\n]",s.address);
    getchar();

    FILE* pf;
    pf = fopen("data.txt","a");
    if(pf == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the file.\n" RESET);
        return;
    }
    fwrite(&s,sizeof(student),1,pf);
    fclose(pf);

    printf("Enter any key to continue: ");
    char ch;
    scanf("%c",&ch);
    if(ch != '\0'){
        system("cls");
        Menu_admin();
    }
}

void view(){

    system("cls");
    printf(HEADER_COLOR "\n\t<---View All Students Data--->\n\n" RESET);
    student s;
    FILE *pf;
    pf = fopen("data.txt","r");

    if(pf == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the file.\n" RESET);
        return;
    }

    while(fread(&s, sizeof(student), 1, pf)){
        printf(OPTIONS_COLOR "Name:            " BRIGHT_MAGENTA "%s\n",s.name);
        printf(OPTIONS_COLOR "Roll No:         " BRIGHT_MAGENTA "%s\n",s.RollNo);
        printf(OPTIONS_COLOR "Gender:          " BRIGHT_MAGENTA "%s\n",s.gender);
        printf(OPTIONS_COLOR "Date of Birth:   " BRIGHT_MAGENTA "%02d/%02d/%04d\n",s.dob.date,s.dob.month,s.dob.year);
        printf(OPTIONS_COLOR "Phone Number:    " BRIGHT_MAGENTA "%s\n",s.phonenum);
        printf(OPTIONS_COLOR "Address:         " BRIGHT_MAGENTA "%s\n\n" RESET,s.address);
    }
    fclose(pf);

    printf("Enter any key to continue: ");
    char ch;
    scanf("%c",&ch);
    if(ch != '\0'){
        system("cls");
        if(user_type == 1){
            Menu_admin();
        }
        else if(user_type == 2){
            Menu_student();
        }
    }
}

void search(){

    system("cls");
    printf(HEADER_COLOR "\n\t<---Search a Student Data--->\n\n" RESET);
    char roll[10];
    printf(INPUT_COLOR "Enter the Roll No. of Student: " RESET);
    scanf("%[^\n]",roll);
    getchar();
    student s;

    FILE *pf;
    pf = fopen("data.txt","r");

    if(pf == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the file.\n" RESET);
        return;
    }
    int found = 0;
    while(fread(&s, sizeof(student), 1, pf)){
        if(strcmp(roll,s.RollNo)==0){
            printf(OPTIONS_COLOR "Name:            " BRIGHT_MAGENTA "%s\n",s.name);
            printf(OPTIONS_COLOR "Roll No:         " BRIGHT_MAGENTA "%s\n",s.RollNo);
            printf(OPTIONS_COLOR "Gender:          " BRIGHT_MAGENTA "%s\n",s.gender);
            printf(OPTIONS_COLOR "Date of Birth:   " BRIGHT_MAGENTA "%02d/%02d/%04d\n",s.dob.date,s.dob.month,s.dob.year);
            printf(OPTIONS_COLOR "Phone Number:    " BRIGHT_MAGENTA "%s\n",s.phonenum);
            printf(OPTIONS_COLOR "Address:         " BRIGHT_MAGENTA "%s\n\n" RESET,s.address);
            found = 1;
        }
    }
    if(!found){
        printf(ERROR_COLOR "\n\nNo Student Data found with Roll No. %s\n\n" RESET,roll);
    }
    printf("Enter any key to continue: ");
    char ch;
    scanf("%c",&ch);
    if(ch != '\0'){
        system("cls");
        if(user_type == 1){
            Menu_admin();
        }
        else if(user_type == 2){
            Menu_student();
        }
    }
}

void edit(){

    system("cls");
    printf(HEADER_COLOR "\n\t<---Edit Existing Student Data--->\n\n" RESET);
    char roll[10];
    printf(INPUT_COLOR "Enter the Roll No. of student you want to change: " RESET);
    scanf("%[^\n]",roll);
    getchar();

    FILE *pf1,*pf2;
    pf1 = fopen("data.txt","r");
    pf2 = fopen("data2.txt","w");
    
    if(pf1 == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the Data file.\n" RESET);
        return;
    }
    if(pf2 == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the Temperory file.\n" RESET);
        return;
    }
    
    student s;
    int found = 0;
    while(fread(&s, sizeof(student), 1, pf1)){
        if(strcmp(roll,s.RollNo) != 0){
            continue;
        }
        else{
            found = 1;
            break;
        }
    }
    if(!found){
        printf(ERROR_COLOR "\n\nNo student found with roll number %s.\nTry Again.\n" RESET, roll);
        remove("data2.txt");
        edit();
    }

    char yn;
    printf(INPUT_COLOR "Do you want to Change Roll No. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter the New Roll No. of student: " RESET);
        scanf("%[^\n]",s.RollNo);
        getchar();
    }

    printf(INPUT_COLOR "Do you want to Change Name of Student. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter the Name of Student: " RESET);
        scanf("%[^\n]",s.name);
        getchar();
    }

    printf(INPUT_COLOR "Do you want to Change Gender. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter Gender of Student: " RESET);
        scanf("%[^\n]",s.gender);
        getchar();
    }

    printf(INPUT_COLOR "Do you want to Change Date of Birth. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter the Date of Birth of Student (dd mm yyyy): " RESET);
        scanf("%d %d %d", &s.dob.date, &s.dob.month, &s.dob.year);
        getchar();
    }

    printf(INPUT_COLOR "Do you want to Change Phone No. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter the Phone No. of Student: " RESET);
        scanf("%[^\n]",s.phonenum);
        getchar();
    }
    
    printf(INPUT_COLOR "Do you want to Address. (Y/N): " RESET);
    yn = getchar();
    getchar();
    if(yn == 'y' || yn == 'Y'){
        printf(INPUT_COLOR "Enter Address of Student: " RESET);
        scanf("%[^\n]",s.address);
        getchar();
    }

    rewind(pf1); // Reset the file pointer

    student s1;
    found = 0;
    while(fread(&s1, sizeof(student), 1, pf1)){
        if(strcmp(roll,s1.RollNo) != 0){
            fwrite(&s1, sizeof(student), 1, pf2);
        }
        else{
            strcpy(s1.RollNo,roll);
            fwrite(&s, sizeof(student), 1, pf2);
            found = 1;
        }
    }

    fclose(pf1);
    fclose(pf2);
    
    if(found) {
        if(remove("data.txt") != 0){
            perror(ERROR_COLOR "Error deleting data.txt" RESET);
        }
        if(rename("data2.txt", "data.txt") != 0){
            perror(ERROR_COLOR "Error renaming data2.txt" RESET);
        }
        else{
            printf(OPTIONS_COLOR "\n\nRoll No. %s has been edited successfully\n\n" RESET, roll);
        }
    }
    else {
        printf(ERROR_COLOR "\n\nNo student found with roll number %s.\n" RESET, roll);
        remove("data2.txt");
    }

    printf("press any key continue ");
    char ch;
    scanf("%c",&ch);
    system("cls");
    if(ch !='\0'){
        Menu_admin();
    }
}

void delete(){
    
    system("cls");
    printf(HEADER_COLOR "\n\t<---Delete Existing Student Data--->\n\n" RESET);
    char roll[10];
    printf(INPUT_COLOR "Enter the Roll No. of student you want to delete: " RESET);
    scanf("%[^\n]",roll);
    char ch = getchar();

    FILE *pf1,*pf2;
    pf1 = fopen("data.txt","r");
    pf2 = fopen("data2.txt","a");

    if(pf1 == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the Data file.\n" RESET);
        return;
    }
    if(pf2 == NULL) {
        printf(ERROR_COLOR "Error: Unable to open the Temperory file.\n" RESET);
        return;
    }

    student s;
    int found = 0;
    while(fread(&s, sizeof(student), 1, pf1)){
        
        if(strcmp(roll,s.RollNo) != 0){
            fwrite(&s, sizeof(student), 1, pf2);
        }
        else{
            found = 1;
            continue;
        }
    }

    fclose(pf1);
    fclose(pf2);

    if(found){
        printf(OPTIONS_COLOR "Student with roll number %s has been deleted.\n" RESET,roll);
        remove("data.txt");
        rename("data2.txt", "data.txt");
    }
    else{
        printf(ERROR_COLOR "No student data found with roll number %s.\n" RESET, roll);
    }

    printf("press any key continue ");
    char c;
    scanf("%c",&c);
    system("cls");
    if(c !='\0'){
        Menu_admin();
    }
}

void statistics(){

    system("cls");
    printf(HEADER_COLOR "\n\t<---View Statistics of Students--->\n\n" RESET);
    FILE *pf = fopen("data.txt", "r");
    if(pf == NULL){
        printf(ERROR_COLOR "Error: Unable to open the file.\n" RESET);
        return;
    }

    student s[100];
    int count = 0;
    while(fread(&s[count], sizeof(student), 1, pf)){
        count++;
    }
    fclose(pf);

    if(count == 0){
        printf(ERROR_COLOR "No student data available to sort.\n" RESET);
        return;
    }
    int choicesort;
    startchoice:
    printf(HEADER_COLOR "Sort data by:\n" RESET);
    printf(OPTIONS_COLOR "1. Roll Number\n");
    printf("2. Date of Birth\n" RESET);
    printf(INPUT_COLOR "Enter your choice: " RESET);
    scanf("%d", &choicesort);
    getchar();
    system("cls");

    if(choicesort == 1){
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - 1 - i; j++) {
                if (strcmp(s[j].RollNo, s[j + 1].RollNo) > 0) {
                    student temp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = temp;
                }
            }
        }
    }
    else if(choicesort == 2){
        for(int i = 0; i < count - 1; i++){
            for(int j = 0; j < count - 1 - i; j++){
                if(s[j].dob.year > s[j + 1].dob.year || 
                   (s[j].dob.year == s[j + 1].dob.year && s[j].dob.month > s[j + 1].dob.month) || 
                   (s[j].dob.year == s[j + 1].dob.year && s[j].dob.month == s[j + 1].dob.month && s[j].dob.date > s[j + 1].dob.date)){
                    student temp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = temp;
                }
            }
        }
    }
    else{
        printf(ERROR_COLOR "Invalid choice.\n" RESET);
        goto startchoice;
        return;
    }
    printf(HEADER_COLOR "\nSorted Student Data:\n" RESET);
    for (int i = 0; i < count; i++) {
        printf(OPTIONS_COLOR "Name:            " BRIGHT_MAGENTA" %s\n" RESET, s[i].name);
        printf(OPTIONS_COLOR "Roll No:         " BRIGHT_MAGENTA" %s\n" RESET, s[i].RollNo);
        printf(OPTIONS_COLOR "Gender:          " BRIGHT_MAGENTA" %s\n" RESET, s[i].gender);
        printf(OPTIONS_COLOR "Date of Birth:   " BRIGHT_MAGENTA" %02d/%02d/%04d\n" RESET, s[i].dob.date, s[i].dob.month, s[i].dob.year);
        printf(OPTIONS_COLOR "Phone Number:    " BRIGHT_MAGENTA" %s\n" RESET, s[i].phonenum);
        printf(OPTIONS_COLOR "Address:         " BRIGHT_MAGENTA" %s\n\n" RESET, s[i].address);
    }

    printf("Enter any key to continue: ");
    char ch;
    scanf("%c", &ch);
    system("cls");

    if(user_type == 1){
        Menu_admin();
    }
    else if(user_type == 2){
        Menu_student();
    }
}

void Menu(){

    FILE *pf;
    pf = fopen("data.txt","r");
    if(pf == NULL){
        pf = fopen("data.txt","w");
        if(pf == NULL){
            printf(ERROR_COLOR "An ERROR Occurred.\nTry Again." RESET);
        }
    }
    fclose(pf);
    
    printf(HEADER_COLOR "\t<--:Enter Your Mode of Access:-->\n\n" RESET);
    printf(OPTIONS_COLOR"1. Admin\n");
    printf("2. Student\n" RESET);

    int temp;
    while(1){
        printf(INPUT_COLOR"Enter your mode: " RESET);
        mode:
        scanf("%d",&temp);
        if(temp != 1 && temp!=2){
            printf(ERROR_COLOR "Enter Valid Mode: " RESET);
            goto mode;
        }
        else if(temp == 2){
            user_type = 2;
            printf(OPTIONS_COLOR "\nAccess Granted!\n" RESET);
            break;
        }
        else{
            printf(INPUT_COLOR "Enter Password For Admin Mode: " RESET);
            char password[10];
            int i = 0;
            while(1){
                char ch = getch();
                if(ch == '\n' || ch == '\r'){
                    password[i] = '\0';
                    break;
                }
                else if(ch == '\b' && i > 0){
                    printf("\b \b");
                    i--;
                }
                else if(isprint(ch) && i<8){
                    password[i++] = ch;
                    printf("*");
                }
            }
            if(strcmp(PASS,password) == 0){
                user_type = 1;
                printf(OPTIONS_COLOR "\nAccess Granted!\n" RESET);
                break;
            }
            else{
                printf(ERROR_COLOR "\nINCORRECT PASSWORD" RESET);
                printf(INPUT_COLOR "\nEnter Mode Again: " RESET);
                goto mode;
            }
        }
    }

    getchar();
    printf("Enter any key to continue: ");
    char c;
    scanf("%c", &c);
    
    if(c != '\0'){
        system("cls");
        if(user_type == 1){
            Menu_admin();
        }
        else if(user_type == 2){
            Menu_student();
        }
    }
}

void Menu_student(){
    printf(HEADER_COLOR "\n\t<----MENU---->\n\n" RESET);
    printf(OPTIONS_COLOR "1. search Student\n");
    printf("2. View all Student data\n");
    printf("3. View Statistics\n");
    printf("4. exit\n\n" RESET);
    int choice = 0;
    printf(INPUT_COLOR "ENTER YOUR CHOICE: " RESET);
    scanf("%d",&choice);
    getchar();
    switch(choice){
        case 1:
            search();
            break;
        case 2:
            view();
            break;
        case 3:
            statistics();
            break;
        case 4:
            exit(0);
            break;
        default:
            printf(ERROR_COLOR "Invalid Choice.\n" RESET);
            printf(INPUT_COLOR "Enter any key to Try Again: " RESET);
            char ch;
            scanf("%c",&ch);

            if(ch != '\0'){
                system("cls");
                Menu_student();
            }
    }
}

void Menu_admin(){
    printf(HEADER_COLOR "\n\t<----MENU---->\n\n" RESET);
    printf(OPTIONS_COLOR"1. Add Student\n");
    printf("2. search Student\n");
    printf("3. View all Student\n");
    printf("4. Edit student data\n");
    printf("5. Delete Student\n");
    printf("6. View Statistics\n");
    printf("7. exit\n\n" RESET);
    int choice = 0;
    printf(INPUT_COLOR "ENTER YOUR CHOICE: " RESET);
    scanf("%d",&choice);
    getchar();
    switch(choice){
        case 1:
            add();
            break;
        case 2:
            search();
            break;
        case 3:
            view();
            break;
        case 4:
            edit();
            break;
        case 5:
            delete();
            break;
        case 6:
            statistics();
            break;
        case 7:
            exit(0);
            break;
        default:
            printf(ERROR_COLOR "Invalid Choice.\n" RESET);
            printf(INPUT_COLOR "Enter any key to Try Again: " RESET);
            char ch;
            scanf("%c",&ch);

            if(ch != '\0'){
                system("cls");
                Menu_admin();
            }
    }
}

int main(){
    system("cls");
    printf(HEADER_COLOR "\tWELCOME TO STUDENT DATA MANAGEMENT PORTAL\n\n" RESET);
    printf("Enter any key to continue: ");
    char ch;
    scanf("%c",&ch);

    if(ch != '\0'){
        system("cls");
        Menu();
    }
}