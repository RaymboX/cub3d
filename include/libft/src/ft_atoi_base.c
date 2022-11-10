/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:02:06 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:55:49 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static void	skip_space(const char *str, int *i)
{
	while (((int)str[*i] >= 9 && (int)str[*i] <= 13) || (int)str[*i] == 32)
		*i += 1;
}

static int	val_signed(const char *str, int *i)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		*i += 1;
		if (str[*i - 1] == '-')
			return (-1);
	}
	return (1);
}

static int	is_in_base(const char *str, int str_base, char *base)
{
	int	i[2];

	i[0] = -1;
	while (str[++i[0]])
	{
		i[1] = 0;
		while (str[i[0]] != base[i[1]] && i[1] < str_base)
			i[1]++;
		if (str[i[0]] != base[i[1]])
			return (0);
	}
	return (1);
}

static int	base_val(char c)
{
	if (c >= '0' && c <= '9')
		return (c - '0');
	if (c >= 'a' && c <= 'f')
		return (c - 'a' + 10);
	if (c >= 'A' && c <= 'F')
		return (c - 'A' + 10);
	return (0);
}

int	ft_atoi_base(const char *str, int str_base)
{
	int	neg;
	int	val;
	int	i;

	i = 0;
	val = 0;
	skip_space(str, &i);
	neg = val_signed(str, &i);
	if (is_in_base(&str[i], str_base, "0123456789abcdef") == 1
		|| is_in_base(&str[i], str_base, "0123456789ABCDEF") == 1)
	{
		while (str[i])
		{
			val *= str_base;
			val += base_val(str[i]);
			i += 1;
		}
	}
	return (val * neg);
}
