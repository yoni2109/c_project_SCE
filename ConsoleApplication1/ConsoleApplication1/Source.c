#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>


#define TEMP_SIZE 1024
#define SIZE 25
#define MODEOUT "w"
#define USER_FILE_NAME "users.txt"
#define PROJECTS_FILE_NAME "projects.txt"
#define ADMIN_FILE "web_manager.txt"
#define MESSAGE_FILE "messeges.txt"
#define MESSAGE_SIZE 200
#define TASKS_FILE "tasks.txt"
#define PROJECT_MANAGERS_FILE "projects_managers.txt"
#define UNIVERSAL_DIRECTOR "ADMIN"



typedef enum{ False = 0, True = 1 } bool;
typedef struct
{
	char target[SIZE];
	char sender[SIZE];
	char* content;

}Messages;
typedef struct
{
	char name[SIZE];
}WebManager;
typedef struct
{
	char name[SIZE];
	char password[SIZE];
	char** project_list;
	int projects_amount;
	Messages** message_list;
	int messages_amount;
}Users;
typedef struct
{
	char project_name[SIZE];
	char status_name[SIZE];
	char name[SIZE];
	char* task_details;
	bool task_progres;
	char assign_to[SIZE];
}Tasks;
typedef struct
{
	char name[SIZE];
	Tasks** tasks_list;
	int tasks_amount;
}Status;
typedef struct
{
	char name[SIZE];
	char** users_list;
	int users_amount;
	Status* status_list;
	int status_amount;
	char** Manager_list;
	int manager_amount;
	int archived;

}Projects;
void choose_user_to_remove();
void insert_details_for_signup();
char* new_user_name();
void move_task(int status, int task);
void new_project_name();
bool confirm_task(int, int);
void change_name();
bool scan_no1();
bool scan_no2();
bool scan_no3();
bool sort_tasks_no4();
bool sort_projects_to_users_no5();
bool scan_no6();
bool print_arrays_to_files();
bool sort_messages_to_users_no7();
bool print_no1();
bool print_no2();
bool print_no3();
bool print_no4();
bool add_new_project();
void print_user_projects();
bool signUp(char*, char*);
void cleanBuffer();
bool log_in();
int String(char arry[]);
void cleanString(char arry[]);
int check_member(char user[], char password[]);
int compareArrays(char user_from_list[], char user_from_member[]);
void play();
void system_massage();
void print_projects_task();
void print_web_users();
int check_admin(char * name);
int confirm_project();
bool fill_arrays();
void send_message(char *sender, char* target, char* message);
char * func_to_get_message();
void allocate_messages();
void send_message_about_new_task();
void change_pass();
void assigned_to(int, int);
void print_users();
void print_all_messages();
void print_login_singup();
int get_user_index_by_name();
bool add_user_to_project(int, char*);
int get_project_index(char*);
void defult_status_to_new_project();
void print_users_project();
bool new_task(char*, char*);
void print_tasks_array();
bool send_message_by_admin(char* message);
bool send_message_by_user(char *sender, char* target, char* message);
bool send_message_for_all_in_project(char *sender, char* message);
void manage_task(int status, int task);
void choose_task();
bool remove_user(int);
int choose_yes_or_no();
void add_Wmanager(int index_user);
void change_name();
bool exit_from_project();
void message_abute_task();
void change_status();
bool remove_user_from_project(int index_to_delete);
bool remove_task(int status, int task);
void print_project_menu(int);
int print_and_choose_user_projects();
void print_main_menu();
bool add_new_status(char*);
void print_chosen_user_menu(int, int);
void user_main_menu();
int get_user_index(char*username);
void print_user_messages();
int check_if_last_project(int index_project_to_check, int user_to_check);
void insert_username_to_add();
void manager_menu();
void delete_user_from_project_by_index_users_and_prpject(int project, int user);
void get_status_name();

WebManager* Wmanager;//will contain the web managet user name
Users* users_array;// will contain all web users
int web_users_amount = 0;//will contain the amount of users registered to web
Projects* projects_array;// will contain all web projects
int web_projects_amount = 0;//will contain the amount of all web projects
Messages* messages_array;// will contain all messages that moves on the web
int web_messages_amount = 0;//amount of all messages
Tasks* tasks_array;//will contain all tasks in web
int web_tasks_amount = 0;//tasks amount
int curr_index_user;//the current user after log in
int curr_index_project;
bool prmotoe_user_to_manger(int user_to_promote);
void archived_project_menu();

int main()
{
	int choose = 0;
	printf("choose 1 to play program or 2 to run tests\n");
	while (choose<1 || choose>2){
		scanf("%d", &choose);
		getchar();
	}
	switch (choose){
	case(1) : {
				  fill_arrays();
				  play();
				  free(messages_array);
				  free(users_array);
				  free(projects_array);
				  free(tasks_array);
				  break;
	}
	case(2) : {
				  Unit_tests();
				  web_messages_amount = 0;
				  web_users_amount = 0;
				  web_tasks_amount = 0;
				  web_projects_amount = 0;
				  free(messages_array);
				  free(users_array);
				  free(projects_array);
				  free(tasks_array);
				  break;
	}
	}

	return 0;
}

/*sign up*/
void insert_details_for_signup(){
	int member_Exist = False;
	char member[SIZE], password[SIZE];//open arry
	do//loop for sign up
	{
		if (member_Exist){//if user make mistake
			member_Exist = False;//reset the flag
			if (choose_yes_or_no())//print to user quiquestion if Continue if not return
				return;
		}
		printf("please enter a new member: ");//print to user Guidelines
		member_Exist = String(member);//get the user name from user
		if (!member_Exist){//if user name is correct get in loop
			for (int i = 0; i < web_users_amount && member_Exist == False; i++){//loop for check if user name in system
				if (!strcmp(users_array[i].name, member)){//return true if the user in system
					printf("this member Exists!\n");
					member_Exist = True;
				}
			}
		}
	} while (member_Exist);
	printf("pleaes enter password without space: ");//Manual
	do
	{
		if (member_Exist){//if user make mistake
			member_Exist = False;//reset the flag
			if (choose_yes_or_no()){//check if the user want to continue
				return;
			}
			printf("please enter password again: ");//print to user massage
		}
		member_Exist = String(password);//get password from user
	} while (member_Exist);
	return signUp(member, password);
}
bool signUp(char* member, char* password){

	users_array = (Users*)realloc(users_array, (web_users_amount + 1)*sizeof(Users));
	if (users_array == NULL){//if not open quit
		return False;
	}
	web_users_amount++;
	strcpy(users_array[web_users_amount - 1].name, member);
	strcpy(users_array[web_users_amount - 1].password, password);
	users_array[web_users_amount - 1].messages_amount = 0;
	users_array[web_users_amount - 1].projects_amount = 0;
	return True;
}
void cleanBuffer(){//clean the buffer
	char buffer;
	while (buffer = getchar(), buffer != '\n');
}
void cleanString(char arry[]){//If there are more letters than the size of the string-> string reset
	for (int i = 0; arry[i] != '\0'; i++){
		arry[i] = '\0';
	}
}
bool log_in(){
	int Not_Valid_Pass = False, Not_Valid_Name = False, Not_Member = True;
	char password[SIZE], member[SIZE];//open string
	do{
		if (!Not_Member){//if user make mistake 
			printf("wrong member or password\n");//print error
			return False;//return to loby\main
		}
		do//loop for scan name and password
		{
			if (Not_Valid_Pass || Not_Valid_Name){//if we scan over the size we:
				printf("Invalid Username\n");//print error to user
				Not_Valid_Name = False;//restart the flag
				if (choose_yes_or_no())
					return False;
			}
			printf("enter your users maximum chars [%d]: ", SIZE - 1); //Writes the user what to do
			Not_Valid_Name = String(member);//Receiving a string if size of letters big then size of arry Raise Flag (notvalid)
		} while (Not_Valid_Name);//if notvalid = true -> loop
		do
		{
			if (Not_Valid_Pass){
				printf("Invalid Password\n");//print error to user
				Not_Valid_Pass = False;//restart the flag
				if (choose_yes_or_no())
					return False;
			}
			printf("enter your Password maximum chars [%d]: ", SIZE - 1);//Writes the user what to do
			Not_Valid_Pass = String(password);//Receiving a string if size of letters big then size of arry Raise Flag (notvalid)
		} while (Not_Valid_Pass);//if notvalid = true -> loop
		Not_Member = check_member(member, password);//check if appropriate password to use
	} while (!Not_Member);


	return True;
}
int String(char arry[]){//function to get string for user
	char temp = '\0';
	int count = 0;//flag
	while (temp = getchar(), temp != '\n'){//loop for get the string
		arry[count] = temp;//put temp in arry
		if (temp == ' '){//if temp = space(name with space) close arry with end char and return error
			arry[count] = '\0';
			while (temp = getchar(), temp != '\n');
			printf("please enter with out space\n");
			return True;
		}
		count++;
		if (count > SIZE - 1){//if the string biger then size of arry exit from func and start again{
			arry[count - 1] = '\0';//close arry with end char
			return True;
		}
	}
	arry[count] = '\0';//put \0-> end of string in the end of string
	return False;
}
int check_member(char user[], char password[]){
	for (int i = 0; i < web_users_amount; i++){//loop for check if member exist
		if (!strcmp(users_array[i].name, user)){//open function if user exsist check password
			if (!strcmp(users_array[i].password, password)){//If appropriate password to use
				curr_index_user = i;
				return True;
			}
			return False;
		}
	}
	return False;
}
int choose_yes_or_no(){//function to ask the user if exit to loby/main
	char temp = '\0';
	printf("you want enter again if so enter Y else enter other key: ");//massage to user
	scanf("%c", &temp);//scan flag
	if (!(temp == 'y' || temp == 'Y')){//if flag = y(yes) continue
		cleanBuffer();//clean buffer
		return True;
	}
	cleanBuffer();
	return False;
}
/*reading files and arrays sorting functions*/
bool fill_arrays(){
	/*1. scans user names and passwords into users array*/
	scan_no1();
	/*end of 1.*/
	/*2. scan all projects and users that assigned to it from projects file*/
	scan_no2();
	/*end of 2.*/
	/*3. scan all tasks to tasks global array*/
	scan_no3();
	/*end of  3.*/
	/*4. sort tasks to projects*/
	sort_tasks_no4();
	/*end of 4.*/
	/*5. sort projects to users*/
	sort_projects_to_users_no5();
	/*end of 5.*/
	/*6. scan messages to messages global array*/
	scan_no6();
	/*end of 6.*/
	/*7. sort messages into users*/
	sort_messages_to_users_no7();
	/*end of 7.*/

	return True;
}

