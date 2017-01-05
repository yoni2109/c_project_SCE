#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define SIZE 20

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
void signUp(){
	FILE* usersdb = fopen("users.txt", "w+");
	char name[20];
	fgets(name,SIZE,stdin);
	//if (name[SIZE - 1] = !'\0') printf("error");
    fprintf(usersdb,"*%s\n", name);
}
void log_in_manager(){
	int notvalid = False, count = 0;
	char temp;
	char name[SIZE], password[SIZE];
	do
	{
		if (notvalid){
			temp = NULL;
			notvalid = False;
			for (int i = 0; i < SIZE; i++){
				name[i] = NULL;
			}
			count = 0;
			printf("Invalid Username\n");
		}
		printf("enter your users maximum chars [20]: ");
		while (temp = getchar(), temp != '\n' && !notvalid){
			name[count] = temp;
			count++;
			if (count > SIZE - 1)
				notvalid = True;
		}
	} while (notvalid);
	do
	{
		if (notvalid){
			temp = NULL;
			notvalid = False;
			for (int i = 0; i < SIZE - 1; i++){
				password[i] = NULL;
			}
			count = 0;
			printf("Invalid Password\n");
		}
		printf("enter your Password maximum chars [20]: ");
		while (temp = getchar(), temp != '\n' && !notvalid){
			password[count] = temp;
			count++;
			if (count > SIZE - 1)
				notvalid = True;
		}
	} while (notvalid);


}
int main(){
	signUp();


	return 0;
}