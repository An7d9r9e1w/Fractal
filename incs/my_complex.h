#ifndef MY_COMPLEX_H
# define MY_COMPLEX_H

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_complex
{
	double	re;
	double	im;
}	t_complex;

double		cxabs(t_complex c);
t_complex	cpow2(t_complex c);
t_complex	cpow3(t_complex c);
t_complex	cdiv(t_complex c1, t_complex c2);
t_complex	cmult(t_complex c, double m);
t_complex	csubre(t_complex c, double re);
t_complex	csub(t_complex c1, t_complex c2);
t_complex	cadd(t_complex c1, t_complex c2);
#endif	/*MY_COMPLEX_H*/
