/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 12:47:25 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:48 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	s_len;
	size_t	i;
	char	*dst;

	if (s != NULL)
	{
		s_len = ft_strlen(s);
		dst = (char *)malloc(sizeof(char) * (s_len + 1));
		if (dst != NULL)
		{
			i = -1;
			while (s[++i] != '\0')
				dst[i] = f((unsigned int)i, (char)s[i]);
			dst[i] = '\0';
		}	
		return (dst);
	}
	else
		return (NULL);
}
