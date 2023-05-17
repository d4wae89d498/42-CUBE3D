/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egiraldi <egiraldi@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 14:16:39 by egiraldi          #+#    #+#             */
/*   Updated: 2021/12/02 14:53:05 by egiraldi         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen_gnl(char const *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strnjoin(char *s1, char *s2, size_t n)
{
	char	*joined;
	size_t	i;
	size_t	j;

	joined = (char *) malloc(sizeof(char) * (ft_strlen_gnl(s1) + n + 1));
	if (!joined)
		return (NULL);
	i = 0;
	while (*s1)
	{
		joined[i] = *s1;
		i++;
		s1++;
	}
	j = 0;
	while (*s2 && j < n)
	{
		joined[i + j] = *s2;
		j++;
		s2++;
	}
	joined[i + j] = 0;
	return (joined);
}
