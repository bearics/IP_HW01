#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>


int readFile(char* path, char** data, int sx, int sy)
{	
	// read file function

	FILE *fp;

	*data = (char*)malloc(sizeof(char)*sx*sy);	// allocate image data memory
	
	fp = fopen(path, "rb");

	if (fp != NULL)
	{	// succeed in opening file
		fread(*data, sizeof(char), sx*sy, fp);
		fclose(fp);
	}
	else
	{	// fail to open file
		printf("Cannot open file\n");
		return -1;
	}
	
	return 0;
}

int writeFile(char* path, char** data, int size)
{
	FILE *fp;

	fp = fopen(path, "rw");
	fwrite(*data, sizeof(char), size, fp);
	fclose(fp);
}

void displayRAW(char** in, int sx, int sy)
{
	for (int i = 0; i < sx; i++)
	{
		for (int j = 0; j < sy; j++)
		{
			printf("%d ", *(*in + i*sx + j));
		}
		printf("\n");
	}
}

void roatateRAW(int sx, int sy, unsigned int *st)
{

}

int main()
{
	int sx = 256, sy = 256;
	char* inData = NULL;
	char* outData = NULL;
		
	readFile("c:\\lena256.raw", &inData, sx, sy);
	displayRAW(&inData, sx, sy);

	free(inData);
	free(outData);

	while (1)
	{

	}

	return 0;
}