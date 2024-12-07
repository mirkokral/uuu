#pragma once
#include <stdint.h>
#include <stddef.h>

// A utility function to reverse a string
inline void reverse(char str[], int length)
{
	int start = 0;
	int end = length - 1;
	while (start < end)
	{
		char temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		end--;
		start++;
	}
}
// Implementation of citoa()
inline char *citoa(int num, char *str, int base)
{
	int i = 0;
	bool isNegative = false;

	/* Handle 0 explicitly, otherwise empty string is
	 * printed for 0 */
	if (num == 0)
	{
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled
	// only with base 10. Otherwise numbers are
	// considered unsigned.
	if (num < 0 && base == 10)
	{
		isNegative = true;
		num = -num;
	}

	// Process individual digits
	while (num != 0)
	{
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);

	return str;
}


inline size_t strlen(const char* str) 
{
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

inline char* strconcat(char* str1, char* str2) {
    int sl1 = strlen(str1);
    int sl2 = strlen(str2);
    
    int sl = sl1+sl2;
    char *buf = "                           ";
    for(int i = 0; i < sl1; i++) {
        buf[i] = str1[i];
    }
    for(int i = sl1; i < sl2; i++) {
        buf[i] = str2[i];
    }
    buf[sl] = '\0';
    return buf;

}