/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vars_init_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:17:04 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/05 10:35:14 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

void	vars_init(t_vars *vars)
{
	vars->tex[0].img = NULL;
	vars->tex[1].img = NULL;
	vars->tex[2].img = NULL;
	vars->tex[3].img = NULL;
	vars->tex[0].stat = false;
	vars->tex[1].stat = false;
	vars->tex[2].stat = false;
	vars->tex[3].stat = false;
	vars->map.is_map = false;
	vars->map.map = NULL;
	vars->map.map_cpy = NULL;
}

/* INIT FUNCTION (screen size reset)
** calcul de la grandeur maximal de raycasting en width et height
*/
void	raycast_init(t_vars *vars)
{
	reset_perso(vars);
	vars->screen.resolution_h = RESOLUTION_H_DEF;
	vars->screen.resolution_w = RESOLUTION_W_DEF;
	max_height_width(&vars->screen);
	center_pixel(&vars->screen);
	column_limit(&vars->screen, &vars->raycast);
	set_fov_angle_div(vars);
	vars->map.coll_buff = COLL_SPACE * MAPSCALE;
}
