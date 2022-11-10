/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:17:39 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:59:16 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Return location of first char of the needle in haystack. If no needle, R null
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i[2];

	if (big == NULL || little == NULL)
		return (NULL);
	if (ft_strlen(little) == 0)
		return ((char *)big);
	i[0] = 0;
	while (big[i[0]] != '\0' && i[0] < len)
	{
		i[1] = 0;
		while (big[i[0] + i[1]] == little[i[1]]
			&& big[i[0] + i[1]] != '\0'
			&& little[i[1]] != '\0'
			&& i[0] + i[1] < len)
			i[1]++;
		if (little[i[1]] == '\0')
			return ((char *)&big[i[0]]);
		i[0]++;
	}
	return (NULL);
}
