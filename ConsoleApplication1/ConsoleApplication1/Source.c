#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define TEMP_SIZE 1024
#define SIZE 20
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
	char content[SIZE];
	char message[MESSAGE_SIZE];
}Messages;
typedef struct
{
	char name[SIZE];
}WebManager;
typedef struct
{
	char name[SIZE];
	char password[SIZE];
	char *project_list[SIZE];
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
	Tasks * tasks_list;
	int tasks_amount;
} Status;
typedef struct
{
	char name[SIZE];
	char* users_list[SIZE];
	int users_amount;
	Status* status_list;
	int status_amount;
	char* Manager_list[SIZE];
	int manager_amount;
	int archived;

}Projects;
void scan_no1();
void scan_no2();
void scan_no3();
void sort_tasks_no4();
void print_user_projects(int index_user_array);
void signUp();
void cleanBuffer();
int log_in();
int String(char arry[]);
void cleanString(char arry[]);
int check_member(char user[], char password[]);
int compareArrays(char user_from_list[], char user_from_member[]);
void play(char member[]);
void system_massage();
void print_projects_task(int index_project_array);
void print_web_users();
int check_admin(char * name);
void confirm_project(int index_user);
void fill_arrays();
void send_message();
char * func_to_get_message();
void allocate_messages();
void change_pass(int index_user_array);

WebManager* Wmanager;//will contain the web managet user name
Users* users_array;// will contain all web users
int web_users_amount = 0;//will contain the amount of users registered to web
Projects* projects_array;// will contain all web projects
int web_projects_amount = 0;//will contain the amount of all web projects
Messages* messages_array;// will contain all messages that moves on the web
int web_messages_amount = 0;//amount of all messages
Tasks* tasks_array;//will contain all tasks in web
int web_tasks_amount=0;//tasks amount

