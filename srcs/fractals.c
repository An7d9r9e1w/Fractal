#include <fractol.h>
#include <my_complex.h>

static unsigned int	get_itered_color(t_data *vars, double x0, double y0, int i)
{
	double	x;
	double	y;
	double	xx;
	double	yy;

	xx = x0 * x0;
	yy = y0 * y0;
	x = x0;
	y = y0;
	if (vars->fg)
	{
		x0 = vars->cx;
		y0 = vars->cy;
	}
	while (xx + yy <= 4 && ++i < vars->deep)
	{
		y = 2 * x * y + y0;
		x = xx - yy + x0;
		xx = x * x;
		yy = y * y;
	}
	if (i < vars->deep)
		return (vars->grad[(int)((double)i / vars->deep * GRAD_LEN)]);
	return (0);
}

void	mandelbrot_or_julia_set(t_data *vars)
{
	double	y0;
	double	c_x;
	double	c_y;
	int		row;
	int		col;

	c_x = (vars->x_max - vars->x_min) / (WIDTH - 1);
	c_y = (vars->y_max - vars->y_min) / (WIDTH - 1);
	row = -1;
	while (++row < HEIGHT)
	{
		y0 = vars->y_min + c_y * row;
		col = -1;
		while (++col < WIDTH)
			draw_pixel(vars, col, row, get_itered_color(vars,
					vars->x_min + c_x * col, y0, 0));
	}
}

void	draw_newton_pixel(t_data *vars, t_complex z, t_point coords,
	const t_complex *r)
{
	const double	tol = 0.0001;
	int				i;

	i = 0;
	while (i < vars->deep && cxabs(csub(z, r[0])) >= tol
		&& cxabs(csub(z, r[1])) >= tol && cxabs(csub(z, r[2])) >= tol)
	{
		if (cxabs(z) > 0)
			z = csub(z, cdiv(csubre(cpow3(z), 1.),
						cmult(cpow2(z), 3)));
		i++;
	}
	if (cxabs(csub(z, r[0])) < tol)
		draw_pixel(vars, coords.x, coords.y, (255 - i * 15) << 16);
	else if (cxabs(csub(z, r[1])) < tol)
		draw_pixel(vars, coords.x, coords.y, (255 - i * 15) << 8);
	else if (cxabs(csub(z, r[2])) < tol)
		draw_pixel(vars, coords.x, coords.y, 255 - i * 15);
}

void	newton(t_data *vars)
{
	const t_complex	r[4] = {{.re = 1, .im = 0},
		{.re = -0.5, .im = sin(2 * M_PI / 3)},
		{.re = -0.5, .im = -sin(2 * M_PI / 3)},
		{.re = (vars->x_max - vars->x_min) / (WIDTH - 1),
		.im = (vars->y_max - vars->y_min) / (WIDTH - 1)}};
	t_complex		z;
	t_point			coords;

	coords.y = -1;
	while (++coords.y < HEIGHT)
	{
		z.im = vars->y_min + r[3].im * coords.y;
		coords.x = -1;
		while (++coords.x < WIDTH)
		{
			z.re = vars->x_min + r[3].re * coords.x;
			draw_newton_pixel(vars, z, coords, r);
		}
	}
}
