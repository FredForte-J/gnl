/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fforte-j <fforte-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 19:15:45 by fforte-j          #+#    #+#             */
/*   Updated: 2024/11/28 21:14:18 by fforte-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	character;

	character = c;
	while (*s)
	{
		if (*s == character)
			return ((char *)s);
		s++;
	}
	if (character == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	int		total_len;
	int		i;

	i = 0;
	total_len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc(sizeof(char) * (total_len + 1));
	if (joined == NULL)
		return (NULL);
	while (*s1)
	{
		joined[i] = *s1;
		s1++;
		i++;
	}
	while (*s2)
	{
		joined[i] = *s2;
		s2++;
		i++;
	}
	joined[i] = '\0';
	return (joined);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*string;

	string = (unsigned char *)s;
	while (n >= 1)
	{
		*string = 0;
		n--;
		string++;
	}
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	t_size;
	void	*alloc;

	if (count == 0 || size == 0)
	{
		count = 1;
		size = 1;
	}
	if (count > ((size_t)-1 / size))
		return (NULL);
	t_size = count * size;
	alloc = malloc(t_size);
	if (alloc == NULL)
		return (NULL);
	else
		ft_bzero(alloc, t_size);
	return (alloc);
}

size_t	ft_strlen(const char *s)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		count++;
		s++;
	}
	return (count);
}
