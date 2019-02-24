#include <stdio.h>
#include <string.h>
int main(int argc, char * argv[])
{
	char *file_contents;
	long file_size;
	FILE *fp = fopen_s(&fp, "CMSC491.txt", "rb");
	fseek(fp, 0, SEEK_END);
	file_size = ftell(fp);

	rewind(fp);
	file_contents = malloc(file_size * (sizeof(char)));
	fread(file_contents, sizeof(char), file_size, fp);
	fclose(fp);
	
	return 0;
}