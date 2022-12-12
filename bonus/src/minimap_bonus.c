/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:41:50 by anhebert          #+#    #+#             */
/*   Updated: 2022/12/12 13:42:05 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	minimap_init(t_vars *vars)
{
	vars->minimap.limit = vars->map.map_limit[0] * MINIMAPSIZE;
	if (vars->map.map_limit[1] >= vars->map.map_limit[0])
		vars->minimap.limit = vars->map.map_limit[1] * MINIMAPSIZE;
	vars->minimap.ratio_y = SCREEN_H / vars->minimap.limit;
	vars->minimap.ratio_x = SCREEN_W / vars->minimap.limit;
	vars->minimap.pos_x = vars->perso.position[0] / MAPSCALE;
	vars->minimap.pos_x *= vars->minimap.ratio_x;
	vars->minimap.pos_x -= vars->minimap.ratio_x / 2;
	vars->minimap.pos_x += vars->minimap.ratio_x * 2.5;
	vars->minimap.pos_y = vars->perso.position[1] / MAPSCALE;
	vars->minimap.pos_y *= vars->minimap.ratio_y;
	vars->minimap.pos_y -= vars->minimap.ratio_y / 2;
	vars->minimap.pos_y += vars->minimap.ratio_y * 2.5;
}

void	draw_perso(t_vars *vars)
{
	int	i;
	int	ii;

	i = 0;
	while (++i < vars->minimap.ratio_y)
	{
		ii = 0;
		while (ii < vars->minimap.ratio_x)
		{
			my_mlx_pixel_put(vars, vars->minimap.pos_x + ii,
				vars->minimap.pos_y + i,
				create_trgb(1, 0, 255, 0));
			ii++;
		}
	}
}

void	do_rows(t_vars *vars, int i, int ii, int y)
{
	int	x;

	while (ii < vars->map.map_limit[0] + 2)
	{			
		x = ii * (SCREEN_W / vars->minimap.limit);
		while (x < (ii + 1) * (SCREEN_W / vars->minimap.limit))
		{
			if (vars->map.map[i - 2][ii - 2] == '1')
				my_mlx_pixel_put(vars, x, y, 0000);
			else if (vars->map.map[i - 2][ii - 2] == '0'
				|| is_startchar(vars->map.map[i - 2][ii - 2]))
				my_mlx_pixel_put(vars, x, y,
					create_trgb(0, 255, 255, 255));
			x++;
		}
		ii++;
	}
}

void	draw_map(t_vars *vars)
{
	int		i;
	int		ii;
	int		y;

	i = 1;
	while (++i < vars->map.map_limit[1] + 2)
	{
		y = i * (SCREEN_H / vars->minimap.limit);
		while (y < (i + 1) * (SCREEN_H / vars->minimap.limit))
		{
			ii = 1;
			do_rows(vars, i, ii, y);
			y++;
		}
	}
}
