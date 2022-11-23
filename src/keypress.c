#include "../include/cube3d.h"

//replace all keycode from letter to keycode

void    keypress_handler(int keycode, t_vars *vars)
{
 turning(keycode, vars);

void    turning(int keycode, t_vars *vars)
{
 if (keycode == 'a')
  vars->perso.angle = ajust_angle(vars->perso.angle - TURN_ANGLE);
 if (keycode == 'd')
  vars->perso.angle = ajust_angle(vars->perso.angle + TURN_ANGLE);
}

void    move(int keycode, t_vars *vars)
{
 int move_angle;
 int move[2];
 int dir[2];
 if (keycode == 'w' || keycode == 's')
 {
  angle_direction_xy(vars->perso.angle, dir);
  if (vars->perso.angle % 90 == 0)
   //move_grid_parallel;
  else
  {
   move_angle = quadrant_angle(vars->perso.angle);
   move[0] = cos(move_angle * PI / 180) * PACE;
   move[1] = sin(move_angle * PI / 180) * PACE;
   if (keycode == 'w')
    colision_check_move(vars, move, 1);
   else
    colision_check_move(vars, move, -1);
  }
 }
}

void    colision_check_move(t_vars *vars, int move[2], int dir)
{



int    quadrant_angle(int angle)
{
 if (angle / 90 == 0 || angle % 90 == 0)
  return (angle);
 else if (angle / 90 == 1)
  return (90 - angle);
 else if (angle / 90 == 2)
  return (angle - 180);
 else
  return (360 - angle);
}

void    angle_direction_xy(int angle, int dir[2])
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
   dir[1] == 1;
 }
 else
 {
  dir[1] = -1;
  if (angle / 180 == 0)
   dir[1] = 1;
  dir[0] = 1;
  if ((angle > 90 && angle < 270)
   dir[0] == -1;
 }
} 



  
