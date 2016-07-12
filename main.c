#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>
#include <unistd.h>

#define forever 1

const char different_delim_flag[] = "//";

int exception;

size_t linelen(const char *s) {
	const char *original = s;
	while(1) {
		if (*s == 0 or *s == '\n') break;
		s++;
	}
	return s - original;
}

int add(char *numbers) {
	if (*numbers == 0) return 0;

	char *different_delimiter = ",";
	size_t delimlength = 1;

	if (strncmp(numbers, different_delim_flag, 2) == 0) {
		numbers += sizeof(different_delim_flag) - 1;
		delimlength = linelen(numbers);
		different_delimiter = numbers;
		if (delimlength > 1 and *numbers == '[') {
			different_delimiter = numbers + 1;
			numbers += delimlength;
			delimlength -= 2;
		} else {
			numbers += delimlength;
		}
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
		if (*ending == ',' or *ending == '\n') numbers = ending +1; else
		if (strncmp(ending, different_delimiter, delimlength) == 0) {
			numbers = ending + delimlength;
		} else break;
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

bool add_test_variable_length_delimiter() {
	if (add("//[zzap]\n3,5zzap1") == 9) return true;
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
	perform_test("Testing variable-lenght delimiter", add_test_variable_length_delimiter);

	return EXIT_SUCCESS;
}
