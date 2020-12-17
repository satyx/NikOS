#include <stdio.h>
void putchar(const char c)
{
	monitor_write(c);
}

size_t print_num(int32_t num)
{
	char digits[10];
	int i = -1;
	bool sign = 0;
	if(num<0){
		sign = 1;
		num = num*(-1);
	}
	
	
	while(num>0)
	{
		i++;
		digits[i] = '0'+num%10;
		num = num/10;
	}
	if(sign)
		putchar('-');
	size_t n_digits = i+1;
	while(i>=0)
	{
		putchar(digits[i]);
		i--;
	}
	return n_digits+sign;
}

int printf(const char *inp,...)
{
	va_list parameters;
	va_start(parameters, inp);
	
	size_t i=0;
	size_t char_count = 0;
	while(inp[i])
	{
		if(inp[i]!='%'){
			putchar(inp[i]);
		}
		else
		{
			if(inp[i+1]=='d'||inp[i+1]=='l')
			{
				int num = va_arg(parameters, int);
				char_count += print_num(num);
			}
			else if(inp[i+1]=='c')
			{
				char c = (char)va_arg(parameters, int /* char promotes to int */);
				putchar(c);
			}
			else if(inp[i+1]=='s')
			{
				const char* c = va_arg(parameters, const char*);
				char_count += printf(c);
			}
			i++;
			char_count-=2;
		}
		i++;
	}
	va_end(parameters);
	char_count += i;
	return char_count;
}