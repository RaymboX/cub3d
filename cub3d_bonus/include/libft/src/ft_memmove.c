/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 09:56:33 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:13 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

static int	mem_overlap(char *d, char *s, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len && &s[i] != d)
		i++;
	if (i == len)
		return (0);
	return (1);
}

//Copy src in dst for len char ovoiding overlaping problem
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;
	int		way;

	if (dst != NULL || src != NULL)
	{
		d = (char *)dst;
		s = (char *)src;
		i = 0;
		way = 1;
		if (mem_overlap(d, s, len))
		{
			i = len - 1;
			way = -1;
		}
		while (i < len)
		{
			d[i] = s[i];
			i += way;
		}
	}
	return (dst);
}
