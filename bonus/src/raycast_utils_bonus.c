/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:30 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:28 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

//calcule la hauteur du mur selon la distance et le MAPSCALE
void	wall_pixel_height(t_vars *vars, t_raycast *rc)
{
	if (rc->smallest_dist > 0)
		rc->wall_height = (vars->screen.max_height * MAPSCALE)
			/ rc->smallest_dist;
	rc->real_wall_height = rc->wall_height;
	if (rc->wall_height > vars->screen.max_height || rc->smallest_dist == 0)
		rc->wall_height = vars->screen.max_height;
	if (rc->smallest_dist == -1)
		rc->wall_height = -1;
}

//trouve la coord de la cell selon la direction en x lorsque sur grid vertical
void	cell_x00(t_vars *vars, int x, int y, int cell[2])
{
	if (vars->raycast.direction[0] == -1)
		x -= 1;
	x /= MAPSCALE;
	y /= MAPSCALE;
	cell[0] = x;
	cell[1] = y;
}

//trouve la coord de la cell selon la direction en y lorsque sur grid horizontal
void	cell_y00(t_vars *vars, int x, int y, int cell[2])
{
	if (vars->raycast.direction[1] == -1)
		y -= 1;
	y /= MAPSCALE;
	x /= MAPSCALE;
	cell[0] = x;
	cell[1] = y;
}

//set les directions lorsque l'angle du perso est parallele au grid
void	set_grid_parallele_direction(t_raycast *rc)
{
	if (rc->rayangle == 0)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 90)
	{
		rc->direction[0] = 0;
		rc->direction[1] = 1;
	}
	if (rc->rayangle == 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 270)
	{
		rc->direction[0] = 0;
		rc->direction[1] = -1;
	}
}

//set les directions et la pente selon l'angle du perso
void	set_general_direction_and_m(t_raycast *rc)
{
	if (rc->rayangle > 0 && rc->rayangle < 90)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 1;
		rc->m = tanf(rc->rayangle * PI / 180) * -1;
	}
	if (rc->rayangle > 90 && rc->rayangle < 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 1;
		rc->m = tanf((180.00 - rc->rayangle) * PI / 180);
	}
	if (rc->rayangle > 180 && rc->rayangle < 270)
	{
		rc->direction[0] = -1;
		rc->direction[1] = -1;
		rc->m = tanf((rc->rayangle - 180) * PI / 180) * -1;
	}
	if (rc->rayangle > 270 && rc->rayangle < 360)
	{
		rc->direction[0] = 1;
		rc->direction[1] = -1;
		rc->m = tanf((360 - rc->rayangle) * PI / 180);
	}
}
