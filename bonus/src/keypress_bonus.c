/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:54 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 13:57:15 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

//replace all keycode from letter to keycode

int	keypress_handler(int keycode, t_vars *vars)
{
	turning(keycode, vars);
	move(keycode, vars);
	pace_change(keycode, vars);
	if (keycode == 53)
		exit(0);
	return (0);
}

void	turning(int keycode, t_vars *vars)
{
	if (keycode == 123)
		vars->perso.angle = degree_ajust(vars->perso.angle - TURN_ANGLE);
	if (keycode == 124)
		vars->perso.angle = degree_ajust(vars->perso.angle + TURN_ANGLE);
}

void	pace_change(int keycode, t_vars *vars)
{
	if (keycode == 126)
	{
		vars->perso.pace *= 1.2;
		if (vars->perso.pace > MAPSCALE / 2)
			vars->perso.pace = MAPSCALE / 2;
	}
	if (keycode == 125)
	{
		vars->perso.pace *= 0.8;
		if (vars->perso.pace < 2)
			vars->perso.pace = 2;
	}
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
	{
		vars->perso.position[0] += movedist[0];
		vars->perso.position[1] += movedist[1];
	}
	else if ((celldir_value[0] != '1' || celldir_value[2] != '1')
		&& (celldir_value[0] != celldir_value[2]))
	{
		angle_direction_xy(angle, dir);
		if ((celldir_value[0] != '1' && dir[0] == dir[1])
			|| (celldir_value[2] != '1' && dir[0] != dir[1]))
			vars->perso.position[0] += movedist[0];
		else
			vars->perso.position[1] += movedist[1];
	}
}


void	move(int keycode, t_vars *vars)
{
	if (keycode == 13)
		move_collsion(vars, vars->perso.angle);
	if (keycode == 1)
		move_collsion(vars, degree_ajust(vars->perso.angle - 180));
	if (keycode == 0)
		move_collsion(vars, degree_ajust(vars->perso.angle - 90));
	if (keycode == 2)
		move_collsion(vars, degree_ajust(vars->perso.angle + 90));
	if (keycode == 126)
	{
		vars->perso.pace *= 1.2;
		if (vars->perso.pace > MAPSCALE / 2)
			vars->perso.pace = MAPSCALE / 2;
	}
	if (keycode == 125)
	{
		vars->perso.pace *= 0.8;
		if (vars->perso.pace < 2)
			vars->perso.pace = 2;
	}
}
