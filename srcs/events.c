#include <fractol.h>

static int	close(t_data *vars)
{
	if (vars->img)
		mlx_destroy_image(vars->mlx, vars->img);
	if (vars->win)
		mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

int	destory_event(t_data *vars)
{
	return (close(vars));
}

int	press_event(int keycode, t_data *vars)
{
	if (keycode == 53)
		close(vars);
	else if (keycode == 43)
		deep_change(vars, -1);
	else if (keycode == 47)
		deep_change(vars, 1);
	else if (keycode == 2)
	{
		vars->x_max = 2;
		vars->x_min = -2;
		vars->y_max = 2;
		vars->y_min = -2;
	}
	else if (keycode == 123 || keycode == 124)
		move(&vars->x_max, &vars->x_min, -(keycode == 123));
	else if (keycode == 125 || keycode == 126)
		move(&vars->y_max, &vars->y_min, -(keycode == 126));
	else if (keycode >= 6 || keycode <= 9)
		complex_change(vars, (keycode == 6 || keycode == 7),
			-(keycode == 6 || keycode == 8));
	render(vars);
	return (0);
}

int	click_event(int	button, int x, int y, t_data *vars)
{
	if (button == 4 || button == 5)
	{
		scale(vars, x, y, -(button == 4));
		render(vars);
	}
	return (0);
}

void	terminate(t_data *vars)
{
	perror(0);
	close(vars);
}
