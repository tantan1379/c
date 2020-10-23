#pragma once
#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;

int bfType, bfSize, bfOffBits;;
int bmpWidth;//ͼ��Ŀ�
int bmpHeight;//ͼ��ĸ�
int biBitCount;//ͼ�����ͣ�ÿ����λ����3*8��
int MN;
int lineByte;  //ÿһ�е��ֽ�����4�ı�����
int biXPelsPerMeter, biYPelsPerMeter;//�ֱ���
unsigned char* fxs;//���ڴ�����ص�ָ��

unsigned char* read(const char* str)  //����Ϊstr��bmp�ļ�
{
	FILE* f1;
	fopen_s(&f1,str,"rb"); 
	if (f1 == 0)
	{
		cout << "unable to open the bmp file" << endl;
	}
	if (f1)
	{
		//��λͼ�ļ�ͷ
		BITMAPFILEHEADER head;
		fread(&head, sizeof(BITMAPFILEHEADER), 1, f1);      //(void *buffer, size_t size, size_t count, FILE *stream)
		bfType = head.bfType;
		bfSize = head.bfSize;
		bfOffBits = head.bfOffBits;
		cout << "�ļ�����:" << head.bfType << endl;
		cout << "�ļ���С:" << head.bfSize << endl;
		cout << "������:" << head.bfReserved1 << endl;
		cout << "������:" << head.bfReserved2 << endl;
		cout << "ƫ���ֽ���:" << head.bfOffBits << endl;   //14+40

		//��λͼ��Ϣͷ
		BITMAPINFOHEADER info;
		fread(&info, sizeof(BITMAPINFOHEADER), 1, f1);
		bmpWidth = info.biWidth;
		bmpHeight = info.biHeight;
		biBitCount = info.biBitCount;
		cout << "�ýṹ�ĳ���:" << info.biSize << endl;
		cout << "ͼ��Ŀ��:" << info.biWidth << endl;
		cout << "ͼ��ĸ߶�:" << info.biHeight << endl;
		cout << "ƽ����:" << info.biPlanes << endl;
		cout << "��ɫλ��:" << info.biBitCount << endl;
		cout << "ѹ������:" << info.biCompression << endl;
		cout << "ʵ��λͼ����ռ�õ��ֽ���:" << info.biSizeImage << endl;
		biXPelsPerMeter = info.biXPelsPerMeter;
		biYPelsPerMeter = info.biYPelsPerMeter;
		cout << "ˮƽ�ֱ���:" << info.biXPelsPerMeter << endl;
		cout << "��ֱ�ֱ���:" << info.biYPelsPerMeter << endl;
		cout << "ʵ��ʹ�õ���ɫ��:" << info.biClrUsed << endl;
		cout << "��Ҫ����ɫ��:" << info.biClrImportant << endl;
		lineByte = (bmpWidth * biBitCount / 8 + 3) / 4 * 4;
		MN = lineByte * bmpHeight;
		cout << "ͼƬ��С:" << MN << endl;
		fxs = new unsigned char[MN];

		//����ɫ��
		RGBQUAD colorTable[256];
		fread(colorTable, sizeof(RGBQUAD), 256, f1);

		//������
		fread(fxs, 1, MN, f1);
		fclose(f1);
	}
	return fxs;
}