/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/04/2018
* DESCRIPTION	: This program implements cmocka test conditions for the doubly linked list

* HEADER FILES	: testfile.h
* REFERENCE: http://zhuyong.me/blog/2014/03/19/c-code-unit-testing-using-cmocka/
****************************************************************/

#include "testfile.h"

static void test_insert_at_beginning_null_pointer(void **state){
	assert_non_null(insert_at_beginning(NULL,10));
}

static void test_insert_at_end_null_pointer(void **state){
	assert_non_null(insert_at_end(NULL,10));
}

static void test_insert_at_position_null_pointer(void **state){
	assert_non_null(insert_at_position(NULL,10,0));
}

static void test_delete_from_beginning_null_pointer(void **state){
	assert_null(delete_from_beginning(NULL));
}

static void test_delete_from_end_null_pointer(void **state){
	assert_null(delete_from_end(NULL));
}

static void test_delete_from_position_null_pointer(void **state){
	assert_null(delete_from_position(NULL,0));
}

static void test_size(void **state){
	assert_non_null(size(NULL));
}

int main(void){

const struct CMUnitTest tests[] = {
	cmocka_unit_test(test_insert_at_beginning_null_pointer),
	cmocka_unit_test(test_insert_at_end_null_pointer),
	cmocka_unit_test(test_insert_at_position_null_pointer),
	cmocka_unit_test(test_delete_from_beginning_null_pointer),
	cmocka_unit_test(test_delete_from_end_null_pointer),
	cmocka_unit_test(test_delete_from_position_null_pointer),
	cmocka_unit_test(test_size)
};

return cmocka_run_group_tests(tests,NULL,NULL);
}