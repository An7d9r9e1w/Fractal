#ifndef FRACTOL_H
# define FRACTOL_H

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# define WIDTH 1000
# define HEIGHT 1000
# define GRAD_LEN 1000

typedef struct s_data
{
	void			*mlx;
	void			*win;

	double			x_max;
	double			x_min;
	double			y_max;
	double			y_min;

	unsigned int	grad[GRAD_LEN];

	void			*img;
	char			*addr;
	int				bpp;
	int				line_length;
	int				endian;

	double			cx;
	double			cy;
	int				fg;
	int				deep;
}	t_data;

/*
 *	events
 */
int		destory_event(t_data *vars);
int		press_event(int keycode, t_data *vars);
int		click_event(int	button, int x, int y, t_data *vars);
void	terminate(t_data *vars);

/*
 *	initializations
 */
int		str_cmp(const char *s1, const char *s2);
void	init_grad(t_data *vars);
void	init_vars(t_data *vars);

/*
 *	render
 */
void	draw_pixel(t_data *vars, int x, int y, unsigned int color);
/*void	draw_line(t_data *vars, t_point p0, t_point p1, unsigned int color);*/
int		render(t_data *vars);

/*
 *	moves
 */
void	deep_change(t_data *vars, int direct);
void	move(double *max, double *min, int direct);
void	scale(t_data *vars, int x, int y, int direct);
void	complex_change(t_data *vars, int part, int direct);

/*
 *	fractals
 */
void	mandelbrot_or_julia_set(t_data *vars);
void	newton(t_data *vars);
#endif	/*FRACTOL_H*/
