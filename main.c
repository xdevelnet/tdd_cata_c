#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>

int add(char *numbers) {
    return 0;
}

bool add_test_empty() {
    if (add("") == 0) return true;
    return false;
}

bool add_test_one_number() {
    if (add("5") == 5) return true;
    return false;
}

bool add_test_two_numbers() {
    if (add("5,7") == 12) return true;
    return false;
}

void perform_test(char *test_name, bool(testfunc)()) {
    if (testfunc() == true) printf("%s passed.\n\n", test_name); else printf("%s not passed.\n\n", test_name);
}

int main(int argc, char **argv) {
    perform_test("Testing empty string", add_test_empty);
    perform_test("Testing one number", add_test_one_number);
    perform_test("Testing two number", add_test_two_numbers);
    return EXIT_SUCCESS;
}