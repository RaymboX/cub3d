
#include "../include/cub3d.h"

/* INIT FUNCTION (screen size reset)
** calcul de la grandeur maximal de raycasting en width et height
*/
void	max_height_width(t_screen *screen)
{
	screen->max_width = 100 - OFFSET_CENTER_X;
	if (100 - abs(OFFSET_CENTER_X) < USED_WIDTH)
		screen->max_width = (100 - abs(OFFSET_CENTER_X)) * SCREEN_WIDTH / 100;
	else
		screen->max_width = USED_WIDTH * SCREEN_WIDTH / 100;
	screen->max_height = 100 - OFFSET_CENTER_Y;
	if (100 - abs(OFFSET_CENTER_Y) < USED_HEIGHT)
		screen->max_height = (100 - abs(OFFSET_CENTER_Y)) * SCREEN_HEIGHT / 100;
	else
		screen->max_height = USED_HEIGHT * SCREEN_HEIGHT / 100;
}

/* INIT FUNCTION (screen size reset)
**calcul du point central du raycasting
*/
void	center_pixel(t_screen *screen)
{
	screen->center_pixel_w = SCREEN_WIDTH / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_WIDTH;
	screen->center_pixel_w = SCREEN_WIDTH / 2
		+ (OFFSET_CENTER_X / 100) * SCREEN_WIDTH;
}

void	set_fov_angle_div(t_raycast *raycast)
{
	 
	raycast->fov_angle_div = fov / 2
}

void	raycast_main_loop(t_vars *vars)
{
	//init first data before loop
	//
}
