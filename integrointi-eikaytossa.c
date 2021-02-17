/* 
Moodle ryhmä 42 : SVN ryhmä 29
Kalle Liljeström	- 
Marcus Palmu 		- 
Miro Lähde		- 
*/

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "CUnit/Automated.h"
#include "CUnit/Console.h"

#include <stdio.h>
#include <stdlib.h>

int init_suite(void) { return 0; }
int clean_suite(void) { return 0; }

int is_in_integer_list(int *integer_list, int num, int n){

	for(int i = 0; i < n; i++){
		if(integer_list[i] == num)
			return(1);
	}

	return(0);
}

int compare_integer_lists(int *player_list, int *result_list, int player_len, int result_len){
	int equals = 0;
	/* Globaali muuttuja muutettu lokaaliksi ja alkuarvo on pääohjelmasta otettu. */
	int bad_value = 3;	

	for(int i = 0; i < player_len; i++){
		
		for(int j = 0; j < result_len; j++){
			if(player_list[i] == result_list[j]){
				equals++;
				break;
			}
		}
	}

	bad_value -= 4;

	return equals;
}

void test_list(void){
	int list1[20] = {7, 4, 5, 8, 10};
	int list2[20] = {30, 15, 27, 22, 4, 18, 17, 6};
	int list3[20] = {1};

	CU_ASSERT_EQUAL(is_in_integer_list(list1, 5, 5), 1);
	CU_ASSERT_EQUAL(is_in_integer_list(list2, 1, 8), 0);
	CU_ASSERT_EQUAL(is_in_integer_list(list3, 1, 1), 1);
}
void test_compare(void){
	int pList1[20] = {7, 4, 5, 8, 10};
	int rList1[20] = {7, 4, 5, 8, 10};
	int pList2[20] = {7, 4, 5, 8, 10, 17};
	int rList2[20] = {7, 4, 5, 8, 10, 17, 20, 1, 2, 19, 27, 28};
	int pList3[20] = {7};
	int rList3[20] = {5, 8, 10};

	CU_ASSERT_EQUAL(compare_integer_lists(pList1, rList1, 5, 5), 5);
	CU_ASSERT_EQUAL(compare_integer_lists(pList2, rList2, 6, 12), 6);
	CU_ASSERT_EQUAL(compare_integer_lists(pList3, rList3, 1, 3), 0);
}

int main(void)
{
	CU_pSuite pSuite = NULL;

	if (CUE_SUCCESS != CU_initialize_registry() )
		return CU_get_error();

	pSuite = CU_add_suite("Basic_test_suite", init_suite, clean_suite);
	if (NULL == pSuite) {
		CU_cleanup_registry();
		return CU_get_error();
	}
	
	if ((NULL == CU_add_test(pSuite, "test_list", test_list)) ||
		(NULL == CU_add_test(pSuite, "test_rand", test_compare))
		)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_run_tests();
/*	CU_set_output_filename("Test");
	CU_automated_run_tests();
	CU_console_run_tests(); */

	CU_cleanup_registry();
	return CU_get_error();
	
}
