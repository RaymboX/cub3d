/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:04:11 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:56:47 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*l;

	if (!(lst))
		return (lst);
	l = lst;
	while (l->next != NULL)
		l = l->next;
	return (l);
}
