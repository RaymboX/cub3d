/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 08:28:44 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:10 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//copy char data from src to dst for len long
char	*ft_memcpy(char *dst, const char *src, size_t len)
{
	size_t	i;

	if (dst != NULL || src != NULL)
	{
		i = -1;
		while (++i < len)
			dst[i] = src[i];
	}
	return (dst);
}
