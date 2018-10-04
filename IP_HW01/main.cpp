#define _CRT_SECURE_NO_DEPRECATE


#include <stdio.h>
#include <iostream>

using namespace std;


unsigned char** readFile(string path, int sx, int sy)
{
	// read file function

	FILE* fp;

	unsigned char** data = NULL;

	data = new unsigned char*[sy];

	for (int i = 0; i < sy; i++)
	{
		data[i] = new unsigned char[sx];
	}

	fp = fopen(path.c_str(), "rb");

	if (fp != NULL)
	{	// succeed in opening file
		for (int i = 0; i < sy; i++)
		{
			fread(data[i], sizeof(unsigned char), sx, fp);
		}
		fclose(fp);
	}
	else
	{	// fail to open file
		printf("Cannot open file\n");
		return NULL;
	}

	return data;
}

int writeFile(string path, unsigned char** data, int sx, int sy)
{
	FILE* fp;
	fp = fopen(path.c_str(), "w+");

	for (int i = 0; i < sy; i++)
	{
		fwrite(data[i], sizeof(unsigned char), sx, fp);
	}
	fclose(fp);

	return 0;
}

void displayRAW(unsigned char** in, int sx, int sy)
{
	for (int i = 0; i < sx; i++)
	{
		for (int j = 0; j < sy; j++)
		{
			printf("%d ", *(*in + i * sx + j));
		}
		printf("\n");
	}
}

int main(void)
{
	unsigned char **data = NULL;

	data = readFile("c:\\lena256.raw",256, 256);
	//displayRAW(data, 256, 256);
	writeFile("C:\\lena256_o.raw", data, 256, 256);
	

	return 0;
}

