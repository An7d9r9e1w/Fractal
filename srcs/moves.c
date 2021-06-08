#include <fractol.h>

void	deep_change(t_data *vars, int direct)
{
	int	delta;

	delta = vars->deep / 10;
	if (!delta)
		delta = 1;
	if (direct < 0)
	{
		vars->deep -= delta;
		if (vars->deep < 1)
			vars->deep = 1;
	}
	else
	{
		vars->deep += delta;
		if (vars->deep > GRAD_LEN)
			vars->deep = GRAD_LEN;
	}
}

void	move(double *max, double *min, int direct)
{
	double	delta;

	delta = (*max - *min) / 30;
	if (direct < 0)
		delta = -delta;
	*max += delta;
	*min += delta;
}

void	scale(t_data *vars, int x, int y, int direct)
{
	double	mx;
	double	my;
	double	dfx;
	double	dfy;

	mx = (double)x / WIDTH;
	my = (double)y / HEIGHT;
	dfx = (vars->x_max - vars->x_min) * -0.2;
	dfy = (vars->y_max - vars->y_min) * -0.2;
	if (direct < 0)
	{
		vars->x_max -= dfx * (1 - mx);
		vars->x_min += dfx * mx;
		vars->y_max -= dfy * (1 - my);
		vars->y_min += dfy * my;
	}
	else
	{
		vars->x_max += dfx * (1 - mx);
		vars->x_min -= dfx * mx;
		vars->y_max += dfy * (1 - my);
		vars->y_min -= dfy * my;
	}
}

void	complex_change(t_data *vars, int part, int direct)
{
	double	d;

	if (direct < 0)
		d = 0.05;
	else
		d = -0.05;
	if (part)
		vars->cy += d;
	else
		vars->cx += d;
}
