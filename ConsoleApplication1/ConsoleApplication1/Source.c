#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#define SIZE 20
#define MODEOUT "w"
#define USER_FILE_NAME "users.txt"
#define ADMIN_FILE "web_manager.txt"
#define MESSAGE_FILE "messeges.txt"
#define MESSAGE_SIZE 200

typedef enum{ False = 0, True = 1 } bool;
typedef struct
{
	char name[SIZE];
}WebManager;
typedef struct
{
	char name[SIZE];
	char password[SIZE];
	struct Projects** project_list;
	int projects_amount;
	struct Messages** message_list;
	int messages_amount;
}Users;
typedef struct
{
	char name[SIZE];
	struct Users** users_list;
	int users_amount;
	struct Status** status_list;
	int status_amount;
	char** Manager_list;
	int manager_amount;

}Projects;
typedef struct
{
	char name[SIZE];
	struct Tasks** tasks_list;
	int tasks_amount;
} Status;
typedef struct
{
	char project_name[SIZE];
	char name[SIZE];
	char* task_details;
	bool task_progres;
	struct Users* assign_to;
}Tasks;
typedef struct
{
	char sender[SIZE];
	char content[MESSAGE_SIZE];
}Messages;
void signUp();
void cleanBuffer();
int log_in(char member[]);
int String(char arry[]);
void cleanString(char arry[]);
int If_Member_Return_True(char user[], char password[]);
int compareArrays(char user_from_list[], char user_from_member[]);
void play(char member[]);
void system_massage();

WebManager* Wmanager;
Users* users_array;
Projects* projects_array;
Messages* messages_array;
Tasks* tasks_array;
void fill_arrays();
int main(){
	char member[] = { "zohar" };
	int enter = 0;
	system_massage(member);
	
	do
	{
		printf("1.log in\n2.sign up\nplease enter you chooic: ");//זמנית בנתיים עד שנראה איך מריצים דרך פונקציה play
		scanf("%d", &enter);
		cleanBuffer();
		if (enter == 1){
			if (log_in(member))
				play(member);
		}
		if (enter == 2){
			signUp();
		}
		enter = 0;
	} while (True);
	return 0;
}

