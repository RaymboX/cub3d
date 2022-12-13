/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:54 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/13 13:49:41 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

//replace all keycode from letter to keycode

int	keypress_handler(int keycode, t_vars *vars)
{
	turning(keycode, vars);
	move(keycode, vars);
	pace_change(keycode, vars);
	if (keycode == 53)
		end_program(vars);
	return (0);
}

void	turning(int keycode, t_vars *vars)
{
	if (keycode == 123)
		vars->perso.angle = degree_ajust(vars->perso.angle - TURN_ANGLE);
	if (keycode == 124)
		vars->perso.angle = degree_ajust(vars->perso.angle + TURN_ANGLE);
}

void	pace_change(int keycode, t_vars *vars)
{
	if (keycode == 126)
	{
		vars->perso.pace *= 1.2;
		if (vars->perso.pace > MAPSCALE / 2)
			vars->perso.pace = MAPSCALE / 2;
	}
	if (keycode == 125)
	{
		vars->perso.pace *= 0.8;
		if (vars->perso.pace < 2)
			vars->perso.pace = 2;
	}
}

void	move(int keycode, t_vars *vars)
{
	if (keycode == 13)
		move_position(vars, vars->perso.angle);
	if (keycode == 1)
		move_position(vars, degree_ajust(vars->perso.angle - 180));
	if (keycode == 0)
		move_position(vars, degree_ajust(vars->perso.angle - 90));
	if (keycode == 2)
		move_position(vars, degree_ajust(vars->perso.angle + 90));
	valid_position_check(vars);
}
