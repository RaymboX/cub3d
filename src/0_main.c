#include "../include/cub3d.h"

int	end_program(t_vars *vars)
{
	if (vars->map.fd >= 0)
		close(vars->map.fd);
	if (vars->tex[0].img)
		free(vars->tex[0].img);
	if (vars->tex[1].img)
		free(vars->tex[1].img);
	if (vars->tex[2].img)
		free(vars->tex[2].img);
	if (vars->tex[3].img)
		free(vars->tex[3].img);
	if (vars->map.map)
		free_map(vars, vars->map.map);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		vars_init(&vars);
    	vars_mlx_init(&vars);
		check_file(argv, &vars);
 	   //mlx stuff
		(void)argv;
		vars_mlx_init(&vars);
		raycast_init(&vars);
		mlx_loop_hook(vars.mlx.mlx, render_next_frame, &vars);
		mlx_hook(vars.mlx.win, 6, 0, mouse_move, &vars);
		mlx_hook(vars.mlx.win, 17, 0, end_program, &vars);
		mlx_loop(vars.mlx.mlx);
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}

void	my_mlx_pixel_put_walls(t_vars *vars, int x, int y, char *color)
{
	char			*dst;
	unsigned char	t;

	dst = vars->mlx.addr + (y * vars->mlx.line_len + x
			* (vars->mlx.bpp / 8));
	t = FLUIDITY;
	if (vars->raycast.cardinal_wall % 2 == 0)
	{
		*dst++ = DARKER * *color++;
		*dst++ = DARKER * *color++;
		*dst++ = DARKER * *color++;
	}
	else
	{
		*dst++ = *color++;
		*dst++ = *color++;
		*dst++ = *color++;
	}
	*dst++ = t;
}

void	my_mlx_pixel_put(t_vars *vars, int x, int y, int color)
{
	char	*dst;

	dst = vars->mlx.addr + (y * vars->mlx.line_len + x
			* (vars->mlx.bpp / 8));
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
//--------------------------------------------------------------------------
void	vars_mlx_init(t_vars *vars)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx.i_img = 0;
	vars->mlx.img[0] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
}

int	render_next_frame(t_vars *vars)
{
	int i[2];

	i[1] = vars->mlx.i_img;
	i[0] = i[1] + 1;
	if (i[0] >= NB_IMG)
		i[0] = 0;
	vars->mlx.i_img = i[0];
	vars->mlx.img[i[0]] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img[i[0]], &vars->mlx.bpp,
			&vars->mlx.line_len, &vars->mlx.endian);
	mlx_hook(vars->mlx.win, 2, 0, keypress_handler, vars);
	raycast_main_loop(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img[i[0]], 0, 0);
	mlx_destroy_image (vars->mlx.mlx, vars->mlx.img[i[1]]);
	return (0);
}
//-------------------------------------------------------------------------------

/* void	vars_mlx_init(t_vars *vars)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx.i_img = 0;
	vars->mlx.img[0] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
	vars->mlx.img[1] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img[0], &vars->mlx.bpp,
			&vars->mlx.line_len, &vars->mlx.endian);
}

int	render_next_frame(t_vars *vars)
{
	int i[2];

	i[1] = vars->mlx.i_img;
	i[0] = i[1] + 1;
	if (i[0] >= NB_IMG)
		i[0] = 0;
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img[i[0]], &vars->mlx.bpp,
			&vars->mlx.line_len, &vars->mlx.endian);
	mlx_hook(vars->mlx.win, 2, 0, keypress_handler, vars);
	raycast_main_loop(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img[i[0]], 0, 0);
	return (0);
} */

/*
//-----------------------------------------------------------------------------
void	vars_mlx_init(t_vars *vars)
{
	vars->mlx.mlx = mlx_init();
	vars->mlx.win = mlx_new_window(vars->mlx.mlx, SCREEN_W, SCREEN_H,
			"cub3d");
	vars->mlx.img[0] = mlx_new_image(vars->mlx.mlx, SCREEN_W, SCREEN_H);
	vars->mlx.addr = mlx_get_data_addr(vars->mlx.img[0], &vars->mlx.bpp,
			&vars->mlx.line_len, &vars->mlx.endian);
}

 int	render_next_frame(t_vars *vars)
{
	mlx_hook(vars->mlx.win, 2, 0, keypress_handler, vars);
	raycast_main_loop(vars);
	mlx_put_image_to_window(vars->mlx.mlx, vars->mlx.win, vars->mlx.img[0], 0, 0);
	return (0);
} */

//-----------------------------------------------------------------------------