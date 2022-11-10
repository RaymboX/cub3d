/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   progress_bar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 08:57:37 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:59:36 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	progress_bar(int start, int end, int now, int bar_len)
{
	int	i;

	if (now == start)
	{
		write(1, "progress:", 9);
		i = -1;
		while (++i < bar_len)
			write(1, "_", 1);
		i = -1;
		while (++i < bar_len)
			write(1, "\b", 1);
	}
	else if ((now - start) % ((end - start) / bar_len) == 0)
		write(1, "|", 1);
	else if (now == end)
		write(1, "\n", 1);
}
