/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:48:39 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 22:48:51 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	header_map(t_data *data, char *line, int count, int *parsed_count)
{
	char	**work;

	work = ft_split(line, count);
	if (strcmp(work[0], "NO") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "SO") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "EA") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "WE") == 0)
		parse_side(data, work, count, parsed_count);
	else if (strcmp(work[0], "F") == 0)
		parse_fc(data, work, count, parsed_count);
	else if (strcmp(work[0], "C") == 0)
		parse_fc(data, work, count, parsed_count);
	else
		error("Invalid identifier");
	free_split(work);
}

void	skip_whitespace(char **line, int *i)
{
	while ((*line)[*i] == 32 || ((*line)[*i] >= 9 && (*line)[*i] <= 13))
		(*i)++;
}

int	process_line(t_map *map, t_data *data, char *line,
				int *parsed_count)
{
	int	count;
	int	i;

	count = count_words(line, 32, ',');
	i = 0;
	skip_whitespace(&line, &i);
	if (!line[i] || line[i] == '\n')
		return (0);
	if (*parsed_count != 6)
		header_map(data, line, count, parsed_count);
	return (1);
}

int	parsing(t_map *map, int fd, t_data *data)
{
	char	*line;
	int		parsed_count;

	parsed_count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (!process_line(map, data, line, &parsed_count))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (parsed_count == 6)
		{
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}
