/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:33 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:29:57 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	flood_fill_inside(t_vars *vars, int y, int x)
{
	if (vars->map.map_cpy[y][x] != '1' && vars->map.map_cpy[y][x] != 'F')
	{
		if (vars->map.map_cpy[y][x] != '0' && vars->map.map_cpy[y][x] != 'N'
			&& vars->map.map_cpy[y][x] != 'E' && vars->map.map_cpy[y][x] != 'S'
			&& vars->map.map_cpy[y][x] != 'W' && vars->map.map_cpy[y][x] != 'F'
			&& vars->map.map_cpy[y][x] != '1')
			error_exit("Error: Map not closed by walls/Space in map\n", 0, vars);
		vars->map.map_cpy[y][x] = 'F';
		if (y - 1 >= 0)
			flood_fill_inside(vars, y - 1, x);
		if (y - 1 >= 0 && x + 1 < vars->map.map_limit[0])
			flood_fill_inside(vars, y - 1, x + 1);
		if (x + 1 < vars->map.map_limit[0])
			flood_fill_inside(vars, y, x + 1);
		if (x + 1 < vars->map.map_limit[0] && y + 1 < vars->map.map_limit[1])
			flood_fill_inside(vars, y + 1, x + 1);
		if (y + 1 < vars->map.map_limit[1])
			flood_fill_inside(vars, y + 1, x);
		if (y + 1 < vars->map.map_limit[1] && x - 1 >= 0)
			flood_fill_inside(vars, y + 1, x - 1);
		if (x - 1 >= 0)
			flood_fill_inside(vars, y, x - 1);
		if (x - 1 >= 0 && y - 1 >= 0)
			flood_fill_inside(vars, y - 1, x - 1);
	}
}

void	flood_fill_walls(t_vars *vars, int y, int x)
{
	if (vars->map.map_cpy[y][x] == '1')
	{
		vars->map.map_cpy[y][x] = 'Z';
		if (x + 1 < vars->map.map_limit[0])
			flood_fill_walls(vars, y, x + 1);
		if (y - 1 >= 0)
			flood_fill_walls(vars, y - 1, x);
		if (x - 1 >= 0)
			flood_fill_walls(vars, y, x - 1);
		if (y + 1 < vars->map.map_limit[1])
			flood_fill_walls(vars, y + 1, x);
	}
}

void	flood_fill_inside_rooms(t_vars *vars, int y, int x, char c)
{
	if (vars->map.map_cpy[y][x] == ' ')
		error_exit("Error: Map not closed by walls/Space in map\n", 0, vars);
	if (vars->map.map_cpy[y][x] == c)
	{
		if (c == '1')
			vars->map.map_cpy[y][x] = 'Z';
		if (c == '0')
			vars->map.map_cpy[y][x] = 'F';
		if (y - 1 >= 0)
			flood_fill_inside_rooms(vars, y - 1, x, c);
		if (y - 1 >= 0 && x + 1 < vars->map.map_limit[0])
			flood_fill_inside_rooms(vars, y - 1, x + 1, c);
		if (x + 1 < vars->map.map_limit[0])
			flood_fill_inside_rooms(vars, y, x + 1, c);
		if (x + 1 < vars->map.map_limit[0] && y + 1 < vars->map.map_limit[1])
			flood_fill_inside_rooms(vars, y + 1, x + 1, c);
		if (y + 1 < vars->map.map_limit[1])
			flood_fill_inside_rooms(vars, y + 1, x, c);
		if (y + 1 < vars->map.map_limit[1] && x - 1 >= 0)
			flood_fill_inside_rooms(vars, y + 1, x - 1, c);
		if (x - 1 >= 0)
			flood_fill_inside_rooms(vars, y, x - 1, c);
		if (x - 1 >= 0 && y - 1 >= 0)
			flood_fill_inside_rooms(vars, y - 1, x - 1, c);
	}
}
