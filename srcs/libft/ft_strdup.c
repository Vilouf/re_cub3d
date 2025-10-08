/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 13:05:35 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/08 13:08:20 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

char	*ft_strdup(t_gc *gc, const char *s)
{
	int		i;
	char	*dest;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	dest = gc_malloc(gc, (i + 1) * sizeof(char));
	i = 0;
	while (s[i] && s[i] != '\n')
	{
		dest[i] = s[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}
