#include <windows.h>
#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	FILE* fp;
	RGBQUAD strPal[256];
	unsigned char* imagedata;
	char num[20] = { 0 };
	char picture[20] = { 0 };
	char picture_output[20] = { 0 };
	cout << "please input the picture number:" << endl;
	cin >> num;
	strcat_s(picture, sizeof(picture), num);
	strcat_s(picture, sizeof(picture), ".bmp");

	fopen_s(&fp, picture, "rb");//��ֻ����ʽ��bmpͼƬ
	if (fp == 0) {
		printf("can't open the bmp file");
		exit(0);
	}
	if (fp)
	{
		BITMAPFILEHEADER filehead;//�����ļ�ͷ����Ϣͷ
		BITMAPINFOHEADER infohead;
		//��ͼƬ���ļ�ͷ����Ϣͷ���ηŽ������Ľṹ����
		fread(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//size_t fread(void* restrict buffer, size_t size, size_t count, FILE * restrict stream);//C99��
		fread(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);//�Ӹ���������stream��ȡ���count����������buffer��

		//��ͼƬ256�����ض�Ӧ�ĵ�ɫ������strPal�ṹ��������
		fread(&strPal, sizeof(RGBQUAD), 256, fp);
		//����һ����̬����imagedata���ڴ��ͼ������
		int height = infohead.biHeight;
		int width = infohead.biWidth;
		int MN = height * width * sizeof(BYTE);
		imagedata = new unsigned char[MN];

		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				imagedata[width * i + j] = 0;
			}
		}

		//�����ݶ���imagedata������
		fread(imagedata, MN, 1, fp);//�ܷ�ĳ�ֻ��һ���أ�
		fclose(fp);
		strcat_s(picture_output, sizeof(picture_output), num);
		strcat_s(picture_output, sizeof(picture_output), "_output.bmp");
		fopen_s(&fp, picture_output, "wb");
		if (fp == 0) {
			printf("can't open the bmp file");
			exit(0);
		}
		if (fp)
		{
			fwrite(&filehead, sizeof(BITMAPFILEHEADER), 1, fp);//size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream)
			fwrite(&infohead, sizeof(BITMAPINFOHEADER), 1, fp);//��ptr��ָ��������е�����д�뵽������stream��

			//�޸ĵ�ɫ��ģ�飬ʹRGB�����������
			for (unsigned int num_str = 0; num_str < 256; num_str++) {
				fwrite(&strPal[num_str].rgbBlue, sizeof(BYTE), 1, fp);
				fwrite(&strPal[num_str].rgbBlue, sizeof(BYTE), 1, fp);
				fwrite(&strPal[num_str].rgbBlue, sizeof(BYTE), 1, fp);
				fwrite(&strPal[num_str].rgbReserved, sizeof(BYTE), 1, fp);
			}

			//д��ͼ������
			fwrite(imagedata, MN, 1, fp);

			fclose(fp);
			printf("\n\n==================================\n");
			printf("Gray level transformation finished\n");
			printf("==================================\n\n");
			return 0;
		}
	}
}