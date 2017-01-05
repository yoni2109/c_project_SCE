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
struct Messeges
{
	char sender[SIZE];
	char* content;
};
void signUp(){
	char name[20];
	scanf("%20s", name);
	//if (name[SIZE - 1] = !'\0') printf("error");
    printf("%s", name);
}
int main(){
	signUp();
}