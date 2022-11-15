#include "../include/cub3d.h"

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	//free_stuff
	exit(1);
}

void	check_map_errors(t_vars *vars)
{
	int		i;
	int		ii;
	bool	start;

	start = false;
	i = 0;
	ii = 0;
	while (i < vars->map.map_limit[1])
	{
		ii = 0;
		while (vars->map.map[i][ii])
		{
			if (!is_mapchar(vars->map.map[i][ii]))
				print_error("Error: Wrong character inside the map zone\n");
			if (is_startchar(vars->map.map[i][ii]))
			{
				if (!start)
				{
					vars->map.perso_start[0] = ii;
					vars->map.perso_start[1] = i;
					start = true;
				}
				else
					print_error("Error: Too many starting point\n");
			}
			ii++;
		}
		i++;
	}
	if (!start)
		print_error("Error: No start detected\n");
}