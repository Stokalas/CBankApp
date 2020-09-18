#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "authentication.h"
#include "utilities.h"

/*Main authentication function, which calls other functions according to the choice of the user and returns folder of logged in user*/
FILE* authentication()
{
    char username[20];
    while(1){
        int alreadyRegistered = userInput();/*Taking user input*/
        if (alreadyRegistered == 3) break;/*If it returned 3, quiting app*/
        if(alreadyRegistered){/*If it was one allowing to login*/
            strcpy(username, login());/*Getting the username that logged in*/
            if(strcmp(username, ""))
            {
                username, username[strlen(username)-1] = 0;
                strncat(username, ".txt", 4);
                FILE* userData = fopen(username, "r+");
                if(userData == NULL){
                    printf("Failed to open the file of logged user, creating new file...\n");
                    delay(3);
                    userData = fopen(username, "w");
                    if(userData == NULL){
                        printf("Failed to create new file, logging off..");
                        continue;
                    }
                    fprintf(userData,"%s", "0");
                }
                clrscr();
                return(userData);
            }else
            {
                printf("login unsuccesfull\n");
            }
        }else{/*If choice was 0 - allowing to register*/
            registerNew();
            }
        }
    return 0;
}

/*This function allows user to choose if he wants to login or register*/
int userInput()
{
    int choice;/*Saves input of the user, which function returns*/
    clrscr();
    printf("If You already have an account press 1,\nif You don't have an account press 0\n");
    printf("If You want to quit, type 3\n");
    scanf("%d", &choice);
    return choice;/*If user wants to login, 1 is returned, if user wants to register - 0 returned, if user wants to quit - 3 returned*/
}

/*This function allows to enter username and password and checks if this info matches one in database*/
char* login(){
    char username[20];
    char password[20];
    char databaseLine[20];/*Used to read from database*/
    int usernameFound; /*Used to check if the username has been found, to not to print line in the end*/
    FILE *database;
    database = fopen("logins.txt", "r");

    /*Checking if it was possible to open text file*/
    if(database == NULL){
        printf("Failed to access database\n");
        delay(3);
        return NULL;
    }

    while(1){
    rewind(database);/*Each time resets to the start of file, to go through all data*/
    usernameFound = 0;/*Reseting value*/
    clrscr();
    printf("To return to authentication type 0 as your username\n");
    printf("Enter your username:\n");
    scanf("%s", username);

    /*If 0 entered as username, returns to authentication*/
    if(!strcmp(username, "0")){
        fclose(database);
        return NULL;
    }

    strncat(username, "\n",1);/*Adding \n at the end of both inputs, since ones read from file has it at the end*/
    printf("Enter your password: \n");
    scanf("%s", password);
    strncat(password, "\n",1);


    while (fgets(databaseLine, sizeof(databaseLine), database) != NULL)/*While not the end of file*/
    {
        if(!strcmp(username, databaseLine))/*Checking if such usernames matches*/
        {
           usernameFound = 1;/*Username found, no need to print message that such user does not exist*/
           fgets(databaseLine, sizeof(databaseLine), database);/*Taking password*/
           if(!strcmp(password, databaseLine)){/*If passwords match, login succesfull, string with username*/
             fclose(database);
             char *temp = username; /*variables are allocated on the stack, by default. But declaring a pointer, the value the pointers points to is allocated on the heap, and the heap is not cleared when the function ends.*/
             return temp;
           }else{/*If they don't, printing message and after 3 secons allowing to input logins again*/
               printf("Incorrect Password\n");
               delay(3);
               break;
           }
        }else
        {
            fgets(databaseLine, sizeof(databaseLine), database);/*If usernames does not match, skipping line of password as well*/
        }
    }
    if(!usernameFound){/*If no match for entered username found, printing this message*/
       printf("Incorrect Username, or user not registered\n");
       delay(3);
    }
    }

}

/*Function used to register new account*/
int registerNew()
{
    char username[20];
    char password[20];
    char passwordConfirm[20];/*Used for password confirmation*/
    while(1)
    {
        clrscr();
        printf("Registration\nTo exit type 0 as username\n");
        printf("Please enter your username: \n");
        scanf("%s", username);
        if(!strcmp(username, "0"))/*If 0 entered as username, returns to authentication*/
        {
            return -1;
        }
        if(checkIfUserExists(username)){/*If such user exists returning*/
            printf("This user is already registered!");
            delay(3);
            return -1;
        }
        printf("Enter your password: \n");
        scanf("%s", password);
        clrscr();
        printf("Confirm your password: \n");
        scanf("%s", passwordConfirm);
        if(!strcmp(password, passwordConfirm)){/*Checking if passwords match*/
            FILE *database;/*If they do, appending new user to the end of database file*/
            database = fopen("logins.txt", "a");
            if(database == NULL){
                printf("Failed to access database\n");
                return -1;
            }
            fprintf(database, "%s", username);
            fprintf(database, "%s", "\n");
            fprintf(database, "%s", password);
            fprintf(database, "%s", "\n");
            fclose(database);
            clrscr();
            printf("Account succesfully registered:%s", username);/*Printing message and after 3 seconds going to authentication*/
            strncat(username, ".txt", 4);
            FILE* newUser = fopen(username, "w");
            fprintf(newUser, "%s", "0");
            fclose(newUser);
            delay(3);
            return 1;
        }
        printf("Passwords does not match!\n");/*Printing and waiting to allow to register again if passwords didn't match*/
        delay(3);
    }



}

/*Used in registration, to ensure that no accounts have same username*/
int checkIfUserExists(char* username)
{
    strncat(username, "\n",1);
    char databaseLine[20];
    FILE* database = fopen("logins.txt", "r");

    /*Checking if it was possible to open text file*/
    if(database == NULL){
        printf("Failed to access database\n");
        return NULL;
    }

    while (fgets(databaseLine, sizeof(databaseLine), database) != NULL)/*While not the end of file*/
    {
        if(!strcmp(username, databaseLine))/*Checking if such usernames matches*/
        {
            username, username[strlen(username)-1] = 0;
            fclose(database);
            return 1;
        }
        fgets(databaseLine, sizeof(databaseLine), database);/*If usernames does not match, skipping line of password as well*/
    }
    username, username[strlen(username)-1] = 0;
    fclose(database);
    return 0; /*if no matches returning 0*/
}
