#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

unsigned char isnum(char c) {
	return (c >= '0' && c <= '9');
}

int spelttonum(char * str) {
	const char * spelt[10] = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

	for (unsigned int i = 1; i < 10; ++i) {
		unsigned int len = strlen(spelt[i]);
		if (spelt[i][0] != str[0] || spelt[i][1] != str[1]) {
			continue;
		}
		
		if (strncmp(spelt[i], str, len) == 0) {
			return i;
		}
	}

	return -1;
}

char numtochr(unsigned int num) {
	char nums[10] = "0123456789";
	return nums[num];
}

int main() {
	char * buffer = NULL;
	unsigned long long int len = 0;

	{
		FILE * fp = fopen("1.txt", "rb");
		if (fp == NULL) {
			return 1;
		}

		fseek(fp, 0L, SEEK_END);
		len = ftell(fp);
		fseek(fp, 0L, SEEK_SET);

		buffer = malloc(len + 1);
		if (buffer == NULL) {
			fclose(fp);
			return 2;
		}
		buffer[len] = '\0';

		if (fread(buffer, 1, len, fp) != len) {
			fclose(fp);
			return 3;
		}

		fclose(fp);
	}

	unsigned long long int accumulator = 0;

	char cbuf[3] = { '\0', '\0', '\0' };
	unsigned long long int first = 0;
	long long int last = -1;
	char lastchr = '\0';
	unsigned long long int spelt = 0;
	unsigned long long int line = 1;
	unsigned long long int column = 1;
	for (unsigned long long int i = 0; i < len; ++i) {
		if (buffer[i] == '\n') {
			cbuf[1] = lastchr;
			last = -1;

			unsigned long long int num = strtoull(cbuf, NULL, 10);
			printf("(line %llu : column %llu) num: %llu\n", line, column, num);
			accumulator += num;

			memset(cbuf, 0, 2);

			++line;
			column = 1;
			continue;
		}

		if (isnum(buffer[i])) {
			if (last == -1) {
				cbuf[0] = buffer[i];
				first = i;
			}
			lastchr = buffer[i];
			last = i;
		} else {
			int num = spelttonum(&buffer[i]);
			if (num != -1) {
				if (last == -1) {
					cbuf[0] = numtochr(num);
					first = i;
				}
				last = i;
				const char nums[10] = "0123456789";
				lastchr = nums[num];
			}
		}
		++column;
	}

	printf("%llu\n", accumulator);
}
