#include <fractol.h>

int	str_cmp(const char *s1, const char *s2)
{
	unsigned char	*c1;
	unsigned char	*c2;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	while (*c1 && *c1 == *c2)
	{
		c1++;
		c2++;
	}
	return (*c1 - *c2);
}

static int	fill_color_range(unsigned int *grad,
	const unsigned int *colors, float step)
{
	float	rgb[3];
	float	drgb[3];
	int		i;

	rgb[0] = (*(colors - 1) >> 16) & 255;
	rgb[1] = (*(colors - 1) >> 8) & 255;
	rgb[2] = *(colors - 1) & 255;
	drgb[0] = (((*colors >> 16) & 255) - rgb[0]) / step;
	drgb[1] = (((*colors >> 8) & 255) - rgb[1]) / step;
	drgb[2] = ((*colors & 255) - rgb[2]) / step;
	i = 0;
	while (i < (int)round(step))
	{
		rgb[0] += drgb[0];
		rgb[1] += drgb[1];
		rgb[2] += drgb[2];
		grad[i++] = ((int)rgb[0] << 16)
			| ((int)rgb[1] << 8) | (int)rgb[2];
	}
	return (i);
}

static void	get_grad(t_data *vars, const unsigned int *colors, const int len)
{
	float	step;
	float	range;
	int		i;
	int		j;

	range = GRAD_LEN / (len - 1);
	step = range;
	i = 0;
	j = 0;
	while (++i < len)
	{
		j += fill_color_range(vars->grad + j, colors + i, step);
		range += step;
	}
}

void	init_grad(t_data *vars)
{
	const unsigned int	colors[5] = {0, 0x00000080, 0x00ffffff,
		0x00ffb000, 0};

	get_grad(vars, colors, 5);
}

void	init_vars(t_data *vars)
{
	vars->win = 0;
	vars->img = 0;
	vars->mlx = mlx_init();
	if (!vars->mlx)
		terminate(vars);
	vars->win = mlx_new_window(vars->mlx, WIDTH, HEIGHT, "Mandelbrot set");
	if (!vars->win)
		terminate(vars);
	vars->img = mlx_new_image(vars->mlx, WIDTH, HEIGHT);
	if (!vars->img)
		terminate(vars);
	vars->addr = mlx_get_data_addr(vars->img, &vars->bpp,
			&vars->line_length, &vars->endian);
	init_grad(vars);
	vars->deep = 50;
	vars->x_max = 2.;
	vars->x_min = -2.;
	vars->y_max = 2.;
	vars->y_min = -2.;
	vars->cx = -0.8;
	vars->cy = 0.8;
	mlx_hook(vars->win, 2, 0, press_event, vars);
	mlx_mouse_hook(vars->win, click_event, vars);
	mlx_hook(vars->win, 17, 0, destory_event, vars);
}
