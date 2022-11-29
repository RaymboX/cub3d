#include "../include/cub3d.h"

void	flood_fill_inside(t_vars *vars, int y, int x)
{
	if (vars->map.map_cpy[y][x] != '1' && vars->map.map_cpy[y][x] != 'F')
	{
		if (vars->map.map_cpy[y][x] != '0' && vars->map.map_cpy[y][x] != 'N'
			&& vars->map.map_cpy[y][x] != 'E' && vars->map.map_cpy[y][x] != 'S'
			&& vars->map.map_cpy[y][x] != 'W' && vars->map.map_cpy[y][x] != 'F'
			&& vars->map.map_cpy[y][x] != '1')
			error_exit("Error: Map is not enclosed by walls/Spaces in map\n", NULL, NULL, vars);
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
		error_exit("Error: Map is not enclosed by walls/Spaces in map\n", NULL, NULL, vars);
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
