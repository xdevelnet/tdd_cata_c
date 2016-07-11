#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>

#define forever 1

const char different_delim_flag[] = "//";

int exception;

int add(char *numbers) {
	if (*numbers == 0) return 0;

	char different_delimiter = ',';

	if (strncmp(numbers, different_delim_flag, 2) == 0) {
		numbers += sizeof(different_delim_flag)-1;
		different_delimiter = *numbers;
		numbers++;
	}

	int sum = 0;
	int tmpsum;
	char *ending;
	while(forever) {
		tmpsum = (int) strtol(numbers, &ending, 10);
		if (tmpsum < 0) {
			fprintf(stdout, "negatives not allowed\n");
			exception = 1;
		}
		if (tmpsum > 1000) tmpsum -= 1000;
		sum += tmpsum;
		if (*ending == 0) break; else
		if (*ending == ',' or *ending == '\n' or *ending == different_delimiter) numbers = ending +1; else break;
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

bool add_test_newline_delimiter() {
	if (add("7,9\n5,1,3") == 25) return true;
	return false;
}

bool add_test_different_delimiter() {
	if (add("//z\n3,5z1") == 9) return true;
	return false;
}

bool add_test_negative_exception() {
	add("99,-11,-7"); // should we care about result with such "good" exception handling?
	if (exception == 1) return true;
	return false;
}
bool add_test_bigger_than_thousand() {
	if (add("466,913,1009,0,1") == 1389) return true;
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
	perform_test("Testing newline delimiter", add_test_newline_delimiter);
	perform_test("Testing different delimiter", add_test_different_delimiter);
	perform_test("Testing negative exception", add_test_negative_exception);
	perform_test("Testing numbers > 1000", add_test_bigger_than_thousand);

	return EXIT_SUCCESS;
}
