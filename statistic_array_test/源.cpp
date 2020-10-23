#include <stdio.h>
#include <windows.h>

/*
Note:
指针变量的地址不是&(*p)，而是&p,因为p就叫指针变量
*/

void dynamic(int n)
{
	int* a= NULL; //指针=NULL表示a不指向任何内存空间
	a = (int*)malloc(sizeof(int) * n); //开辟一个大小为4*10的内存空间，malloc函数返回开辟空间的首地址，并转换为int*型，a指向这个空间
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