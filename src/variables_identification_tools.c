/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variables_identification_tools.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:53 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/30 14:16:54 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

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

bool	is_type_texture(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E'
		|| c == 'F' || c == 'C')
		return (true);
	return (false);
}

bool	is_end(char c, int counter)
{
	if ((c == '\0' || c == '\n') && counter < 2)
		print_error("Error: Wrong color format\n");
	if (c == '\0' || c == '\n')
		return (true);
	return (false);
}

bool	identify_texture(t_vars *vars, char *path, char *temp)
{
	if (temp[0] == 'N' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->tex[3].stat)
		assign_texture(vars, &vars->tex[3].stat, path, 3);
	else if (temp[0] == 'S' && temp[1] == 'O' && temp[2] == ' '
		&& !vars->tex[1].stat)
		assign_texture(vars, &vars->tex[1].stat, path, 1);
	else if (temp[0] == 'W' && temp[1] == 'E' && temp[2] == ' '
		&& !vars->tex[2].stat)
		assign_texture(vars, &vars->tex[2].stat, path, 2);
	else if (temp[0] == 'E' && temp[1] == 'A' && temp[2] == ' '
		&& !vars->tex[0].stat)
		assign_texture(vars, &vars->tex[0].stat, path, 0);
	else if (temp[0] == 'F' && temp[1] == ' ' && !vars->cnf.f_stat)
		assign_texture(vars, &vars->cnf.f_stat, path, 'F');
	else if (temp[0] == 'C' && temp[1] == ' ' && !vars->cnf.c_stat)
		assign_texture(vars, &vars->cnf.c_stat, path, 'C');
	else
		return (false);
	return (true);
}
