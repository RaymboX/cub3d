/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr_i.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/04 14:54:13 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:22 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Return location(index) of first c in s. If no c in s, return -1 
int	ft_strchr_i(const char *s, int c)
{
	int		i;
	char	*str;
	char	tofind;

	str = (char *)s;
	tofind = (char)c;
	i = 0;
	while (str[i] != tofind && str[i] != '\0')
		i++;
	if (str[i] == tofind)
		return (i);
	else
		return (-1);
}
