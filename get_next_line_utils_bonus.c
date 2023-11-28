/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohertzbe <ohertzbe@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 15:26:51 by ohertzbe          #+#    #+#             */
/*   Updated: 2023/11/27 15:26:56 by ohertzbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*ptr;

	ptr = (char *)s;
	i = 0;
	while (ptr[i])
	{
		if (ptr[i] == (char)c)
			return (&ptr[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&ptr[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	int		s1_len;
	int		s2_len;
	char	*new_s;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	s1_len = ft_strlen((char *)s1);
	s2_len = ft_strlen((char *)s2);
	new_s = (char *)malloc((s1_len + s2_len) + 1);
	if (!new_s)
		return (NULL);
	while (j < s1_len)
		new_s[i++] = s1[j++];
	j = 0;
	while (j < s2_len)
		new_s[i++] = s2[j++];
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_substr(char	const *s, unsigned int start, size_t len)
{
	char			*sub;
	unsigned int	i;
	unsigned int	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start > s_len || len == 0 || !s)
		return ((char *)ft_calloc(1, 1));
	s_len = ft_strlen(s + start);
	if (s_len > len)
		s_len = len;
	sub = (char *)malloc(sizeof(char) * (s_len + 1));
	if (!sub)
		return (NULL);
	i = 0;
	while ((s[i + start]) && i < len)
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	void	*p;
	size_t	max_t;

	max_t = 0;
	max_t -= 1;
	if (count > 0 && size > 0 && ((max_t / count) < size))
		return (NULL);
	i = 0;
	p = malloc(size * count);
	if (!p)
		return (NULL);
	while (i < (count * size))
	{
		((char *)p)[i++] = 0;
	}
	return (p);
}
