/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:12:54 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:27 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static char	*ft_strcpy(char *dest, const char *src)
{
	size_t	i;

	i = -1;
	while (src[++i])
		dest[i] = src[i];
	dest[i] = '\0';
	return (dest);
}

//Retourne le pointeur de la cpy de s
char	*ft_strdup(const char *s)
{
	char	*str;

	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (str != NULL)
		ft_strcpy(str, s);
	return (str);
}