int main(){
	fill_arrays();
	char member[] = { "zohar" };
	int enter = 0;
//	system_massage(member);
	
	
	do
	{
		printf("1.log in\n2.sign up\nplease enter you chooic: ");//זמנית בנתיים עד שנראה איך מריצים דרך פונקציה play
		scanf("%d", &enter);
		cleanBuffer();
		if (enter == 1)
			log_in(member);
		if (enter == 2){
			signUp();
		}
		enter = 0;
	} while (True);
	return 0;
}
void signUp(){
	int member_Exist = False;
	char member[SIZE], password[SIZE];//open arry
	do//loop for sign up
	{
		if (member_Exist){//if user make mistake
			member_Exist = False;//reset the flag
			if (wont_exit())//print to user quiquestion if Continue if not return
				return;
			}
		printf("please enter a new member: ");//print to user Guidelines
		member_Exist = String(member);//get the user name from user
		if (!member_Exist){//if user name is correct get in loop
			for (int i = 0; i < web_projects_amount && member_Exist == False; i++){//loop for check if user name in system
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
			if (wont_exit()){//check if the user want to continue
				return;
			}
			printf("please enter password again: ");//print to user massage
		}
		member_Exist = String(password);//get password from user
	} while (member_Exist);
	realloc(users_array, web_projects_amount+1);
	strcpy(users_array[web_projects_amount].name, member);
	strcpy(users_array[web_projects_amount].password, password);
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
				if (wont_exit())
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
				if (wont_exit())
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
		if (!strcmp(users_array[i].name, user))//open function if user exsist check password
			if (!strcmp(users_array[i].password, password))//If appropriate password to use
				return True;
			}
	return False;
}
int compareArrays(char user_from_list[], char user_from_member[]) {//Check for identical strings 
	int i;
	for (i = 0; user_from_list[i] != '\0' && user_from_member[i] != '\0'; i++) {
		if (user_from_list[i] != user_from_member[i])
			return False;
		if (user_from_list[i + 1] == '\0' && user_from_member[i + 1] != '\0')
			return False;
		if (user_from_list[i + 1] != '\0' && user_from_member[i + 1] == '\0')
			return False;
	}
	return True;
}
int wont_exit(){//function to ask the user if exit to loby/main
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
void system_massage(char sender[]){
	int count = 0, member_Exist = False;
	char temp = '\0';
	FILE *message;//Declaring files
	Messages system_massage;// Opening indicates the size of the array;
	FILE *users;
	Users *check_user;// Opening indicates the size of the array;
	users = fopen(USER_FILE_NAME, "r+");//open file to read
	if (users == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	fscanf(users, "%d", &count);//get the number of users
	check_user = (Users*)malloc((count)*sizeof(Users));//Opening indicates the size of the array;
	message = fopen(MESSAGE_FILE, "a");//open file to read
	if (message == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	printf("%s you want to send system massage?\nif yes press Y other print any key: ", sender);
	scanf("%c", &temp);
	cleanBuffer();
	if (temp == 'y' || temp == 'Y'){
		if (!(strcmp(sender, UNIVERSAL_DIRECTOR)))
			if (check_admin(sender))
				strcpy(sender, UNIVERSAL_DIRECTOR);
		do
		{
			if (member_Exist){
				printf("member not Exists");
				member_Exist = False;
				if (wont_exit()){//check if the user want to continue
					free(check_user);//frre the pointer
					return;
				}
			}

			printf("enter content name: ");
			cleanBuffer();
			member_Exist = String(system_massage.content);
			if (!member_Exist){
				member_Exist = True;
				for (int i = 0; i < count && member_Exist == True; i++){//loop for check if user name in system
					fscanf(users, "%s%s", &check_user[i].name, check_user[i].password);//scan from file to pointer
					if (compareArrays(check_user[i].name, system_massage.content))//return true if the user in system
						member_Exist = False;
				}
			}
		} while (member_Exist);
		strcpy(system_massage.sender, sender);
		printf("enter your mesagge: ");
		fgets(system_massage.message, MESSAGE_SIZE, stdin);
		fprintf(message, "%s\n%s\n%s", system_massage.sender, system_massage.content, system_massage.message);
		fclose(users);
		fclose(message);
	}
}
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
}
void change_pass();

void scan_no1(){
	FILE* users_File = fopen(USER_FILE_NAME, "r");
	fscanf(users_File, "%d", &web_users_amount);
	users_array = (Users*)malloc(sizeof(Users)*web_users_amount);
	for (int i = 0; i < web_users_amount; i++){
		fscanf(users_File, "%s", &users_array[i].name);
		users_array[i].name[SIZE - 1] = '/0';
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
		*projects_array[i].users_list = (char*)malloc(sizeof(char)*projects_array[i].users_amount);
		for (int j = 0; j < projects_array[i].users_amount; j++){
			fscanf(projects_file, "%s", &projects_array[i].users_list[j]);
		}
		char temp[20];
		fscanf(projects_managers_file, "%s", &temp);
		fscanf(projects_managers_file, "%d", &projects_array[i].manager_amount);
		*projects_array[i].Manager_list = (char*)malloc(sizeof(char)*projects_array[i].manager_amount);
		for (int j = 0; j < projects_array[i].manager_amount; j++){
			fscanf(projects_managers_file, "%s", &projects_array[i].Manager_list[j]);
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
		temp[j-1] = '\0';
		tasks_array[i].task_details = (char*)malloc(sizeof(char)*strlen(temp));
		strcpy(tasks_array[i].task_details, temp);
		fscanf(tasks_file, "%d %s", &tasks_array[i].task_progres, &tasks_array[i].assign_to);
	}
	fclose(tasks_file);
}
void sort_tasks_no4(){
	for (int i = 0; i < web_projects_amount; i++){
		for (int j = 0; j < web_tasks_amount; j++){
			if (strcmp(projects_array[i].name, tasks_array[j].project_name)!=0){
				for (int k = 0; k < projects_array[i].status_amount; k++){
					if (!strcmp(projects_array[i].status_list[k].name, tasks_array[j].status_name)){
						if (!projects_array[i].status_list[k].tasks_amount){
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks*)malloc(sizeof(Tasks));
							strcpy(projects_array[i].status_list[k].tasks_list[0].name , tasks_array[j].name);
							strcpy(projects_array[i].status_list[k].tasks_list[0].assign_to , tasks_array[j].assign_to);
							strcpy(projects_array[i].status_list[k].tasks_list[0].project_name , tasks_array[j].project_name);
							strcpy(projects_array[i].status_list[k].tasks_list[0].status_name , tasks_array[j].status_name);
							projects_array[i].status_list[k].tasks_list[0].task_details = (char*)malloc(sizeof(char)*strlen(tasks_array[j].task_details));
							strcpy(projects_array[i].status_list[k].tasks_list[0].task_details , tasks_array[j].task_details);
							projects_array[i].status_list[k].tasks_list[0].task_progres = tasks_array[j].task_progres;
						}
						else{
							projects_array[i].status_list[k].tasks_amount++;
							projects_array[i].status_list[k].tasks_list = (Tasks*)realloc(projects_array[i].status_list[k].tasks_list, projects_array[i].status_list[k].tasks_amount++);
							projects_array[i].status_list[k].tasks_list[projects_array[i].status_list[k].tasks_amount - 1] = tasks_array[j];
						}
					}
				}

			}
		}

	}
}
void remove_task(int index_user_array){
	int proj_to_delete_from;//value for project to delte from the task
	print_user_projects(index_user_array);
	printf("Choose Project By Number:\n");
	scanf("%d", &proj_to_delete_from);//get what user choose
	print_projects_task(proj_to_delete_from);


}
void print_user_projects(int index_user_array){
	printf("Those Your projects:\n");
	for (int i = 0; i < web_users_amount; i++){
		printf("%d. %s",(i+1), users_array[index_user_array].project_list[i]);
	}
	}
void print_projects_task(int index_project_array){
	printf("Tasks In Project:\n");
	for (int i = 0; i < projects_array[index_project_array].status_amount; i++){
		//for (int j = 0; j < projects_array[index_project_array].status_amount;j++)
		//printf("1. %s", (projects_array[index_project_array].status_list[0]).);
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
void confirm_project(int index_project, char * manager_project){//func to archived the project *only maneger can do that*
	for (int i = 0; i < projects_array[index_project].manager_amount; i++){//loop to check if manager exists in the managers array 
		if (!strcmp(projects_array[index_project].Manager_list[i], manager_project)){
			projects_array[index_project].archived = True;//if we found we will change the archived variable to True
	}
}
}
//void send_message(int index_user_array){
//	int chosen_project, chosen_user;
//	char temp_message[TEMP_SIZE];
//	//צריכה להיות פה פונקציה של לוג אין
//	print_user_projects(index_user_array);
//	printf("Choose Project :\n");
//	scanf("%d",&chosen_project);
//	//צריכה להיות פונקציה שמדפיסה את כל האפשריות
//	print_user_projects(index_user_array);//הדפסה של כל משתמשי הפרויקט
//	printf("Choose user :\n");
//	scanf("%d", &chosen_user);
//	printf("Write Your Message :\n");
//	get(temp_message);
//	realloc(messages_array, 1 * sizeof *messages_array);//realloc 1 place for new message
//	//realloc(users_array[chosen_user].message_list, 1 * sizeof *messages_array);
//	for (int i = 0; i < SIZE; i++){//loop to fill the name,target name,conntent in the last place of array messages
//		messages_array[web_messages_amount].sender[i] = users_array[index_user_array].name[i];//update sender in the global messages array
//		messages_array[web_messages_amount].target[i] = users_array[chosen_user].name[i];//update target user in the global messages array
//		messages_array[web_messages_amount].content[i] = temp_message[i];//update contain in the global messages array
//	}
//	web_messages_amount++;
//}
//void change_pass(int index_user_array){
//	char temp_pass[SIZE];
//	printf("Enter New Pass:\n");
//	get(temp_pass);//get new password
//	for (int i = 0; i < SIZE; i++){//loop to change the password
//		users_array[index_user_array].password[i] = temp_pass[i];
//	}
//}
//









