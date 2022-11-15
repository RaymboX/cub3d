#include "../include/cub3d.h"

void	flood_fill(t_vars *vars, int pos_x, int pos_y)
{
	int	i;

	i = -1;
	if (vars->map.map_cpy[pos_x][pos_y] != '1' && vars->map.map_cpy[pos_x][pos_y] != 'F')
	{
		if (vars->map.map_cpy[pos_x][pos_y] != '0' && vars->map.map_cpy[pos_x][pos_y] != 'N'
			&& vars->map.map_cpy[pos_x][pos_y] != 'E' && vars->map.map_cpy[pos_x][pos_y] != 'S'
			&& vars->map.map_cpy[pos_x][pos_y] != 'W' && vars->map.map_cpy[pos_x][pos_y] != 'F'
			&& vars->map.map_cpy[pos_x][pos_y] != '1')
			print_error("Error: Map is not enclosed by walls\n");
		vars->map.map_cpy[pos_x][pos_y] = 'F';
		while (++i < vars->map.map_limit[1])
			printf("%s\n", vars->map.map_cpy[i]);
		flood_fill(vars, pos_x + 1, pos_y);
		flood_fill(vars, pos_x, pos_y + 1);
		flood_fill(vars, pos_x - 1, pos_y);
		flood_fill(vars, pos_x, pos_y - 1);
	}
	return ;
}
