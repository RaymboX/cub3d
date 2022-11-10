/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 11:46:32 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:59:24 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//retourne ptr s1 avec set en moins en debut & fin
char	*ft_strtrim(char const *s1, char const *set)
{
	long int	i[3];
	char		*dst;

	if (s1 == NULL && set == NULL)
		return (NULL);
	i[0] = 0;
	i[1] = ft_strlen(s1) - 1;
	while (ft_strchr(set, (int)s1[i[0]]) != NULL && i[0] <= i[1])
		i[0]++;
	while (ft_strchr(set, (int)s1[i[1]]) != NULL && i[1] >= i[0])
		i[1]--;
	dst = ft_substr(s1, i[0], i[1] - i[0] + 1);
	return (dst);
}
