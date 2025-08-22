/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ouel-afi <ouel-afi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:30:56 by ouel-afi          #+#    #+#             */
/*   Updated: 2025/08/22 13:11:45 by ouel-afi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# include <unistd.h>
# include <stdlib.h>

char	*get_next_line(int fd);
size_t	ft_strlen1(const char *s);
char	*ft_strdup1(const char *s1);
char	*ft_strjoin1(const char *s1, const char *s2);
char	*ft_substr1(char *s, unsigned int start, size_t len);
char	*ft_strchr1(const char *s, int c);

#endif