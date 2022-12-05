/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moving_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:41:52 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 14:55:26 by mraymond         ###   ########.fr       */
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

int	in_map(t_vars *vars, int x, int y)
{
	if (x >= 0 && y >= 0
		&& x < vars->map.map_limit[0]
		&& y < vars->map.map_limit[1])
		return (1);
	return (0);
}

int	iscoll(t_vars *vars, int x, int y)
{
	if (in_map(vars, x, y) == 1
		&& vars->map.map[y][x] == '1')
		return (1);
	return (0);
}
