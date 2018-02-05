/***************************************************************
* AUTHOR	: Praveen Gnanasekaran
* DATE		: 02/04/2018
* DESCRIPTION	: This program contains header libraries and 

* HEADER FILES	: testfile.c
* REFERENCE: http://zhuyong.me/blog/2014/03/19/c-code-unit-testing-using-cmocka/
****************************************************************/
#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdlib.h>
#include <stdio.h>
#include <cmocka.h>
#include "../p6/doublylinkedlist.h"


static void test_insert_at_beginning_null_pointer(void **state);