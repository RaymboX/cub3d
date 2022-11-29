#include "../include/cub3d.h"


//ajuste les angles en degree pour qu'il soit toujours entre 0 et 360
float	degree_ajust(float degree)
{
	if (degree >= 360)
		degree -= 360;
	if (degree < 0)
		degree += 360;
	return (degree);
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

//set les directions lorsque l'angle du perso est parallele au grid
void	set_grid_parallele_direction(t_raycast *rc)
{
	if (rc->rayangle == 0)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 90)
	{
		rc->direction[0] = 0;
		rc->direction[1] = 1;
	}
	if (rc->rayangle == 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 0;
	}
	if (rc->rayangle == 270)
	{
		rc->direction[0] = 0;
		rc->direction[1] = -1;
	}
}

//set les directions et la pente selon l'angle du perso
void	set_general_direction_and_m(t_raycast *rc)
{
	if (rc->rayangle > 0 && rc->rayangle < 90)
	{
		rc->direction[0] = 1;
		rc->direction[1] = 1;
		rc->m = tanf(rc->rayangle * PI / 180) * -1;
	}
	if (rc->rayangle > 90 && rc->rayangle < 180)
	{
		rc->direction[0] = -1;
		rc->direction[1] = 1;
		rc->m = tanf((180.00 - rc->rayangle) * PI / 180);
	}
	if (rc->rayangle > 180 && rc->rayangle < 270)
	{
		rc->direction[0] = -1;
		rc->direction[1] = -1;
		rc->m = tanf((rc->rayangle - 180) * PI / 180) * -1;
	}
	if (rc->rayangle > 270 && rc->rayangle < 360)
	{
		rc->direction[0] = 1;
		rc->direction[1] = -1;
		rc->m = tanf((360 - rc->rayangle) * PI / 180);
	}
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

//calcule la hauteur du mur selon la distance et le MAPSCALE
void	wall_pixel_height(t_vars *vars, t_raycast *rc)
{
	if (rc->smallest_dist > 0)
		rc->wall_height = (vars->screen.max_height * MAPSCALE)
			/ rc->smallest_dist;
	rc->real_wall_height = rc->wall_height;
	if (rc->wall_height > vars->screen.max_height || rc->smallest_dist == 0)
		rc->wall_height = vars->screen.max_height;
	if (rc->smallest_dist == -1)
		rc->wall_height = -1;
}

//retourne la coord en x dans la texture
int	xpm_x(t_vars *vars)
{
	float	y;

	if (vars->raycast.i_dist == 0)//x00 EAST 0 WEST 2
		y = vars->raycast.y_x00 % MAPSCALE;
	else//y00
		y = vars->raycast.x_y00 % MAPSCALE;
	if (vars->raycast.cardinal_wall == 1 || vars->raycast.cardinal_wall == 2)
		y = MAPSCALE - y;
	y /= MAPSCALE;
	y *= vars->textures[vars->raycast.cardinal_wall].width;
	return ((int)y);
}

//retourne la coord en y dans la texture
int	xpm_y(t_vars *vars, int pixel_h, int way)
{
	int		xpm_half;
	float	xpm_y_div;

	xpm_half = vars->textures[vars->raycast.cardinal_wall].height / 2;
	xpm_y_div = (float)vars->textures[vars->raycast.cardinal_wall].height / (float)vars->raycast.real_wall_height;
	return(xpm_half + (int)((float)pixel_h * (float)way * xpm_y_div));
}

//x et y à definir
void	draw_wall(t_vars *vars, int i_resol[2], int pixel_h)
{
	char	*color;
	int		x;
	int		y;
	int		pos;

	x = xpm_x(vars);
	y = xpm_y(vars, pixel_h, 1);
	pos = y * vars->textures[vars->raycast.cardinal_wall].size_line + x * (vars->textures[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->textures[vars->raycast.cardinal_wall].addr[pos];
	my_mlx_pixel_put_walls(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h + pixel_h,
		color);
	y = xpm_y(vars, pixel_h, -1);
	pos = y * vars->textures[vars->raycast.cardinal_wall].size_line + x * (vars->textures[vars->raycast.cardinal_wall].bpp / 8);
	color = &vars->textures[vars->raycast.cardinal_wall].addr[pos];
	//color = (unsigned int)vars->textures[vars->raycast.cardinal_wall].addr[pos];
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
		create_trgb(0, 0, 102, 0));
	my_mlx_pixel_put(vars,
		vars->screen.center_pixel_w + vars->raycast.ray_i + i_resol[0],
		vars->screen.center_pixel_h - pixel_h,
		create_trgb(0, 0, 255, 255));
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

//trouve la coord de la cell selon la direction en x lorsque sur grid vertical
void	cell_x00(t_vars *vars, int x, int y, int cell[2])
{
	if (vars->raycast.direction[0] == -1)
		x -= 1;
	x /= MAPSCALE;
	y /= MAPSCALE;
	cell[0] = x;
	cell[1] = y;
}

//trouve la coord de la cell selon la direction en y lorsque sur grid horizontal
void	cell_y00(t_vars *vars, int x, int y, int cell[2])
{
	if (vars->raycast.direction[1] == -1)
		y -= 1;
	y /= MAPSCALE;
	x /= MAPSCALE;
	cell[0] = x;
	cell[1] = y;
}

//calcul la distance entre les coord du perso et xy en parametre
int	calcul_dist(t_vars *vars, int x, int y)
{
	return ((int)sqrt(pow((double)(x - vars->perso.position[0]), 2)
			+ pow((double)(y - vars->perso.position[1]), 2)));
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
				&& rc->cell00[0][0] >= 0
				&& rc->cell00[0][1] < vars->map.map_limit[1]
				&& rc->cell00[0][1] >= 0)
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
				&& rc->cell00[1][0] >= 0
				&& rc->cell00[1][1] < vars->map.map_limit[1]
				&& rc->cell00[1][1] >= 0)
				vars->raycast.cellvalue[1]
					= vars->map.map[rc->cell00[1][1]][rc->cell00[1][0]];
			else
				vars->raycast.cellvalue[1] = '-';
		}
		if (rc->cellvalue[1] != '-')
			rc->dist[1] = calcul_dist(vars, rc->x_y00, rc->y00);
	}
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

/*returne l'orientation du mur selon la direction et l'intersection du grid
//0:East 1:South 2:West 3:North
*/
int	find_cardinal_wall(t_vars *vars, int i_dist)
{
	if (i_dist == 0)
	{
		if (vars->raycast.direction[0] == -1)
			return (2);
		else
			return (0);
	}
	else
	{
		if (vars->raycast.direction[1] == -1)
			return (3);
		else
			return (1);
	}
}

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
