#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iso646.h>
#include <string.h>

#define forever 1

const char different_delim_flag[] = "//"; // sizeof() == 3

int exception;

size_t linelen(const char *s) {
	const char *original = s;
	while(forever) {
		if (*s == 0 or *s == '\n') break;
		s++;
	}
	return s - original;
}

size_t is_delimiter(char *str, char *possibledelimiter) {
	if (str == NULL or possibledelimiter == NULL or *possibledelimiter == 0 or *str == 0) return 0;
	if ((*str == ',' or *str == '\n') and ((*(str + 1) >= '0' and *(str + 1) <= '9') or *(str + 1) == '-')) return 1;

	size_t delimlength = 0;

	if (strncmp(possibledelimiter, different_delim_flag, sizeof(different_delim_flag) -1) == 0) {
		if (*(possibledelimiter += sizeof(different_delim_flag) - 1) != '[' and *str == *possibledelimiter) return 1;

		char *search;
		while (forever) {
			search = strchr(++possibledelimiter, ']');
			if (search == NULL or search > linelen(possibledelimiter) + possibledelimiter) break;
			delimlength = search - possibledelimiter;
			if (strncmp(str, possibledelimiter, delimlength) == 0) return delimlength;
			possibledelimiter = search + 1;
		}
	}
	return 0;
}

int add(char *numbers_str) {
	if (*numbers_str == 0) return 0;

	char *starting_part_of_str = numbers_str;
	int sum = 0;
	int tmpsum;
	char *ending;
	size_t length;

	if (strncmp(numbers_str, different_delim_flag, sizeof(different_delim_flag) - 1) == 0) numbers_str += linelen(numbers_str) + 1;


	while(forever) {
		tmpsum = (int) strtol(numbers_str, &ending, 10);
		if (tmpsum < 0) {
			fprintf(stdout, "negatives not allowed\n");
			exception = 1;
		}
		if (tmpsum > 1000) tmpsum -= 1000;
		sum += tmpsum;
		if ((length = is_delimiter(ending, starting_part_of_str)) > 0) numbers_str = ending + length; else break;
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

bool add_test_variable_length_multiple_delimiters() {
	if (add("//[abc][def]\n1,2,3abc4def5") == 15) return true;
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
	perform_test("Testing variable-length delimiter", add_test_variable_length_delimiter);
	perform_test("Testing variable-length multiple delimiters", add_test_variable_length_multiple_delimiters);
	return EXIT_SUCCESS;
}
