/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:23 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/30 14:43:41 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

void	movecell_ajust(t_vars *vars, int movecell[2])
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		if (movecell[i] < 0)
			movecell[i] = 0;
		else if (movecell[i] >= vars->map.map_limit[i])
			movecell[i] = vars->map.map_limit[i] - 1;
	}
}

// to add collision space, set collision to 1. No collision space, collision = 0
char	cell_move_val(t_vars *vars, int angle)
{
	int	movedist[2];
	int	moveposition[2];
	int	movecell[2];

	set_move_dist(vars, angle, movedist);
	moveposition[0] = vars->perso.position[0] + movedist[0];
	moveposition[1] = vars->perso.position[1] + movedist[1];
	movecell[0] = moveposition[0] / MAPSCALE;
	movecell[1] = moveposition[1] / MAPSCALE;
	movecell_ajust(vars, movecell);
	return (vars->map.map[movecell[1]][movecell[0]]);
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
