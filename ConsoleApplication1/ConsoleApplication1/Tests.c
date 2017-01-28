#define _CRT_SECURE_NO_WARNINGS
#include "MinUnit.h"

typedef enum{ False = 0, True = 1 } bool;

MU_TEST(test_fill_arrays) 
{
	mu_check(fill_arrays() == True);
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
MU_TEST(test_print_all_messages){
	mu_check(print_all_messages());

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
	MU_RUN_TEST(test_check_admin);
	MU_RUN_TEST(test_print_all_messages);
}
int Unit_tests(int argc, char *argv[]) 
{
	MU_RUN_SUITE(test_suite_fill_arrays);
	MU_RUN_SUITE(test_suite_checking_functions);
	MU_REPORT();
	return 0;
}
