#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define SIZE 20

typedef enum{ False = 0, True = 1 } bool;
typedef struct
{
	char Name[SIZE];
} WebManager;

typedef struct
{
	char name[SIZE];
	char password[SIZE];
	Projects** project_list;
	int projects_amount;
	Messages** message_list;
	int messages_amount;
} Users;

typedef struct
{
	char name[SIZE];
	Users** users_list;
	int users_amount;
	Status** status_list;
	int status_amount;
	char** Manager_list;
	int manager_amount;

} Projects;

typedef struct
{
	char name[SIZE];
	Tasks** tasks_list;
	int tasks_amount;
} Status;

typedef struct
{
	char name[SIZE];
	char* task_details;
	bool task_progres;
	Users* assign_to;
} Tasks;

typedef struct
{
	char sender[SIZE];
	char* content;
} Messages;




int main(int argc, char** argv)
{










	return 0;
}