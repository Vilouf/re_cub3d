/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:23:05 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/05 14:40:26 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((char *)dest)[i] = ((const char *)src)[i];
		i++;
	}
	return (dest);
}

static char	*strjoin_tab(t_gc *gc, char **tab)
{
	int		len;
	int		i;
	int		j;
	char	*ret;

	len = 0;
	i = 0;
	while (tab[i])
	{
		len += ft_strlen(tab[i]);
		i++;
	}
	ret = gc_malloc(gc, len + 1 * sizeof(char));
	j = 0;
	i = 0;
	while (tab[i])
	{
		ft_memcpy(&ret[j], tab[i], ft_strlen2(tab[i]));
		j += ft_strlen(tab[i]);
		i++;
	}
	return (ret);
}

static int	check_color_nums(char **nums)
{
	int	i;
	int	j;

	i = 0;
	if (!nums)
		return (0);
	while (nums[i])
	{
		j = 0;
		if (i == 3 || nums[i][j] == 0 || nums[i][j] == '\n')
			return (0);
		while (nums[i][j])
		{
			if (((nums[i][j] < '0' || nums[i][j] > '9')
				&& nums[i][j] != '\n') || j > 3)
			{
				return (0);
			}
			j++;
		}
		i++;
	}
	if (i < 3)
		return (0);
	return (1);
}

int	get_color(t_struct *data, char **tab, int type)
{
	char	**nums;
	char	*color;
	int		i;

	if (type == 1 && data->color_f[0] != -1)
		return (data->color_f[0] = -1, 0);
	else if (type != 1 && data->color_c[0] != -1)
		return (data->color_c[0] = -1, 0);
	color = strjoin_tab(data->gc, tab);
	nums = ft_split(color, ',', data->gc);
	if (!check_color_nums(nums))
		return (0);
	i = 0;
	while (i < 3)
	{
		if (type == 1)
			data->color_f[i] = ft_atoi(nums[i]);
		else
			data->color_c[i] = ft_atoi(nums[i]);
		i++;
	}
	return (1);
}
