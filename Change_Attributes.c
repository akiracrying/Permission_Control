#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>

#define CHANGE_FILE "Check.txt"
#define FOREVER() for(;;)

int main()
{
	enum
	{
		ADD = 1,
		READ,
		CHANGE_1,
		CHANGE_2,
		CHANGE_3,
		CHANGE_4
	};

	FILE* first = NULL;
	int operation = 0;
	char lol[50];
	memset(lol, 0, 50);

	wchar_t wtext[100];
	mbstowcs(wtext, CHANGE_FILE, strlen(CHANGE_FILE) + 1);

	SetFileAttributes(wtext, FILE_ATTRIBUTE_NORMAL);
	if ((first = fopen(CHANGE_FILE, "w+")) == NULL)
		exit(1);

	FOREVER()
	{
		fprintf(stdout, "1 - Add information\n2 - Read information\n3 - Read only\n4 - Hide\n5 - Default\n");
		fprintf(stdout, "6 - Read only + Hidden\n7 - Exit\n\n");
		if (fscanf(stdin, "%d", &operation) != 1 || operation < 1 || operation > 7)
		{
			fprintf(stdout, "Invalid input!\n");
			return EXIT_FAILURE;
		}
		switch (operation)
		{
		case ADD:
			fprintf(first, "New");
			fprintf(stdout, "File changed!\n");
			break;
		case READ:
			fseek(first, 0, SEEK_SET);
			fread(lol, 1, 50, first);
			fprintf(stdout, "File has been read. Content:\n%s\n", lol);
			break;
		case CHANGE_1:
			if (SetFileAttributes(wtext, FILE_ATTRIBUTE_READONLY) == 0)
			{
				fprintf(stdout, "Error!\n");
				return EXIT_FAILURE;
			}
			fprintf(stdout, "Attributes was changed\n");
			break;
		case CHANGE_2:
			if (SetFileAttributes(wtext, FILE_ATTRIBUTE_HIDDEN) == 0)
			{
				fprintf(stdout, "Error!\n");
				return EXIT_FAILURE;
			}
			fprintf(stdout, "Attributes was changed\n");
			break;
		case CHANGE_3:
			if (SetFileAttributes(wtext, FILE_ATTRIBUTE_NORMAL) == 0)
			{
				fprintf(stdout, "Error!\n");
				return EXIT_FAILURE;
			}
			fprintf(stdout, "Attributes was changed\n");
			break;
		case CHANGE_4:
			if (SetFileAttributes(wtext, FILE_ATTRIBUTE_HIDDEN | FILE_ATTRIBUTE_READONLY) == 0)
			{
				fprintf(stdout, "Error!\n");
				return EXIT_FAILURE;
			}
			fprintf(stdout, "Attributes was changed\n");
			break;
		default:
			return EXIT_SUCCESS;
		}
	}

	return EXIT_SUCCESS;
}
