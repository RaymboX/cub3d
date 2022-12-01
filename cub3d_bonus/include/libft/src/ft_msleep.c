/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:15:50 by mraymond          #+#    #+#             */
/*   Updated: 2022/09/01 13:50:40 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_msleep(long unsigned int wait_millisecond)
{
	long unsigned int	start;

	start = now_millisecond();
	while (now_millisecond() < wait_millisecond + start)
		usleep(50);
}
