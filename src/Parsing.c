#include "../include/cub3d.h"

// Mettre les x en fonction de la largeur de la limite et non de get_next_line(), possiblement mallocer chaque line de la map et faire un strjoin de la line et get_next_line()
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
		if (vars->map.map[i] == NULL)
		{
			free (vars->map.map[i]);
			close(fd);
			break ;
		}
		i++;
	}
}

// À revérifier pour éviter des segfault
void	check_ext(char *arg)
{
	char	*res;

	res = ft_strrchr(arg, '.');
	if (res == NULL)
		print_error("Error: No extension found\n");
	if (*(res + 1) == 'c' && *(res + 2) == 'u'
		&& *(res + 3) == 'b' && *(res + 4) == '\0')
		return ;
	print_error("Error: Extension is not '.cub'\n");
}

//Segfault lorsque la carte ne finie par par un '\n', ne sait pas pourquoi
//vars->map.map-limit[1] ne fonctionne pas
void	map_size(int fd, t_vars *vars) //Work in progress, doit déterminer les attributs de la map avant
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
		print_error("Error: Impossible map\n");
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

	i = 0;
	while (i < vars->map.start)
	{
		temp = get_next_line(fd);
		free(temp);
		i++;
	}
	while (1)
	{
		temp = get_next_line(fd);
		if (temp == NULL)
		{
			free (temp);
			print_error("Error: Couldn't find the map\n");
		}
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

void	copy_map(t_vars *vars)
{
	int	i;

	i = 0;
	vars->map.map_cpy = malloc(sizeof(char *) * vars->map.map_limit[1] + 1);
	while (i < vars->map.map_limit[1])
	{
		vars->map.map_cpy[i] = ft_strdup(vars->map.map[i]);
		printf("%s\n", vars->map.map_cpy[i]);
		i++;
	}
	vars->map.map_cpy[i] = NULL;
}

void	check_file(char **av, t_vars *vars)
{
	int		fd;

	check_ext(av[1]);
	fd = open(av[1], O_RDONLY);
	if (texture_init(fd, vars) != 6)
		print_error("Error: Not all texture identifier present\n");
	fd = open(av[1], O_RDONLY);
	ft_map_start(fd, vars);
	fd = open(av[1], O_RDONLY);
	map_size(fd, vars);
	fd = open(av[1], O_RDONLY, 0777);
	create_map(fd, vars);
	check_map_errors(vars);
	copy_map(vars);
	flood_fill(vars, vars->map.perso_start[1], vars->map.perso_start[0]);
}
