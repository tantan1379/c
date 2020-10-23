#include <stdio.h>
#include <iostream>

using namespace std;

int main()
{
	unsigned char* c;
	int MN = 10;
	char a[256] = { 0 };
	c=new unsigned char [MN];
	for (int i = 0; i < MN; i++)
	{
		c[i] = i;
		printf("%d\n", c[i]);
	}
}