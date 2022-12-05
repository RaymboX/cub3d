/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:48 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 10:34:54 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	quadrant_angle(int angle)
{
	if (angle / 90 == 0 || angle % 90 == 0)
		return (angle);
	else if (angle / 90 == 1)
		return (180 - angle);
	else if (angle / 90 == 2)
		return (angle - 180);
	else
		return (360 - angle);
}

void	angle_direction_xy(int angle, int dir[2])
{
	if (angle == 0 || angle == 180)
	{
		dir[1] = 0;
		dir[0] = -1;
		if (angle == 0)
			dir[0] = 1;
	}
	else if (angle == 90 || angle == 270)
	{
		dir[0] = 0;
		dir[1] = -1;
		if (angle == 90)
			dir[1] = 1;
	}
	else
	{
		dir[1] = -1;
		if (angle / 180 == 0)
		dir[1] = 1;
		dir[0] = 1;
		if (angle > 90 && angle < 270)
			dir[0] = -1;
	}
}

//ajuste les angles en degree pour qu'il soit toujours entre 0 et 360
float	degree_ajust(float degree)
{
	if (degree >= 360)
		degree -= 360;
	if (degree < 0)
		degree += 360;
	return (degree);
}

/*returne l'orientation du mur selon la direction et l'intersection du grid
//0:East 1:South 2:West 3:North
*/
int	find_cardinal_wall(t_vars *vars, int i_dist)
{
	if (i_dist == 0)
	{
		if (vars->raycast.direction[0] == -1)
			return (2);
		else
			return (0);
	}
	else
	{
		if (vars->raycast.direction[1] == -1)
			return (3);
		else
			return (1);
	}
}

int	is_in_map(t_vars *vars, int x, int y)
{
	if (x >= 0 && y >= 0
		&& x < vars->map.map_limit[0]
		&& y < vars->map.map_limit[1])
		return (1);
	return (0);
}