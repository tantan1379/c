#include <stdio.h>

//(1)���������ں�������ָ��ʵ����һ�����ݽṹ���������ݽṹ�������飻

//(2)���������������������ת��Ϊָ����ָ��ʵ���ָ�룬������һ��ָ�볣����
 
//(3)ָ�������ָ����������һ�ֱ������ͣ���WIN32ƽ̨�£�����Ϊ4����������ζ������Ĵ�ŵ�ַ��

int main()
{
	int array[7] = {1,2,3,4,5,6,7};
	//printf("%p", &array[0]);
	//printf("%p", p);
	//printf("%d",sizeof(array));
//	for (p = &array[0]; p <= &(array[6]); p++)
//	{
//		printf("1:%d\n",*p);
//	}
//	p = array;
//	while (p <= &(array[6]))
//	{
//		printf("2:%d\n", *p);
//		p++;
//	}
	printf("%d\n", array);
	printf("%d\n", *array);
	printf("%d", &array);
}