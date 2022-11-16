#include "../include/cub3d.h"

void	create_map(int fd, t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	vars->map.map = malloc(sizeof(char *) * vars->map.map_limit[1]);
	while (i < vars->map.start)
	{
		temp = get_next_line(fd);
		free (temp);
		i++;
	}
	i = 0;
	while (i < vars->map.map_limit[1])
	{
		temp = get_next_line(fd);
		vars->map.map[i] = ft_strcat(temp, vars->map.map_limit[0]);
		i++;
	}
	close (fd);
}

void	map_size(int fd, t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	vars->map.map_limit[0] = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
		{
			free (temp);
			close(fd);
			break ;
		}
		if (i >= vars->map.start && ft_strlen_nl(temp) > vars->map.map_limit[0])
			vars->map.map_limit[0] = ft_strlen_nl(temp);
		free(temp);
		i++;
	}
	vars->map.map_limit[1] = i - vars->map.start;
	if (vars->map.map_limit[0] <= 2 || vars->map.map_limit[1] <= 2)
		print_error("Error: Impossible map, map too small\n");
}

void	copy_map(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.map_cpy = malloc(sizeof(char *) * vars->map.map_limit[1] + 1);
	while (i < vars->map.map_limit[1])
	{
		vars->map.map_cpy[i] = ft_strdup(vars->map.map[i]);
		i++;
	}
	vars->map.map_cpy[i] = NULL;
}

bool	is_first_line(char *line)
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
				print_error("Error: Starting point out of bound\n");
			else
				print_error("Error: Wrong character inside the map zone\n");
		}
		i++;
	}
	return (is_one);
}

void	ft_map_start(int fd, t_vars *vars)
{
	int		i;
	char	*temp;

	i = -1;
	while (++i < vars->map.start)
		free(get_next_line(fd));
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
			error_exit("Error: Couldn't find the map\n", fd, temp);
		if (is_first_line(temp) == true)
		{
			vars->map.start = i;
			free (temp);
			close(fd);
			break ;
		}
		free (temp);
		i++;
	}
}
