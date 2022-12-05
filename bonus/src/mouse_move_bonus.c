/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_move_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 14:56:09 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 14:56:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	mouse_move(int x, int y, t_vars *vars)
{
	(void)y;
	vars->perso.angle = degree_ajust(vars->perso.angle
			+ (x - vars->screen.center_pixel_w) * 0.1);
	mlx_mouse_move(vars->mlx.win, vars->screen.center_pixel_w,
		0);
	return (0);
}
