/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_str_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 12:49:44 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/30 12:50:27 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//return 0 if str contain only digit
int	ft_is_str_digit(char *str)
{
	int	i;

	if (str == NULL)
		return (1);
	i = 0;
	while (str[i] && ft_isdigit((int)str[i]) == 1)
		i++;
	if (str[i] != '\0')
		return (2);
	return (0);
}
