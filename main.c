#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>

#define forever 1

int add(char *numbers) {
	int sum = 0;
	char *ending = 0;

	while(forever) {
		sum += (int) strtol(numbers, &ending, 10);
		if (*ending == 0) break;
		if (*ending == ',') numbers = ending +1;
	}

	return sum;
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

bool add_test_unknown_amount() {
	if (add("5,7,88,911,0,3") == 1014) return true;
	return false;
}

void perform_test(char *test_name, bool(testfunc)()) {
	if (testfunc() == true) printf("%s: passed.\n\n", test_name); else printf("%s: NOT passed.\n\n", test_name);
}

int main(int argc, char **argv) {
	perform_test("Testing empty string", add_test_empty);
	perform_test("Testing one number", add_test_one_number);
	perform_test("Testing two number", add_test_two_numbers);
	perform_test("Testing unknown amount of numbers", add_test_unknown_amount);

	return EXIT_SUCCESS;
}
