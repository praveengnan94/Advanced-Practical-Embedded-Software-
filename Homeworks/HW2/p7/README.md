Using cmocka I did the unit tests

I tested for the following conditions:

	cmocka_unit_test(test_insert_at_beginning_null_pointer),
	cmocka_unit_test(test_insert_at_end_null_pointer),
	cmocka_unit_test(test_insert_at_position_null_pointer),
	cmocka_unit_test(test_delete_from_beginning_null_pointer),
	cmocka_unit_test(test_delete_from_end_null_pointer),
	cmocka_unit_test(test_delete_from_position_null_pointer),
	cmocka_unit_test(test_size)


In their function definitions test_insert_at_beginning_null_pointer,test_insert_at_end_null_pointer and test_insert_at_position_null_pointer check if a NULL pointer(using assert_non_null) is returned and PASS if a non-NULL pointer is returned. Hence these cases pass as the return type is always a head node_t* type and not NULL.

For the test_delete_from_beginning_null_pointer,test_delete_from_end_null_pointer and test_delete_from_position_null_pointer, the return type is checked(using assert_null) and a PASS is given when a NULL pointer is returned. Since there are no nodes are created, these conditions also always pass. 