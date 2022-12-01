#include "../include/cub3d.h"

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
