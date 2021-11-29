#include <stdio.h>

int main() {
	FILE *fp;
	char fileToRead[] = "index.html";
	char buf[1025];
	int n;

	fp = fopen( fileToRead, "r" );
	if (fp == NULL) {
		printf("File %s not found.\n", fileToRead); return 1;
	}
	do {
		n = fread( buf, 1, 1024, fp );
		printf("%s", buf);
	} while (n > 0);

	fclose(fp);
	return 0;
}
