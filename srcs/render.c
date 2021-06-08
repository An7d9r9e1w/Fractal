#include <fractol.h>
/*
static int	absi(int num)
{
	if (num < 0)
		return (-num);
	return (num);
}
*/
void	draw_pixel(t_data *vars, int x, int y, unsigned int color)
{
	*(unsigned int *)(vars->addr + y * vars->line_length
		+ x * (vars->bpp >> 3)) = color;
}
/*
static void	delta_point(double *err, int *point, int delta, int step)
{
	*err += delta;
	*point += step;
}

void	draw_line(t_data *vars, t_point p0, t_point p1, unsigned int color)
{
	t_point	delta;
	t_point	step;
	double	err;
	double	etmp;

	delta.x = absi(p1.x - p0.x);
	step.x = -(p1.x < p0.x) | 1;
	delta.y = -absi(p1.y - p0.y);
	step.y = -(p1.y < p0.y) | 1;
	err = delta.x + delta.y;
	while (1)
	{
		draw_pixel(vars, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break;
		etmp = 2 * err;
		if (etmp >= delta.y)
			delta_point(&err, &p0.x, delta.y, step.x);
		if (etmp <= delta.x)
			delta_point(&err, &p0.y, delta.x, step.y);
	}
}*/

int	render(t_data *vars)
{
	void	*tmp;

	tmp = vars->img;
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img)
	{
		mlx_destroy_image(vars->mlx, tmp);
		terminate(vars);
	}
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp,
			&vars->line_length, &vars->endian);
	if (vars->fg < 2)
		mandelbrot_or_julia_set(vars);
	else
		newton(vars);
	mlx_clear_window(vars->mlx, vars->win);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img, 0, 0);
	mlx_destroy_image(vars->mlx, tmp);
	return (0);
}
