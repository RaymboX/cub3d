#include "../include/cub3d.h"

//replace all keycode from letter to keycode

int	keypress_handler(int keycode, t_vars *vars)
{
	turning(keycode, vars);
	move(keycode, vars);
	if (keycode == 53)
		exit(0);
	return (0);
}

void	turning(int keycode, t_vars *vars)
{
	if (keycode == 123)
		vars->perso.angle = degree_ajust(vars->perso.angle - TURN_ANGLE);
	if (keycode == 124)
		vars->perso.angle = degree_ajust(vars->perso.angle + TURN_ANGLE);
}

void	move(int keycode, t_vars *vars)
{
	if (keycode == 13)
		move_collsion(vars, vars->perso.angle);
	if (keycode == 1)
		move_collsion(vars, degree_ajust(vars->perso.angle - 180));
	if (keycode == 0)
		move_collsion(vars, degree_ajust(vars->perso.angle - 90));
	if (keycode == 2)
		move_collsion(vars, degree_ajust(vars->perso.angle + 90));
}

void	move_collsion(t_vars *vars, int angle)
{
	int	i;
	int	celldir_value[3];
	int	movedist[2];
	int	dir[2];

	i = -1;
	while (++i < 3)
		celldir_value[i] = cell_move_val(vars,
				degree_ajust(angle + 45 * (i - 1)));
	set_move_dist(vars, angle, movedist);
	if (celldir_value[0] != '1' && celldir_value[1] != '1'
		&& celldir_value[2] != '1')
	{
		vars->perso.position[0] += movedist[0];
		vars->perso.position[1] += movedist[1];
	}
	else if (celldir_value[0] != '1' || celldir_value[2] != '1')
	{
		angle_direction_xy(angle, dir);
		if ((celldir_value[0] != '1' && dir[0] == dir[1])
			|| (celldir_value[2] != '1' && dir[0] != dir[1]))
			vars->perso.position[0] += movedist[0];
		else
			vars->perso.position[1] += movedist[1];
	}
}

char	cell_move_val(t_vars *vars, int angle)
{
	int	movedist[2];
	int	moveposition[2];
	int	movecell[2];

	set_move_dist(vars, angle, movedist);
	moveposition[0] = vars->perso.position[0] + movedist[0];
	moveposition[1] = vars->perso.position[1] + movedist[1];
	movecell[0] = moveposition[0] / MAPSCALE;
	movecell[1] = moveposition[1] / MAPSCALE;
	return (vars->map.map[movecell[1]][movecell[0]]);
}

void	set_move_dist(t_vars *vars, int angle, int movedist[2])
{
	int	dir[2];

	angle_direction_xy(angle, dir);
	if (vars->perso.angle % 90 == 0)
	{
		movedist[0] = PACE * dir[0];
		movedist[1] = PACE * dir[1];
	}
	else
	{
		angle = quadrant_angle(angle);
		movedist[0] = (int)(cos((double)(angle * PI / 180)) * PACE) * dir[0];
		movedist[1] = (int)(sin((double)(angle * PI / 180)) * PACE) * dir[1];
	}
}

int	quadrant_angle(int angle)
{
	if (angle / 90 == 0 || angle % 90 == 0)
		return (angle);
	else if (angle / 90 == 1)
		return (180 - angle);
	else if (angle / 90 == 2)
		return (angle - 180);
	else
		return (360 - angle);
}

void	angle_direction_xy(int angle, int dir[2])
{
	if (angle == 0 || angle == 180)
	{
		dir[1] = 0;
		dir[0] = -1;
		if (angle == 0)
			dir[0] = 1;
	}
	else if (angle == 90 || angle == 270)
	{
		dir[0] = 0;
		dir[1] = -1;
		if (angle == 90)
			dir[1] = 1;
	}
	else
	{
		dir[1] = -1;
		if (angle / 180 == 0)
		dir[1] = 1;
		dir[0] = 1;
		if (angle > 90 && angle < 270)
			dir[0] = -1;
	}
}
