#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define SIZE 21

typedef enum{ False = 0, True = 1 } bool;
struct WebManager
{
	char Name[SIZE];
};
struct Users
{
	char name[SIZE];
	char password[SIZE];
	struct Projects** project_list;
	int projects_amount;
	struct Messages** message_list;
	int messages_amount;
};
struct Projects
{
	char name[SIZE];
	struct Users** users_list;
	int users_amount;
	struct Status** status_list;
	int status_amount;
	char** Manager_list;
	int manager_amount;

};
struct Status
{
	char name[SIZE];
	struct Tasks** tasks_list;
	int tasks_amount;
} Status;
struct Tasks
{
	char name[SIZE];
	char* task_details;
	bool task_progres;
	struct Users* assign_to;
};
struct Messages
{
	char sender[SIZE];
	char* content;
};
void signUp();
void cleanBuffer();
void log_in();
int String(char arry[SIZE]);
void cleanString(char arry[SIZE]);


int main(){
	//log_in();
	char yosu[20];
	scanf("%s", yosu);
	yosu[20-1] = NULL;
	printf("%s", yosu);

	return 0;
}

void signUp(){
	FILE* usersdb = fopen("users.txt", "w+");
	char name[20];
	fgets(name, SIZE, stdin);
	//if (name[SIZE - 1] = !'\0') printf("error");
	fprintf(usersdb, "*%s\n", name);
}
void cleanBuffer(){//clean the buffer
	char buffer;
	while (buffer = getchar(), buffer != '\n');
}
void cleanString(char arry[SIZE]){//If there are more letters than the size of the string string reset
	for (int i = 0; i < SIZE; i++){
		arry[i] = '\0';
	}
}
void log_in(){
	int Not_Valid_Pass = False, Not_Valid_Name = False, Not_Member=False, count = 0;
	char temp= '\0';
	char name[SIZE], password[SIZE];//open string
	do{
		do//loop for scan name and password
		{
			if (Not_Valid_Pass || Not_Valid_Name){//if we scan over the size we:
				cleanBuffer();//clean the buffer (temp)
				cleanString(name);//put null in the string
				printf("Invalid Username\n");//print error to user
				Not_Valid_Name = False;//restart the flag
			}
			printf("enter your users maximum chars [20]: "); //Writes the user what to do
			Not_Valid_Name = String(name);//Receiving a string if size of letters big then size of arry Raise Flag (notvalid)
		} while (Not_Valid_Name);//if notvalid = true -> loop
		do
		{
			if (Not_Valid_Pass){
				cleanBuffer();//clean the buffer (temp)
				cleanString(password);//put null in the string
				printf("Invalid Password\n");//print error to user
				Not_Valid_Pass = False;//restart the flag
			}
			printf("enter your Password maximum chars [20]: ");//Writes the user what to do
			Not_Valid_Pass = String(password);//Receiving a string if size of letters big then size of arry Raise Flag (notvalid)
		} while (Not_Valid_Pass);//if notvalid = true -> loop

	} while (Not_Member);
}
int String(char arry[SIZE]){//function to get string for user
	char temp = '\0';
	int count = 0;//flag
	while (temp = getchar(), temp != '\n'){//loop for get the string
		arry[count] = temp;
		count++;
		if (count > SIZE - 1)//if the string biger then size of arry exit from func and start again
			return True;
	}
	arry[count] = '\0';//put NULL in the end of string
	return False;
}