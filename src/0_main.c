#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		texture_struct_init(&vars);
		check_file(argv, &vars);
	}
	return (0);
}

/* void	vars_mlx_init(t_vars *vars)
{
	vars->mlx_vars.mlx = mlx_init();
	vars->mlx_vars.win = mlx_new_window(vars->mlx_vars.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx_vars.img = mlx_new_image(vars->mlx_vars.mlx, SCREEN_W, SCREEN_H);
	vars->mlx_vars.addr = mlx_get_data_addr(vars->mlx_vars.img,
			&vars->mlx_vars.bits_per_pixel,
			&vars->mlx_vars.line_length, &vars->mlx_vars.endian);
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx_vars.addr + (y * vars->mlx_vars.line_length + x
			* (vars->mlx_vars.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
} */