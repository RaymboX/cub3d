#include "../include/cub3d.h"

void	check_texture_ext(char *texture)
{
	char	*res;

	res = ft_strrchr(texture, '.');
	if (res == NULL)
		print_error("Error: No extension found\n");
	if (*(res + 1) == 'x' && *(res + 2) == 'p'
		&& *(res + 3) == 'm' && *(res + 4) == '\n')
		return ;
	print_error("Error: Texture file is not a '.xpm'\n");
}

void	assign_texture(char *texture, bool *stat, char *path, char type)
{
	texture = path;
	*stat = true;
	if (type == 'N' || type == 'S' || type == 'W' || type == 'E')
		check_texture_ext(path);
}

bool	identify_texture(t_vars *vars, char *path, char *temp)
{
	if (temp[0] == 'N' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->textures.no_stat)
		assign_texture(vars->textures.no, &vars->textures.no_stat, path, 'N');
	else if (temp[0] == 'S' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->textures.so_stat)
		assign_texture(vars->textures.so, &vars->textures.so_stat, path, 'S');
	else if (temp[0] == 'W' && temp[1] == 'E' && temp[2] == ' '
		&& !vars->textures.we_stat)
		assign_texture(vars->textures.we, &vars->textures.we_stat, path, 'W');
	else if (temp[0] == 'E' && temp[1] == 'A' && temp[2] == ' '
		&& !vars->textures.ea_stat)
		assign_texture(vars->textures.ea, &vars->textures.ea_stat, path, 'E');
	else if (temp[0] == 'F' && temp[1] == ' ' && !vars->textures.f_stat)
		assign_texture(vars->textures.f, &vars->textures.f_stat, path, 'F');
	else if (temp[0] == 'C' && temp[1] == ' ' && !vars->textures.c_stat)
		assign_texture(vars->textures.c, &vars->textures.c_stat, path, 'C');
	else
	{
		free(temp);
		return (false);
	}
	return (true);
}

bool	texture_path(char *temp, t_vars *vars)
{
	int		i;
	int		ii;
	char	*path;

	i = 0;
	ii = 0;
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
	return (identify_texture(vars, path, temp));
}

void	texture_init(int fd, t_vars *vars)
{
	int		i;
	int		counter;
	char	*temp;

	counter = 0;
	vars->map.start = 0;
	while (1)
	{
		i = 0;
		temp = get_next_line(fd);
		vars->map.start += 1;
		if (temp == NULL || temp[i] == '1')
			break ;
		while (temp[i] && temp[i] == ' ' && temp[i] != '\n')
			i++;
		if (temp[i] == '1')
			break ;
		if (temp[i] == '\0' || temp[i] == '\n')
			i = 0;
		else if (temp[i] == 'N' || temp[i] == 'S' || temp[i] == 'W'
			|| temp[i] == 'E' || temp[i] == 'F' || temp[i] == 'C')
		{
			if (texture_path(&temp[i], vars) != 1)
				error_exit("Error: Wrong texture identifier\n", fd, temp);
			counter++;
			if (counter == 6)
				break ;
		}
		else
			error_exit("Error: Wrong character in texture's space\n", fd, temp);
		free(temp);
	}
	if (counter != 6)
		error_exit("Error: Not all texture identifier present\n", fd, temp);
}
