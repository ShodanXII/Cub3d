/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 22:27:46 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 22:39:56 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (!ptr)
		return (malloc(new_size));
	if (new_size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new_ptr = malloc(new_size);
	if (!new_ptr)
		return (NULL);

	if (old_size < new_size)
		ft_memcpy(new_ptr, ptr, old_size);
	else
		ft_memcpy(new_ptr, ptr, new_size);
	free(ptr);
	return (new_ptr);
}

static int	is_valid_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == 32 || (line[i] >= 9 && line[i] <= 13))
		i++;
	return (line[i] && line[i] != '\n');
}

static void	append_line(t_map *map, char *line, int count)
{
	char	**tmp;

	tmp = realloc(map->map, sizeof(char *) * (count + 2));
	if (!tmp)
	{
		free(line);
		error("Memory reallocation failed");
	}
	map->map = tmp;
	map->map[count] = ft_strdup(line);
	if (!map->map[count])
		error("String duplication failed");
	map->map[count + 1] = NULL;
}

int	store_map(t_map *map, int fd)
{
	char	*line;
	int		count;

	count = 0;
	map->map = NULL;
	line = get_next_line(fd);
	while (line)
	{
		if (is_valid_line(line))
		{
			append_line(map, line, count);
			count++;
		}
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}
