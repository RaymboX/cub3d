/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:10:29 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:25 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Return location(ptr) of first c in s. If no c in s, return NULL 
char	*ft_strchr(const char *s, int c)
{
	size_t	i;
	char	*str;
	char	tofind;

	str = (char *)s;
	tofind = (char)c;
	i = 0;
	while (str[i] != tofind && str[i] != '\0')
		i++;
	if (str[i] == tofind)
		return (str + i);
	else
		return (NULL);
}
