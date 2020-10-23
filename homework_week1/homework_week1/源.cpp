#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <windows.h>
#include <fstream>

using namespace std;


typedef struct
{
	BITMAPFILEHEADER file;
	BITMAPINFOHEADER info;
}bmp;

void showFileHeader(BITMAPFILEHEADER fh);
void showInfoHeader(BITMAPINFOHEADER ih);

int main()
{
	char num[20] = { 0 };
	char picture[20] = { 0 };
	FILE* fp;
	cout << "please input the picture number:" << endl;
	cin >> num;
	strcat_s(picture, sizeof(picture), num);
	strcat_s(picture, sizeof(picture), ".bmp");
	fopen_s(&fp, picture, "rb");
	if (fp == 0)
	{
		printf("can't open the bmp image.\n ");
		exit(0);
	}
	BITMAPFILEHEADER fileheader;
	BITMAPINFOHEADER infoheader;
	fread(&fileheader, sizeof(BITMAPFILEHEADER), 1, fp);
	fread(&infoheader, sizeof(BITMAPINFOHEADER), 1, fp);
	showFileHeader(fileheader);
	showInfoHeader(infoheader);
	//bmp m;
	//m = readbmpfile();
	//printf("%d", sizeof(unsigned short int));

	return 0;
}

void showFileHeader(BITMAPFILEHEADER fh)
{
	ofstream outfile("fileheader.txt", ios::out | ios::trunc);
	cout << "--------" << endl;
	cout << "λͼ�ļ�ͷ��" << endl;
	outfile << "λͼ�ļ�ͷ��" << endl;
	cout << "�ļ����ͣ�" << fh.bfType << endl;
	outfile << "�ļ����ͣ�" << fh.bfType << endl;
	cout << "�ļ���С:" << fh.bfSize << endl;
	outfile << "�ļ���С:" << fh.bfSize << endl;
	cout << "������_1:" << fh.bfReserved1 << endl;
	outfile << "������_1:" << fh.bfReserved1 << endl;
	cout << "������_2:" << fh.bfReserved2 << endl;
	outfile << "������_2:" << fh.bfReserved2 << endl;
	cout << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << fh.bfOffBits << endl;
	outfile << "ʵ��λͼ���ݵ�ƫ���ֽ���:" << fh.bfOffBits << endl;
}

void showInfoHeader(BITMAPINFOHEADER ih)
{
	ofstream outfile("infoheader.txt", ios::out | ios::trunc);
	cout << "--------" << endl;
	cout << "λͼ��Ϣͷ:" << endl;
	outfile << "λͼ��Ϣͷ:" << endl;
	cout << "ͼƬ��ȣ����أ�:" << ih.biWidth << endl;
	outfile << "ͼƬ��ȣ����أ�:" << ih.biWidth << endl;
	cout << "ͼƬ�߶ȣ����أ�:" << ih.biHeight << endl;
	outfile << "ͼƬ�߶ȣ����أ�:" << ih.biHeight << endl;
	cout << "��ɫλ��:" << ih.biBitCount << endl;
	outfile << "��ɫλ��:" << ih.biBitCount << endl;
	cout << "ʵ��λͼ����ռ�õ��ֽ���:" << ih.biSizeImage << endl;
	outfile << "ʵ��λͼ����ռ�õ��ֽ���:" << ih.biSizeImage << endl;
	cout << "ʵ��ʹ�õ���ɫ��:" << ih.biClrUsed << endl; //����0ʱ��ʾ��2^biBitCount����ɫ������
	outfile << "ʵ��ʹ�õ���ɫ��:" << ih.biClrUsed << endl;
	cout << "��Ҫ����ɫ��:" << ih.biClrImportant << endl;
	outfile << "��Ҫ����ɫ��:" << ih.biClrImportant << endl;
}
//bmp readbmpfile()
//{
//	bmp m;
//	FILE* fp;
//	if ((fp=fopen("1.bmp","rb")) ==NULL)
//	{
//		printf("can't open the bmp image.\n ");
//		exit(0);
//	}
//
//	else
//	{
//		fread(&m.file.bfType, sizeof(m.file.bfType),1, fp);
//		printf("����Ϊ%s\n", m.file.bfType);
//		/*fread(&m.file.bfType, sizeof(char), 1, fp);
//		printf("%c\n",m.file.bfType);*/
//		fread(&m.file.bfSize, sizeof(long), 1, fp);
//		printf("�ļ�����Ϊ%d\n", m.file.bfSize);
//		fread(&m.file.bfReserverd1, sizeof(short int), 1, fp);
//		printf("������1Ϊ%d\n", m.file.bfReserverd1);
//		fread(&m.file.bfReserverd2, sizeof(short int), 1, fp);
//		printf("������2Ϊ%d\n", m.file.bfReserverd2);
//		fread(&m.file.bfOffBits, sizeof(long), 1, fp);
//		printf("ƫ����Ϊ%d\n", m.file.bfOffBits);
//		fread(&m.info.biSize, sizeof(long), 1, fp);
//		printf("�˽ṹ��СΪ%d\n", m.info.biSize);
//		fread(&m.info.biWidth, sizeof(long), 1, fp);
//		printf("λͼ�Ŀ��Ϊ%d\n", m.info.biWidth);
//		fread(&m.info.biHeight, sizeof(long), 1, fp);
//		printf("λͼ�ĸ߶�Ϊ%d\n", m.info.biHeight);
//		fread(&m.info.biPlanes, sizeof(short), 1, fp);
//		printf("Ŀ���豸λͼ��%d\n", m.info.biPlanes);
//		fread(&m.info.biBitcount, sizeof(short), 1, fp);
//		printf("��ɫ���Ϊ%d\n", m.info.biBitcount);
//		fread(&m.info.biCompression, sizeof(long), 1, fp);
//		printf("λͼѹ������%d\n", m.info.biCompression);
//		fread(&m.info.biSizeImage, sizeof(long), 1, fp);
//		printf("λͼ��С%d\n", m.info.biSizeImage);
//		fread(&m.info.biXPelsPermeter, sizeof(long), 1, fp);
//		printf("λͼˮƽ�ֱ���Ϊ%d\n", m.info.biXPelsPermeter);
//		fread(&m.info.biYPelsPermeter, sizeof(long), 1, fp);
//		printf("λͼ��ֱ�ֱ���Ϊ%d\n", m.info.biYPelsPermeter);
//		fread(&m.info.biClrUsed, sizeof(long), 1, fp);
//		printf("λͼʵ��ʹ����ɫ��%d\n", m.info.biClrUsed);
//		fread(&m.info.biClrImportant, sizeof(long), 1, fp);
//		printf("λͼ��ʾ�бȽ���Ҫ��ɫ��%d\n", m.info.biClrImportant);
//	}
//	return m;
//}