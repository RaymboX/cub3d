/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:32:36 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:56:54 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*s_list;

	s_list = (t_list *)ft_calloc(1, sizeof(t_list));
	if (s_list == NULL)
		return (NULL);
	s_list->content = content;
	s_list->next = NULL;
	return (s_list);
}
