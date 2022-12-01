/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:28:15 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:37 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Return ptr de s1 + s2 + '\0'
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	char	*dst;
	size_t	s_len[2];

	if (s1 != NULL && s2 != NULL)
	{
		s_len[0] = ft_strlen(s1);
		s_len[1] = ft_strlen(s2);
		dst = (char *)malloc(sizeof(char) * (s_len[0] + s_len[1]) + 1);
		if (dst != NULL)
		{
			i = -1;
			while (++i < s_len[0])
				dst[i] = s1[i];
			i = -1;
			while (++i < s_len[1])
				dst[i + s_len[0]] = s2[i];
			dst[i + s_len[0]] = '\0';
		}
		return (dst);
	}
	else
		return (NULL);
}
