/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:02:18 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:04 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Find first c in s and return location(ptr). If no c in s, return NULL
void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;
	char	*a;

	a = (char *)s;
	i = 0;
	while (i < n && a[i] != (char)c)
		i++;
	if (i < n)
		return ((void *)s + i);
	else
		return (NULL);
}
