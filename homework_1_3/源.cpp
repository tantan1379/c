#include <Windows.h>
#include <iostream>

typedef struct tagIMAGEDATA
{
	BYTE blue;///8λ�Ҷ�ͼ������1��
	//BYTE green;
	//BYTE red;
}IMAGEDATA;

using namespace std;
int main()
{
	char num[20] = { 0 };
	char picture[20] = { 0 };
	char picture_output_1[20] = { 0 };
	char picture_output_2[20] = { 0 };
	cout << "please input the picture number:" << endl;
	cin >> num;

	strcat_s(picture, sizeof(picture), num);
	strcat_s(picture, sizeof(picture), ".bmp");
	FILE* fp;
	RGBQUAD strPla[256];//256ɫ��ɫ��

	fopen_s(&fp, picture, "rb");
	if (fp == 0) {
		printf("�ļ���ʧ�ܣ�\n");
	}
	BITMAPFILEHEADER fileHead;//����λͼ�ļ�ͷ�ṹ
	fread(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	fseek(fp, sizeof(BITMAPFILEHEADER), 0);//����λͼ�ļ�ͷ�ṹ
	BITMAPINFOHEADER infoHead;//����λͼ��Ϣͷ�ṹ
	fread(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	cout << "ͼ��߶�Ϊ:" << infoHead.biHeight << endl;
	cout << "ͼ����Ϊ:" << infoHead.biWidth << endl;



	fread(strPla, sizeof(RGBQUAD), 256, fp);

	IMAGEDATA* imagedata = NULL; //��̬����洢ԭͼƬ��������Ϣ�Ķ�ά����
	IMAGEDATA* imagedataReverse = NULL;//��̬����洢�ü����ͼƬ��������Ϣ�Ķ�ά����
	IMAGEDATA* imagedataScal = NULL;

	int height, width;
	height = infoHead.biHeight;
	width = infoHead.biWidth;
	imagedata = (IMAGEDATA*)malloc(height * width * sizeof(IMAGEDATA));//Ϊԭʼͼ������ڴ�ռ�
	imagedataReverse = (IMAGEDATA*)malloc(height * width * sizeof(IMAGEDATA));//Ϊԭʼͼ������ڴ�ռ�

	//��ʼ��ԭʼͼƬ����������
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			(*(imagedata + i * width + j)).blue = 0;
		}
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			(*(imagedataReverse + i * width + j)).blue = 0;
		}
	}

	//����ͼƬ���������ݣ���ȡʱһ��һ�У����߶�������
	fread(imagedata, sizeof(struct tagIMAGEDATA) * width, height, fp);
	fclose(fp);

	//ͼƬ����
	float ExpScalValue; int ZoomToWidth; int ZoomToHeight;
	cout << "\n������Ҫ���ŵı���" << endl;
	cin >> ExpScalValue;

	ZoomToHeight = (int)(ExpScalValue * height);
	ZoomToWidth = (int)(ExpScalValue * width);
	ZoomToWidth = (ZoomToWidth * sizeof(IMAGEDATA) + 3) / 4 * 4;

	cout << "���ź�ͼ��߶�Ϊ: " << ZoomToHeight << endl;
	cout << "���ź�ͼ����Ϊ: " << ZoomToWidth << endl;


	imagedataScal = (IMAGEDATA*)malloc(sizeof(IMAGEDATA) * ZoomToHeight * ZoomToWidth);
	//��ʼ�����ź����������
	for (int i = 0; i < ZoomToHeight; i++) {
		for (int j = 0; j < ZoomToWidth; j++) {
			(*(imagedataScal + ZoomToWidth * i + j)).blue = 0;
		}
	}

	int pre_i, pre_j, after_i, after_j;
	for (int i = 0; i < ZoomToHeight; i++) {
		for (int j = 0; j < ZoomToWidth; j++) {
			after_i = i;
			after_j = j;
			pre_i = (int)(after_i / ExpScalValue);
			pre_j = (int)(after_j / ExpScalValue);
			if (pre_i <= height && pre_i >= 0 && pre_j <= width && pre_j >= 0) {
				*(imagedataScal + ZoomToWidth * i + j) = *(imagedata + width * pre_i + pre_j);
			}
		}
	}
	//����bmpͼƬ
	strcat_s(picture_output_1, sizeof(picture_output_1), num);
	strcat_s(picture_output_1, sizeof(picture_output_1), "_zoom.bmp");
	if (fopen_s(&fp, picture_output_1, "wb") != 0) {
		cout << "�ļ�����ʧ�ܴ��룺" << GetLastError();
		cout << "create the bmp file error!" << endl;
		return NULL;
	}
	BITMAPFILEHEADER zoomfileheader;
	BITMAPINFOHEADER zoominfoheader;
	zoomfileheader = fileHead;
	zoomfileheader.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 1024 + ZoomToHeight * ZoomToWidth;
	fwrite(&zoomfileheader, sizeof(BITMAPFILEHEADER), 1, fp);
	zoominfoheader = infoHead;
	zoominfoheader.biHeight = ZoomToHeight;
	zoominfoheader.biWidth = ZoomToWidth;
	fwrite(&zoominfoheader, sizeof(BITMAPINFOHEADER), 1, fp);

	fwrite(strPla, sizeof(RGBQUAD), 256, fp);

	for (int i = 0; i < ZoomToHeight; i++) {
		for (int j = 0; j < ZoomToWidth; j++) {
			fwrite(&((*(imagedataScal + i * ZoomToWidth + j)).blue), sizeof(BYTE), 1, fp);
		}
	}
	printf("\n\n�������\n");
	fclose(fp);

	strcat_s(picture_output_2, sizeof(picture_output_2), num);
	strcat_s(picture_output_2, sizeof(picture_output_2), "_reverse.bmp");
	if (fopen_s(&fp, picture_output_2, "wb") != 0) {
		cout << "�ļ�����ʧ�ܴ��룺" << GetLastError();
		cout << "create the bmp file error!" << endl;
		return NULL;
	}

	fwrite(&fileHead, sizeof(BITMAPFILEHEADER), 1, fp);
	fwrite(&infoHead, sizeof(BITMAPINFOHEADER), 1, fp);
	fwrite(strPla, sizeof(RGBQUAD), 256, fp);


	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			(*(imagedataReverse + width * i + j)).blue = 255 - (*(imagedata + width * i + j)).blue;
		}
	}

	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			fwrite(&((*(imagedataReverse + i * width + j)).blue), sizeof(BYTE), 1, fp);
		}
	}
	printf("\n\n�������\n");
	fclose(fp);
}
