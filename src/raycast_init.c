#include "../include/cub3d.h"

/* INIT FUNCTION (screen size reset)
** calcul de la grandeur maximal de raycasting en width et height
*/

void	rawycast_init(t_vars *vars)
{
	max_height_width(&vars->screen);
	center_pixel(&vars->screen);
	set_fov_angle_div(&vars->raycast);
	column_limit(&vars->screen, &vars->raycast);
}

void	max_height_width(t_screen *screen)
{
	screen->max_width = 100 - abs(OFFSET_CENTER_X);
	if (100 - abs(OFFSET_CENTER_X) < USED_W)
		screen->max_width = (100 - abs(OFFSET_CENTER_X)) * SCREEN_W / 100;
	else
		screen->max_width = USED_W * SCREEN_W / 100;
	screen->max_height = 100 - abs(OFFSET_CENTER_Y);
	if (100 - abs(OFFSET_CENTER_Y) < USED_H)
		screen->max_height = (100 - abs(OFFSET_CENTER_Y)) * SCREEN_H / 100;
	else
		screen->max_height = USED_H * SCREEN_H / 100;
}

/* INIT FUNCTION (screen size reset)
**calcul du point central du raycasting
*/
void	center_pixel(t_screen *screen)
{
	screen->center_pixel_w = SCREEN_W / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_W;
	screen->center_pixel_h = SCREEN_H / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_H;
}

void	set_fov_angle_div(t_raycast *raycast)
{
	raycast->fov_angle_div = (raycast->fov / 2) / raycast->ray_i_max;
}

void	column_limit(t_screen *screen, t_raycast *raycast)
{
	raycast->ray_i_min = screen->max_width / 2 * -1;
	if (screen->max_width % 2 == 1)
		raycast->ray_i_max = screen->max_width / 2 - 1;
	else
		raycast->ray_i_max = screen->max_width / 2;
	screen->col_left = screen->center_pixel_w + raycast->ray_i_min;
	screen->col_right = screen->center_pixel_w + raycast->ray_i_max;
}