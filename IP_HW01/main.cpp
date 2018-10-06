#define _CRT_SECURE_NO_DEPRECATE

#define PI 3.141592653589793238462643383279

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

unsigned char** memAllocate2D(int sx, int sy)
{
	unsigned char** data = NULL;

	data = new unsigned char*[sy];

	for (int i = 0; i < sy; i++)
	{
		data[i] = new unsigned char[sx];
	}

	return data;
}





unsigned char** readFile(string path, int sx, int sy)
{
	// read file function

	FILE* fp;

	unsigned char** data = memAllocate2D(sx, sy);

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


void rotateRAW(unsigned char** data, int sx, int sy, double degree)
{
	unsigned char** outData = memAllocate2D(sx, sy);

	int ori_x, ori_y;
	unsigned char pixel;
	double rad = degree * PI / 180.0;
	double cc = cos(rad), ss = sin(-rad);
	double xc = (double)sx / 2.0, yc = (double)sy / 2.0;	// x,y 's center

	for (int y = 0; y < sy; y++)
	{
		for (int x = 0; x < sx; x++)
		{
			ori_x = (int)(xc + ((double)y - yc) * ss + ((double)x - xc) * cc);
			ori_y = (int)(yc + ((double)y - yc) * cc - ((double)x - xc) * ss);
			pixel = (unsigned char)0;
			if (( (ori_y >= 0 && ori_y < sy) && (ori_x >= 0 && ori_x < sx) ))
				pixel = data[ori_y][ori_x];
			outData[y][x] = pixel;
		}
	}

	string path = "c:\\lena256_rotate_" + to_string((int)(degree)) + ".raw";

	writeFile(path, outData, (int)sx, (int)sy);
	cout << "finish to write file\n";

}

unsigned char bilinearInterpolation(unsigned char** data, int x, int y, int sx, int sy, double scale)
{
	unsigned char m[2][2];
	double ori_x = x / scale;
	double ori_y = y / scale;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			int py = floor(ori_y) + i < sy ? floor(ori_y) + i : floor(ori_y);
			int px = floor(ori_x) + j < sx ? floor(ori_x) + j : floor(ori_x);
			m[i][j] = data[py][px];
		}
	}

	double d1 = ori_x - floor(ori_x);
	double d2 = 1 - d1;
	double d3 = ori_y - floor(ori_y);
	double d4 = 1 - d3;

	return (unsigned char)(d4 * (d2 * (int)m[0][0] + d1 * (int)m[0][1]) + d3 * (d2 * (int)m[1][0] + d1 * (int)m[1][1]));
}

void scaleRAW(unsigned char** data, int sx, int sy, double scale)
{
	int new_sx = (int)sx*scale;
	int new_sy = (int)sy*scale;

	unsigned char** outData = memAllocate2D(new_sx, new_sy);

	for (int y = 0; y < new_sy; y++)
	{
		for (int x = 0; x < new_sx; x++)
		{
			outData[y][x] = bilinearInterpolation(data, x, y, sx, sy, scale);
		}
	}

	string path = "c:\\lena256_scaling_" + to_string((int)(sx*scale)) + ".raw";

	writeFile(path, outData, (int)sx*scale, (int)sy*scale);
	cout << "finish to write file\n";
}

int main(void)
{
	unsigned char **data = NULL;
	unsigned char **out_data = memAllocate2D(512, 512);

	data = readFile("c:\\lena256.raw", 256, 256);
	
	//scaleRAW(data, 256, 256, 436.0 / 256.0);
	rotateRAW(data, 256, 256, 30.0);

	return 0;
}
