/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achat <achat@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:44:03 by achat             #+#    #+#             */
/*   Updated: 2025/11/09 22:13:20 by achat            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*free_split(char **split, int j)
{
	int	k;

	if (!split)
		return (NULL);
	k = 0;
	while (k < j)
	{
		free(split[k]);
		k++;
	}
	free(split);
	return (NULL);
}

static char	**my_split(char const *s, char **split, int end, int count)
{
	int	j;
	int	start;

	j = 0;
	start = 0;
	split = malloc((count + 1) * sizeof(char *));
	if (!s || !split)
		return (NULL);
	while (s[end])
	{
		while (s[end] == 32 || s[end] == ',')
			end++;
		if (s[end] != '\0')
		{
			start = end;
			while (s[end] && s[end] != 32 && s[end] != ',')
				end++;
			split[j] = ft_substr(s, start, end - start);
			if (!split[j])
				return (free_split(split, j));
			j++;
		}
	}
	split[j] = NULL;
	return (split);
}

char	**ft_split(char const *s, int count)
{
	char	**split;
	int		i;

	split = NULL;
	i = 0;
	return (my_split(s, split, i, count));
}
