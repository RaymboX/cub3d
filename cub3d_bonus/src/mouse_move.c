#include "../include/cub3d.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->perso.angle = degree_ajust(vars->perso.angle
			+ (x - vars->screen.center_pixel_w) * 0.1);
	mlx_mouse_move(vars->mlx.win, vars->screen.center_pixel_w,
		0);
	return (0);
}