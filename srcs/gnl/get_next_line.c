/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:16:58 by egiraldi          #+#    #+#             */
/*   Updated: 2021/12/02 14:54:55 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_find_index(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-42);
}

static void	ft_shift_buffer(char buffer[BUFFER_SIZE + 1], int n)
{
	size_t	i;

	i = 0;
	while (n > 0 && n + i < BUFFER_SIZE + 1)
	{
		buffer[i] = buffer[n + i];
		i++;
	}
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = 0;
		i++;
	}
}

static void	ft_join_buffer(char **line, char buffer[BUFFER_SIZE + 1], int n)
{
	char	*temp;
	size_t	tojoinlen;

	if (n < 0)
		tojoinlen = ft_strlen_gnl(buffer);
	else
		tojoinlen = n;
	if (!*line && !ft_strlen_gnl(buffer))
		return ;
	if (!*line)
		*line = ft_strnjoin((char *)"", buffer, tojoinlen);
	else
	{
		temp = *line;
		*line = ft_strnjoin(*line, buffer, tojoinlen);
		free(temp);
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	int			newline_idx;

	line = NULL;
	while (42)
	{
		newline_idx = ft_find_index(buffer, '\n');
		ft_join_buffer(&line, buffer, newline_idx + 1);
		ft_shift_buffer(buffer, newline_idx + 1);
		if (0 <= newline_idx)
			return (line);
		if (read(fd, buffer, BUFFER_SIZE) <= 0)
			return (line);
	}
}
