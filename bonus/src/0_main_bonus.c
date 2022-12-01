/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0_main_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:14:58 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 12:09:10 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

int	main(int argc, char **argv)
{
	t_vars	vars;

	if (argc == 2)
	{
		vars_init(&vars);
		vars_mlx_init(&vars);
		check_file(argv, &vars);
		vars_mlx_init(&vars);
		raycast_init(&vars);
		mlx_mouse_hide();
		mlx_loop_hook(vars.mlx.mlx, render_next_frame, &vars);
		mlx_hook(vars.mlx.win, 6, 0, mouse_move, &vars);
		mlx_hook(vars.mlx.win, 17, 0, end_program, &vars);
		mlx_loop(vars.mlx.mlx);
	}
	else
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	return (0);
}
