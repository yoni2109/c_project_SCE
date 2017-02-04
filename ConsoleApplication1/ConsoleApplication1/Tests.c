#define _CRT_SECURE_NO_WARNINGS
#include "MinUnit.h"

typedef enum{ False = 0, True = 1 } bool;

MU_TEST(test_fill_arrays){
	mu_check(fill_arrays());
}
MU_TEST(test_scan_no1)
{
	mu_check(scan_no1() == True);
}
MU_TEST(test_scan_no2)
{
	mu_check(scan_no2() == True);
}
MU_TEST(test_scan_no3)
{
	mu_check(scan_no3() == True);
}
MU_TEST(test_sort_tasks_no4)
{
	mu_check(sort_tasks_no4() == True);
}
MU_TEST(test_sort_projects_to_users_no5)
{
	mu_check(sort_projects_to_users_no5() == True);
}
MU_TEST(test_scan_no6)
{
	mu_check(scan_no6() == True);
}
MU_TEST(test_sort_messages_to_users_no7)
{
	mu_check(sort_messages_to_users_no7() == True);
}
MU_TEST(test_check_admin){
	mu_check(check_admin("zohar") == True);
}
MU_TEST(test_print_arrays_to_files)
{
	mu_check(print_arrays_to_files() == True);
}
MU_TEST(test_print_no1)
{
	mu_check(print_no1() == True);
}
MU_TEST(test_print_no2){
	mu_check(print_no2());
}
MU_TEST(test_print_no3)
{
	mu_check(print_no3() == True);
}
MU_TEST(test_print_no4)
{
	mu_check(print_no4() == True);
}
MU_TEST(test_sign_up){
	mu_check(signUp("test", "1234"));
	
}
MU_TEST(test_log_in){
	mu_check(check_member("test", "1234"));
}
MU_TEST(test_get_project_index){
	mu_check(get_project_index("test project") != -1);
}
MU_TEST(test_add_new_project){
	mu_check(add_new_project("test project"));
}
MU_TEST(test_add_user_to_project){
	mu_check(add_user_to_project(0, "yoni"));
}
MU_TEST(test_remove_task){
	mu_check(remove_task(0,0));
}
MU_TEST(test_new_task){
	mu_check(new_task("test", "test"));
}
MU_TEST(test_send_message){
	mu_check(send_message_by_user("mark", "mark", "test"));
}
MU_TEST(test_send_system_message){
	mu_check(send_message_by_admin("test"));
}
MU_TEST(test_send_message_in_project){
	mu_check(send_message_for_all_in_project("yoni", "test"));
}
MU_TEST(test_remove_user_from_project){
	mu_check(remove_user_from_project(get_user_index("yoni")));
}
MU_TEST(test_confirm_task){
	mu_check(confirm_task(0, 0));
}
MU_TEST(test_remove_user_from_web){
	mu_check(remove_user(get_user_index("test")));
}
MU_TEST(test_exit_from_project){
	mu_check(exit_from_project());
}
MU_TEST(test_user_promotion){
	mu_check(!prmotoe_user_to_manger(0));
}
MU_TEST(test_add_new_status){
	mu_check(add_new_status("testing"));
}
MU_TEST_SUITE(test_suite_print_arrays_to_files)
{
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_print_arrays_to_files);
	MU_RUN_TEST(test_print_no1);
	MU_RUN_TEST(test_print_no2);
	MU_RUN_TEST(test_print_no3);
	MU_RUN_TEST(test_print_no4);
	MU_REPORT_SUITE();
}
MU_TEST_SUITE(test_suite_fill_arrays)
{
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_fill_arrays);
	MU_RUN_TEST(test_scan_no1);
	MU_RUN_TEST(test_scan_no2);
	MU_RUN_TEST(test_scan_no3);
	MU_RUN_TEST(test_sort_tasks_no4);
	MU_RUN_TEST(test_sort_projects_to_users_no5);
	MU_RUN_TEST(test_scan_no6);
	MU_RUN_TEST(test_sort_messages_to_users_no7);
	MU_REPORT_SUITE();
}
MU_TEST_SUITE(test_suite_checking_functions){
	MU_SUITE_CONFIGURE(NULL, NULL);
	MU_RUN_TEST(test_sign_up);
	MU_RUN_TEST(test_log_in);
	MU_RUN_TEST(test_check_admin);
	MU_RUN_TEST(test_add_new_project);
	MU_RUN_TEST(test_add_user_to_project);
	MU_RUN_TEST(test_get_project_index);
	MU_RUN_TEST(test_new_task);
	MU_RUN_TEST(test_confirm_task);
	MU_RUN_TEST(test_remove_task);
	MU_RUN_TEST(test_send_message);
	MU_RUN_TEST(test_send_system_message);
	MU_RUN_TEST(test_send_message_in_project);
	MU_RUN_TEST(test_remove_user_from_project);
	MU_RUN_TEST(test_user_promotion);
	MU_RUN_TEST(test_add_new_status);
	MU_RUN_TEST(test_exit_from_project);
	MU_RUN_TEST(test_remove_user_from_web);
	MU_REPORT_SUITE();
}
int Unit_tests() 
{
	MU_RUN_SUITE(test_suite_fill_arrays);
	MU_RUN_SUITE(test_suite_checking_functions);
	MU_RUN_SUITE(test_suite_print_arrays_to_files);
	MU_REPORT();
	return 0;
}
