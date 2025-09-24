/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/06 19:36:23 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/23 17:54:14 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	*ft_calloc2(size_t nmemb, size_t size)
{
	char	*ret;
	size_t	i;

	i = 0;
	ret = malloc(nmemb * size);
	if (ret == NULL)
		return (NULL);
	while (i < nmemb * size)
		ret[i++] = 0;
	return (ret);
}

size_t	ft_strlen2(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char	*ft_substr2(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ret;

	if (!s || start - len <= 0)
		return (NULL);
	i = 0;
	s_len = ft_strlen2(s);
	if (len > s_len - start)
		len = s_len - start;
	if (start > s_len)
		len = 0;
	ret = ft_calloc2((len + 1), sizeof(char));
	if (!ret)
		return (NULL);
	while (i < len && start < s_len)
	{
		ret[i] = s[start];
		i++;
		start++;
	}
	ret[i] = 0;
	return (ret);
}

char	*ft_strchr2(const char *s, int c)
{
	size_t	i;

	i = 0;
	while (s[i] != (char) c && s[i])
		i++;
	if (s[i] == (char) c)
		return ((char *) &s[i]);
	return (NULL);
}

char	*ft_strjoin2(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ret;

	if (!s1)
		s1 = ft_calloc2(1, sizeof (char));
	if (!s1 || !s2)
		return (NULL);
	i = -1;
	j = 0;
	ret = ft_calloc2(ft_strlen2(s1) + ft_strlen2(s2) + 1, sizeof (char));
	if (!ret)
		return (NULL);
	while (s1[++i])
		ret[i] = s1[i];
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = 0;
	free(s1);
	return (ret);
}
