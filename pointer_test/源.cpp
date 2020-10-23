#include <stdio.h>

//(1)数组名的内涵在于其指代实体是一种数据结构，这种数据结构就是数组；

//(2)数组名的外延在于其可以转换为指向其指代实体的指针，而且是一个指针常量；
 
//(3)指向数组的指针则是另外一种变量类型（在WIN32平台下，长度为4），仅仅意味着数组的存放地址！

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