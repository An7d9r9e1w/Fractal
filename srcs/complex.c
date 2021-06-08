#include <my_complex.h>

double	cxabs(t_complex c)
{
	return (c.re * c.re + c.im * c.im);
}

t_complex	cpow2(t_complex c)
{
	t_complex	res;

	res.re = c.re * c.re - c.im * c.im;
	res.im = 2 *c.re * c.im;
	return (res);
}

t_complex	cpow3(t_complex c)
{
	t_complex	res;
	double		xx;
	double		yy;

	xx = c.re * c.re;
	yy = c.im * c.im;
	res.re = c.re * (xx - 3 * yy);
	res.im = c.im * (3 * xx - yy);
	return (res);
}

t_complex	cdiv(t_complex c1, t_complex c2)
{
	t_complex	res;
	double		xx;
	double		yy;

	xx = c2.re * c2.re;
	yy = c2.im * c2.im;
	res.re = (c1.re * c2.re + c1.im * c2.im) / (xx + yy);
	res.im = (c1.im * c2.re - c1.re * c2.im) / (xx + yy);
	return (res);
}

t_complex	cmult(t_complex c, double m)
{
	c.re *= m;
	c.im *= m;
	return (c);
}
