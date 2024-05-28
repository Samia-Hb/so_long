/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shebaz <shebaz@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 10:41:22 by shebaz            #+#    #+#             */
/*   Updated: 2023/12/16 11:10:20 by shebaz           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strjoin(char *next_line, char *str)
{
	int		i;
	int		j;
	char	*result;

	i = 0;
	j = 0;
	if (!next_line)
	{
		next_line = malloc(1);
		next_line[0] = '\0';
	}
	if (!next_line || !str)
		return (NULL);
	result = malloc(ft_strlen(next_line) + ft_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (next_line[j])
		result[i++] = next_line[j++];
	j = 0;
	while (str[j])
		result[i++] = str[j++];
	result[i] = '\0';
	free (next_line);
	return (result);
}

char	*ft_read(char *next_line, int fd)
{
	char	*buffer;
	int		i;

	buffer = malloc((size_t)BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	i = 1;
	while (!check_new_line(next_line) && i != 0)
	{
		i = read(fd, buffer, BUFFER_SIZE);
		if (i == -1)
		{
			free(next_line);
			free(buffer);
			return (NULL);
		}
		buffer[i] = '\0';
		next_line = ft_strjoin(next_line, buffer);
	}
	free(buffer);
	return (next_line);
}

char	*get_next_line(int fd)
{
	static char	*next_line[MAX_FD];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	next_line[fd] = ft_read(next_line[fd], fd);
	if (!next_line[fd])
		line = NULL;
	else
		line = extract_line(next_line[fd]);
	next_line[fd] = ft_update(next_line[fd]);
	return (line);
}
