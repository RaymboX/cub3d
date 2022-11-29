#include "../include/cub3d.h"

void	create_map(t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	vars->map.map = malloc(sizeof(char *) * vars->map.map_limit[1] + 1);
	while (i < vars->map.start)
	{
		temp = get_next_line(vars->map.fd);
		free (temp);
		i++;
	}
	i = 0;
	while (i < vars->map.map_limit[1])
	{
		temp = get_next_line(vars->map.fd);
		vars->map.map[i] = ft_strcat(temp, vars->map.map_limit[0]);
		i++;
	}
	close (vars->map.fd);
}

void	map_size(t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	vars->map.map_limit[0] = 0;
	while (1)
	{
		temp = get_next_line(vars->map.fd);
		if (temp == NULL)
		{
			free (temp);
			close(vars->map.fd);
			break ;
		}
		if (i >= vars->map.start && ft_strlen_nl(temp) > vars->map.map_limit[0])
			vars->map.map_limit[0] = ft_strlen_nl(temp);
		free(temp);
		i++;
	}
	vars->map.map_limit[1] = i - vars->map.start;
	if (vars->map.map_limit[0] <= 2 || vars->map.map_limit[1] <= 2)
		error_exit("Error: Impossible map, map too small\n", NULL, vars);
}

void	copy_map(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.map_cpy = malloc(sizeof(char *) * vars->map.map_limit[1]);
	while (i < vars->map.map_limit[1])
	{
		vars->map.map_cpy[i] = ft_strdup(vars->map.map[i]);
		i++;
	}
}

bool	is_first_line(char *line, t_vars *vars)
{
	int		i;
	bool	is_one;

	i = 0;
	is_one = false;
	while (line[i])
	{
		if (line[i] == '1' && is_one == false)
		{
			is_one = true;
			break ;
		}
		else if (line[i] != '1' && line[i] != ' ' && line[i] != '\n')
		{
			if (is_startchar(line[i]))
				error_exit("Error: Starting point out of bound\n", line, vars);
			else
				error_exit("Error: Wrong character inside the map zone\n", line, vars);
		}
		i++;
	}
	return (is_one);
}

void	ft_map_start(t_vars *vars)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < vars->map.start)
		free(get_next_line(vars->map.fd));
	while (1)
	{
		temp = get_next_line(vars->map.fd);
		if (temp == NULL)
			error_exit("Error: Couldn't find the map\n", temp, vars);
		if (is_first_line(temp, vars))
		{
			vars->map.start = i;
			free (temp);
			close(vars->map.fd);
			break ;
		}
		free (temp);
		i++;
	}
}
