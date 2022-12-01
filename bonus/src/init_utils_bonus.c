/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:43 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:01 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	reset_perso(t_vars *vars)
{
	vars->perso.pace = PACE * MAPSCALE;
	vars->perso.position[0] = vars->map.perso_start[0] * MAPSCALE
		+ MAPSCALE / 2;
	vars->perso.position[1] = vars->map.perso_start[1] * MAPSCALE
		+ MAPSCALE / 2;
	vars->perso.fov = FOV;
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
	screen->center_pixel_w = (SCREEN_W / 2)
		+ ((OFFSET_CENTER_X * SCREEN_W / 2) / 100);
	screen->center_pixel_h = (SCREEN_H / 2)
		+ (OFFSET_CENTER_Y * SCREEN_H / 2) / 100;
}

void	set_fov_angle_div(t_vars *vars)
{
	vars->raycast.fov_angle_div = (vars->perso.fov / 2);
	vars->raycast.fov_angle_div /= vars->raycast.ray_i_max;
}

void	column_limit(t_screen *screen, t_raycast *raycast)
{
	raycast->ray_i_min = screen->max_width / 2 * -1;
	if (screen->max_width % 2 == 0)
		raycast->ray_i_max = screen->max_width / 2 - 1;
	else
		raycast->ray_i_max = screen->max_width / 2;
	screen->col_left = screen->center_pixel_w + raycast->ray_i_min;
	screen->col_right = screen->center_pixel_w + raycast->ray_i_max;
}
