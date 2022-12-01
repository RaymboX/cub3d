/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   various_tools_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anhebert <anhebert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 14:16:57 by mraymond          #+#    #+#             */
/*   Updated: 2022/12/01 11:30:38 by anhebert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d_bonus.h"

char	*ft_strcat(char *s1, int len)
{
	char	*new;
	int		i;
	int		ii;

	i = 0;
	ii = 0;
	new = malloc(sizeof(char) * len + 1);
	if (!new)
		return (NULL);
	while (s1[i] && s1[i] != '\n')
	{
		new[ii++] = s1[i++];
	}
	while (ii < len)
		new[ii++] = ' ';
	new[ii] = '\0';
	free(s1);
	return (new);
}

int	ft_strlen_nl(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0' && str[i] != '\n')
	{
		i++;
		len++;
	}
	return (len);
}
