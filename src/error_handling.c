#include "../include/cub3d.h"

void	error_exit(char *error, int fd, char *temp, t_vars *vars)
{
	(void)vars;
	close(fd);
	if (temp)
		free(temp);
	if (vars->textures.n)
		free(vars->textures.n);
	if (vars->textures.s)
		free(vars->textures.s);
	if (vars->textures.e)
		free(vars->textures.e);
	if (vars->textures.w)
		free(vars->textures.w);
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
				print_error("Error: Character outside the map walls\n");
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
				print_error("Error: Wrong character inside the map zone\n");
			if (is_startchar(vars->map.map[i][ii]))
			{
				if (!start)
					set_start(&start, vars, i, ii);
				else
					print_error("Error: Too many starting point\n");
			}
			ii++;
		}
	}
	if (!start)
		print_error("Error: No start detected\n");
}
