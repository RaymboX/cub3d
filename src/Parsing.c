#include "../include/cub3d.h"

//MODIFIER LE PARSING POUR TROUVER LA PREMIERE LIGNE DE LA MAP ET S'ASSURER QU'IL N'Y AIT PAS DE MAUVAIS CHARACTERES À L'INTÉRIEUR

char	*ft_strcat(char *s1, int len)
{
	char	*new;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	new = malloc(sizeof(char) * len);
	while (s1[i] != '\n')
	{
		new[ii++] = s1[i++];
	}
	while (ii < len)
		new[ii++] = ' ';
	new[ii] = '\0';
	free(s1);
	return (new);
}

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
		if (temp[ii] == '\0' || temp[ii] == '\n')
		{
			free(temp);
			return (0);
		}
	}
	while (temp[ii] == ' ')
	{
		ii++;
		if (temp[ii] == '\0' || temp[ii] == '\n')
		{
			free(temp);
			return (0);
		}
	}
	path = ft_calloc(ft_strlen(&temp[ii]), sizeof(char));
	while (temp[ii])
	{
		path[i] = temp[ii];
		i++;
		ii++;
	}
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
		vars->textures.we_stat = true;
	}
	else if (temp[i] == 'E' && temp[i + 1] == 'A' && temp[i + 2] == ' ' && vars->textures.ea_stat == false)
	{
		vars->textures.ea = path;
		vars->textures.ea_stat = true;
	}
	else if (temp[i] == 'F' && temp[i + 1] == ' ' && vars->textures.f_stat == false)
	{
		vars->textures.f = path;
		vars->textures.f_stat = true;
	}
	else if (temp[i] == 'C' && temp[i + 1] == ' ' && vars->textures.c_stat == false)
	{
		vars->textures.c = path;
		vars->textures.c_stat = true;
	}
	else
	{
		return (0);
		free(temp);
	}
	return (1);
}

int	texture_init(int fd, t_vars *vars)
{
	int		i;
	int		counter;
	char	*temp;

	(void)vars;
	counter = 0;
	while (1)
	{
		i = 0;
		temp = get_next_line(fd);
		if (temp == NULL || temp[i] == '1')
			break ;
		while (temp[i] && temp[i] == ' ' && temp[i] != '\n')
		{
			i++;
			if (temp[i] == '1')
				break ;
		}
		if (temp[i] == '\0' || temp[i] == '\n')
			i = 0;
		else if (temp[i] == 'N' || temp[i] == 'S' || temp[i] == 'W'
			|| temp[i] == 'E' || temp[i] == 'F' || temp[i] == 'C')
		{
			if (texture_path(&temp[i], vars) != 1)
				print_error("Error: Wrong texture identifier\n");
			counter++;
			if (counter == 6)
				break ;
		}
		else
			print_error("Error: Wrong characters in the file's texture space\n");
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
		print_error("Error: No extension found\n");
	if (*(res + 1) == 'c' && *(res + 2) == 'u'
		&& *(res + 3) == 'b' && *(res + 4) == '\0')
		return ;
	print_error("Error: Extension is not '.cub'\n");
}

int	ft_strlen_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
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
		if (i >= vars->map.start && ft_strlen_nl(temp) > max)
			max = ft_strlen_nl(temp);
		free(temp);
		i++;
	}
	vars->map.map_limit[0] = max;
	vars->map.map_limit[1] = i - (vars->map.start + 1);
}

bool is_first_line(char *line)
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
			return (false);
		i++;
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
		i++;
	}
	vars->map.map_cpy[i] = NULL;
}

bool	is_mapchar(char c)
{
	if (c == ' ' || c == '0' || c == '1'
		|| c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}

bool	is_startchar(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (true);
	return (false);
}

void	check_map_erros(t_vars *vars)
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

void	check_file(char **av, t_vars *vars)
{
	int		fd;

	check_ext(av[1]);
	fd = open(av[1], O_RDONLY);
	ft_map_start(fd, vars);
	fd = open(av[1], O_RDONLY);
	map_size(fd, vars);
	fd = open(av[1], O_RDONLY);
	if (texture_init(fd, vars) != 6)
		print_error("Error: Not all texture identifier present\n");
	fd = open(av[1], O_RDONLY, 0777);
	create_map(fd, vars);
	check_map_erros(vars);
	copy_map(vars);
	flood_fill(vars, vars->map.perso_start[1], vars->map.perso_start[0]);
}
