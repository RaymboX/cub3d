#include "../include/cub3d.h"

void	set_to_zero(t_vars *vars, int index)
{
	int	i;

	i = -1;
	while (++i < vars->map.map_limit[0])
	{
		if (vars->map.map[index][i] == '\0')
			vars->map.map[index][i] == ' ';
	}
}

// Mettre les x en fonction de la largeur de la limite et non de get_next_line(), possiblement mallocer chaque line de la map et faire un strjoin de la line et get_next_line()
void	create_map(int fd, t_vars *vars)
{
	int		i;
	char	*temp;

	i = -1;
	vars->map.map = malloc(sizeof(char *) * vars->map.map_limit[1]);
	while (++i < vars->map.start)
	{
		temp = get_next_line(fd);
		free (temp);
	}
	i = -1;
	while (++i < vars->map.map_limit[1])
	{
		temp = ft_calloc(vars->map.map_limit[0], sizeof(char));
		vars->map.map[i] = ft_strcat(get_next_line(fd), temp);
		set_to_zero(vars, i);
		if (vars->map.map[i] == NULL)
		{
			free (vars->map.map[i]);
			close(fd);
			break ;
		}
	}
}

bool	texture_path(char *temp, t_vars *vars)
{
	int		i;
	int		ii;
	char	*path;

	i = 0;
	ii = 0; // À revoir
	while (temp[ii] != ' ')
	{
		ii++;
		if (temp[ii] == '\0')
		{
			free(temp);
			return (0);
		}
	}
	while (temp[ii] == ' ')
	{
		ii++;
		if (temp[ii] == '\0')
		{
			free(temp);
			return (0);
		}
	}
	path = ft_calloc(ft_strlen(&temp[ii]), sizeof(char));
	while (temp[ii])
		path[i++] = temp[ii++];
	i = 0;
	if (temp[i] == 'N' && temp[i + 1] == 'O' && temp[i + 2] == ' ' && vars->textures.no_stat == false)
	{
		vars->textures.no = path;
		vars->textures.no_stat = true;
	}
	else if (temp[i] == 'S' && temp[i + 1] == 'O' && temp[i + 2] == ' ' && vars->textures.so_stat == false)
	{
		vars->textures.so = path;
		vars->textures.so_stat = true;
	}
	else if (temp[i] == 'W' && temp[i + 1] == 'E' && temp[i + 2] == ' ' && vars->textures.we_stat == false)
	{
		vars->textures.we = path;
		vars->textures.we = true;
	}
	else if (temp[i] == 'E' && temp[i + 1] == 'A' && temp[i + 2] == ' ' && vars->textures.ea_stat == false)
	{
		vars->textures.ea = path;
		vars->textures.ea = true;
	}
	else if (temp[i] == 'F' && temp[i + 1] == ' ' && vars->textures.f_stat == false)
	{
		vars->textures.f = path;
		vars->textures.f = true;
	}
	else if (temp[i] == 'C' && temp[i + 1] == ' ' && vars->textures.c_stat == false)
	{
		vars->textures.c = path;
		vars->textures.c = true;
	}
	else
	{
		free(temp);
		return (0);
	}
	free(temp);
	return (1);
}

int	texture_init(int fd, t_vars *vars)
{
	int		i;
	int		counter;
	char	*temp;

	while (1)
	{
		i = 0;
		temp = get_next_line(fd);
		while (temp[i] || temp[i] == ' ' || temp[i] != '\n')
			i++;
		if (temp[i] == 'N' || temp[i] == 'S' || temp[i] == 'W'
			|| temp[i] == 'E' || temp[i] == 'F' || temp[i] == 'C')
		{
			if (texture_path(&temp[i], vars) != 1)
			{
				free(temp);
				//write(error);
				exit(1);
			}
			counter++;
			if (counter == 6)
				break ;
		}
		else
		{
			free(temp);
			//write(error);
			exit(1);
		}
		free(temp);
	}
	free(temp);
	return (counter);
}

// À revérifier pour éviter des segfault
void	check_ext(char *arg)
{
	char	*res;

	res = ft_strrchr(arg, '.');
	if (res == NULL)
	{
		write(2, "Error\n", 6);
		ft_putstr_fd(strerror(EINVAL), 2);
		exit (1);
	}
	if (*(res + 1) == 'c' && *(res + 2) == 'u'
		&& *(res + 3) == 'b' && *(res + 4) == '\0')
		return ;
	write(2, "Error\n", 6);
	ft_putstr_fd(strerror(EINVAL), 2);
	exit (1);
}

//À revoir pour gérer des espaces à la fin et limit[1] vérifier si + 1 ou pas
void	map_size(int fd, t_vars *vars) //Work in progress, doit déterminer les attributs de la map avant
{
	int		i;
	int		max;
	char	*temp;

	i = 0;
	max = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
		{
			free (temp);
			close(fd);
			break ;
		}
		if (i >= vars->map.start && ft_strlen(temp) > max)
			max = ft_strlen(temp);
		free(temp);
		i++;
	}
	vars->map.map_limit[0] = max;
	vars->map.map_limit[1] = i - vars->map.start;
}

bool is_first_line(char *line)
{
	int		i;
	bool	is_one;

	i = -1;
	while (line[++i])
	{
		if (line[i] == '1' && is_one == false)
			is_one = true;
		else if (line[i] != '1' || line[i] != ' ' || line[i] != '\n')
			return (false);
	}
	return (is_one);
}

void	ft_map_start(int fd, t_vars *vars)
{
	int		i;
	char	*temp;

	i = 0;
	while (1)
	{
		temp = get_next_line(fd);
		if (is_first_line(temp) == true)
		{
			vars->map.start = i;
			free (temp);
			close(fd);
			break ;
		}
		if (temp == NULL)
		{
			free (temp);
			close(fd);
			//write(error);
			exit(1);
		}
		free (temp);
		i++;
	}
}

void	check_map(char **av, t_vars *vars)
{
	int		fd;

	check_ext(av[1]);
	fd = open(av[1], O_RDONLY);
	ft_map_start(fd, vars);
	fd = open(av[1], O_RDONLY);
	map_size(fd, vars);
	if (texture_init(fd, vars) != 6)
	{
		//write(error)
		exit(1);
	}
	fd = open(av[1], O_RDONLY, 0777);
	if (fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		exit (1);
	}
}