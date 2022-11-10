/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 15:25:26 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 13:00:09 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/get_next_line.h"
#include "../header/libft.h"

//trouve ou creer l'adresse du fd passer en argument
void	fd_findoralloc(int ptr_fd[NB_FD][BUFFER_SIZE + 2], int fd, t_index *s_i)
{
	while (ptr_fd[s_i->fd][0] != fd && ptr_fd[s_i->fd][0] != 0)
		s_i->fd++;
	if (ptr_fd[s_i->fd][0] == 0)
		ptr_fd[s_i->fd][0] = fd;
}

//calloc rtn + BUFFER_SIZE + 1, cpy old rtn and free
char	*rtn_calloc_n_cpy(char *str_rtn, t_index *s_i)
{
	char	*temp;

	temp = str_rtn;
	s_i->buf_loop += 1;
	str_rtn = (char *)ft_calloc(sizeof(char), BUFFER_SIZE * s_i->buf_loop + 1);
	if (str_rtn == NULL)
		return (NULL);
	if (s_i->buf_loop > 1)
	{
		ft_memmove(str_rtn, temp, BUFFER_SIZE * s_i->buf_loop);
		free(temp);
	}
	return (str_rtn);
}

//cpy 1 char from read to rtn, note last_cpy, put /0 to read, increment index
void	cpy_read_to_rtn(char *str_read, char *str_rtn, t_index *s_i,
	char *last_cpy)
{
	if (s_i->len_read > 0)
	{
		str_rtn[s_i->rtn] = str_read[s_i->read];
		*last_cpy = str_read[s_i->read];
		str_read[s_i->read] = '\0';
		s_i->read += 1;
		s_i->rtn += 1;
	}
	else
		*last_cpy = '\0';
}

//find index read, read if needed, rtn dynamic alloc if need, call cpy fct
char	*read_n_fill(char *str_read, char *str_rtn, t_index *s_i, int fd)
{
	char	last_cpy;

	while (s_i->read < BUFFER_SIZE && str_read[s_i->read] == '\0')
		s_i->read++;
	last_cpy = '0';
	while (last_cpy != '\n' && last_cpy != '\0')
	{
		if (s_i->read == BUFFER_SIZE)
		{
			s_i->len_read = read(fd, str_read, BUFFER_SIZE);
			if (s_i->len_read + 1 == 0)
				return (NULL);
			s_i->read = 0;
		}
		if (s_i->rtn == BUFFER_SIZE * s_i->buf_loop && s_i->len_read > 0)
		{
			str_rtn = rtn_calloc_n_cpy(str_rtn, s_i);
			if (str_rtn == NULL)
				return (NULL);
		}
		cpy_read_to_rtn(str_read, str_rtn, s_i, &last_cpy);
	}
	return (str_rtn);
}

//return ptr of next line to read on fd in argument (multiple fd)
char	*get_next_line(int fd)
{
	static int	ptr_fd[NB_FD][BUFFER_SIZE + 2] = {0};
	char		*str_rtn;
	t_index		s_i;

	s_i.fd = 0;
	s_i.read = 0;
	s_i.rtn = 0;
	s_i.buf_loop = 0;
	str_rtn = NULL;
	fd_findoralloc(ptr_fd, fd, &s_i);
	str_rtn = read_n_fill((char *)&ptr_fd[s_i.fd][1], str_rtn, &s_i, fd);
	if (str_rtn != NULL)
		ft_bzero(&str_rtn[s_i.rtn], BUFFER_SIZE * s_i.buf_loop + 1 - s_i.rtn);
	return (str_rtn);
}
