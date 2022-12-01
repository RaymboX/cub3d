/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:15:00 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:40 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Add src to dst end + \0. Return len of dest after.
size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	i;

	dest_len = ft_strlen(dest);
	if (size > dest_len)
	{
		i = -1;
		while (++i < (size - dest_len - 1) && src[i] != '\0')
			dest[dest_len + i] = src[i];
		dest[dest_len + i] = '\0';
	}
	if (size < dest_len)
		return (size + ft_strlen(src));
	else
		return (dest_len + ft_strlen(src));
}