bool scan_no1()
{
	FILE* wmanager = fopen(ADMIN_FILE, "r");
	if (!wmanager)
	{
		return False;
	}
	Wmanager = (WebManager*)malloc(sizeof(WebManager));
	fscanf(wmanager, "%s", &Wmanager->name);
	FILE* users_File = fopen(USER_FILE_NAME, "r");
	if (!users_File)
	{
		return False;
	}
	fscanf(users_File, "%d", &web_users_amount);
	users_array = (Users*)malloc(sizeof(Users)*web_users_amount);
	for (int i = 0; i < web_users_amount; i++){
		fscanf(users_File, "%s", &users_array[i].name);
		//users_array[i].name[SIZE - 1] = '/0';
		users_array[i].projects_amount = 0;
		users_array[i].messages_amount = 0;
		fscanf(users_File, "%s", &users_array[i].password);
	}
	fclose(users_File);

	return True;
}

bool scan_no2()
{
	FILE* projects_file = fopen(PROJECTS_FILE_NAME, "r");
	if (!projects_file)
	{
		return False;
	}
	FILE* projects_managers_file = fopen(PROJECT_MANAGERS_FILE, "r");
	if (!projects_managers_file)
	{
		return False;
	}
	fscanf(projects_file, "%d", &web_projects_amount);
	projects_array = (Projects*)malloc(sizeof(Projects)*web_projects_amount);
	if (projects_array == NULL)
	{
		return False;
	}
	for (int i = 0; i < web_projects_amount; i++){
		fscanf(projects_file, "%s", &projects_array[i].name);
		fscanf(projects_file, "%d", &projects_array[i].users_amount);
		projects_array[i].users_list = (char**)malloc(sizeof(char*)*projects_array[i].users_amount + 1);
		if (projects_array[i].users_list == NULL)
		{
			return False;
		}
		for (int j = 0; j < projects_array[i].users_amount; j++){
			char temp[SIZE];
			projects_array[i].users_list[j] = (char*)malloc(sizeof(char)*SIZE);
			if (projects_array[i].users_list[j] == NULL)
			{
				return False;
			}
			fscanf(projects_file, "%s", &temp);
			strcpy(projects_array[i].users_list[j], temp);
		}
		char temp[SIZE];
		fscanf(projects_managers_file, "%s", &temp);
		fscanf(projects_managers_file, "%d", &projects_array[i].manager_amount);
		projects_array[i].Manager_list = (char**)malloc(sizeof(char*)*projects_array[i].manager_amount);
		if (projects_array[i].Manager_list == NULL)
		{
			return False;
		}
		for (int j = 0; j < projects_array[i].manager_amount; j++){
			projects_array[i].Manager_list[j] = (char*)malloc(sizeof(char)*SIZE);
			if (projects_array[i].Manager_list[j] == NULL)
			{
				return False;
			}
			char temp[SIZE];
			fscanf(projects_managers_file, "%s", &temp);
			strcpy(projects_array[i].Manager_list[j], temp);

		}
		fscanf(projects_file, "%d", &projects_array[i].status_amount);
		projects_array[i].status_list = (Status*)malloc(sizeof(Status)*projects_array[i].status_amount);
		if (projects_array[i].status_list == NULL)
		{
			return False;
		}
		for (int j = 0; j < projects_array[i].status_amount; j++){
			fscanf(projects_file, "%s", &projects_array[i].status_list[j].name);
			projects_array[i].status_list[j].tasks_amount = 0;
		}
		fscanf(projects_file, "%d", &projects_array[i].archived);
	}
	fclose(projects_file);
	fclose(projects_managers_file);

	return True;
}

bool scan_no3(){
	FILE* tasks_file = fopen(TASKS_FILE, "r");
	if (!tasks_file)
	{
		return False;
	}
	fscanf(tasks_file, "%d", &web_tasks_amount);
	tasks_array = (Tasks*)malloc(sizeof(Tasks)*web_tasks_amount);
	if (tasks_array == NULL)
	{
		return False;
	}
	for (int i = 0; i < web_tasks_amount; i++){
		fscanf(tasks_file, "%s %s %s", &tasks_array[i].project_name, &tasks_array[i].status_name, &tasks_array[i].name);
		char temp[TEMP_SIZE];
		int j = 0;
		fgetc(tasks_file);
		while ((temp[j++] = fgetc(tasks_file)) != '\n');
		temp[j - 1] = '\0';
		tasks_array[i].task_details = (char*)malloc(sizeof(char)*strlen(temp));
		if (tasks_array[i].task_details == NULL)
		{
			return False;
		}
		strcpy(tasks_array[i].task_details, temp);
		fscanf(tasks_file, "%d %s", &tasks_array[i].task_progres, &tasks_array[i].assign_to);
	}
	fclose(tasks_file);

	return True;
}

bool sort_tasks_no4(){
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < projects_array[i].status_amount; j++){
			projects_array[i].status_list[j].tasks_amount = 0;
		}
	}
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < web_tasks_amount; j++){
			if (!strcmp(projects_array[i].name, tasks_array[j].project_name)){
				for (int k = 0; k < projects_array[i].status_amount; k++){
					if (!strcmp(projects_array[i].status_list[k].name, tasks_array[j].status_name)){
						if (!projects_array[i].status_list[k].tasks_amount){
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks**)malloc(sizeof(Tasks*));
							if (projects_array[i].status_list[k].tasks_list == NULL)
							{
								return False;
							}
							projects_array[i].status_list[k].tasks_list[0] = &tasks_array[j];

						}
						else{
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks**)realloc(projects_array[i].status_list[k].tasks_list, projects_array[i].status_list[k].tasks_amount*sizeof(Tasks*));
							if (projects_array[i].status_list[k].tasks_list == NULL)
							{
								return False;
							}
							projects_array[i].status_list[k].tasks_list[projects_array[i].status_list[k].tasks_amount - 1] = &tasks_array[j];
						}
					}
				}

			}
		}

	}

	return True;
}

bool sort_projects_to_users_no5(){
	for (int i = 0; i < web_users_amount; i++){
		for (int j = 0; j < web_projects_amount; j++){
			for (int k = 0; k < projects_array[j].users_amount; k++){
				if (!strcmp(users_array[i].name, projects_array[j].users_list[k])){
					if (!users_array[i].projects_amount){
						users_array[i].projects_amount++;
						users_array[i].project_list = (char**)malloc(sizeof(char*));
						if (users_array[i].project_list == NULL)
						{
							return False;
						}
						users_array[i].project_list[0] = (char*)malloc(sizeof(char)*SIZE);
						if (users_array[i].project_list[0] == NULL)
						{
							return False;
						}
						strcpy(users_array[i].project_list[0], projects_array[j].name);
					}
					else{
						users_array[i].projects_amount++;
						users_array[i].project_list = (char**)realloc(users_array[i].project_list, users_array[i].projects_amount*sizeof(char*));
						if (users_array[i].project_list == NULL)
						{
							return False;
						}
						users_array[i].project_list[users_array[i].projects_amount - 1] = (char*)malloc(sizeof(char)*SIZE);
						if (users_array[i].project_list[users_array[i].projects_amount - 1] == NULL)
						{
							return False;
						}
						strcpy(users_array[i].project_list[users_array[i].projects_amount - 1], projects_array[j].name);
					}
				}
			}
		}
	}

	return True;
}

bool scan_no6(){
	FILE* messages_file = fopen(MESSAGE_FILE, "r");
	if (!messages_file)
	{
		return False;
	}
	fscanf(messages_file, "%d", &web_messages_amount);
	messages_array = (Messages*)malloc(sizeof(Messages)*web_messages_amount);
	if (messages_array == NULL)
	{
		return False;
	}
	for (int i = 0; i < web_messages_amount; i++){
		fscanf(messages_file, "%s", &messages_array[i].sender);
		fscanf(messages_file, "%s", &messages_array[i].target);
		char temp[MESSAGE_SIZE];
		int j = 0;
		fgetc(messages_file);
		while ((temp[j++] = fgetc(messages_file)) != '\n');
		temp[j - 1] = '\0';
		messages_array[i].content = (char*)malloc(sizeof(char)*strlen(temp));
		if (messages_array[i].content == NULL)
		{
			return False;
		}
		for (j = 0; j < strlen(temp); j++){
			messages_array[i].content[j] = temp[j];
		}
		messages_array[i].content[j] = '\0';
	}
	fclose(messages_file);

	return True;
}

