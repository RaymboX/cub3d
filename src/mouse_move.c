#include "../include/cub3d.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	printf("x:%d, y:%d, menfou:%d\n", x, y, vars->perso.angle);
	if (x < 0 || x > SCREEN_W)
		mlx_mouse_move(vars->mlx_vars.win, vars->screen.center_pixel_w, y);
	if (y < 0 || y > SCREEN_H)
		mlx_mouse_move(vars->mlx_vars.win, x, vars->screen.center_pixel_h);
	return (0);
}