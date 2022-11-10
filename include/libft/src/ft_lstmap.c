/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 08:09:05 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:56:50 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"
#define SRC 0
#define NEW 1
#define NEXT 2

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*l[3];

	if (lst == NULL)
		return (NULL);
	l[NEW] = NULL;
	l[SRC] = lst;
	while (l[SRC] != NULL)
	{
		l[NEXT] = ft_lstnew(f(l[SRC]->content));
		if (l[NEXT] == NULL)
		{
			ft_lstclear(&l[NEW], del);
			return (NULL);
		}
		ft_lstadd_back(&l[NEW], l[NEXT]);
		l[SRC] = l[SRC]->next;
	}
	return (l[NEW]);
}
