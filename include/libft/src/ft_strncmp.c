/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/28 13:16:26 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:59:13 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//Return the ascii diff of s1 & s2. If s1 = s2, return 0
int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc1;
	unsigned char	*uc2;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	while (uc1[i] != '\0' && uc1[i] == uc2[i] && i < n - 1 && n > 0)
		i++;
	if (n == 0)
		return (0);
	else
		return ((int)(uc1[i] - uc2[i]));
}
