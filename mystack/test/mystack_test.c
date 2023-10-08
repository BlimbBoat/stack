#include <string.h>
#include <stdio.h>

#include "mystack.h"
#include "unity.h"

// I rather dislike keeping line numbers updated, so I made my own macro to ditch the line number
#define MY_RUN_TEST(func) RUN_TEST(func, 0)

void setUp(void)
{
}

void tearDown(void)
{
    // This is run after EACH test
}

void mystack_create_list_is_null(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_create_multiple_stacks(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(1));
  TEST_ASSERT_EQUAL(3,mystack_create(1));
  TEST_ASSERT_EQUAL(4,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(3));
  TEST_ASSERT_EQUAL(0,mystack_destroy(4));
}

void mystack_create_multiple_stacks_but_remove_some_in_between(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
}

void mystack_create_different_objsizes(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(23));
  TEST_ASSERT_EQUAL(3,mystack_create(89));
  TEST_ASSERT_EQUAL(4,mystack_create(7));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(3));
  TEST_ASSERT_EQUAL(0,mystack_destroy(4));
}

void mystack_push_list_is_null(void)
{
  int i = 0;
  TEST_ASSERT_EQUAL(-1,mystack_push(1,&i));
}

void mystack_push_objPointer_is_null(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(-1,mystack_push(1,NULL));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_push_handle_not_found(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(-1,mystack_push(2,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_push_success(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_push_multiple_objects_of_different_data_types_in_same_handler(void)
{
  int i = 0;
  char k = 0;
  char s[3] = "as";

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&k));
  TEST_ASSERT_EQUAL(0,mystack_push(1,s));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_push_object_in_different_handlers(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(1));
  TEST_ASSERT_EQUAL(3,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(2,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(3,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(3));
}

void mystack_pop_list_is_null(void)
{
  int i = 0;
  TEST_ASSERT_EQUAL(-1,mystack_pop(1,&i));
}

void mystack_pop_objPointer_is_null(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(-1,mystack_pop(1,NULL));
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_pop_handle_not_found(void)
{
  int i = 0;
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(-1,mystack_pop(2,&i));
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_pop_no_object_to_pop(void)
{
  int i = 0;
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(-1,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_pop_popped_value_has_the_same_value_as_pushed_value(void)
{
  int i = 5;
  int j = 0;
  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(1,&j));
  TEST_ASSERT_EQUAL(i,j);
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_pop_multiple_obj_in_the_same_handler(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));

  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(-1,mystack_pop(1,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_pop_objects_in_different_handlers(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(1));
  TEST_ASSERT_EQUAL(3,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(2,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(3,&i));

  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(3,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(2,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(3));
}

void mystack_pop_objects_in_different_data_type(void)
{
  char c = 1;
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&c));

  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));

  TEST_ASSERT_EQUAL(c,i);

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_destroy_list_is_null(void)
{
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_destroy_handle_not_found(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(-1,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_destroy_success(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_list_is_null(void)
{
  TEST_ASSERT_EQUAL(-1,mystack_nofelem(1));
}

void mystack_nofelem_handle_not_found(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(-1,mystack_nofelem(2));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_handle_is_empty(void)
{
  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_nofelem(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_handle_has_one_object(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));

  TEST_ASSERT_EQUAL(1,mystack_nofelem(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_handle_has_multiple_objects(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));

  TEST_ASSERT_EQUAL(3,mystack_nofelem(1));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_handle_has_data_pushed_and_popped(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(1,&i));

  TEST_ASSERT_EQUAL(3,mystack_nofelem(1));

  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));
  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));

  TEST_ASSERT_EQUAL(1,mystack_nofelem(1));

  TEST_ASSERT_EQUAL(0,mystack_pop(1,&i));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
}

void mystack_nofelem_of_different_handles(void)
{
  int i = 0;

  TEST_ASSERT_EQUAL(1,mystack_create(1));
  TEST_ASSERT_EQUAL(2,mystack_create(1));
  TEST_ASSERT_EQUAL(3,mystack_create(1));

  TEST_ASSERT_EQUAL(0,mystack_push(2,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(2,&i));
  TEST_ASSERT_EQUAL(0,mystack_push(3,&i));

  TEST_ASSERT_EQUAL(0,mystack_nofelem(1));
  TEST_ASSERT_EQUAL(2,mystack_nofelem(2));
  TEST_ASSERT_EQUAL(1,mystack_nofelem(3));

  TEST_ASSERT_EQUAL(0,mystack_destroy(1));
  TEST_ASSERT_EQUAL(0,mystack_destroy(2));
  TEST_ASSERT_EQUAL(0,mystack_destroy(3));
}

int main (int argc, char * argv[])
{
    UnityBegin();

    MY_RUN_TEST(mystack_create_list_is_null);
    MY_RUN_TEST(mystack_create_multiple_stacks);
    MY_RUN_TEST(mystack_create_multiple_stacks_but_remove_some_in_between);
    MY_RUN_TEST(mystack_create_different_objsizes);

    MY_RUN_TEST(mystack_push_list_is_null);
    MY_RUN_TEST(mystack_push_objPointer_is_null);
    MY_RUN_TEST(mystack_push_handle_not_found);
    MY_RUN_TEST(mystack_push_success);
    MY_RUN_TEST(mystack_push_multiple_objects_of_different_data_types_in_same_handler);
    MY_RUN_TEST(mystack_push_object_in_different_handlers);

    MY_RUN_TEST(mystack_pop_list_is_null);
    MY_RUN_TEST(mystack_pop_objPointer_is_null);
    MY_RUN_TEST(mystack_pop_handle_not_found);
    MY_RUN_TEST(mystack_pop_no_object_to_pop);
    MY_RUN_TEST(mystack_pop_popped_value_has_the_same_value_as_pushed_value);
    MY_RUN_TEST(mystack_pop_multiple_obj_in_the_same_handler);
    MY_RUN_TEST(mystack_pop_objects_in_different_handlers);
    MY_RUN_TEST(mystack_pop_objects_in_different_data_type);

    MY_RUN_TEST(mystack_destroy_list_is_null);
    MY_RUN_TEST(mystack_destroy_handle_not_found);
    MY_RUN_TEST(mystack_destroy_success);

    MY_RUN_TEST(mystack_nofelem_list_is_null);
    MY_RUN_TEST(mystack_nofelem_handle_not_found);
    MY_RUN_TEST(mystack_nofelem_handle_is_empty);
    MY_RUN_TEST(mystack_nofelem_handle_has_one_object);
    MY_RUN_TEST(mystack_nofelem_handle_has_multiple_objects);
    MY_RUN_TEST(mystack_nofelem_handle_has_data_pushed_and_popped);
    MY_RUN_TEST(mystack_nofelem_of_different_handles);
    return UnityEnd();
}
