/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 19:54:18 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/08/22 13:10:48 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_read(char **combine, int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	char		*tmp;
	ssize_t		bytes_read;

	if (!combine || fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	bytes_read = 1;
	while (bytes_read != 0 && (!*combine || ft_strchr1(*combine, '\n') == NULL))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(*combine);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		tmp = ft_strjoin1(*combine, NULL);
		free(*combine);
		*combine = ft_strjoin1(tmp, buffer);
		free(tmp);
	}
	return (*combine);
}

static char	*sub_line(char *line)
{
	int	i;

	i = 0;
	if (!line || ft_strlen1(line) == 0)
		return (NULL);
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\n')
		i++;
	return (ft_substr1(line, 0, i));
}

static char	*rest_func(char *combine)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	j = 0;
	if (!combine)
		return (NULL);
	while (combine[i] != '\n' && combine[i] != '\0')
		i++;
	if (combine[i] == '\n')
		i++;
	if (combine[i] == '\0')
	{
		free(combine);
		return (NULL);
	}
	tmp = malloc(ft_strlen1(combine) - i + 1);
	if (!tmp)
		return (NULL);
	while (combine[i])
		tmp[j++] = combine[i++];
	tmp[j] = '\0';
	free(combine);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*combine;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	combine = append_read(&combine, fd);
	if (!combine)
		return (NULL);
	line = sub_line(combine);
	combine = rest_func(combine);
	return (line);
}
