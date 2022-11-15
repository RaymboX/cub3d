#include "../include/cub3d.h"

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
