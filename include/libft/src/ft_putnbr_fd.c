/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 14:13:15 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static void	int_x10(long int n, long int *x10)
{
	while (n / (*x10 * 10) != 0)
		*x10 *= 10;
}

static void	write_nbr(long int *n, long int *x10, int fd)
{
	char	c;

	if (*x10 != 0)
	{
		c = *n / *x10 + '0';
		write (fd, &c, 1);
		*n -= (*n / *x10) * *x10;
		*x10 /= 10;
		write_nbr(n, x10, fd);
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	long int	x10;
	long int	val;

	val = n;
	if (fd >= 0)
	{
		if (val < 0)
		{
			write (fd, "-", 1);
			val *= -1;
		}
		x10 = 1;
		int_x10(val, &x10);
		write_nbr(&val, &x10, fd);
	}
}