bool sort_messages_to_users_no7()
{
	for (int i = 0; i < web_users_amount; i++){
		for (int j = 0; j < web_messages_amount; j++){
			if (!strcmp(users_array[i].name, messages_array[j].target)){
				if (!users_array[i].messages_amount){
					users_array[i].messages_amount++;
					users_array[i].message_list = (Messages**)malloc(sizeof(Messages*));
					if (users_array[i].message_list == NULL)
					{
						return False;
					}
					users_array[i].message_list[0] = &messages_array[j];
				}
				else{
					users_array[i].messages_amount++;
					users_array[i].message_list = (Messages**)realloc(users_array[i].message_list, users_array[i].messages_amount*sizeof(Messages*));
					if (users_array[i].message_list == NULL)
					{
						return False;
					}
					users_array[i].message_list[users_array[i].messages_amount - 1] = &messages_array[j];
				}
			}
		}
	}

	return True;
}
/*end of reading files and arrays sorting functions */
/*print arrays to files functions*/
bool print_arrays_to_files(){
	/*1. prints users array*/
	print_no1();
	/*end of 1.*/
	/*2. print projects array*/
	print_no2();
	/*end of 2.*/
	/*3. print tasks to files*/
	print_no3();
	/*4. print messages to file*/
	print_no4();
	/*end of 4.*/
	return True;
}
bool print_no1(){
	FILE* users_file = fopen(USER_FILE_NAME, "w");
	if (users_file == NULL)
	{
		return False;
	}
	fprintf(users_file, "%d\n", web_users_amount);
	for (int i = 0; i < web_users_amount; i++){
		fprintf(users_file, "%s\n%s\n", users_array[i].name, users_array[i].password);
	}
	fclose(users_file);

	return True;
}
bool print_no2(){
	FILE* projects_file = fopen(PROJECTS_FILE_NAME, "w");
	if (projects_file == NULL)
	{
		return False;
	}
	FILE* project_managers = fopen(PROJECT_MANAGERS_FILE, "w");
	if (project_managers == NULL)
	{
		return False;
	}
	fprintf(projects_file, "%d\n", web_projects_amount);
	for (int i = 0; i < web_projects_amount; i++){
		fprintf(projects_file, "%s\n%d\n", projects_array[i].name, projects_array[i].users_amount);
		for (int j = 0; j < projects_array[i].users_amount; j++){
			fprintf(projects_file, "%s\n", projects_array[i].users_list[j]);
		}
		fprintf(projects_file, "%d\n", projects_array[i].status_amount);
		for (int j = 0; j < projects_array[i].status_amount; j++){
			fprintf(projects_file, "%s\n", projects_array[i].status_list[j].name);
		}
		fprintf(projects_file, "%d\n", projects_array[i].archived);
		fprintf(project_managers, "%s\n%d\n", projects_array[i].name, projects_array[i].manager_amount);
		for (int j = 0; j < projects_array[i].manager_amount; j++){
			fprintf(project_managers, "%s\n", projects_array[i].Manager_list[j]);
		}
	}
	fclose(projects_file);
	fclose(project_managers);

	return True;
}
bool print_no3(){
	FILE* tasks_file = fopen(TASKS_FILE, "w");
	if (tasks_file == NULL)
	{
		return False;
	}
	fprintf(tasks_file, "%d\n", web_tasks_amount);
	for (int i = 0; i < web_tasks_amount; i++){
		fprintf(tasks_file, "%s\n%s\n%s\n%s\n%d\n%s\n", tasks_array[i].project_name, tasks_array[i].status_name, tasks_array[i].name, tasks_array[i].task_details, tasks_array[i].task_progres, tasks_array[i].assign_to);
	}
	fclose(tasks_file);

	return True;
}
bool print_no4(){
	FILE* messages_file = fopen(MESSAGE_FILE, "w");
	if (messages_file == NULL)
	{
		return False;
	}
	fprintf(messages_file, "%d\n", web_messages_amount);
	for (int i = 0; i < web_messages_amount; i++){
		fprintf(messages_file, "%s\n%s\n%s\n", messages_array[i].sender, messages_array[i].target, messages_array[i].content);
	}
	fclose(messages_file);

	return True;
}
/*end of print arrays to files functions*/
int print_and_choose_user_projects(){
	int chosen_proj;
	system("cls");
	printf("Those Your projects:\n");
	for (int i = 0; i < users_array[curr_index_user].projects_amount; i++){
		printf("%d. %s", (i + 1), users_array[curr_index_user].project_list[i]);
		if (projects_array[get_project_index(users_array[curr_index_user].project_list[i])].archived){
			printf(" **project is archived**");
		}
		printf("\n");
	}
	printf("Choose Project By Number:\nchoose 0 to go back\n");
	scanf("%d", &chosen_proj);
	getchar();//get the enter
	if (chosen_proj == 0){
		return -1;
	}
	return get_project_index(users_array[curr_index_user].project_list[chosen_proj - 1]);
}
void print_projects_task(){
	printf("Tasks In Project:\n");
	for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
		printf("%d. %s", (i + 1), (projects_array[curr_index_project].status_list[0]).tasks_list[i]->name);
	}
}
int check_admin(char * name){
	if (!strcmp(name, Wmanager->name)) return True;//check if the name that func get is the same name as web manager
	else return False;
}
void print_web_users(){
	printf("Those All Site Members:\n");
	for (int i = 0; i < web_users_amount; i++){//loop to print all users
		printf("%d.%s\n", (i + 1), users_array[i].name);
	}
}
int confirm_project(){//func to archived the project *only maneger can do that*
	for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){//loop to check if manager exists in the managers array 
		if (!strcmp(projects_array[curr_index_project].Manager_list[i], users_array[curr_index_user].name)){
			projects_array[curr_index_project].archived = True;//if we found we will change the archived variable to True
			return 1;
		}
	}
	return -1;
}
bool send_message_by_user(char *sender, char* target, char *message){
	web_messages_amount++;
	if (web_messages_amount == 1){
		messages_array = (Messages*)malloc(sizeof(Messages));
		if (messages_array == NULL)
		{
			return False;
		}
	}
	else{
		messages_array = (Messages*)realloc(messages_array, web_messages_amount * sizeof(Messages));//realloc 1 place for new message
		if (messages_array == NULL)
		{
			return False;
		}
		messages_array[web_messages_amount - 1].content = (char*)malloc(strlen(message)*sizeof(char));//Opening indicates the size of the array
		if (messages_array[web_messages_amount - 1].content == NULL)
		{
			return False;
		}
		strcpy(messages_array[web_messages_amount - 1].content, message);//העתקות לתוך מערך
		strcpy(messages_array[web_messages_amount - 1].sender, sender);
		strcpy(messages_array[web_messages_amount - 1].target, target);
		sort_messages_to_users_no7();
		if (strcmp(message, "test")){
			printf("\nMessage succesfully sent\n");
		}
		return True;
	}
}
bool send_message_by_admin(char *message){
	int j = 0;
	messages_array = (Messages*)realloc(messages_array, (web_messages_amount + web_users_amount) * sizeof(Messages));//realloc 1 place for new message
	if (!messages_array){
		return False;
	}
	for (int i = web_messages_amount; i < web_users_amount + web_users_amount; i++){
		messages_array[i - 1].content = (char*)malloc(strlen(message)*sizeof(char));//Opening indicates the size of the array
		strcpy(messages_array[i - 1].content, message);//העתקות לתוך מערך
		strcpy(messages_array[i - 1].sender, "ADMIN");
		strcpy(messages_array[i - 1].target, users_array[j].name);
		j++;
	}
	web_messages_amount += web_users_amount;
	sort_messages_to_users_no7();
	if (strcmp(message, "test")){
		printf("\nMessage succesfully sent\n");
	}
	return True;
}
bool send_message_for_all_in_project(char *sender, char* message_demand){//פונקציה לשליחת הודעה לחברי הפרויקט מקבלת שולח אינדקס פרויקט והודעה
	int j = 0;
	messages_array = (Messages*)realloc(messages_array, (web_messages_amount + projects_array[curr_index_project].users_amount) * sizeof(Messages));//realloc 1 place for new message
	if (!messages_array){
		return False;
	}
	for (int i = web_messages_amount; i < web_messages_amount + projects_array[curr_index_project].users_amount; i++){
		messages_array[i].content = (char*)malloc(strlen(message_demand)*sizeof(char));//Opening indicates the size of the array
		if (messages_array[i].content == NULL)
		{
			return False;
		}
		strcpy(messages_array[i].content, message_demand);//העתקות לתוך מערך
		strcpy(messages_array[i].sender, sender);
		strcpy(messages_array[i].target, projects_array[curr_index_project].users_list[j]);
		j++;
	}
	web_messages_amount += projects_array[curr_index_project].users_amount;
	sort_messages_to_users_no7();
	if (strcmp(message_demand, "test")){
		printf("\nMessage succesfully sent\n");
	}
	return True;
}
void change_pass(){
	char temp_pass[SIZE];
	printf("Enter New Pass:\n");
	int accept = String(temp_pass);//get new password
	if (!accept){
		strcpy(users_array[curr_index_user].password, temp_pass);
	}
}
void change_name(){

	//func to change user name
	char temp_name[SIZE];
	strcpy(temp_name, new_user_name());
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < projects_array[i].users_amount; j++){
			if (!strcmp(users_array[curr_index_user].name, projects_array[i].users_list[j])){
				free(projects_array[i].users_list[j]);
				projects_array[i].users_list[j] = (char*)malloc(sizeof(char)*SIZE);
				strcpy(projects_array[i].users_list[j], temp_name);
			}
		}
		for (int j = 0; j < projects_array[i].manager_amount; j++){
			if (!strcmp(users_array[curr_index_user].name, projects_array[i].Manager_list[j])){
				free(projects_array[i].Manager_list[j]);
				projects_array[i].Manager_list[j] = (char*)malloc(sizeof(char)*SIZE);
				strcpy(projects_array[i].Manager_list[j], temp_name);
			}
		}
	}
	for (int i = 0; i < web_tasks_amount; i++){
		if (!strcmp(users_array[curr_index_user].name, tasks_array[i].assign_to)){
			strcpy(tasks_array[i].assign_to, temp_name);
		}
	}
	strcpy(users_array[curr_index_user].name, temp_name);
}
void assigned_to(int status, int task){
	int  chosen_user;//indicates the users choice
	printf("Choose The User That Will Perform The Task :\n");
	for (int i = 0; i < projects_array[curr_index_project].users_amount; i++){/*print all users in current project*/
		printf("%d: %s\n", (i + 1), projects_array[curr_index_project].users_list[i]);
	}
	scanf("%d", &chosen_user);/*ask user to choose username*/
	/*copy the selected name to selected task at "assigned to" field*/
	strcpy(projects_array[curr_index_project].status_list[status].tasks_list[task]->assign_to, projects_array[curr_index_project].users_list[chosen_user - 1]);
}
void print_users(){
	for (int i = 0; i < web_users_amount; i++){//loop to run array users
		printf("name:%s ", users_array[i].name);
		printf("password:%s\n", users_array[i].password);
		//printf("message messages_amount :%d ", users_array[i].messages_amount);
		for (int j = 0; j < users_array[i].messages_amount; j++){//print user messages
			printf("message:%s *", users_array[i].message_list);
		}
		printf("\n");
		printf("projects_amount :%d ", users_array[i].projects_amount);//print users projects
		for (int j = 0; j < users_array[i].projects_amount; j++){
			printf("projects:%s ", users_array[i].project_list[j]);
		}
		printf("\n");
	}
}
void print_all_messages()
{
	for (int i = 0; i < web_messages_amount; i++){//print all messages from array
		printf("# # #Message #%d # # #\n", (i + 1));
		printf("The Sender : %s\n", messages_array[i].sender);
		printf("The Target : %s\n", messages_array[i].target);
		printf("Content : %s\n", messages_array[i].content);
	}
}
void insert_username_to_add(){
	char temp_user[SIZE];
	int flag = -1, index_try = 0;
	while (flag == -1){//loop to get the name of user that we want add - if there is no exist this user - again
		printf("Enter user name that You want add to project [20 chars] : \n");
		fgets(temp_user, SIZE, stdin);
		temp_user[strlen(temp_user) - 1] = '\0';
		index_try++;
		for (int i = 0; i < projects_array[curr_index_project].users_amount; i++){
			if (!strcmp(projects_array[curr_index_project].status_list[i].name, temp_user)){
				printf("this user is already a member in this project");
				return;
			}
		}
		for (int i = 0; i < web_users_amount; i++){//loop to find the user in web array users
			if (strcmp(temp_user, users_array[i].name) == 0) flag = i;
		}
		if (index_try == 3){
			return;
		}

	}
	return add_user_to_project(flag, temp_user);
}
bool add_user_to_project(int flag, char* temp_user){//fund to add new user to project
	if (flag == -1){
		return False;

	}

	projects_array[curr_index_project].users_amount++;//increase the amount of users in the project
	projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*projects_array[curr_index_project].users_amount);//increas by one the users list
	if (projects_array[curr_index_project].users_list == NULL)
	{
		return False;
	}
	projects_array[curr_index_project].users_list[projects_array[curr_index_project].users_amount - 1] = (char*)malloc(sizeof(char)* 25);//allocate new memory 
	if (projects_array[curr_index_project].users_list[projects_array[curr_index_project].users_amount - 1] == NULL)
	{
		return False;
	}
	strcpy(projects_array[curr_index_project].users_list[projects_array[curr_index_project].users_amount - 1], temp_user);//copy the new name 
	users_array[flag].projects_amount++;
	if (users_array[flag].projects_amount == 1){
		users_array[flag].project_list = (char**)malloc(sizeof(char*));
		if (users_array[flag].project_list == NULL)
		{
			return False;
		}
	}
	else
	{
		users_array[flag].project_list = (char**)realloc(users_array[flag].project_list, sizeof(char*)*users_array[flag].projects_amount);
		if (users_array[flag].project_list == NULL)
		{
			return False;
		}
	}
	users_array[flag].project_list[users_array[flag].projects_amount - 1] = (char*)malloc(sizeof(char)*SIZE);
	if (users_array[flag].project_list[users_array[flag].projects_amount - 1] == NULL)
	{
		return False;
	}
	strcpy(users_array[flag].project_list[users_array[flag].projects_amount - 1], projects_array[curr_index_project].name);

	return True;
}
void defult_status_to_new_project(){
	projects_array[web_projects_amount - 1].status_amount = 4;
	projects_array[web_projects_amount - 1].status_list = (Status*)malloc(sizeof(Status)*projects_array[web_projects_amount - 1].status_amount);
	if (projects_array[web_projects_amount - 1].status_list == NULL)
	{
		printf("error ellocation");
		exit(1);
	}
	strcpy(projects_array[web_projects_amount - 1].status_list[0].name, "Elicitation");
	strcpy(projects_array[web_projects_amount - 1].status_list[1].name, "Analasys");
	strcpy(projects_array[web_projects_amount - 1].status_list[2].name, "VandV");
	strcpy(projects_array[web_projects_amount - 1].status_list[3].name, "Approved");
	projects_array[web_projects_amount - 1].status_list[0].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[1].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[2].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[3].tasks_amount = 0;
}
void new_project_name(){
	int flag = 0;
	printf("\nInsert your Project Name:(projects name must be up to 25 characters)\n");
	char temp1[1024], *temp;
	while (!flag){
		fgets(temp1, 1024, stdin);
		temp1[strlen(temp1) - 1] = '\0';
		if (strlen(temp1) > 25)
			printf("the inserted name is too long pls try again!\n");
		else flag = 1;
		for (int i = 0; i < web_projects_amount; i++){
			if (!strcmp(temp1, projects_array[i].name)){
				printf("this name is already taken, pls choose another name\n");
				flag = 0;
				i = web_projects_amount;
			}
		}
	}
	for (int i = 0; i < strlen(temp1); i++){
		if (temp1[i] == 32){
			temp1[i] = '_';
		}
	}
	temp = (char*)malloc(sizeof(char)*SIZE);
	if (temp == NULL)
	{
		printf("error ellocation");
		exit(1);
	}
	for (int i = 0; i < strlen(temp1); i++){
		temp[i] = temp1[i];
	}
	temp[strlen(temp1)] = '\0';
	return add_new_project(temp);
}
bool add_new_project(char* temp){
	/**/
	if (!web_projects_amount){
		web_projects_amount++;
		projects_array = (Projects*)malloc(sizeof(Projects));
		if (projects_array == NULL)
		{
			return False;
		}
	}
	else{
		web_projects_amount++;
		projects_array = (Projects*)realloc(projects_array, sizeof(Projects)* web_projects_amount);
		if (projects_array == NULL)
		{
			return False;
		}
	}
	strcpy(projects_array[web_projects_amount - 1].name, temp);
	projects_array[web_projects_amount - 1].users_amount = 1;
	projects_array[web_projects_amount - 1].manager_amount = 1;
	projects_array[web_projects_amount - 1].users_list = (char**)malloc(sizeof(char*));
	if (projects_array[web_projects_amount - 1].users_list == NULL)
	{
		return False;
	}
	projects_array[web_projects_amount - 1].users_list[0] = (char*)malloc(sizeof(char)*strlen(users_array[curr_index_user].name));
	if (projects_array[web_projects_amount - 1].users_list[0] == NULL)
	{
		return False;
	}
	strcpy(projects_array[web_projects_amount - 1].users_list[0], users_array[curr_index_user].name);
	projects_array[web_projects_amount - 1].Manager_list = (char**)malloc(sizeof(char*));
	if (projects_array[web_projects_amount - 1].Manager_list == NULL)
	{
		return False;
	}
	projects_array[web_projects_amount - 1].Manager_list[0] = (char*)malloc(sizeof(char)*strlen(users_array[curr_index_user].name));
	if (projects_array[web_projects_amount - 1].Manager_list[0] == NULL)
	{
		return False;
	}
	strcpy(projects_array[web_projects_amount - 1].Manager_list[0], users_array[curr_index_user].name);
	projects_array[web_projects_amount - 1].archived = 0;

	if (!users_array[curr_index_user].projects_amount){
		users_array[curr_index_user].projects_amount++;
		users_array[curr_index_user].project_list = (char**)malloc(sizeof(char*));
		if (users_array[curr_index_user].project_list == NULL)
		{
			return False;
		}
	}
	else{
		users_array[curr_index_user].projects_amount++;
		users_array[curr_index_user].project_list = (char**)realloc(users_array[curr_index_user].project_list, sizeof(char*)* users_array[curr_index_user].projects_amount);
		if (users_array[curr_index_user].project_list == NULL)
		{
			return False;
		}
	}
	users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1] = (char*)malloc(sizeof(char)*sizeof(temp));
	if (users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1] == NULL)
	{
		return False;
	}
	strcpy(users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1], temp);
	defult_status_to_new_project();
	//temp[SIZE - 1] = '\0';
	curr_index_project = web_projects_amount - 1;

	return True;
}
int get_project_index(char* project_name){
	for (int i = 0; i < web_projects_amount; i++){
		if (!strcmp(project_name, projects_array[i].name)){
			return i;
		}
	}
	return -1;
}
void print_users_project(){//func to print the users in project
	printf("The Users In This Project :\n");
	for (int i = 0; i < projects_array[curr_index_project].users_amount; i++){
		printf("%d. %s\n", (i + 1), projects_array[curr_index_project].users_list[i]);
	}
}
void get_task_details(){
	char temp_task[SIZE], details_task[TEMP_SIZE];//temprory strings to get status name and details from user
	printf("Fill Details:\n");
	printf("Enter Name:");
	fgets(temp_task, SIZE, stdin);
	temp_task[strlen(temp_task) - 1] = '\0';
	printf("Enter Details:");
	fgets(details_task, TEMP_SIZE, stdin);
	details_task[strlen(details_task) - 1] = '\0';
	return new_task(temp_task, details_task);
}
bool new_task(char* temp_task, char* details_task){

	/*if the first task created*/
	if (web_tasks_amount == 0){
		web_tasks_amount++;
		tasks_array = (Tasks *)malloc(sizeof(Tasks)*web_tasks_amount);
		if (tasks_array == NULL)
		{
			return False;
		}
		strcpy(tasks_array[web_tasks_amount - 1].assign_to, "None");
		strcpy(tasks_array[0].name, temp_task);
		tasks_array[0].task_details = (char*)malloc(sizeof(char)*strlen(details_task));
		if (tasks_array[0].task_details == NULL)
		{
			return False;
		}
		strcpy(tasks_array[0].task_details, details_task);
		strcpy(tasks_array[0].project_name, projects_array[curr_index_project].name);
		strcpy(tasks_array[0].status_name, projects_array[curr_index_project].status_list[0].name);
		tasks_array[0].task_progres = 0;
	}
	/*end of first task created*/
	/*if not first task created*/
	else{
		web_tasks_amount++;
		tasks_array = (Tasks *)realloc(tasks_array, sizeof(Tasks)*web_tasks_amount);
		if (tasks_array == NULL)
		{
			return False;
		}
		strcpy(tasks_array[web_tasks_amount - 1].name, temp_task);
		tasks_array[web_tasks_amount - 1].task_details = (char*)malloc(sizeof(char)*strlen(details_task));
		if (tasks_array[web_tasks_amount - 1].task_details == NULL)
		{
			return False;
		}
		strcpy(tasks_array[web_tasks_amount - 1].task_details, details_task);
		strcpy(tasks_array[web_tasks_amount - 1].project_name, projects_array[curr_index_project].name);
		strcpy(tasks_array[web_tasks_amount - 1].status_name, projects_array[curr_index_project].status_list[0].name);
		tasks_array[web_tasks_amount - 1].task_progres = 0;
		strcpy(tasks_array[web_tasks_amount - 1].assign_to, "None");
	}
	if (strcmp(details_task, "test")){
		send_message_for_all_in_project(projects_array[curr_index_project].name, "a new task was added to project");
	}
	/*end of case for bot first task created*/
	sort_tasks_no4();
	return True;
}
bool confirm_task(int status_index, int task_index){
	projects_array[curr_index_project].status_list[status_index].tasks_list[task_index]->task_progres = 1;
	if (projects_array[curr_index_project].status_list[status_index].tasks_list[task_index]->task_progres){
		return True;
	}
	return False;

}
void choose_task(){//this function will print all project tasks by the following order:
	//1. STATUS NAME
	//   1.task name
	//   2.task name
	// and so on
	int flag = 0;
	system("cls");
	printf("pls choose a task from the following tasks:\n\n");
	for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
		printf("status %d: %s\n", (i + 1), projects_array[curr_index_project].status_list[i].name);
		for (int j = 0; j < projects_array[curr_index_project].status_list[i].tasks_amount; j++){
			flag++;
			printf("   %d.: %s\n", (j + 1), projects_array[curr_index_project].status_list[i].tasks_list[j]->name);
		}
	}
	if (!flag){
		printf("\nno tasks yet\n");
		return;
	}
	printf("first chose the status by number\nto choose nothing and return to previous menu choose 0\n");
	int status = -1, task = -1;
	int tryes = 0;
	while (status<1 || status>projects_array[curr_index_project].status_amount){
		if (tryes){
			printf("pls choose status again! notice!! status are between 1 to %d\n", projects_array[curr_index_project].status_amount);
		}
		tryes++;
		scanf("%d", &status);
		getchar();
		if (!status){
			return;
		}
	}
	status--;
	printf("chose the task by number\nto choose nothing and return to previous menu choose 0\n");
	tryes = 0;
	if (!projects_array[curr_index_project].status_list[status].tasks_amount){
		printf("the status you chose has no tasks");
		return;
	}
	while (task<1 || task>projects_array[curr_index_project].status_list[status].tasks_amount){
		if (tryes){
			printf("pls choose task again! notice!! taks in ''%s'' are between 1 to %d\n", projects_array[curr_index_project].status_list[status].name, projects_array[curr_index_project].status_list[status].tasks_amount);
		}
		tryes++;
		scanf("%d", &task);
		getchar();
		if (!task){
			return;
		}
	}
	task--;
	manage_task(status, task);

}
void manage_task(int status, int task){
	system("cls");
	printf("\n this is the task you chose:\ntask name: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->name);
	printf("status: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->status_name);
	printf("details: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->task_details);
	printf("what wuld you like to do:(choose one from the following options)\n1.Move task to another status.\n2.Assign task to user.\n3.Complete task\n4.Remove task\n5.Return to previous menue");
	int command = 0;
	while (command<1 || command>5){
		scanf("%d", &command);
	}
	switch (command)
	{
	case(1) : {
				  move_task(status, task);
				  break;
	}
	case(2) : {
				  assigned_to(status, task);
				  break;
	}
	case(3) : {
				  confirm_task(status, task);
				  break;
	}
	case(4) : {
				  remove_task(status, task);
				  break;
	}
	case(5) : {
				  break;
	}

	}

}
void move_task(int status, int task){
	system("cls");
	printf("\nchoose status to move task to:\n");
	for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
		printf("%d: %s\n", (i + 1), projects_array[curr_index_project].status_list[i].name);
	}
	int chosenstatus;
	scanf("%d", &chosenstatus);
	chosenstatus--;
	/*first task to status*/
	if (!projects_array[curr_index_project].status_list[chosenstatus].tasks_amount){//if there are no tasks in this status
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list = (Tasks**)malloc(sizeof(Tasks*));
		if (projects_array[curr_index_project].status_list[chosenstatus].tasks_list == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list[0] = projects_array[curr_index_project].status_list[status].tasks_list[task];
		projects_array[curr_index_project].status_list[status].tasks_amount--;
		Tasks** temparray = (Tasks**)malloc(sizeof(Tasks*)*projects_array[curr_index_project].status_list[status].tasks_amount);
		if (temparray == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		for (int j = 0, k = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount + 1; j++){
			if (!(j == task)){
				temparray[k] = projects_array[curr_index_project].status_list[status].tasks_list[j];
				k++;
			}
		}
		free(projects_array[curr_index_project].status_list[status].tasks_list);
		projects_array[curr_index_project].status_list[status].tasks_list = (Tasks*)malloc(sizeof(Tasks)*projects_array[curr_index_project].status_list[status].tasks_amount);
		if (projects_array[curr_index_project].status_list[status].tasks_list == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		for (int j = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount; j++){
			projects_array[curr_index_project].status_list[status].tasks_list[j] = temparray[j];
		}
		strcpy(projects_array[curr_index_project].status_list[chosenstatus].tasks_list[0][0].status_name, projects_array[curr_index_project].status_list[chosenstatus].name);
		projects_array[curr_index_project].status_list[chosenstatus].tasks_amount++;
		free(temparray);
	}
	/*end of first task to status*/
	/*not first task in chosen status*/
	else{
		projects_array[curr_index_project].status_list[chosenstatus].tasks_amount++;
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list = (Tasks*)realloc(projects_array[curr_index_project].status_list[chosenstatus].tasks_list, sizeof(Tasks)*projects_array[curr_index_project].status_list[chosenstatus].tasks_amount);
		if (projects_array[curr_index_project].status_list[chosenstatus].tasks_list == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list[projects_array[curr_index_project].status_list[chosenstatus].tasks_amount - 1] = projects_array[curr_index_project].status_list[status].tasks_list[task];
		projects_array[curr_index_project].status_list[status].tasks_amount--;
		Tasks** temparray = (Tasks**)malloc(sizeof(Tasks*)*projects_array[curr_index_project].status_list[status].tasks_amount);
		if (temparray == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		for (int j = 0, k = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount; j++){
			if (!j == task){
				temparray[k] = projects_array[curr_index_project].status_list[status].tasks_list[j];
				k++;
			}
		}
		free(projects_array[curr_index_project].status_list[status].tasks_list);
		projects_array[curr_index_project].status_list[status].tasks_list = (Tasks*)malloc(sizeof(Tasks)*projects_array[curr_index_project].status_list[status].tasks_amount);
		if (projects_array[curr_index_project].status_list[status].tasks_list == NULL)
		{
			printf("error ellocation");
			exit(1);
		}
		for (int j = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount; j++){
			projects_array[curr_index_project].status_list[status].tasks_list[j] = temparray[j];
		}
		strcpy(projects_array[curr_index_project].status_list[chosenstatus].tasks_list[projects_array[curr_index_project].status_list[chosenstatus].tasks_amount - 1][0].status_name, projects_array[curr_index_project].status_list[chosenstatus].name);
		free(temparray);
	}
	/*end of not first task in chosen status*/
}
char *new_user_name(){
	int flag = 0;
	printf("\nInsert your new username:(user name must be up to 25 characters)\n");
	char temp1[1024], *temp;
	while (!flag){
		fgets(temp1, 1024, stdin);
		temp1[strlen(temp1) - 1] = '\0';
		if (strlen(temp1) > 25)
			printf("the inserted name is too long pls try again!\n");
		else flag = 1;
		for (int i = 0; i <web_users_amount; i++){
			if (!strcmp(temp1, users_array[i].name)){
				printf("this username is already taken, pls choose another name\n");
				flag = 0;
				i = web_users_amount;
			}
		}
	}
	for (int i = 0; i < strlen(temp1); i++){
		if (temp1[i] == 32){
			temp1[i] = '_';
		}
	}
	temp = (char*)malloc(sizeof(char)*SIZE);
	if (temp == NULL)
	{
		printf("error ellocation");
		exit(1);
	}
	for (int i = 0; i < strlen(temp1); i++){
		temp[i] = temp1[i];
	}
	temp[strlen(temp1)] = '\0';
	return temp;
}
bool exit_from_project(){

	for (int i = 0, j = 0; i < projects_array[curr_index_project].users_amount; i++, j++){//loop to run on the project array and find the user that we want to delete
		if (strcmp(projects_array[curr_index_project].users_list[i], users_array[curr_index_user].name) == 0){//if we found the user
			projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[i + 1];//we will delete
			j = i + 1;//increase the j
		}
		projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[j];//copy all the other users in 1 place before
	}

	projects_array[curr_index_project].users_amount--;//decrase the amnout users in project
	int new_user_amount_in_project;
	new_user_amount_in_project = projects_array[curr_index_project].users_amount;
	projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*new_user_amount_in_project);//realloc the users array 
	if (projects_array[curr_index_project].users_list == NULL&&projects_array[curr_index_project].users_amount != 0)
	{
		return False;
	}
	if (strcmp(users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1], projects_array[curr_index_project].name) == 0){
		users_array[curr_index_user].projects_amount--;
		users_array[curr_index_user].project_list = (char**)realloc(users_array[curr_index_user].project_list, sizeof(char*)*users_array[curr_index_user].projects_amount);
		return True;

	}
	for (int i = 0, j = 0; i < users_array[curr_index_user].projects_amount - 1; i++){//loop to run on the users array and find the project that we want to delete
		if (strcmp(users_array[curr_index_user].project_list[i], projects_array[curr_index_project].name) == 0){//if we found the project
			j = 1;//increase the j
		}
		if (j){
			users_array[curr_index_user].project_list[i] = users_array[curr_index_user].project_list[i + 1];//we will delete
		}

	}
	users_array[curr_index_user].projects_amount--;//decrease the amount projects of user
	int new_project_amount_in_users;
	new_project_amount_in_users = users_array[curr_index_user].projects_amount;
	users_array[curr_index_user].project_list = (char **)realloc(users_array[curr_index_user].project_list, sizeof(char*)*new_project_amount_in_users);//allocate new array of projects
	if (users_array[curr_index_user].project_list == NULL)
	{
		return False;
	}
	if (new_project_amount_in_users){
		if (users_array[curr_index_user].project_list[new_project_amount_in_users - 1])
		{
			return False;
		}
	}

	return True;
}
void delete_user_from_project_by_index_users_and_prpject(int project, int user){
	char ** temp_users = (char **)malloc(sizeof(char*)*projects_array[project].users_amount);
	if (temp_users == NULL)
	{
		return False;
	}
	for (int i = 0; i < projects_array[project].users_amount; i++){
		temp_users[i] = (char*)malloc(sizeof(char)*SIZE);
		if (temp_users[i] == NULL)
		{
			return False;
		}
	}
	int user_ind = get_user_index(projects_array[project].users_list[user]);
	for (int i = 0, j = 0; i < projects_array[project].users_amount; i++){
		if (strcmp(projects_array[project].users_list[j], users_array[user_ind].name) != 0){
			//temp_users[j] = projects_array[project].users_list[i];
			strcpy(temp_users[j], projects_array[project].users_list[i]);
			j++;
		}
	}
	//free(projects_array[project].users_list);
	projects_array[project].users_amount--;
	projects_array[project].users_list = (char**)realloc(projects_array[project].users_list, sizeof(char*)*projects_array[project].users_amount);
	if (projects_array[project].users_list == NULL)
	{
		return False;
	}
	for (int i = 0, j = 0; i < projects_array[project].users_amount; j++, i++){
		//if (strcmp(projects_array[project].users_list[j], users_array[user].name) == 0)j++;
		strcpy(projects_array[project].users_list[i], temp_users[i]);
		//projects_array[project].users_list[i] = temp_users[i];
	}

	//projects_array[project].users_amount--;
	free(temp_users);
	//print_arrays_to_files();
	//fill_arrays();
}
void choose_user_to_remove(){
	int user_to_remove, temp;
	printf("choose member to remove from site \nenter the number between 1-%d:\nchoose 0 to return\n ", web_users_amount);
	print_web_users();
	scanf("%d", &temp);
	getchar();
	if (temp == 0){
		return;
	}
	user_to_remove = temp - 1;
	return remove_user(user_to_remove);
}
bool remove_user(int user_to_remove){

	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < projects_array[i].users_amount; j++){
			if (strcmp(projects_array[i].users_list[j], users_array[user_to_remove].name) == 0){
				delete_user_from_project_by_index_users_and_prpject(i, j);
			}
		}
	}
	if (strcmp(users_array[user_to_remove].name, users_array[web_users_amount - 1].name) == 0){//if the user that we want delete is the last
		web_users_amount--;
		users_array = (Users*)realloc(users_array, (web_users_amount)* sizeof(Users));//we will do realloc and just delete the last one
		if (users_array == NULL)
		{
			return False;
		}
	}
	else{
		int flag = 0;
		for (int i = 0, j = 0; i < web_users_amount - 1; j++, i++){//loop to run on the user array to find the user that we delete
			if (strcmp(users_array[i].name, users_array[user_to_remove].name) == 0){ flag = 1; }//if we find the user
			if (flag == 1){
				strcpy(users_array[i].name, users_array[i + 1].name);//we will copy the next one to the place that we want to delete
				strcpy(users_array[i].password, users_array[i + 1].password);
				users_array[i].messages_amount = users_array[i + 1].messages_amount;
				users_array[i].message_list = (Messages**)malloc(sizeof(Messages*)*users_array[i].messages_amount);
				if (users_array[i].message_list == NULL)
				{
					return False;
				}
				for (int k = 0; k < users_array[i].messages_amount; k++){
					users_array[i].message_list[k] = users_array[i + 1].message_list[k];
				}
				users_array[i].projects_amount = users_array[i + 1].projects_amount;
				users_array[i].project_list = (char**)malloc(sizeof(char*)*users_array[i].projects_amount);
				if (users_array[i].project_list == NULL)
				{
					return False;
				}
				for (int k = 0; k < users_array[i].projects_amount; k++){
					users_array[i].project_list[k] = (char*)malloc(sizeof(char)*SIZE);
					if (users_array[i].project_list[k] == NULL)
					{
						return False;
					}
					strcpy(users_array[i].project_list[k], users_array[i + 1].project_list[k]);
				}
				//j = i + 1;
			}
			//strcpy(users_array[i].name, users_array[j].name);//we will continue to copy the next 
		}
		web_users_amount--;
		users_array = (Users*)realloc(users_array, (web_users_amount)* sizeof(Users));//we will do realloc and just delete the last one
		if (users_array == NULL)
		{
			return False;
		}
	}



}
void add_Wmanager(int index_user){
	printf("you want to make %s manger in this project", projects_array[curr_index_project].users_list[index_user]);//print to user 
	if (!choose_yes_or_no()){//if manger choose yes continue
		projects_array[curr_index_project].manager_amount++;//manager_amount +1
		projects_array[curr_index_project].Manager_list = (char**)realloc(projects_array[curr_index_project].Manager_list, sizeof(char*)*projects_array[curr_index_project].manager_amount);//Memory allocation
		if (projects_array[curr_index_project].Manager_list == NULL)
		{
			printf("error allocation");
			exit(1);
		}
		projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1] = (char*)malloc(sizeof(char)*SIZE);//Memory allocation
		if (projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1] == NULL)
		{
			printf("error allocation");
			exit(1);
		}
		strcpy(projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1], projects_array[curr_index_project].users_list[index_user]);//copy the name to new arry
	}
}
void message_abute_task(int index){
	send_message_for_all_in_project(users_array[curr_index_user].name, curr_index_project, ("%s open new task", users_array[curr_index_user].name));
}
void change_status(){

}
bool remove_user_from_project(int index_to_delete){
	int flag = 0, check_if_manager = 0, check_if_last = 0, succes = 0;
	int check_if_last_projectt = 0;

	for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){//loop to check if we connected as a manger of project
		if (strcmp(projects_array[curr_index_project].Manager_list[i], users_array[curr_index_user].name) == 0)flag = 1;//if yes change the flag to 1
	}//end of check if project manager

	for (int i = 0; i < projects_array[curr_index_project].users_amount; i++){//check if we try to delete the last
		if (strcmp(projects_array[curr_index_project].users_list[i], users_array[index_to_delete].name) == 0){
			if (i == projects_array[curr_index_project].users_amount - 1) check_if_last = 1;
		}
	}//end loop check if lest

	if (strcmp(users_array[curr_index_user].name, users_array[index_to_delete].name) == 0)check_if_manager = 1;//check if manager try to delete itself 

	if (check_if_last == 1){//we will only realloc and delete the last if we want delete the last
		projects_array[curr_index_project].users_amount--;//decrase the amnout users in project
		int new_user_amount_in_project;
		new_user_amount_in_project = projects_array[curr_index_project].users_amount;
		projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*new_user_amount_in_project);//realloc the users array 
		if (projects_array[curr_index_project].users_list == NULL)
		{
			return False;
		}
		succes = 1;
	}

	if (flag == 1 && check_if_manager == 0 && check_if_last == 0){
		for (int i = 0, j = 0; i < projects_array[curr_index_project].users_amount; i++, j++){//loop to run on the project array and find the user that we want to delete

			if (strcmp(projects_array[curr_index_project].users_list[i], users_array[index_to_delete].name) == 0 && i != projects_array[curr_index_project].users_amount - 1){//if we found the user
				projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[i + 1];//we will delete
				j = i + 1;//increase the j
			}
			projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[j];//copy all the other users in 1 place before
		}
		projects_array[curr_index_project].users_amount--;//decrase the amnout users in project
		int new_user_amount_in_project;
		new_user_amount_in_project = projects_array[curr_index_project].users_amount;
		projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*new_user_amount_in_project);//realloc the users array 
		if (projects_array[curr_index_project].users_list == NULL)
		{
			return False;
		}
		succes = 1;
	}
	if (succes == 1){//if we delete succesfully user from project ,we need delete the project from user projects 
		check_if_last_projectt = check_if_last_project(curr_index_project, index_to_delete);
		if (check_if_last_projectt == 1){
			users_array[index_to_delete].projects_amount--;//decrease the amount projects of user
			int new_project_amount_in_users;
			new_project_amount_in_users = users_array[index_to_delete].projects_amount;
			users_array[index_to_delete].project_list = (char **)realloc(users_array[index_to_delete].project_list, sizeof(char*)*new_project_amount_in_users);//allocate new array of projects
			if (users_array[index_to_delete].project_list == NULL)
			{
				return False;
			}
		}
		if (check_if_last_projectt != 1){
			for (int i = 0, j = 0; i < users_array[index_to_delete].projects_amount; i++, j++){//loop to run on the users array and find the project that we want to delete
				if (strcmp(users_array[index_to_delete].project_list[i], projects_array[curr_index_project].name) == 0){//if we found the project
					users_array[index_to_delete].project_list[i] = users_array[curr_index_user].project_list[i + 1];//we will delete
					j = i + 1;//increase the j
				}

				users_array[index_to_delete].project_list[i] = users_array[curr_index_user].project_list[j];//copy all the other projects in 1 place before

			}
			users_array[index_to_delete].projects_amount--;//decrease the amount projects of user
			int new_project_amount_in_users;
			new_project_amount_in_users = users_array[index_to_delete].projects_amount;
			users_array[index_to_delete].project_list = (char **)realloc(users_array[index_to_delete].project_list, sizeof(char*)*new_project_amount_in_users);//allocate new array of projects
			if (users_array[index_to_delete].project_list == NULL)
			{
				return False;
			}
		}
	}
	if (flag == 0){
		printf("You Are Not Manager - You Can't Remove User From This Project\n");
		return False;
	}
	if (check_if_manager == 1){
		printf("You Are Try To Delete Your Self - You Can't Do That\n");
		return False;
	}
	return True;
}
int check_if_last_project(int index_project_to_check, int user_to_check){
	for (int i = 0; i < users_array[user_to_check].projects_amount; i++){//check if we try to delete the last
		if (strcmp(users_array[user_to_check].project_list[i], projects_array[index_project_to_check].name) == 0){
			if (i == users_array[user_to_check].projects_amount - 1) return 1;
			else return 0;
		}
	}
}
bool remove_task(int status, int task){
	int task_index_global = -1;
	/*search for task in tasks global array*/
	for (int i = 0; i < web_tasks_amount; i++){
		if (!strcmp(projects_array[curr_index_project].status_list[status].tasks_list[task]->project_name, tasks_array[i].project_name)){
			if (!strcmp(projects_array[curr_index_project].status_list[status].tasks_list[task]->status_name, tasks_array[i].status_name)){
				if (!strcmp(projects_array[curr_index_project].status_list[status].tasks_list[task]->name, tasks_array[i].name)){
					task_index_global = i;
				}
			}
		}
	}
	/*end of search for task in tasks global array*/
	if (task_index_global == -1){//if task not found in global array
		printf("\ntask not found\n");
		return False;
	}
	Tasks* temp = (Tasks*)malloc(sizeof(Tasks)*web_tasks_amount);
	if (temp == NULL)
	{
		return False;
	}
	for (int i = 0, k = 0; i < web_tasks_amount; i++){
		if (!(i == task_index_global)){
			temp[k] = tasks_array[i];
			k++;
		}
	}
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < projects_array[i].status_amount; j++){
			if (projects_array[i].status_list[j].tasks_amount != 0){
				free(projects_array[i].status_list[j].tasks_list);
				projects_array[i].status_list[j].tasks_amount = 0;
			}
		}
	}
	free(tasks_array);
	web_tasks_amount--;
	tasks_array = (Tasks*)malloc(sizeof(Tasks)*web_tasks_amount);
	if (tasks_array == NULL)
	{
		return False;
	}
	for (int i = 0; i < web_tasks_amount; i++){
		tasks_array[i] = temp[i];
	}
	sort_tasks_no4();
	free(temp);
	printf("\ntask was removesd succesfully\n");
	return True;
}
void archived_project_menu(){
	while (1){
		int choose = 0;
		printf("Choose What You Want To Do:\n");
		printf("1.Show Users In Project\n");
		printf("2.Show Tasks In Project\n");
		printf("3.return to your main menu\n");
		while (choose <1 || choose > 3){
			scanf("%d", &choose);
			getchar();
		}
		switch (choose){
		case(1) : {
					  print_users_project();
					  break;

		}//end of case 1
		case(2) :/*choose and manage projects tasks*/ {
					 for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
						 printf("status: %s\ntasks:\n", projects_array[curr_index_project].status_list[i].name);
						 for (int j = 0; j < projects_array[curr_index_project].status_list[i].tasks_amount; j++){
							 printf("task name: %s\ntask details: %s\nperformed by: %s\n", projects_array[curr_index_project].status_list[i].tasks_list[j]->name, projects_array[curr_index_project].status_list[i].tasks_list[j]->task_details, projects_array[curr_index_project].status_list[i].tasks_list[j]->assign_to);
						 }
					 }
					 break;

		}//end of case 2
		case(3) :/*return to user main menu*/ {
					 curr_index_project = -1;
					 return;
		}//end of case 3

		}
	}
}
void print_project_menu(int project_manager){
	if (projects_array[curr_index_project].archived){
		archived_project_menu();
		return;
	}
	if (!project_manager){
		while (1){
			int choose = 0;
			system("cls");
			printf("Choose What You Want To Do:\n");
			printf("1.Show Users In Project\n");
			printf("2.Show Tasks In Project\n");
			printf("3.Add new Task\n");
			printf("4.Add new status\n");
			printf("5.Add User To Project\n");
			printf("6.Exit From This Project\n");
			printf("7.send team message\n");
			printf("8.return to your main menu\n");
			while (choose <1 || choose > 8){
				scanf("%d", &choose);
				getchar();
			}
			switch (choose){
			case(1) : {
						  print_users_project();
						  int choose_user;
						  printf("\nchoose 0 to go back");
						  scanf("%d", &choose_user);
						  if (!choose_user){
							  break;
						  }
						  choose_user--;
						  print_chosen_user_menu(choose_user, project_manager);//todo
						  break;

			}//end of case 1
			case(2) :/*choose and manage projects tasks*/ {
						 choose_task();
						 system("pause");
						 break;

			}//end of case 2
			case(3) :/*creat new task*/ {
						 get_task_details();
						 break;
			}//end of case 3
			case(4) : {
						  get_status_name();
						  break;
			}//end of case 4
			case(5) :/*add user to this project*/ {
						 insert_username_to_add();
						 break;
			}//end of case 5
			case(6) :/*exit from current project will remove user from this project and this project from users projects array*/ {
						 exit_from_project();
						 curr_index_project = -1;
						 return;
			}//end of case 6
			case(7) :/*send message to all project members*/ {
						 printf("pls insert your message\n");
						 char message[TEMP_SIZE];
						 fgets(message, TEMP_SIZE, stdin);
						 send_message_for_all_in_project(users_array[curr_index_user].name, message);
						 break;
			}//end of case 7
			case(8) :/*return to user main menu*/ {
						 curr_index_project = -1;
						 return;
			}//end of case 8

			}//end of switch
		}
	}//end of menu for member whos not project manager
	if (project_manager){
		while (1){
			int choose = 0;
			system("cls");
			printf("Choose What You Want To Do:\n");
			printf("1.Show Users In Project\n");
			printf("2.Show Tasks In Project\n");
			printf("3.Add new Task\n");
			printf("4.Add new status\n");
			printf("5.Add User To Project\n");
			printf("6.Exit From This Project\n");
			printf("7.send team message\n");
			printf("8.return to your main menu\n");
			printf("9.complete project\n");
			while (choose <1 || choose > 9){
				scanf("%d", &choose);
				getchar();
			}
			switch (choose){
			case(1) : {
						  print_users_project();
						  int choose_user;
						  printf("\nchoose 0 to go back");
						  scanf("%d", &choose_user);
						  if (!choose_user){
							  break;
						  }
						  choose_user--;
						  print_chosen_user_menu(choose_user, project_manager);//todo
						  break;

			}//end of case 1
			case(2) :/*choose and manage projects tasks*/ {
						 choose_task();
						 system("pause");
						 break;

			}//end of case 2
			case(3) :/*creat new task*/ {
						 get_task_details();
						 break;
			}//end of case 3
			case(4) : {
						  get_status_name();
						  break;
			}//end of case 4
			case(5) :/*add user to this project*/ {
						 insert_username_to_add();
						 break;
			}//end of case 5
			case(6) :/*exit from current project will remove user from this project and this project from users projects array*/ {
						 exit_from_project();
						 curr_index_project = -1;
						 return;
			}//end of case 6
			case(7) :/*send message to all project members*/ {
						 printf("pls insert your message\n");
						 char message[TEMP_SIZE];
						 fgets(message, TEMP_SIZE, stdin);
						 send_message_for_all_in_project(users_array[curr_index_user].name, message);
						 break;
			}//end of case 7
			case(8) :/*return to user main menu*/ {
						 curr_index_project = -1;
						 return;
			}//end of case 8
			case(9) : {
						  confirm_project();
						  return;
			}//end of case 9
			}//end of switch
		}
	}//end of menu for project manager
}
void play()
{
	while (1)
	{
		int choose = 0;
		system("cls");
		printf("==============================\nWelcome to meister task\n==============================\n");
		printf("\n\n choose one of the following options:\n\n1. log in\n2.sign up\n3. quit program\n");
		while (choose <1 || choose >3){
			scanf("%d", &choose);
			getchar();
		}
		switch (choose){
		case(1) : {
					  int sucsses = log_in();//log in returns true if sucssede
					  if (sucsses){
						  user_main_menu();
					  }
					  system("pause");
					  break;
		}//end of case 1
		case(2) : {
					  insert_details_for_signup();
					  break;
		}//end of case 2
		case(3) : {
					  print_arrays_to_files();
					  return;
		}//end of case 3

		}
	}

}
void user_main_menu(){//after user logs in this menu will appear
	if (!strcmp(users_array[curr_index_user].name, Wmanager->name)){
		manager_menu();
		return;
	}
	while (1){
		int choose = 0;
		system("cls");
		printf("\nchoose one of the following options:\n1. view your projects\n2. add new project\n3. view your messages\n4. sign out\n5. change your user name\n6. change your password\n");
		//TODO web managers menu
		while (choose<1 || choose>6){
			scanf("%d", &choose);
			getchar();
		}
		switch (choose){
		case(1) : {
					  if (!users_array[curr_index_user].projects_amount){
						  printf("you have no projects!\n");
						  system("pause");
						  break;
					  }
					  curr_index_project = print_and_choose_user_projects();
					  if (curr_index_project == -1){
						  break;
					  }
					  int projectmanager = 0;
					  for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){
						  if (!strcmp(users_array[curr_index_user].name, projects_array[curr_index_project].Manager_list[i])){
							  projectmanager = 1;
						  }
					  }
					  print_project_menu(projectmanager);
					  break;
		}//end of case 1
		case(2) : {
					  new_project_name();
					  print_project_menu(1);
					  break;
		}//end of case 2
		case(3) : {
					  print_user_messages();
					  break;
		}//end of case 3
		case(4) : {
					  curr_index_user = -1;
					  return;
		}//end of case 4
		case(5) : {
					  change_name();
					  break;
		}
		case(6) : {
					  change_pass();
					  break;
		}
		}
	}
}
void print_chosen_user_menu(int chosen_user, int projectmanager){
	system("cls");
	printf("your chosen user is: %s\n", projects_array[curr_index_project].users_list[chosen_user]);
	printf("choose one of the following options:\n1.send message to this user\n2. view tasks assigned to %s\n3.do nothing\n", projects_array[curr_index_project].users_list[chosen_user]);
	if (projectmanager)printf("\n4.remove this user (can be executed only by project manager)\n5.Promote User To Project Manager(can be executed only by project manager)\n");
	int choose = 0;
	//TODO add project manager assignment
	while (choose<1 || choose>5){
		scanf("%d", &choose);
		getchar();
		if ((choose == 4 || choose == 5) && !projectmanager){
			choose = -1;
			printf("You Can't Choose That You Are Not project Manager\n.");
		}

	}
	switch (choose)
	{
	case(1) : {
				  system("cls");
				  printf("pls insert your message\n");
				  char message[TEMP_SIZE];
				  fgets(message, TEMP_SIZE, stdin);
				  message[strlen(message) - 1] = '\0';
				  send_message_by_user(users_array[curr_index_user].name, projects_array[curr_index_project].users_list[chosen_user], message);
				  break;
	}//end of case 1
	case(2) : {
				  system("cls");
				  int flag = 0;
				  printf("==================================================\n==================================================\n");
				  for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
					  for (int j = 0; j < projects_array[curr_index_project].status_list[i].tasks_amount; j++){
						  if (!strcmp(projects_array[curr_index_project].users_list[chosen_user], projects_array[curr_index_project].status_list[i].tasks_list[j]->assign_to)){
							  if (!flag) printf("status: %s\ntasks:\n", projects_array[curr_index_project].status_list[i].name);
							  flag++;
							  printf("task name: %s\ntask details: %s\n", projects_array[curr_index_project].status_list[i].tasks_list[j]->name, projects_array[curr_index_project].status_list[i].tasks_list[j]->task_details);
							  if (!projects_array[curr_index_project].status_list[i].tasks_list[j]->task_progres){
								  printf("task in progress\n");
							  }
							  else
							  {
								  printf("task completed\n");
							  }
							  printf("==================================================\n");
						  }


					  }
					  if (flag--) printf("==================================================\n==================================================\n");

				  }
	}
	case(3) : {
				  system("cls");
				  return;
	}//end of case 3
	case(4) : {
				  system("cls");
				  int user_in_global_array = get_user_index(projects_array[curr_index_project].users_list[chosen_user]);//gets the chosen user index in the global array
				  if (user_in_global_array == -1){//if the function returns -1 means user has not been found in the global
					  printf("user not found\n");
					  return;
				  }
				  remove_user_from_project(user_in_global_array);//calls side function that recives the user index in the global array and removing user from project and project from user
				  break;
	}//end of case 4
	case(5) : {
				  system("cls");
				  prmotoe_user_to_manger(chosen_user);
				  break;

	}
	}
}
int get_user_index(char*username){
	for (int i = 0; i < web_users_amount; i++){
		if (!strcmp(username, users_array[i].name)){
			return i;
		}
	}
	return -1;

}
void get_status_name(){
	char temp_status[SIZE];
	system("cls");
	printf("Enter Status Name:");
	fgets(temp_status, SIZE, stdin);//get the status name
	temp_status[strlen(temp_status) - 1] = '\0';//put in the end \0
	return add_new_status(temp_status);
}
bool add_new_status(char* temp_status){
	projects_array[curr_index_project].status_amount++;//increase the the amount of status in the project
	int status_amount_new = projects_array[curr_index_project].status_amount;
	projects_array[curr_index_project].status_list = (Status *)realloc(projects_array[curr_index_project].status_list, sizeof(Status)*status_amount_new);//realloc the status array
	if (projects_array[curr_index_project].status_list == NULL)
	{
		return False;
	}
	if (!projects_array[curr_index_project].status_list){
		projects_array[curr_index_project].status_amount--;
		return False;
	}
	strcpy(projects_array[curr_index_project].status_list[status_amount_new - 1].name, temp_status);//copy to the end of the status list the new status
	projects_array[curr_index_project].status_list[status_amount_new - 1].tasks_amount = 0;	//intilize the amount of tasks to 0
	return True;
}
void print_user_messages(){
	system("cls");
	if (!users_array[curr_index_user].messages_amount){
		printf("\nno messages to show\n");
		return;
	}
	for (int i = 0; i < users_array[curr_index_user].messages_amount; i++){
		printf("from: %s\ncontent: %s\n", users_array[curr_index_user].message_list[i]->sender, users_array[curr_index_user].message_list[i]->content);
	}
	printf("\npress any key to return\n");
	system("pause");
}
void manager_menu(){
	while (1){
		int choose = 0;
		system("cls");
		printf("\nchoose one of the following options:\n1. view your projects\n2. add new project\n3. view your messages\n4. sign out\n");
		printf("5. send system message\n6. remove user from web\n7. view users in web\n");
		while (choose<1 || choose>7){
			scanf("%d", &choose);
			getchar();
		}
		switch (choose){
		case(1) : {
					  if (!users_array[curr_index_user].projects_amount){
						  printf("you have no projects!\n");
						  system("pause");
						  break;
					  }
					  curr_index_project = print_and_choose_user_projects();
					  if (curr_index_project == -1){
						  break;
					  }
					  int projectmanager = 0;
					  for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){
						  if (!strcmp(users_array[curr_index_user].name, projects_array[curr_index_project].Manager_list[i])){
							  projectmanager = 1;
						  }
					  }
					  print_project_menu(projectmanager);
					  break;
		}//end of case 1
		case(2) : {
					  new_project_name();
					  getchar();
					  print_project_menu(1);
					  break;
		}//end of case 2
		case(3) : {
					  print_user_messages();
					  break;
		}//end of case 3
		case(4) : {
					  curr_index_user = -1;
					  return;
		}//end of case 4
		case(5) : {
					  char temp[TEMP_SIZE];
					  system("cls");
					  printf("pls write down your message\nNotice: that message will be sent to all web users\ninsert 0 to go back to menu\n");
					  fgets(temp, TEMP_SIZE, stdin);
					  if (temp[0] == 0){
						  break;
					  }
					  send_message_by_admin(temp);
					  break;
		}//end case 5
		case(6) : {
					  choose_user_to_remove();
					  break;
		}//end case 6
		case(7) : {
					  print_web_users();
					  system("pause");
					  break;

		}//end of case 7
		}
	}

}
bool prmotoe_user_to_manger(int user_to_promote){
	int flag = 0;

	for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){//checks if we trys to promote ourself
		if (strcmp(projects_array[curr_index_project].Manager_list[i], projects_array[curr_index_project].users_list[user_to_promote]) == 0)
		{
			flag = 1;
		}
	}
	if (flag == 0){
		projects_array[curr_index_project].manager_amount++;
		projects_array[curr_index_project].Manager_list = (char**)realloc(projects_array[curr_index_project].Manager_list, sizeof(char*)*projects_array[curr_index_project].manager_amount);
		if (projects_array[curr_index_project].Manager_list == NULL)
		{
			return False;
		}
		projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1] = (char*)malloc(sizeof(char)*SIZE);
		if (projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1] == NULL)
		{
			return False;
		}
		strcpy(projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1], projects_array[curr_index_project].users_list[user_to_promote]);
	}
	else {
		if (strcmp(projects_array[curr_index_project].users_list[user_to_promote], "test"))printf("the user you try to promote is allready a manager or You try promote your self\n");
		return False;

	}
	printf("user promoted succesfully\n");
	return True;

}






