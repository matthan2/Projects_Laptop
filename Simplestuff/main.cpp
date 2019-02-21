// Example program
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <stdio.h>
#include <cstdlib>
using namespace std;

struct mm_game
{
	bool game_active;
};

struct mm_game *party;

static mm_game *find_game()
{
	party = (mm_game*)malloc(sizeof(mm_game));
	party->game_active = true;
	return par
}



size_t foo_min(size_t count, size_t other)
{
	size_t min;
	min = (count <= other) ? count : other;
	return min;

}



int main()
{
	char status[15];
	char str1[15];
	char str2[15];
	char wait;
	int retval;
	int num = 0012;
	void *cookie;

	int target_code[4];
	char buff[4] = { 's','0','0','1' };
	char tarbuff[4];
	char *eight;
	
	cookie = &buff;

	char *tar;
	tar = (char*)cookie;
	
	struct mm_game *temp = find_game();
	
	if (temp->game_active == true)
	{
		printf("this is true\n");
	}

	memset(tarbuff, '0', 4);
	//printf("%i", sizeof(buff));
	printf("%c",tar[0]);
	printf("%c", tar[1]);
	//printf("%c", buff[1]);
	strncpy(tarbuff, (char*)cookie, 4);
/*
	if (!isdigit(tarbuff[0]))
	{
		printf("this is not a digit\n");
	}
	

	printf("%i", sizeof(cookie));
	printf("%c%c%c%c\n", tarbuff[0], tarbuff[1], tarbuff[2], tarbuff[3]);

	for (size_t i = 0; i < 4; i++)
	{
		target_code[i] = tarbuff[i] - 48;
		printf("%i", target_code[i]);
	}
	*/

	getchar();
}