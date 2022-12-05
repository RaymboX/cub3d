/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:23 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 14:49:22 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

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

void	move_collsion(t_vars *vars, int angle)
{
	int		i;
	char	celldir_value[3];
	int		movedist[2];
	int		dir[2];

	i = -1;
	while (++i < 3)
		celldir_value[i] = cell_move_val(vars,
				degree_ajust(angle + 30 * (i - 1)));
	set_move_dist(vars, angle, movedist);
	if (celldir_value[0] != '1' && celldir_value[1] != '1'
		&& celldir_value[2] != '1')
		move_in_xy_ifnotcoll(vars, movedist, 1, 1);
	else if ((celldir_value[0] != '1' || celldir_value[2] != '1')
		&& (celldir_value[0] != celldir_value[2]))
	{
		angle_direction_xy(angle, dir);
		if ((celldir_value[0] != '1' && dir[0] == dir[1])
			|| (celldir_value[2] != '1' && dir[0] != dir[1]))
			move_in_xy_ifnotcoll(vars, movedist, 1, 0);
		else
			move_in_xy_ifnotcoll(vars, movedist, 0, 1);
	}
}

void	move_in_xy_ifnotcoll(t_vars *vars, int movedist[2], int x, int y)
{
	if (iscoll(vars, (vars->perso.position[0] + movedist[0] * x) / MAPSCALE,
			(vars->perso.position[1] + movedist[1] * y) / MAPSCALE) == 0)
	{
		vars->perso.position[0] += movedist[0] * x;
		vars->perso.position[1] += movedist[1] * y;
	}
}
