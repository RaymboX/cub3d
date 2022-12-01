/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_main_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:37 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:30 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

//calcul et dessine l'image selon position et angle
void	raycast_main_loop(t_vars *vars)
{
	t_raycast	*rc;

	rc = &vars->raycast;
	rc->i_dist = 0;
	rc->ray_i = rc->ray_i_min;
	while (rc->ray_i <= rc->ray_i_max)
	{
		raycast_loop_init(rc, &vars->perso);
		set_direction_and_linear_function(rc, &vars->perso);
		set_first00(vars);
		set_dist_n_wall(vars);
		drawing(vars, rc);
		rc->ray_i += vars->screen.resolution_w;
	}
}

//initialise les variables pour le debut du loop de ray_i
void	raycast_loop_init(t_raycast *rc, t_perso *perso)
{
	rc->shift[0] = -1;
	rc->shift[1] = -1;
	rc->rayangle = perso->angle + rc->ray_i * rc->fov_angle_div;
	rc->rayangle = degree_ajust(rc->rayangle);
	rc->cellvalue[0] = '0';
	rc->cellvalue[1] = '0';
	rc->m = 0;
	rc->b = 0;
	rc->first00[0] = 0;
	rc->first00[1] = 0;
	rc->dist[0] = INT_MAX;
	rc->dist[1] = INT_MAX;
	rc->smallest_dist = INT_MAX;
}

/*etabli la formule qui permettera de calculer les intersection de grid
// et set les directions
//Si la pente est parrallele a un grid, les directions sont set a 0
*/
void	set_direction_and_linear_function(t_raycast *rc, t_perso *perso)
{
	if (rc->rayangle == 0 || rc->rayangle == 90
		|| rc->rayangle == 180 || rc->rayangle == 270)
		set_grid_parallele_direction(rc);
	else
	{
		set_general_direction_and_m(rc);
		rc->b = perso->position[1] * -1 - rc->m
			* perso->position[0];
	}
}

/*set le cote du grid (ou se situe le perso)
// ou commence la verification de mur selon la direction
*/
void	set_first00(t_vars *vars)
{
	int	i;

	i = -1;
	while (++i < 2)
	{
		vars->raycast.first00[i] = vars->perso.position[i] / MAPSCALE;
		vars->raycast.first00[i] *= MAPSCALE;
		if (vars->raycast.direction[i] == 1)
			vars->raycast.first00[i] += MAPSCALE;
	}
}
