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
	char *content;

}Messages;
typedef struct
{
	char name[SIZE];
}WebManager;
typedef struct
{
	char name[SIZE];
	char password[SIZE];
	char **project_list;
	int projects_amount;
	Messages* message_list;
	int messages_amount;
}Users;
typedef struct
{
	char project_name[SIZE];
	char status_name[SIZE];
	char name[SIZE];
	char *task_details;
	bool task_progres;
	char assign_to[SIZE];
}Tasks;
typedef struct
{
	char name[SIZE];
	Tasks ** tasks_list;
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
char* new_user_name();
void move_task(int status, int task);
char *new_project_name();
void confirm_task();
void change_name();
void scan_no1();
void scan_no2();
void scan_no3();
void sort_tasks_no4();
void sort_projects_to_users_no5();
void scan_no6();
void print_arrays_to_files();
void sort_messages_to_users_no7();
void print_no1();
void print_no2();
void print_no3();
void print_no4();
void add_new_project();
void print_user_projects();
void signUp();
void cleanBuffer();
int log_in();
int String(char arry[]);
void cleanString(char arry[]);
int check_member(char user[], char password[]);
int compareArrays(char user_from_list[], char user_from_member[]);
void play(char member[]);
void system_massage();
void print_projects_task();
void print_web_users();
int check_admin(char * name);
int confirm_project();
void fill_arrays();
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
void add_user_to_project();
int get_project_index(char*);
void defult_status_to_new_project();
void print_users_project();
void new_task();
void print_tasks_array();
void send_message_by_admin(char *sender, char* message);
void send_message_by_user(char *sender, char* target, char* message);
void send_message_for_all_in_project(char *sender, char* message);
void manage_task(int status, int task);
void choose_task();
void remove_user();
int choose_yes_or_no();
void add_Wmanager(int index_user);
void change_name();
void exit_from_project(int user_array);
void message_abute_task();
void change_status();
void remove_user_from_project(int index_to_delete);

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



int main()
{
	fill_arrays();
	signUp();
	int curr_index_project, user_in;
	char a[6] = { "zohar" };
	char b[] = { "jlkjlklajlkfasfal " };
	if (log_in()){
		//new_task(print_and_choose_user_projects(curr_index_user));
		//exit_from_project(print_and_choose_user_projects(curr_index_user), curr_index_user);
		curr_index_project = print_and_choose_user_projects(curr_index_user);
		print_users_project(curr_index_project);
		printf("Choose User To remove:\n");
		scanf("%d", &user_in);
		remove_user_from_project(curr_index_project, user_in);
	}

	
	//log_in();
	//move_task(0, 0, 0);
	//printf("%s\n", projects_array[0].status_list[0].tasks_list[0]->status_name);
	//printf("%s\n", tasks_array[1].status_name);
	curr_index_project = 0;
	new_task();
	printf("%s\n", projects_array[0].status_list[0].tasks_list[2]->name);
	printf("%s\n", tasks_array[1].status_name);
	//signUp();
	

	//add_Wmanager(1,1);
//	add_Wmanager(1,1);
}
//	char member[] = { "zohar" };
//	int enter = 0;
//	//system_massage(member);
//	
//	
//	do
//	{
//		printf("1.log in\n2.sign up\nplease enter you chooic: ");//זמנית בנתיים עד שנראה איך מריצים דרך פונקציה play
//		scanf("%d", &enter);
//		cleanBuffer();
//		if (enter == 1)
//			log_in(member);
//		if (enter == 2){
//			signUp();
//		}
//		enter = 0;
//	} while (True);
//	return 0;		
void signUp(){
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
	users_array = (Users*)realloc(users_array, (web_users_amount + 1)*sizeof(Users));
	if (users_array == NULL){//if not open quit
		printf("the arry could not be created\n");
		exit(1);
	}
	strcpy(users_array[web_users_amount].name, member);
	strcpy(users_array[web_users_amount].password, password);
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
int log_in(){
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
		}return False;
	}
	return False;
}
int choose_yes_or_no(){//function to ask the user if exit to loby/main
	char temp = '\0';
	printf("you want enter again if so enter Y else enter othe key: ");//massage to user
	scanf("%c", &temp);//scan flag
	if (!(temp == 'y' || temp == 'Y')){//if flag = y(yes) continue
		cleanBuffer();//clean buffer
		return True;
	}
	cleanBuffer();
	return False;
}
/*reading files and arrays sorting functions*/
void fill_arrays(){
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

}
void scan_no1(){
	FILE* users_File = fopen(USER_FILE_NAME, "r");
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
}
void scan_no2(){
	FILE* projects_file = fopen(PROJECTS_FILE_NAME, "r");
	FILE* projects_managers_file = fopen(PROJECT_MANAGERS_FILE, "r");
	fscanf(projects_file, "%d", &web_projects_amount);
	projects_array = (Projects*)malloc(sizeof(Projects)*web_projects_amount);
	for (int i = 0; i < web_projects_amount; i++){
		fscanf(projects_file, "%s", &projects_array[i].name);
		fscanf(projects_file, "%d", &projects_array[i].users_amount);
		projects_array[i].users_list = (char**)malloc(sizeof(char*)*projects_array[i].users_amount + 1);
		for (int j = 0; j < projects_array[i].users_amount; j++){
			char temp[SIZE];
			projects_array[i].users_list[j] = (char*)malloc(sizeof(char)*SIZE);
			fscanf(projects_file, "%s", &temp);
			strcpy(projects_array[i].users_list[j], temp);
		}
		char temp[20];
		fscanf(projects_managers_file, "%s", &temp);
		fscanf(projects_managers_file, "%d", &projects_array[i].manager_amount);
		projects_array[i].Manager_list = (char**)malloc(sizeof(char*)*projects_array[i].manager_amount);
		for (int j = 0; j < projects_array[i].manager_amount; j++){
			projects_array[i].Manager_list[j] = (char*)malloc(sizeof(char)*SIZE);
			char temp[SIZE];
			fscanf(projects_managers_file, "%s", &temp);
			strcpy(projects_array[i].Manager_list[j], temp);

		}
		fscanf(projects_file, "%d", &projects_array[i].status_amount);
		projects_array[i].status_list = (Status*)malloc(sizeof(Status)*projects_array[i].status_amount);
		for (int j = 0; j < projects_array[i].status_amount; j++){
			fscanf(projects_file, "%s", &projects_array[i].status_list[j].name);
			projects_array[i].status_list[j].tasks_amount = 0;
		}
		fscanf(projects_file, "%d", &projects_array[i].archived);
	}
	fclose(projects_file);
	fclose(projects_managers_file);
}
void scan_no3(){
	FILE* tasks_file = fopen(TASKS_FILE, "r");
	fscanf(tasks_file, "%d", &web_tasks_amount);
	tasks_array = (Tasks*)malloc(sizeof(Tasks)*web_tasks_amount);
	for (int i = 0; i < web_tasks_amount; i++){
		fscanf(tasks_file, "%s %s %s", &tasks_array[i].project_name, &tasks_array[i].status_name, &tasks_array[i].name);
		char temp[TEMP_SIZE];
		int j = 0;
		fgetc(tasks_file);
		while ((temp[j++] = fgetc(tasks_file)) != '\n');
		temp[j - 1] = '\0';
		tasks_array[i].task_details = (char*)malloc(sizeof(char)*strlen(temp));
		strcpy(tasks_array[i].task_details, temp);
		fscanf(tasks_file, "%d %s", &tasks_array[i].task_progres, &tasks_array[i].assign_to);
	}
	fclose(tasks_file);
}
void sort_tasks_no4(){
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < web_tasks_amount; j++){
			if (!strcmp(projects_array[i].name, tasks_array[j].project_name)){
				for (int k = 0; k < projects_array[i].status_amount; k++){
					if (!strcmp(projects_array[i].status_list[k].name, tasks_array[j].status_name)){
						if (!projects_array[i].status_list[k].tasks_amount){
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks**)malloc(sizeof(Tasks*));
							projects_array[i].status_list[k].tasks_list[0] = &tasks_array[j];

						}
						else{
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks**)realloc(projects_array[i].status_list[k].tasks_list, projects_array[i].status_list[k].tasks_amount*sizeof(Tasks*));
							projects_array[i].status_list[k].tasks_list[projects_array[i].status_list[k].tasks_amount - 1] = &tasks_array[j];
						}
					}
				}

			}
		}

	}
}
void sort_projects_to_users_no5(){
	for (int i = 0; i < web_users_amount; i++){
		for (int j = 0; j < web_projects_amount; j++){
			for (int k = 0; k < projects_array[j].users_amount; k++){
				if (!strcmp(users_array[i].name, projects_array[j].users_list[k])){
					if (!users_array[i].projects_amount){
						users_array[i].projects_amount++;
						users_array[i].project_list = (char**)malloc(sizeof(char*));
						users_array[i].project_list[0] = (char*)malloc(sizeof(char)*SIZE);
						strcpy(users_array[i].project_list[0], projects_array[j].name);
					}
					else{
						users_array[i].projects_amount++;
						users_array[i].project_list = (char**)realloc(users_array[i].project_list, users_array[i].projects_amount*sizeof(char*));
						users_array[i].project_list[users_array[i].projects_amount - 1] = (char*)malloc(sizeof(char)*SIZE);
						strcpy(users_array[i].project_list[users_array[i].projects_amount - 1], projects_array[j].name);
					}
				}
			}
		}
	}
}
void scan_no6(){
	FILE* messages_file = fopen(MESSAGE_FILE, "r");
	fscanf(messages_file, "%d", &web_messages_amount);
	messages_array = (Messages*)malloc(sizeof(Messages)*web_messages_amount);
	for (int i = 0; i < web_messages_amount; i++){
		fscanf(messages_file, "%s", &messages_array[i].sender);
		fscanf(messages_file, "%s", &messages_array[i].target);
		char temp[MESSAGE_SIZE];
		int j = 0;
		fgetc(messages_file);
		while ((temp[j++] = fgetc(messages_file)) != '\n');
		temp[j - 1] = '\0';
		messages_array[i].content = (char*)malloc(sizeof(char)*strlen(temp));
		for (j = 0; j < strlen(temp); j++){
			messages_array[i].content[j] = temp[j];
		}
		messages_array[i].content[j] = '\0';
	}
	fclose(messages_file);

}
void sort_messages_to_users_no7(){
	for (int i = 0; i < web_users_amount; i++){
		for (int j = 0; j < web_messages_amount; j++){
			if (!strcmp(users_array[i].name, messages_array[j].target)){
				if (!users_array[i].messages_amount){
					users_array[i].messages_amount++;
					users_array[i].message_list = (Messages*)malloc(sizeof(Messages));
					users_array[i].message_list[0] = messages_array[j];
				}
				else{
					users_array[i].messages_amount++;
					users_array[i].message_list = (Messages*)realloc(users_array[i].message_list, users_array[i].messages_amount*sizeof(Messages));
					users_array[i].message_list[users_array[i].messages_amount - 1] = messages_array[j];
				}
			}
		}
	}
}
/*end of reading files and arrays sorting functions */
/*print arrays to files functions*/
void print_arrays_to_files(){
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
}
void print_no1(){
	FILE *users_file = fopen(USER_FILE_NAME, "w");
	fprintf(users_file, "%d\n", web_users_amount);
	for (int i = 0; i < web_users_amount; i++){
		fprintf(users_file, "%s\n%s\n", users_array[i].name, users_array[i].password);
	}
	fclose(users_file);
}
void print_no2(){
	FILE* projects_file = fopen(PROJECTS_FILE_NAME, "w");
	FILE* project_managers = fopen(PROJECT_MANAGERS_FILE, "w");
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
}
void print_no3(){
	FILE* tasks_file = fopen(TASKS_FILE, "w");
	fprintf(tasks_file, "%d\n", web_tasks_amount);
	for (int i = 0; i < web_tasks_amount; i++){
		fprintf(tasks_file, "%s\n%s\n%s\n%s\n%d\n%s\n", tasks_array[i].project_name, tasks_array[i].status_name, tasks_array[i].name, tasks_array[i].task_details, tasks_array[i].task_progres, tasks_array[i].assign_to);
	}
	fclose(tasks_file);
}
void print_no4(){
	FILE * messages_file = fopen(MESSAGE_FILE, "w");
	fprintf(messages_file, "%d\n", web_messages_amount);
	for (int i = 0; i < web_messages_amount; i++){
		fprintf(messages_file, "%s\n%s\n%s\n", messages_array[i].sender, messages_array[i].target, messages_array[i].content);
	}
	fclose(messages_file);

}
/*end of print arrays to files functions*/
int print_and_choose_user_projects(int index_user_array){
	int chosen_proj;
	printf("Those Your projects:\n");
	for (int i = 0; i < users_array[index_user_array].projects_amount; i++){
		printf("%d. %s", (i + 1), users_array[index_user_array].project_list[i]);
		if (projects_array[get_project_index(users_array[index_user_array].project_list[i])].archived){
			printf(" **project is archived**");
		}
		printf("\n");
	}
	printf("Choose Project By Number:\n");
	scanf("%d", &chosen_proj);
	getchar();//get the enter
	return get_project_index(users_array[index_user_array].project_list[chosen_proj - 1]);
}
void print_projects_task(){
	printf("Tasks In Project:\n");
	for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
		//for (int j = 0; j < projects_array[index_project_array].status_amount;j++)
		printf("%d. %s", (i + 1), (projects_array[curr_index_project].status_list[0]).tasks_list[i]->name);
	}
	//projects_array[0].status_list[0]

}
int check_admin(char * name){
	if (!strcmp(name, Wmanager->name)) return True;//check if the name that func get is the same name as web manager
	else return False;
}
void print_web_users(){
	printf("Those All Site Members:\n");
	for (int i = 0; i < web_users_amount; i++){//loop to print all users
		printf("%d,%s\n", (i + 1), users_array[i].name);
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
void send_message_by_user(char *sender, char* target, char *message){
	web_messages_amount++;
	messages_array = (Messages*)realloc(messages_array, web_messages_amount * sizeof(Messages));//realloc 1 place for new message
	if (messages_array == NULL)
		exit(1);
	messages_array[web_messages_amount - 1].content = (char*)malloc(strlen(message)*sizeof(char));//Opening indicates the size of the array
	if (messages_array[web_messages_amount - 1].content == NULL)
		exit(1);
	strcpy(messages_array[web_messages_amount - 1].content, message);//העתקות לתוך מערך
	strcpy(messages_array[web_messages_amount - 1].sender, sender);
	strcpy(messages_array[web_messages_amount - 1].target, target);
}
void send_message_by_admin(char *sender, char *message){
	int j = 0;
	messages_array = (Messages*)realloc(messages_array, (web_messages_amount + web_users_amount) * sizeof(Messages));//realloc 1 place for new message
	for (int i = web_users_amount; i < web_users_amount + web_users_amount; i++){
		messages_array[i - 1].content = (char*)malloc(strlen(message)*sizeof(char));//Opening indicates the size of the array
		strcpy(messages_array[i - 1].content, message);//העתקות לתוך מערך
		strcpy(messages_array[i - 1].sender, "ADMIN");
		strcpy(messages_array[i - 1].target, users_array[j].name);
		j++;
	}
	web_messages_amount += web_users_amount;
}
void send_message_for_all_in_project(char *sender, char* message_demand){//פונקציה לשליחת הודעה לחברי הפרויקט מקבלת שולח אינדקס פרויקט והודעה
	int j = 0;
	messages_array = (Messages*)realloc(messages_array, (web_messages_amount + projects_array[curr_index_project].users_amount) * sizeof(Messages));//realloc 1 place for new message
	for (int i = web_users_amount; i < web_users_amount + projects_array[curr_index_project].users_amount; i++){
		messages_array[i - 1].content = (char*)malloc(strlen(message_demand)*sizeof(char));//Opening indicates the size of the array
		strcpy(messages_array[i - 1].content, message_demand);//העתקות לתוך מערך
		strcpy(messages_array[i - 1].sender, sender);
		strcpy(messages_array[i - 1].target, projects_array[curr_index_project].users_list[j]);
		j++;
	}
	web_messages_amount += projects_array[curr_index_project].users_amount;
}
void change_pass(){
	char temp_pass[SIZE];
	printf("Enter New Pass:\n");
	int accept = String(temp_pass);//get new password
	if (!accept){
		strcpy(users_array[curr_index_user].password, temp_pass);
	}
}
/*void send_message_about_new_task(int index_user_array)
{
int chosen_project;
char *temp_message[31] = { "There Is New Task - Check It" };
char *temp_sender = { "System" };
print_user_projects(index_user_array);
printf("Choose Project :\n");
scanf("%d", &chosen_project);
//צריכה להיות פונקציה שמדפיסה את כל האפשריות
print_user_projects(index_user_array);//הדפסה של כל משתמשי הפרויקט
//printf("Choose user :\n");
//scanf("%d", &chosen_user);
//printf("Write Your Message :\n");
//get(temp_message);
realloc(messages_array, projects_array[chosen_project].users_amount * sizeof *messages_array);//realloc 1 place for new message
//realloc(users_array[chosen_user].message_list, 1 * sizeof *messages_array);
web_messages_amount = projects_array[chosen_project].users_amount+web_messages_amount;
/*for (int i = projects_array[chosen_project].users_amount; i < web_users_amount; i++){//loop to fill the name,target name,conntent in the last place of array messages
for (int j = 0; j < 31; j++){
messages_array[i].sender[j] = temp_sender[j];//update sender in the global messages array
messages_array[i].target[j] = projects_array[chosen_project].users_list[0].;//update target user in the global messages array
//messages_array[web_messages_amount].content[i] = temp_message[i];//update contain in the global messages array
}
}*/
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
	fscanf("%d", &chosen_user);/*ask user to choose username*/
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
void print_login_singup(){
	int enter;
	printf("1.log in\n2.sign up\nplease enter you chooic: ");//זמנית בנתיים עד שנראה איך מריצים דרך פונקציה play
	scanf("%d", &enter);
	cleanBuffer();
	if (enter == 1)
		log_in();
	if (enter == 2){
		signUp();
		//printf("%s", projects_array[1].Manager_list[0]);
	}
}
void add_user_to_project(){//fund to add new user to project
	char temp_user[20];
	int flag = 0, index_try = 0;
	while (flag == 0){//loop to get the name of user that we want add - if there is no exist this user - again
		printf("Enter user name that You want add to project [20 chars] : \n");
		fgets(temp_user, SIZE, stdin);
		temp_user[strlen(temp_user) - 1] = '\0';
		for (int i = 0; i < web_users_amount; i++){//loop to find the user in web array users
			if (strcmp(temp_user, users_array[i].name) == 0) flag = 1;
		}
	}
	projects_array[curr_index_project].users_amount++;//increase the amount of users in the project
	projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*projects_array[curr_index_project].users_amount);//increas by one the users list
	projects_array[curr_index_project].users_list[projects_array[curr_index_project].users_amount - 1] = (char*)malloc(sizeof(char)* 25);//allocate new memory 
	strcpy(projects_array[curr_index_project].users_list[projects_array[curr_index_project].users_amount - 1], temp_user);//copy the new name 
}
void defult_status_to_new_project(){
	projects_array[web_projects_amount - 1].status_amount = 4;
	projects_array[web_projects_amount - 1].status_list = (Status*)malloc(sizeof(Status)*projects_array[web_projects_amount - 1].status_amount);
	*projects_array[web_projects_amount - 1].status_list[0].name = "Elicitation";
	*projects_array[web_projects_amount - 1].status_list[1].name = "Analasys";
	*projects_array[web_projects_amount - 1].status_list[2].name = "VandV";
	*projects_array[web_projects_amount - 1].status_list[3].name = "Approved";
	projects_array[web_projects_amount - 1].status_list[0].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[1].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[2].tasks_amount = 0;
	projects_array[web_projects_amount - 1].status_list[3].tasks_amount = 0;
}
char* new_project_name(){
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
	for (int i = 0; i < strlen(temp1); i++){
		temp[i] = temp1[i];
	}
	temp[strlen(temp1)] = '\0';
	return temp;
}
void add_new_project(){
	/**/
	char *temp = (char*)malloc(sizeof(char)*SIZE);
	strcpy(temp, new_project_name());
	/**/
	if (!web_projects_amount){
		web_projects_amount++;
		projects_array = (Projects*)malloc(sizeof(Projects));
	}
	else{
		web_projects_amount++;
		projects_array = (Projects*)realloc(projects_array, sizeof(Projects)* web_projects_amount);
	}
	strcpy(projects_array[web_projects_amount - 1].name, temp);
	projects_array[web_projects_amount - 1].users_amount = 1;
	projects_array[web_projects_amount - 1].manager_amount = 1;
	projects_array[web_projects_amount - 1].users_list = (char**)malloc(sizeof(char*));
	projects_array[web_projects_amount - 1].users_list[0] = (char*)malloc(sizeof(char)*strlen(users_array[curr_index_user].name));
	strcpy(projects_array[web_projects_amount - 1].users_list[0], users_array[curr_index_user].name);
	projects_array[web_projects_amount - 1].Manager_list = (char**)malloc(sizeof(char*));
	projects_array[web_projects_amount - 1].Manager_list[0] = (char*)malloc(sizeof(char)*strlen(users_array[curr_index_user].name));
	strcpy(projects_array[web_projects_amount - 1].Manager_list[0], users_array[curr_index_user].name);
	projects_array[web_projects_amount - 1].archived = 0;

	if (!users_array[curr_index_user].projects_amount){
		users_array[curr_index_user].projects_amount++;
		users_array[curr_index_user].project_list = (char**)malloc(sizeof(char*));
	}
	else{
		users_array[curr_index_user].projects_amount++;
		users_array[curr_index_user].project_list = (char**)realloc(users_array[curr_index_user].project_list, sizeof(char*)* users_array[curr_index_user].projects_amount);
	}
	users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1] = (char*)malloc(sizeof(char)*sizeof(temp));
	strcpy(users_array[curr_index_user].project_list[users_array[curr_index_user].projects_amount - 1], temp);
	defult_status_to_new_project();
	//temp[SIZE - 1] = '\0';


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
void new_task(){
	char temp_task[SIZE], details_task[TEMP_SIZE];//temprory strings to get status name and details from user
	printf("Fill Details:\n");
	printf("Enter Name:");
	fgets(temp_task, SIZE, stdin);
	temp_task[strlen(temp_task) - 1] = '\0';
	printf("Enter Details:");
	fgets(details_task, TEMP_SIZE, stdin);
	details_task[strlen(details_task) - 1] = '\0';
	/*if the first task created*/
	if (web_tasks_amount == 0){
		web_tasks_amount++;
		tasks_array = (Tasks *)malloc(sizeof(Tasks)*web_tasks_amount);
		strcpy(tasks_array[web_tasks_amount - 1].assign_to,"None");
		strcpy(tasks_array[0].name, temp_task);
		tasks_array[0].task_details = (char*)malloc(sizeof(char)*strlen(details_task));
		strcpy(tasks_array[0].task_details, details_task);
		strcpy(tasks_array[0].project_name, projects_array[curr_index_project].name);
		strcpy(tasks_array[0].status_name, projects_array[curr_index_project].status_list[0].name);
		tasks_array[0].task_progres = 0;
		projects_array[curr_index_project].status_list[0].tasks_amount++;
		projects_array[curr_index_project].status_list[0].tasks_list = (Tasks**)malloc(sizeof(Tasks*));
		projects_array[curr_index_project].status_list[0].tasks_list[0] = &tasks_array[0];
	}
	/*end of first task created*/
	/*if not first task created*/
	else{
			web_tasks_amount++;
			tasks_array = (Tasks *)realloc(tasks_array, sizeof(Tasks)*web_tasks_amount);
			strcpy(tasks_array[web_tasks_amount - 1].name,temp_task);
			tasks_array[web_tasks_amount - 1].task_details = (char*)malloc(sizeof(char)*strlen(details_task));
			strcpy(tasks_array[web_tasks_amount - 1].task_details, details_task);
			strcpy(tasks_array[web_tasks_amount - 1].project_name, projects_array[curr_index_project].name);
			strcpy(tasks_array[web_tasks_amount - 1].status_name, projects_array[curr_index_project].status_list[0].name);
			tasks_array[web_tasks_amount - 1].task_progres = 0;
			strcpy(tasks_array[web_tasks_amount - 1].assign_to, "None");
			/*if first task for project or for status*/
			if (!projects_array[curr_index_project].status_list[0].tasks_amount){
				projects_array[curr_index_project].status_list[0].tasks_amount++;
				projects_array[curr_index_project].status_list[0].tasks_list = (Tasks**)malloc(sizeof(Tasks*));
				projects_array[curr_index_project].status_list[0].tasks_list[0] = &tasks_array[web_tasks_amount - 1];
			}
			/*end of case that firs task for project or status*/
			/*if not first task created for project or status*/
			else{
				projects_array[curr_index_project].status_list[0].tasks_amount++;
				projects_array[curr_index_project].status_list[0].tasks_list = (Tasks**)realloc(projects_array[curr_index_project].status_list[0].tasks_list, sizeof(Tasks*)*projects_array[curr_index_project].status_list[0].tasks_amount);
				projects_array[curr_index_project].status_list[0].tasks_list[projects_array[curr_index_project].status_list[0].tasks_amount - 1] = &tasks_array[web_tasks_amount - 1];
			}
			/*end of case that not first task for project or status*/
		}
	/*end of case for bot first task created*/

}
void confirm_task( int status_index, int task_index){
	projects_array[curr_index_project].status_list[status_index].tasks_list[task_index]->task_progres = 1;
}
void choose_task(){
	printf("pls choose a task from the following tasks:\nfirst insert status number, than insert task number\n");
	for (int i = 0; i < projects_array[curr_index_project].status_amount; i++){
		printf("status %d: %s\n", (i + 1), projects_array[curr_index_project].status_list[i].name);
		for (int j = 0; j < projects_array[curr_index_project].status_list[i].tasks_amount; j++){
			printf("%d.: %s\n", projects_array[curr_index_project].status_list[j].name);
		}
	}
	int status, task;
	fscanf("%d", &status);
	fscanf("%d", &task);
	status--;
	task--;
	manage_task( status, task);

}
void manage_task(int status, int task){
	printf("\n this is the task you chose:\ntask name: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->name);
	printf("status: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->status_name);
	printf("details: %s\n", projects_array[curr_index_project].status_list[status].tasks_list[task]->task_details);
	printf("what wuld you like to do:(choose one from the following options)\n1.Move task to another status.\n2.Assign task to user.\n3.Complete task\n4.Remove task\n");
	int command;
	scanf("%d", &command);
	switch (command)
	{
	case(1) : {
				  move_task( status, task);
				  break;
	}
	case(2) : {
				  assigned_to(status, task);
				  break;
	}
	default:
		break;
	}

}
void move_task(int status, int task){
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
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list[0] = projects_array[curr_index_project].status_list[status].tasks_list[task];
		projects_array[curr_index_project].status_list[status].tasks_amount--;
		Tasks** temparray = (Tasks**)malloc(sizeof(Tasks*)*projects_array[curr_index_project].status_list[status].tasks_amount);
		for (int j = 0, k = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount + 1; j++){
			if (!(j == task)){
				temparray[k] = projects_array[curr_index_project].status_list[status].tasks_list[j];
				k++;
			}
		}
		free(projects_array[curr_index_project].status_list[status].tasks_list);
		projects_array[curr_index_project].status_list[status].tasks_list = (Tasks*)malloc(sizeof(Tasks)*projects_array[curr_index_project].status_list[status].tasks_amount);
		for (int j = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount; j++){
			projects_array[curr_index_project].status_list[status].tasks_list[j] = temparray[j];
		}
		strcpy(projects_array[curr_index_project].status_list[chosenstatus].tasks_list[0][0].status_name, projects_array[curr_index_project].status_list[chosenstatus].name);
		free(temparray);
	}
	/*end of first task to status*/
	/*not first task in chosen status*/
	else{
		projects_array[curr_index_project].status_list[chosenstatus].tasks_amount++;
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list = (Tasks*)realloc(projects_array[curr_index_project].status_list[chosenstatus].tasks_list, sizeof(Tasks)*projects_array[curr_index_project].status_list[chosenstatus].tasks_amount);
		projects_array[curr_index_project].status_list[chosenstatus].tasks_list[projects_array[curr_index_project].status_list[chosenstatus].tasks_amount - 1] = projects_array[curr_index_project].status_list[status].tasks_list[task];
		projects_array[curr_index_project].status_list[status].tasks_amount--;
		Tasks** temparray = (Tasks**)malloc(sizeof(Tasks*)*projects_array[curr_index_project].status_list[status].tasks_amount);
		for (int j = 0, k = 0; j < projects_array[curr_index_project].status_list[status].tasks_amount; j++){
			if (!j == task){
				temparray[k] = projects_array[curr_index_project].status_list[status].tasks_list[j];
				k++;
			}
		}
		free(projects_array[curr_index_project].status_list[status].tasks_list);
		projects_array[curr_index_project].status_list[status].tasks_list = (Tasks*)malloc(sizeof(Tasks)*projects_array[curr_index_project].status_list[status].tasks_amount);
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
	for (int i = 0; i < strlen(temp1); i++){
		temp[i] = temp1[i];
	}
	temp[strlen(temp1)] = '\0';
	return temp;
}
void exit_from_project(){
	/*for (int k = 0; k < projects_array[project_index].users_amount; k++){
		printf("Names Before Change:\n");
		printf("%s\n", projects_array[project_index].users_list[k]);
		}*/
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
	/*for (int k = 0; k < projects_array[project_index].users_amount; k++){
		printf("Names After Change:\n");
		printf("%s\n", projects_array[project_index].users_list[k]);
		}*/

	/*printf("Projects Before Change:\n");
	for (int k = 0; k < users_array[curr_index_user].projects_amount; k++){
		printf("%s\n", users_array[curr_index_user].project_list[k]);
	}*/
	for (int i = 0, j = 0; i < users_array[curr_index_user].projects_amount; i++, j++){//loop to run on the users array and find the project that we want to delete
		if (strcmp(users_array[curr_index_user].project_list[i], projects_array[curr_index_project].name) == 0){//if we found the project
			users_array[curr_index_user].project_list[i] = users_array[curr_index_user].project_list[i + 1];//we will delete
			j = i + 1;//increase the j
		}
		users_array[curr_index_user].project_list[i] = users_array[curr_index_user].project_list[j];//copy all the other projects in 1 place before
	}
	users_array[curr_index_user].projects_amount--;//decrease the amount projects of user
	int new_project_amount_in_users;
	new_project_amount_in_users = users_array[curr_index_user].projects_amount;
	users_array[curr_index_user].project_list = (char **)realloc(users_array[curr_index_user].project_list, sizeof(char*)*new_project_amount_in_users);//allocate new array of projects
	/*printf("Projects After Change:\n");
	for (int k = 0; k < users_array[curr_index_user].projects_amount; k++){
		printf("%s\n", users_array[curr_index_user].project_list[k]);
	}*/

}
void remove_user(){
	int i, notvalid = False;
	print_web_users();
	printf("choose member for remove for site enter the number between 1-%d: ", web_users_amount);

	do
	{
		if (notvalid){
			printf("wrong key");
			if (choose_yes_or_no())
				return;
			printf("enter key again");
			notvalid = False;
		}
		scanf("%d", &i);
		if (i<1 || i>web_users_amount + 1)
			notvalid = True;
	} while (notvalid);
	printf("you want to remove %s from the site ", users_array[i - 1].name);
	if (choose_yes_or_no()){
		for (i -= 1; i < web_users_amount - 1; i++){
			strcpy(users_array[i].name, users_array[i + 1].name);
			strcpy(users_array[i].password, users_array[i + 1].password);
		}
		web_users_amount--;
	}
	users_array = (Users*)realloc(users_array, (web_users_amount)* sizeof(Users));
}
void add_Wmanager(int index_user){
	printf("you want to make %s manger in this project", projects_array[curr_index_project].users_list[index_user]);//print to user 
	if (!choose_yes_or_no()){//if manger choose yes continue
		projects_array[curr_index_project].manager_amount++;//manager_amount +1
		projects_array[curr_index_project].Manager_list = (char**)realloc(projects_array[curr_index_project].Manager_list, sizeof(char*)*projects_array[curr_index_project].manager_amount);//Memory allocation
		projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1] = (char*)malloc(sizeof(char)*SIZE);//Memory allocation
		strcpy(projects_array[curr_index_project].Manager_list[projects_array[curr_index_project].manager_amount - 1], projects_array[curr_index_project].users_list[index_user]);//copy the name to new arry
		}
}
void message_abute_task(int index){
	send_message_for_all_in_project(users_array[curr_index_user].name, curr_index_project, ("%s open new task", users_array[curr_index_user].name));
}
void change_status(){

}
void remove_user_from_project(int index_to_delete){
	int flag = 0,check_if_manager=0;

	/*for (int k = 0; k < projects_array[project_index].users_amount; k++){
		printf("Names Before Change:\n");
		printf("%s\n", projects_array[project_index].users_list[k]);
	}*/
	for (int i = 0; i < projects_array[curr_index_project].manager_amount; i++){//loop to check if we connected as a manger of project
		if (strcmp(projects_array[curr_index_project].Manager_list[i], users_array[curr_index_project].name) == 0)flag = 1;//if yes change the flag to 1
		}
	if (strcmp(users_array[curr_index_project].name, users_array[index_to_delete].name) == 0)check_if_manager = 1;//check if manager try to delete itself 
		if (flag == 1 && check_if_manager ==0){
			for (int i = 0, j = 0; i < projects_array[curr_index_project].users_amount; i++, j++){//loop to run on the project array and find the user that we want to delete
				if (strcmp(projects_array[curr_index_project].users_list[i], users_array[index_to_delete].name) == 0){//if we found the user
					projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[i + 1];//we will delete
					j = i + 1;//increase the j
				}
				projects_array[curr_index_project].users_list[i] = projects_array[curr_index_project].users_list[j];//copy all the other users in 1 place before
			}
			projects_array[curr_index_project].users_amount--;//decrase the amnout users in project
			int new_user_amount_in_project;
			new_user_amount_in_project = projects_array[curr_index_project].users_amount;
			projects_array[curr_index_project].users_list = (char **)realloc(projects_array[curr_index_project].users_list, sizeof(char*)*new_user_amount_in_project);//realloc the users array 

		}
		else {
			printf("You Are Not A Manager In This Project - Sorry Only Manager Can Remove User From Project\n");
			printf("Or You Are Manager And you Try To Delete Your Self\n");
		}

		/*for (int k = 0; k < projects_array[project_index].users_amount; k++){
			printf("Names After Change:\n");
			printf("%s\n", projects_array[project_index].users_list[k]);
		}*/
}






