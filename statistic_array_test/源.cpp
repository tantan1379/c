#include <stdio.h>
#include <windows.h>

/*
Note:
ָ������ĵ�ַ����&(*p)������&p,��Ϊp�ͽ�ָ�����
*/

void dynamic(int n)
{
	int* a= NULL; //ָ��=NULL��ʾa��ָ���κ��ڴ�ռ�
	a = (int*)malloc(sizeof(int) * n); //����һ����СΪ4*10���ڴ�ռ䣬malloc�������ؿ��ٿռ���׵�ַ����ת��Ϊint*�ͣ�aָ������ռ�
	for (int i = 0; i < n; i++) {
		a[i] = i; 
		printf("%d", a[i]);
	}
}

int main()
{
	dynamic(10);
	return 0;
}