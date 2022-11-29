#include "../include/cub3d.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		texture_struct_init(&vars);
    	vars_mlx_init(&vars);
		check_file(argv, &vars);
 	   //mlx stuff
		(void)argv;
		vars_mlx_init(&vars);
		raycast_init(&vars);
		mlx_loop_hook(vars.mlx_vars.mlx, render_next_frame, &vars);
		mlx_hook(vars.mlx_vars.win, 6, 0, mouse_move, &vars);
		//mlx_hook(vars.mlx_vars.mlx, 17, exiting function, &vars);
		mlx_loop(vars.mlx_vars.mlx);
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

void	vars_mlx_init(t_vars *vars)
{
	vars->mlx_vars.mlx = mlx_init();
	vars->mlx_vars.win = mlx_new_window(vars->mlx_vars.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx_vars.i_img = 0;
	vars->mlx_vars.img[0] = mlx_new_image(vars->mlx_vars.mlx, SCREEN_W, SCREEN_H);
}

void	my_mlx_pixel_put_walls(t_vars *vars, int x, int y, char *color)
{
	char	*dst;

	dst = vars->mlx_vars.addr + (y * vars->mlx_vars.line_length + x
			* (vars->mlx_vars.bits_per_pixel / 8));
	*dst++ = *color++;
	*dst++ = *color++;
	*dst++ = *color++;
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx_vars.addr + (y * vars->mlx_vars.line_length + x
			* (vars->mlx_vars.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	best_angle_side(int now, int but)
{
	if (abs(now - but) <= 180)
	{
		if (now - but < 0)
			return (1);
		return (-1);
	}
	else
	{
		if (now - but < 0)
			return (-1);
		return (1);
	}
}

int	render_next_frame(t_vars *vars)
{
	int i[2];

	i[1] = vars->mlx_vars.i_img;
	i[0] = i[1] + 1;
	if (i[0] >= NB_IMG)
		i[0] = 0;
	vars->mlx_vars.i_img = i[0];
	vars->mlx_vars.img[i[0]] = mlx_new_image(vars->mlx_vars.mlx, SCREEN_W, SCREEN_H);
	vars->mlx_vars.addr = mlx_get_data_addr(vars->mlx_vars.img[i[0]], &vars->mlx_vars.bits_per_pixel,
			&vars->mlx_vars.line_length, &vars->mlx_vars.endian);

	mlx_hook(vars->mlx_vars.win, 2, 0, keypress_handler, vars);
	raycast_main_loop(vars);
	mlx_put_image_to_window(vars->mlx_vars.mlx, vars->mlx_vars.win, vars->mlx_vars.img[i[0]], 0, 0);
	mlx_destroy_image (vars->mlx_vars.mlx, vars->mlx_vars.img[i[1]]);
	return (0);
}