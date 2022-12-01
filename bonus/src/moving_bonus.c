/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:23 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:22 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	valid_position_check(t_vars *vars)
{
	if (vars->perso.position[0] < 0
		|| vars->perso.position[0] >= vars->map.map_limit[0] * MAPSCALE
		|| vars->perso.position[1] < 0
		|| vars->perso.position[1] >= vars->map.map_limit[1] * MAPSCALE)
		reset_perso(vars);
}

void	move_position(t_vars *vars, int angle)
{
	int		movedist[2];

	set_move_dist(vars, angle, movedist);
	vars->perso.position[0] += movedist[0];
	vars->perso.position[1] += movedist[1];
}

// to add collision space, set collision to 1. No collision space, collision = 0
// Considère multipilicaiton pour pointer??
void	set_move_dist(t_vars *vars, int angle, int mvdis[2])
{
	int	dir[2];

	angle_direction_xy(angle, dir);
	if (vars->perso.angle % 90 == 0)
	{
		mvdis[0] = vars->perso.pace * dir[0];
		mvdis[1] = vars->perso.pace * dir[1];
	}
	else
	{
		angle = quadrant_angle(angle);
		mvdis[0] = (int)(cos((double)(angle * PI / 180)) * vars->perso.pace);
		mvdis[1] = (int)(sin((double)(angle * PI / 180)) * vars->perso.pace);
		mvdis[0] *= dir[0];
		mvdis[1] *= dir[1];
	}
}
