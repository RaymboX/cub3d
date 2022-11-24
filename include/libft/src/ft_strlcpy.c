/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 14:27:07 by mraymond          #+#    #+#             */
/*   Updated: 2022/11/23 14:44:24 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

// Copy scr in dst for dstsize char and add \0. Return src len
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize > 0)
	{
		i = -1;
		while (++i < dstsize - 1 && src[i] != '\0')
			dst[i] = src[i];
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}
