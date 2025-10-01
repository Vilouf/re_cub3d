/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:45:30 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/01 15:49:27 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

static void	*alloc_words(const char *str, char c, t_gc *gc)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (gc_malloc(gc, (count + 1) * sizeof(char *)));
}

static char	*copy_word(const char *str, size_t start, size_t end, t_gc *gc)
{
	char		*word;
	size_t		i;

	word = gc_malloc(gc, (end - start + 1) * sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (start < end)
	{
		word[i] = str[start];
		start++;
		i++;
	}
	word[i] = '\0';
	return (word);
}

static size_t	prepare_word(const char *s, size_t *i, char c)
{
	size_t	start;

	while (s[*i] && s[*i] == c)
		*i += 1;
	start = *i;
	while (s[*i] && s[*i] != c)
		*i += 1;
	return (start);
}

char	**ft_split(char const *s, char c, t_gc *gc)
{
	char		**result;
	size_t		i;
	size_t		j;
	size_t		start;

	if (!s)
		return (NULL);
	result = alloc_words(s, c, gc);
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (s[i])
	{
		start = prepare_word(s, &i, c);
		if (i > start)
		{
			result[j] = copy_word(s, start, i, gc);
			if (!result[j])
				return (NULL);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}
