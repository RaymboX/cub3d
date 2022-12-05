/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_tools2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:09 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:07 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	set_start(bool *start, t_vars *vars, int i, int ii)
{
	vars->map.perso_start[0] = ii;
	vars->map.perso_start[1] = i;
	if (vars->map.map[i][ii] == 'N')
		vars->perso.angle = 270;
	else if (vars->map.map[i][ii] == 'E')
		vars->perso.angle = 0;
	else if (vars->map.map[i][ii] == 'S')
		vars->perso.angle = 90;
	else if (vars->map.map[i][ii] == 'W')
		vars->perso.angle = 180;
	*start = true;
}

void	check_map_errors(t_vars *vars)
{
	int		i;
	int		ii;
	bool	start;

	start = false;
	i = -1;
	while (++i < vars->map.map_limit[1])
	{
		ii = 0;
		while (vars->map.map[i][ii])
		{
			if (!is_mapchar(vars->map.map[i][ii]))
				error_exit("Error: Wrong character in map zone\n", NULL, vars);
			if (is_startchar(vars->map.map[i][ii]))
			{
				if (!start)
					set_start(&start, vars, i, ii);
				else
					error_exit("Error: Too many starting point\n", NULL, vars);
			}
			ii++;
		}
	}
	if (!start)
		error_exit("Error: No start detected\n", NULL, vars);
}

void	check_map_integrity(t_vars *vars)
{
	int	i;
	int	ii;

	i = 0;
	while (i < vars->map.map_limit[1])
	{
		ii = 0;
		while (ii < vars->map.map_limit[0])
		{
			if (vars->map.map_cpy[i][ii] != 'F'
				&& vars->map.map_cpy[i][ii] != 'Z'
				&& vars->map.map_cpy[i][ii] != ' ')
				error_exit("Error: Character outside the map walls\n",
					NULL, vars);
			ii++;
		}
		i++;
	}
}

void	check_inside_rooms(t_vars *vars)
{
	int	i;
	int	ii;

	i = 0;
	while (i < vars->map.map_limit[1])
	{
		ii = 0;
		while (vars->map.map_cpy[i][ii])
		{
			if (vars->map.map_cpy[i][ii] == '1'
				|| vars->map.map_cpy[i][ii] == '0')
				flood_fill_inside_rooms(vars, i, ii, vars->map.map_cpy[i][ii]);
			ii++;
		}
		i++;
	}
}

void	find_first_wall(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->map.map_limit[0])
	{
		if (vars->map.map[0][i] == '1')
			break ;
		i++;
	}
	vars->map.first_wall = i;
}
