/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:16 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:29:51 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

//retourne la coord en x dans la texture
int	xpm_x(t_vars *vars)
{
	float	y;

	if (vars->raycast.i_dist == 0)
		y = vars->raycast.y_x00 % MAPSCALE;
	else
		y = vars->raycast.x_y00 % MAPSCALE;
	if (vars->raycast.cardinal_wall == 1 || vars->raycast.cardinal_wall == 2)
		y = MAPSCALE - y;
	y /= MAPSCALE;
	y *= vars->tex[vars->raycast.cardinal_wall].width;
	return ((int)y);
}

//retourne la coord en y dans la texture
int	xpm_y(t_vars *vars, int pixel_h, int way)
{
	int		xpm_half;
	float	xpm_y_div;

	xpm_half = vars->tex[vars->raycast.cardinal_wall].height / 2;
	xpm_y_div = (float)vars->tex[vars->raycast.cardinal_wall].height
		/ (float)vars->raycast.real_wall_height;
	return (xpm_half + (int)((float)pixel_h * (float)way * xpm_y_div));
}

void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h)
{
	char	*color;
	int		x;
	int		y;
	int		pos;

	x = xpm_x(vars);
	y = xpm_y(vars, pixel_h, 1);
	pos = y * vars->tex[vars->raycast.cardinal_wall].line_len + x
		* (vars->tex[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->tex[vars->raycast.cardinal_wall].addr[pos];
	my_mlx_pixel_put_walls(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		color);
	y = xpm_y(vars, pixel_h, -1);
	pos = y * vars->tex[vars->raycast.cardinal_wall].line_len + x
		* (vars->tex[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->tex[vars->raycast.cardinal_wall].addr[pos];
	my_mlx_pixel_put_walls(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		color);
}

//dessine le plafond et le sol
void	draw_floor_celling(t_vars *vars, int i_resol[2], int pixel_h)
{
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		create_trgb(0, vars->cnf.c_colors[0], vars->cnf.c_colors[1],
			vars->cnf.c_colors[2]));
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		create_trgb(0, vars->cnf.f_colors[0], vars->cnf.f_colors[1],
			vars->cnf.f_colors[2]));
}

//boucle principal de dessin sur image
void	drawing(t_vars *vars, t_raycast *rc)
{
	int	pixel_h;
	int	i_resol[2];

	wall_pixel_height(vars, &vars->raycast);
	i_resol[0] = -1;
	while (++i_resol[0] < vars->screen.resolution_w
		&& vars->screen.center_pixel_w + rc->ray_i + i_resol[0] < SCREEN_W)
	{
		pixel_h = 0;
		while (pixel_h < (vars->screen.max_height - 1) / 2)
		{
			if (pixel_h < rc->wall_height / 2)
				draw_wall(vars, i_resol, pixel_h);
			else
				draw_floor_celling(vars, i_resol, pixel_h);
			pixel_h += vars->screen.resolution_h;
		}
	}
}
