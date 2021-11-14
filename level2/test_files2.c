#include <stdlib.h>
#include <string.h>
#include "files.h"
#include "unity.h"

void setUp (void) {}
void tearDown (void) {}

/**
 */
void test_file_open_valid(void) {
    struct files_t* f = files_open("numbers.txt", 16);
    TEST_ASSERT_NOT_NULL(f);

    TEST_ASSERT_EQUAL_INT(0, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(16, f->ib_size);
    TEST_ASSERT_EQUAL_INT(0, f->ib_position);
    TEST_ASSERT_EQUAL_INT(0, f->ib_left);

    files_close(f);
}

/**
 */
void test_file_open_invalid(void) {
    struct files_t* f = files_open("invalid.txt", 16);
    TEST_ASSERT_NULL(f);

    files_close(f);
}

/**
 */
void test_file_read1(void) {
    struct files_t* f = files_open("numbers.txt", 16);
    TEST_ASSERT_NOT_NULL(f);

    char buffer[11];
    buffer[10] = 0;

    enum files_status status = files_read(f, buffer, 10);
    TEST_ASSERT_EQUAL(FILES_OK, status);

    char* expected = "123456789\n";
    
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_EQUAL_INT(10, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(16, f->ib_size);
    TEST_ASSERT_EQUAL_INT(10, f->ib_position);
    TEST_ASSERT_EQUAL_INT(6, f->ib_left);

    files_close(f);
}

/**
 */
void test_file_read2(void) {
    struct files_t* f = files_open("numbers.txt", 16);
    TEST_ASSERT_NOT_NULL(f);

    char buffer[11];
    buffer[10] = 0;

    enum files_status status1 = files_read(f, buffer, 10);
    enum files_status status2 = files_read(f, buffer, 10);

    char* expected = "123456789\n";
    
    TEST_ASSERT_EQUAL(FILES_OK, status1);
    TEST_ASSERT_EQUAL(FILES_OK, status2);

    TEST_ASSERT_EQUAL_STRING(expected, buffer);    
    TEST_ASSERT_EQUAL_INT(20, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(16, f->ib_size);
    TEST_ASSERT_EQUAL_INT(4, f->ib_position);
    TEST_ASSERT_EQUAL_INT(10, f->ib_left);

    files_close(f);
}

/**
 */
void test_file_read_all(void) {
    struct files_t* f = files_open("numbers.txt", 16);
    TEST_ASSERT_NOT_NULL(f);

    char buffer[11];
    buffer[10] = 0;

    enum files_status status = files_read(f, buffer, 10);
    while(status == FILES_OK) {
        status = files_read(f, buffer, 10);
    }

    TEST_ASSERT_EQUAL(status, FILES_EOF);

    char* expected = "123456789\n";
    
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_EQUAL_INT(30, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(16, f->ib_size);
    TEST_ASSERT_EQUAL_INT(14, f->ib_position);
    TEST_ASSERT_EQUAL_INT(0, f->ib_left);

    files_close(f);
}

/**
 */
void test_file_open_large(void) {
    struct files_t* f = files_open("numbers_large.txt", 24);

    TEST_ASSERT_NOT_NULL(f);

    TEST_ASSERT_EQUAL_INT(0, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(24, f->ib_size);
    TEST_ASSERT_EQUAL_INT(0, f->ib_position);
    TEST_ASSERT_EQUAL_INT(0, f->ib_left);

    files_close(f);
}

/**
 */
void test_file_read_large_all(void) {
    struct files_t* f = files_open("numbers_large.txt", 24);
    TEST_ASSERT_NOT_NULL(f);

    char buffer[11];
    buffer[10] = 0;

    enum files_status status = files_read(f, buffer, 10);
    while(status == FILES_OK) {
        status = files_read(f, buffer, 10);
    }
    TEST_ASSERT_EQUAL(status, FILES_EOF);

    char* expected = "abcdefghi\n";
    
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_EQUAL_INT(100, f->position);
    TEST_ASSERT_NOT_NULL(f->internal_buffer);
    TEST_ASSERT_EQUAL_INT(24, f->ib_size);
    TEST_ASSERT_EQUAL_INT(4, f->ib_position);
    TEST_ASSERT_EQUAL_INT(0, f->ib_left);

    files_close(f);
}


/**
 * The main function for this unit test runner
 */
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_file_open_valid);
    RUN_TEST(test_file_open_invalid);

    RUN_TEST(test_file_read1);
    RUN_TEST(test_file_read2);
    RUN_TEST(test_file_read_all);

    RUN_TEST(test_file_open_large);
    RUN_TEST(test_file_read_large_all);

    return UNITY_END();
}
