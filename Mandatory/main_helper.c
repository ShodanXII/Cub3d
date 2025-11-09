/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 21:53:31 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 21:53:47 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	char	*trimmed;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	end = ft_strlen(s1);
	while (end > start && ft_strchr(set, s1[end - 1]))
		end--;
	trimmed = malloc(sizeof(char) * (end - start + 1));
	if (!trimmed)
		return (NULL);
	ft_strlcpy(trimmed, s1 + start, end - start + 1);
	return (trimmed);
}

void	free_split(char **split)
{
	int	i;

	if (!split)
		return ;
	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}

void	add_data(t_data *data, char *identifier, char *value)
{
	if (!strcmp(identifier, "NO"))
	{
		if (data->map->no_path)
			error("Duplicate NO texture");
		data->map->no_path = ft_strdup(value);
	}
	else if (!strcmp(identifier, "SO"))
	{
		if (data->map->so_path)
			error("Duplicate SO texture");
		data->map->so_path = ft_strdup(value);
	}
	else if (!strcmp(identifier, "EA"))
	{
		if (data->map->ea_path)
			error("Duplicate EA texture");
		data->map->ea_path = ft_strdup(value);
	}
	else if (!strcmp(identifier, "WE"))
	{
		if (data->map->we_path)
			error("Duplicate WE texture");
		data->map->we_path = ft_strdup(value);
	}
}

void	add_color(t_data *data, char **values)
{
	int	r;
	int	g;
	int	b;

	r = ft_atoi(values[1]);
	g = ft_atoi(values[2]);
	b = ft_atoi(values[3]);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		error("Invalid color values (0-255)");
	if (!strcmp(values[0], "F"))
	{
		if (data->map->f_rgb[0] != 0)
			error("Duplicate floor color");
		data->map->f_rgb[0] = r;
		data->map->f_rgb[1] = g;
		data->map->f_rgb[2] = b;
	}
	else if (!strcmp(values[0], "C"))
	{
		if (data->map->c_rgb[0] != 0)
			error("Duplicate ceiling color");
		data->map->c_rgb[0] = r;
		data->map->c_rgb[1] = g;
		data->map->c_rgb[2] = b;
	}
}

void	error(char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
