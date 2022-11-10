/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 11:07:32 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:57:54 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

void	ft_putendl_fd(char *s, int fd)
{
	if (s != NULL)
	{
		write (fd, s, ft_strlen(s));
		write (fd, "\n", 1);
	}
}
