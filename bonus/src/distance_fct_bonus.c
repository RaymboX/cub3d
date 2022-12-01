/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   distance_fct_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:15:08 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:29:49 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

//calcul la distance entre la position et le mur et set l'orientation du mur
void	set_dist_n_wall(t_vars *vars)
{
	int	i_dist;

	vars->raycast.i_dist = find_smallest_dist(vars);
	i_dist = vars->raycast.i_dist;
	if (i_dist == -1)
	{
		vars->raycast.cardinal_wall = -1;
		vars->raycast.smallest_dist = -1;
	}
	else
	{
		vars->raycast.smallest_dist = vars->raycast.dist[i_dist];
		vars->raycast.smallest_dist = cosf(degree_ajust(
					fabsf(vars->perso.angle - vars->raycast.rayangle))
				* PI / 180)
			* vars->raycast.smallest_dist;
		vars->raycast.cardinal_wall = find_cardinal_wall(vars, i_dist);
	}
}

//calcul la distance entre les coord du perso et xy en parametre
int	calcul_dist(t_vars *vars, int x, int y)
{
	return ((int)sqrt(pow((double)(x - vars->perso.position[0]), 2)
		+ pow((double)(y - vars->perso.position[1]), 2)));
}

/*retourne l'orientation du grid du mur rencontrer le plus proche
//0:mur le plus proche rencontrer sur un grid vertical (x00 % MAPSCALE == 0)
//1:mur le plus proche rencontrer sur un grid horizontal (y00 % MAPSCALE == 0)
//-1:Aucun mur rencontrer
//En cas d'egaliter de distance, retourne le dernier mur dessiner (last i_dist)
*/
int	find_smallest_dist(t_vars *vars)
{
	nearest_x00_wall(vars, &vars->raycast);
	nearest_y00_wall(vars, &vars->raycast);
	if (vars->raycast.cellvalue[0] == '-' && vars->raycast.cellvalue[1] == '-')
		return (-1);
	if (vars->raycast.cellvalue[0] == '-')
		return (1);
	if (vars->raycast.cellvalue[1] == '-')
		return (0);
	if (vars->raycast.dist[0] < vars->raycast.dist[1])
		return (0);
	if (vars->raycast.dist[0] > vars->raycast.dist[1])
		return (1);
	return (vars->raycast.i_dist);
}

/*calcul la distance du mur le plus proche sur les grids verticaux
//Si aucun mur rencontrer, la cellvalue est set to '-'
*/
void	nearest_x00_wall(t_vars *vars, t_raycast *rc)
{
	if (rc->direction[0] == 0)
		rc->cellvalue[0] = '-';
	else
	{
		while (rc->cellvalue[0] != '1' && rc->cellvalue[0] != '-')
		{
			rc->shift[0] += 1;
			rc->x00 = rc->first00[0] + rc->shift[0] * rc->direction[0]
				* MAPSCALE;
			if (rc->direction[1] != 0)
				rc->y_x00 = (rc->m * rc->x00 + rc->b) * -1;
			else
				rc->y_x00 = vars->perso.position[1];
			cell_x00(vars, rc->x00, rc->y_x00, rc->cell00[0]);
			if (rc->cell00[0][0] < vars->map.map_limit[0]
				&& rc->cell00[0][0] >= 0 && rc->cell00[0][1] >= 0
				&& rc->cell00[0][1] < vars->map.map_limit[1])
				vars->raycast.cellvalue[0]
					= vars->map.map[rc->cell00[0][1]][rc->cell00[0][0]];
			else
				vars->raycast.cellvalue[0] = '-';
		}
		if (rc->cellvalue[0] != '-')
			rc->dist[0] = calcul_dist(vars, rc->x00, rc->y_x00);
	}
}

/*calcul la distance du mur le plus proche sur les grids horizontaux
//Si aucun mur rencontrer, la cellvalue est set to '-'
*/
void	nearest_y00_wall(t_vars *vars, t_raycast *rc)
{
	if (rc->direction[1] == 0)
		rc->cellvalue[1] = '-';
	else
	{
		while (rc->cellvalue[1] != '1' && rc->cellvalue[1] != '-')
		{
			rc->shift[1] += 1;
			rc->y00 = rc->first00[1] + rc->shift[1] * rc->direction[1]
				* MAPSCALE;
			if (rc->direction[0] != 0)
				rc->x_y00 = (-rc->y00 - rc->b) / rc->m;
			else
				rc->x_y00 = vars->perso.position[0];
			cell_y00(vars, rc->x_y00, rc->y00, rc->cell00[1]);
			if (rc->cell00[1][0] < vars->map.map_limit[0]
				&& rc->cell00[1][0] >= 0 && rc->cell00[1][1] >= 0
				&& rc->cell00[1][1] < vars->map.map_limit[1])
				vars->raycast.cellvalue[1]
					= vars->map.map[rc->cell00[1][1]][rc->cell00[1][0]];
			else
				vars->raycast.cellvalue[1] = '-';
		}
		if (rc->cellvalue[1] != '-')
			rc->dist[1] = calcul_dist(vars, rc->x_y00, rc->y00);
	}
}
