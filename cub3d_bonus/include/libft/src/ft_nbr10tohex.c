/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbr10tohex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 08:27:21 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:43 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	converttohex(long int nbr, char capitalx, char *val, int *i)
{
	if (nbr != 0)
	{
		converttohex(nbr / 16, capitalx, val, i);
		if (nbr % 16 < 10)
			val[*i] = nbr % 16 + '0';
		else
			val[*i] = nbr % 16 + (capitalx - 33);
		*i += 1;
	}
}

//Change nbr base from 10 to 16. return char *. x = minuscule X = majuscule
char	*ft_nbr10tohex(long int nbr, char capitalx)
{
	char	*val;
	int		i;

	val = (char *)ft_calloc(50, sizeof(char));
	if (nbr == 0)
		val[0] = '0';
	i = 0;
	if (nbr < 0)
	{
		val[i++] = '-';
		nbr *= -1;
	}
	converttohex(nbr, capitalx, val, &i);
	return (val);
}
