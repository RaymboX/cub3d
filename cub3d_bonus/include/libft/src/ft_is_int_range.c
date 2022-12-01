/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_int_range.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:48:11 by mraymond          #+#    #+#             */
/*   Updated: 2022/09/07 14:30:51 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

/*return 0: GOOD -> val is a int and in range 
Error list: 1:val null 2:nb_char > max/min int 3:not only digit 
4:over or lower than a int 5:under range min 6=over range max*/
int	ft_is_int_range(char *val, int min, int max)
{
	char	*char_int_min;
	int		len_int_min;

	if (val == NULL || ft_strlen(val) < 1)
		return (1);
	char_int_min = ft_itoa(INT_MIN);
	len_int_min = ft_strlen(char_int_min);
	free(char_int_min);
	if ((int)ft_strlen(val) > len_int_min)
		return (2);
	if (val[0] == '-' && ft_strlen(val) == 1)
		return (3);
	if (val[0] == '-' && ft_is_str_digit(val + 1) != 0)
		return (3);
	if (val[0] != '-' && ft_is_str_digit(val) != 0)
		return (3);
	if (ft_atoi(val) != ft_atol(val))
		return (4);
	if (ft_atoi(val) < min)
		return (5);
	if (ft_atoi(val) > max)
		return (6);
	return (0);
}
