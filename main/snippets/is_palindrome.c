#include <cstring>

bool is_palindrome(const char *str)
{
	const char *front = str;
	const char *back  = str + strlen(str) - 1;

	while (front < back && *front == *back) {
		front++;
		back--;
	}

	return (front >= back);
}
