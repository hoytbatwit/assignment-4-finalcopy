#include <stdlib.h>
#include "files.h"
#include "unity.h"

void setUp (void) {}
void tearDown (void) {}

/**
 */
void test_file_open1(void) {
    struct files_t* f = files_open("numbers.txt", 15);
    files_close(f);
}

/**
 */
void test_file_open2(void) {
    struct files_t* f = files_open("numbers.txt", 15);
    files_close(f);
}
/**
 */
void test_file_read1(void) {
    char buffer[16];
    struct files_t* f = files_open("numbers.txt", 15);
    files_read(f, buffer, 15);
    buffer[15] = 0;
    char* expected = "012345678901234";
    
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_EQUAL_INT(f->position, 15);
    files_close(f);
}

/**
 */
void test_file_read2(void) {
    char buffer[16];
    struct files_t* f = files_open("numbers.txt", 15);
    files_read(f, buffer, 15);
    files_read(f, buffer, 15);
    buffer[15] = 0;
    char* expected = "567890123456789";
    
    TEST_ASSERT_EQUAL_STRING(expected, buffer);
    TEST_ASSERT_EQUAL_INT(f->position, 30);
    files_close(f);
}

/**
 * The main function for this unit test runner
 */
int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_file_open1);
    RUN_TEST(test_file_open2);

    RUN_TEST(test_file_read1);
    RUN_TEST(test_file_read2);

    return UNITY_END();
}
