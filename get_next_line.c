/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:43:57 by ohertzbe          #+#    #+#             */
/*   Updated: 2023/11/28 20:42:02 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>

void	safe_free(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
}

char	*get_newline(char *buffer_pos)
{
	char	*line;
	int		i;

	i = 0;
	if (!buffer_pos || buffer_pos[i] == '\0')
		return (NULL);
	while (buffer_pos[i] != '\n' && buffer_pos[i] != '\0')
		i++;
	if (buffer_pos[i] == '\n')
		i += 2;
	else
		i++;
	line = (char *)malloc(i * (sizeof(char)));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer_pos[i] != '\n' && buffer_pos[i] != '\0')
	{
		line[i] = buffer_pos[i];
		i++;
	}
	if (buffer_pos[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*update_buffer(char **buffer_pos)
{
	char	*temp;
	int		i;

	i = 0;
	while ((*buffer_pos)[i] != '\n' && (*buffer_pos)[i] != '\0')
		i++;
	if ((*buffer_pos)[i] == '\0')
	{
		safe_free(buffer_pos);
		return (NULL);
	}
	temp = *buffer_pos;
	*buffer_pos = ft_substr(*buffer_pos, i + 1, ft_strlen(*buffer_pos + i));
	safe_free(&temp);
	if (!(*buffer_pos))
		return (NULL);
	return (*buffer_pos);
}

int	read_file(int fd, char **buffer_pos, ssize_t bytes_read)
{
	char	*temp;
	char	buffer[BUFFER_SIZE + 1];

	while (bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			safe_free(buffer_pos);
			return (-1);
		}
		buffer[bytes_read] = '\0';
		temp = *buffer_pos;
		*buffer_pos = ft_strjoin(*buffer_pos, buffer);
		if (!*buffer_pos)
		{
			safe_free(&temp);
			return (-1);
		}
		safe_free(&temp);
		if (ft_strchr(*buffer_pos, '\n'))
			break ;
	}
	return (0);
}

char	*get_next_line(int fd)
{
	static char	*buffer_pos;
	char		*new_line;
	ssize_t		bytes_read;

	if (fd < 0)
		return (NULL);
	if (!buffer_pos)
	{
		buffer_pos = (char *)ft_calloc(1, 1);
		if (!buffer_pos)
			return (NULL);
	}
	bytes_read = 1;
	if (read_file(fd, &buffer_pos, bytes_read) < 0)
		return (NULL);
	new_line = get_newline(buffer_pos);
	if (!new_line)
	{
		safe_free(&buffer_pos);
		return (NULL);
	}
	buffer_pos = update_buffer(&buffer_pos);
	return (new_line);
}
