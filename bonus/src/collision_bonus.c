#include "../include/cub3d_bonus.h"

//be call by keypress_handler
void	movecollision(int keycode, t_vars *vars)
{
	if (keycode == 13)
		move_if(vars, vars->perso.angle);
	if (keycode == 1)
		move_if(vars, vars->perso.angle - 180);
	if (keycode == 0)
		move_if(vars, vars->perso.angle - 90);
	if (keycode == 2)
		move_if(vars, vars->perso.angle + 90);
	valid_position_check(vars);
}

//move only if space in front and ajust position for gap
void	move_if(t_vars *vars, int angle)
{
	int	dist;
	int	gap;
	int	pace;
	int	mvdist[2];

	dist = get_dist_front(vars, angle);
	gap = vars->map.coll_buff;
	if (dist > 0 && dist > gap)
	{
		pace = vars->perso.pace;
		if (pace > dist - gap)
			pace = dist - gap;
		set_move_dist(angle, mvdist, pace);
		vars->perso.position[0] += mvdist[0];
		vars->perso.position[1] += mvdist[1];
	}
	position_ajust(vars);
}

/*calculation of actual position cell
//ajust position gap space from adjacent cell
*/
void	position_ajust(t_vars *vars)
{
	int	pos_cell[2];

	pos_cell[0] = vars->perso.position[0] / MAPSCALE;
	pos_cell[1] = vars->perso.position[1] / MAPSCALE;
	position_ajust_cardinal_walls(vars, pos_cell);
	//position_ajust_diag_walls(vars, pos_cell);
}

/*ajust position depending of distance from cardinal wall
//cardinal walls = up down left right
*/
void	position_ajust_cardinal_walls(t_vars *vars, int pos_cell[2])
{
	if (iscoll(vars, pos_cell[0] - 1, pos_cell[1], COLL_CHAR) == 1)
		apply_position_ajust(vars, 0, pos_cell, 0);
	if (iscoll(vars, pos_cell[0] + 1, pos_cell[1], COLL_CHAR) == 1)
		apply_position_ajust(vars, 0, pos_cell, 1);
	if (iscoll(vars, pos_cell[0], pos_cell[1] - 1, COLL_CHAR) == 1)
		apply_position_ajust(vars, 1, pos_cell, 0);
	if (iscoll(vars, pos_cell[0], pos_cell[1] + 1, COLL_CHAR) == 1)
		apply_position_ajust(vars, 1, pos_cell, 1);
}

//ajust position depending of distance from diagonal wall
void	position_ajust_diag_walls(t_vars *vars, int pos_cell[2])
{
	if (iscoll(vars, pos_cell[0] - 1, pos_cell[1] - 1, COLL_CHAR) == 1)
	{
		apply_position_ajust(vars, 0, pos_cell, 0);
		apply_position_ajust(vars, 1, pos_cell, 0);
	}
	if (iscoll(vars, pos_cell[0] - 1, pos_cell[1] + 1, COLL_CHAR) == 1)
	{
		apply_position_ajust(vars, 0, pos_cell, 0);
		apply_position_ajust(vars, 1, pos_cell, 1);
	}
	if (iscoll(vars, pos_cell[0] + 1, pos_cell[1] - 1, COLL_CHAR) == 1)
	{
		apply_position_ajust(vars, 0, pos_cell, 1);
		apply_position_ajust(vars, 1, pos_cell, 0);
	}
	if (iscoll(vars, pos_cell[0] + 1, pos_cell[1] + 1, COLL_CHAR) == 1)
	{
		apply_position_ajust(vars, 0, pos_cell, 1);
		apply_position_ajust(vars, 1, pos_cell, 1);
	}
}

/*change position depending of the distance between position and pos_cell
//x0y1 = 0 for position and cell in x and 1 for position and cell in y
//lu0rd1 -> left_up pos_cell = 0 and right down pos_cell = 1
*/
void	apply_position_ajust(t_vars *vars, int x0y1, int pos_cell[2],
	int lu0rd1)
{
	int	dist;

	dist = vars->perso.position[x0y1]  - ((pos_cell[x0y1] + lu0rd1) * MAPSCALE);
	if (abs(dist) < vars->map.coll_buff)
		vars->perso.position[x0y1] += vars->map.coll_buff - abs(dist)
			* (dist) / abs(dist);
}

//check if map[y][x] is a collision space depending of COLL_CHAR
int	iscoll(t_vars *vars, int x, int y, char *coll_char)
{
	if (is_in_map(vars, x, y)
		&& ft_strchr(coll_char, vars->map.map[y][x]) != NULL)
		return (1);
	return (0);
}

//set mvdist depending of the angle and pace
void	set_move_dist(int angle, int mvdis[2], int pace)
{
	int	dir[2];

	angle_direction_xy(angle, dir);
	if (angle % 90 == 0)
	{
		mvdis[0] = pace * dir[0];
		mvdis[1] = pace * dir[1];
	}
	else
	{
		angle = quadrant_angle(angle);
		mvdis[0] = (int)(cos((double)(angle * PI / 180)) * pace);
		mvdis[1] = (int)(sin((double)(angle * PI / 180)) * pace);
		mvdis[0] *= dir[0];
		mvdis[1] *= dir[1];
	}
}

//return the distance from nearest front wall 
int	get_dist_front(t_vars *vars, int angle)
{
	t_raycast	*rc;

	rc = &vars->raycast;
	rc->i_dist = 0;
	rc->ray_i = 0;
	raycast_loop_init_coll(rc, angle);
	set_direction_and_linear_function(rc, &vars->perso);
	set_first00(vars);
	return (vars->raycast.dist[find_smallest_dist(vars, COLL_CHAR)]);
}

//initialise les variables pour le debut du loop de ray_i
void	raycast_loop_init_coll(t_raycast *rc, int angle)
{
	rc->shift[0] = -1;
	rc->shift[1] = -1;
	rc->rayangle = angle;
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
