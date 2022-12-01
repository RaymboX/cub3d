/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:49:35 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:01 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	if_negative(long long int *n)
{
	if (*n < 0)
	{
		*n *= -1;
		return (1);
	}
	return (0);
}

static int	nb_char_int(long long int n, long long unsigned int *x10)
{
	int	nbchar;

	nbchar = 0;
	while (n / (*x10 * 10) != 0)
	{
		*x10 *= 10;
		nbchar += 1;
	}
	return (nbchar);
}

static void	fill_str(char *str, long long int *n,
					int negative, long long unsigned int *x10)
{
	int	i;

	if (negative == 1)
		str[0] = '-';
	i = negative;
	while (*x10 > 0)
	{
		str[i++] = *n / *x10 + '0';
		*n -= (*n / *x10) * *x10;
		*x10 /= 10;
	}
	str[i] = '\0';
}

//itoa en long int au lieu de int
char	*ft_ltoa(long long int n)
{
	char					*str;
	int						nbchar;
	int						negative;
	long long unsigned int	x10;
	long long int			val;

	val = n;
	negative = if_negative(&val);
	x10 = 1;
	nbchar = nb_char_int(val, &x10);
	str = (char *)malloc(sizeof(char) * (nbchar + negative + 2));
	if (str == NULL)
		return (NULL);
	fill_str(str, &val, negative, &x10);
	return (str);
}
