#include<iostream>
#include <windows.h>
#include <fstream>
#include "Read.h"
#include "Write.h"

using namespace std;


int main()
{
	unsigned char* fxs1;
	unsigned char* fxs2;
	float nk[256] = { 0 };
	int sum[256] = { 0 };
	char num[20] = { 0 };
	char picture[20] = { 0 };
	char picture_output[20] = { 0 };
	int i, j, k, m, sk=0;

	//��ԭʼ�ļ�
	cout << "please input the picture number:" << endl;
	cin >> num;
	strcat_s(picture, sizeof(picture), num);
	strcat_s(picture, sizeof(picture), ".bmp");
	//��ȡ��Ϊstr���ַ������ļ������������ظ�ͼƬ����������
	fxs1=read(picture);

	//�½��ļ�	
	FILE* f2;
	strcat_s(picture_output, sizeof(picture_output), num);
	strcat_s(picture_output, sizeof(picture_output), "_output.bmp");
	fopen_s(&f2, picture_output, "wb");
	if (f2 == 0)
	{
		cout << "unable to create the bmp file!" << endl;
	}
	if (f2)
	{
		//����ͼ����������ȫ��д���ļ�(��ɫ��r=g=b��ʾ�Ҷ�ͼ)�������ļ�ָ��ͣ����ͼ�����ݿ�ͷ
		write(f2);
		//ԭʼͼƬ����ֵ������ļ�����nk
		ofstream outfile("origin_pix.txt", ios::out | ios::trunc);
		for (int i = 0; i < MN; i++)
		{
			m = fxs1[i];
			outfile << m << ",";//��ÿ�����ص������ֵ�Զ��Ÿ�����������txt�ļ���
			if ((i + 1) % 10 == 0)//�����ʽΪÿ����ʾ10�����ص��ֵ
				outfile << endl;

			for (int j = 0; j < 256; j++)//����δ���⻯��ֱ��ͼ���У�ͳ��ͼƬ�����е����ص��ڸ����Ҷȼ��ĸ�����
			{
				if (m==j)
				{
					nk[j]++;
					break;
				}
			}
		}
		cout << "\n\nԭʼͼƬ������������ļ�\n" << endl;

		//���⻯
		fxs2 = new unsigned char[MN];
		for (int k = 0; k < 256; k++)
		{
			for (j = 0; j <= k; j++)
				sum[k] = sum[k] + nk[j];//�����ۻ��ֲ�����
		}
		for (i = 0; i < MN; i++)
		{
			for (j = 0; j < 256; j++)
				if (fxs1[i]==j)
				{
					sk = (int)(255 *sum[j]/MN);//��ʽ������255����Ϊ����ֵ����0-255����ģ�0-1�޷���ʾ
					break;
				}
			sk >= 255 ?255: sk;
			sk <= 0 ? 0 : sk;
			fxs2[i] = sk;//�����⻯�������ֵ���������ļ���ͼ��������
		}

		//���⻯������������ļ�
		ofstream outfile2("output_pix.txt", ios::out | ios::trunc);
		for (int i = 0; i < MN; i++)          //��255,255,255��
		{
			m = fxs1[i];
			outfile2 << m << ",";
			if ((i + 1) % 10 == 0)
				outfile2 << endl;
		}
		cout << "\n���⻯��ͼƬ������������ļ�\n" << endl;

		fwrite(fxs2, MN, 1, f2);
		fclose(f2);
	}
}