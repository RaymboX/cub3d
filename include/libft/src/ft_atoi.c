/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:06:07 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:55:54 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static void	skip_space(const char *nptr, size_t *i)
{
	while (*i < ft_strlen(nptr) && ft_isspace((int)nptr[*i]) == 1)
		*i += 1;
}

static void	ft_signed(const char *nptr, size_t *i, int *negative)
{
	if (*i < ft_strlen(nptr) && (nptr[*i] == '-' || nptr[*i] == '+'))
	{
		if (nptr[*i] == '-')
			*negative = -1;
		*i += 1;
	}
}

//Return int of char nptr 
int	ft_atoi(const char *nptr)
{
	size_t	i;
	int		negative;
	int		value;

	if (nptr == NULL)
		return (0);
	i = 0;
	skip_space(nptr, &i);
	negative = 1;
	ft_signed(nptr, &i, &negative);
	value = 0;
	while (nptr[i] != '\0'
		&& nptr[i] >= '0'
		&& nptr[i] <= '9')
	{
		value *= 10;
		value += nptr[i] - '0';
		i++;
	}
	return (value * negative);
}
