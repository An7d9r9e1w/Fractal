#include <fractol.h>

int	print_tips(char *str)
{
	printf("%s: Must specify one of 'mandelbrot', 'julia', 'newton'\n", str);
	return (1);
}

int	main(int argc, char *argv[])
{
	t_data	vars;

	if (argc < 2)
		return (print_tips(argv[0]));
	if (!str_cmp(argv[1], "mandelbrot"))
		vars.fg = 0;
	else if (!str_cmp(argv[1], "julia"))
		vars.fg = 1;
	else if (!str_cmp(argv[1], "newton"))
		vars.fg = 2;
	else
		return (print_tips(argv[0]));
	init_vars(&vars);
	render(&vars);
	mlx_put_image_to_window(vars.mlx, vars.win, vars.img, 0, 0);
	mlx_loop(vars.mlx);
	return (0);
}
