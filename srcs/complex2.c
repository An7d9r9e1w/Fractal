#include <my_complex.h>

t_complex	csubre(t_complex c, double re)
{
	c.re -= re;
	return (c);
}

t_complex	csub(t_complex c1, t_complex c2)
{
	c1.re -= c2.re;
	c1.im -= c2.im;
	return (c1);
}

t_complex	cadd(t_complex c1, t_complex c2)
{
	c1.re += c2.re;
	c1.im += c2.im;
	return (c1);
}
