#include <stdio.h>
#include <stdlib.h>

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

		
	}
}
