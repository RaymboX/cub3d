#include "../include/cub3d.h"

void	free_map(t_vars *vars, char **map)
{
	int	i;

	i = -1;
	while (++i < vars->map.map_limit[1])
		free(map[i]);
	free(map);
}