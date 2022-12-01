/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 14:16:33 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:58:20 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

//si word=0:Return nbword. Si word>0:Return index premier char du x mot
static size_t	nbword0_index(char const *str, char c, int word)
{
	size_t		i;
	int			nbword;

	nbword = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && (i == 0
				|| ((i > 0) && (str[i - 1] == (const char)c))))
			nbword += 1;
		if (word > 0 && nbword == word)
			return (i);
		i++;
	}
	return ((size_t)nbword);
}

static char	*ft_word(int word, char const *str, char c, size_t *iword_se)
{
	iword_se[0] = nbword0_index(str, c, word + 1);
	iword_se[1] = iword_se[0] + 1;
	while (str[iword_se[1]] != c && str[iword_se[1]] != '\0')
		iword_se[1]++;
	return ((char *)malloc(sizeof(char) * (iword_se[1] - iword_se[0] + 1)));
}

static void	ft_strncpy_range(char const *src, size_t *iword_se, char *dest)
{
	int	i;

	i = -1;
	while (++i + iword_se[0] < iword_se[1])
		dest[i] = src[i + iword_se[0]];
	dest[i] = '\0';
}

//Return a 
char	**ft_split(char const *s, char c)
{
	char	**split;
	int		nbword;
	int		iword;
	size_t	iword_se[2];

	if (s != NULL)
	{
		nbword = nbword0_index(s, c, 0);
		split = (char **)malloc(sizeof(char *) * (nbword + 1));
		if (split == NULL)
			return (NULL);
		iword = -1;
		while (++iword < nbword)
		{
			split[iword] = ft_word(iword, s, c, iword_se);
			ft_strncpy_range(s, iword_se, split[iword]);
		}
		split[iword] = NULL;
		return (split);
	}
	else
		return (NULL);
}
