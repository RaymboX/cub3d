#include "../include/cub3d.h"

void	error_exit(char *error, char *temp, t_vars *vars)
{
	if (vars->map.fd >= 0)
		close(vars->map.fd);
	if (temp)
	{
		free(temp);
		temp = NULL;
	}
	if (vars->textures[0].img)
		free(vars->textures[0].img);
	if (vars->textures[1].img)
		free(vars->textures[1].img);
	if (vars->textures[2].img)
		free(vars->textures[2].img);
	if (vars->textures[3].img)
		free(vars->textures[3].img);
	if (vars->map.map)
		free_map(vars, vars->map.map);
	if (vars->map.map_cpy)
		free_map(vars, vars->map.map_cpy);
	print_error(error);
}

void	print_error(char *error)
{
	ft_putstr_fd(error, 2);
	exit(1);
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
				error_exit("Error: Character outside the map walls\n", NULL, vars);
			ii++;
		}
		i++;
	}
}

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
				error_exit("Error: Wrong character inside the map zone\n", NULL, vars);
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
