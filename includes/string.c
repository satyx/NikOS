#include <string.h>

size_t strlen(const char* str)
{
	size_t length = 0;
	while(str[length++]);
	return length;
}

void memset(void *ptr, int val, size_t n)
{
	unsigned char *c = ptr;
	size_t i = 0;
	while(i<n)
	{
		c[i] = val;
		i++;
	}
}

void memcpy(void *dest, void *source , size_t n)
{
	unsigned char *d = (unsigned char*)dest, *s = (unsigned char*)source;
	size_t i=0;
	while(i<n)
	{
		d[i] = s[i];
		i++;
	}
}