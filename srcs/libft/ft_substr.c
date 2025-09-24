/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 16:26:51 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/24 16:31:46 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_substr(t_gc *gc, char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ret;

	if (!s)
		return (NULL);
	i = 0;
	s_len = ft_strlen2(s);
	if (len > s_len - start)
		len = s_len - start;
	if (start > s_len)
		len = 0;
	ret = gc_malloc(gc, (len + 1) * sizeof(char));
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