void signUp(){
	int count = 0, member_Exist = False, temp = '\0';
	char member[SIZE], password[SIZE];//open arry
	FILE *users;//Declaring files
	Users *check_user;// Opening indicates the size of the array;
	users = fopen(USER_FILE_NAME, "r+");//open file to read
	if (users == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	fscanf(users, "%d", &count);//get the number of users
	check_user = (Users*)malloc((count)*sizeof(Users));//Opening indicates the size of the array;
	do//loop for sign up
	{
		if (member_Exist){//if user make mistake
			member_Exist = False;//reset the flag
			if (wont_exit()){//print to user quiquestion if Continue if not return
				free(check_user);//free pointer
				return;
			}
		}
		printf("please enter a new member: ");//print to user Guidelines
		fseek(users, 0L, SEEK_SET);//go to the start in file
		member_Exist = String(member);//get the user name from user
		if (!member_Exist){//if user name is correct get in loop
			for (int i = 0; i < count && member_Exist == False; i++){//loop for check if user name in system
				fscanf(users, "%s", &check_user[i].name);//scan from file to pointer
				if (compareArrays(check_user[i].name, member)){//return true if the user in system
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
				free(check_user);//frre the pointer
				return;
			}
			printf("please enter password again: ");//print to user massage
		}
		member_Exist = String(password);//get password from user
	} while (member_Exist);
	fseek(users, 0L, SEEK_SET);//go to head of fie
	fscanf(users, "%d", &count);//get the number of users in file
	count++;//after we get name and password we update the number of users
	fseek(users, 0L, SEEK_SET);//go back to head of  file
	fprintf(users, "%d", count);//print the new number of memeber to file
	fseek(users, 0L, SEEK_END);//go to end in file
	fprintf(users, "\n%s %s", member, password);//print to file to new user
	fclose(users);//close the file
	free(check_user);//free the pointer
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
int log_in(char member[]){
	int Not_Valid_Pass = False/*boolean var for password confirmation*/;
	int Not_Valid_Name = False/*boolean var for username confirmation*/;
	int Not_Member = True/*boolean var for member verivication*/;
	char temp = '\0';
	char password[SIZE];//open string
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
		Not_Member = If_Member_Return_True(member, password);//check if appropriate password to use
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
int If_Member_Return_True(char user[], char password[]){
	int count = 0;
	FILE *users;//Declaring files
	Users *check_user; //Open User type structures
	users = fopen(USER_FILE_NAME, "r");//open file to read
	if (users == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	fscanf(users, "%d", &count);//get the number of users
	check_user = (Users*)malloc((count)*sizeof(Users));//Opening indicates the size of the array
	for (int i = 0; i<count; i++){//loop for check if member exist
		fscanf(users, "%s%s", &check_user[i].name, &check_user[i].password);//scan users from file
		if (compareArrays(check_user[i].name, user)){//open function if user exsist check password
			if (compareArrays(check_user[i].password, password)){//If appropriate password to use
				fclose(users);//close file
				free(check_user);//free poinet
				return True;
			}
			else{
				fclose(users);//close file
				free(check_user);//free pointer
				return False;
			}
		}
	}
	free(check_user);
	fclose(users);
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
void play(char member[]){
	int count = 0, i = 0, Not_admin = True;
	char temp = '\0';
	FILE *admin;//Declaring files
	WebManager *check_admin;
	admin = fopen(ADMIN_FILE, "r");//open file to read
	if (admin == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	fscanf(admin, "%d", &count);
	check_admin = (WebManager*)malloc((count)*sizeof(WebManager));//Opening indicates the size of the array
	for (int i = 0; i<count&&Not_admin == True; i++){
		fscanf(admin, "%s", &check_admin[i].name);//scan from file to pointer
		if (compareArrays(check_admin[i].name, member)){
			printf("welcome %s you want to conect to your admin account if so enter Y else enter other any key: ", member);
			scanf("%c", &temp);
			if (temp == 'Y' || temp == 'y'){
				Not_admin = False;
				printf("%s you now Admin\n", member);
			}
		}
	}
	fclose(admin);
	if (Not_admin)
		printf("welcome %s\n", member);
}
int wont_exit(){//function to ask the user if exit to loby/main
	int temp = False;
	printf("you want enter again if so enter Y else enter othe key: ");//massage to user
	scanf("%c", &temp);//scan flag
	if (!(temp == 'y' || temp == 'Y')){//if flag = y(yes) continue
		cleanBuffer();//clean buffer
		return True;
	}
	cleanBuffer();
	return False;
}
void system_massage(char admin_name[]){
	char temp = '\0';
	FILE *message;//Declaring files
	Messages system_massage;// Opening indicates the size of the array;
	message = fopen(MESSAGE_FILE, "a+");//open file to read
	if (message == NULL){//if file not open quit from program
		printf("the file could not be opened\n");
		exit(1);
	}
	printf("helo admin you want to send sysem massage?\nif yes press Y other print any key: ");
	scanf("%c", &temp);
	if (temp == 'y' || temp == 'Y'){
		fgets(system_massage.content, MESSAGE_SIZE, stdin);
		strcpy(system_massage.sender, admin_name);
		fprintf(message, "%s%s", system_massage.sender, system_massage.content);
	}
}
void fill_arrays(){
	FILE* users_File = fopen(USER_FILE_NAME, "r");
	int amount_of_users;
	fscanf(users_File, "%d", amount_of_users);
	users_array = (Users*)malloc(sizeof(Users)*amount_of_users);
	for (int i = 0; i < amount_of_users; i++){
		fscanf(users_File, "%s", users_array[i].name);
		fscanf(users_File, "%s", users_array[i].password);
	}
	printf("%s", users_array[0].name);
}