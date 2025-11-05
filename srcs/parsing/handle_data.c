/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:18:50 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/05 15:18:48 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_direction(t_struct *data, char **words)
{
	if (!ft_strcmp(words[0], "NO"))
	{
		if (data->txt_no != NULL)
			return (data->txt_no = NULL, 0);
		data->txt_no = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "SO"))
	{
		if (data->txt_so != NULL)
			return (data->txt_so = NULL, 0);
		data->txt_so = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "WE"))
	{
		if (data->txt_we != NULL)
			return (data->txt_we = NULL, 0);
		data->txt_we = ft_strdup(data->gc, words[1]);
	}
	else if (!ft_strcmp(words[0], "EA"))
	{
		if (data->txt_ea != NULL)
			return (data->txt_ea = NULL, 0);
		data->txt_ea = ft_strdup(data->gc, words[1]);
	}
	else
		return (0);
	return (1);
}

int	check_id(t_struct *data, char **words)
{
	if (!words || !ft_strcmp(words[0], "\n"))
		return (1);
	if (check_direction(data, words))
		return (1);
	if (!ft_strcmp(words[0], "F"))
		return (get_color(data, &words[1], 1));
	if (!ft_strcmp(words[0], "C"))
		return (get_color(data, &words[1], 2));
	return (0);
}

int	check_data(t_struct *data)
{
	int	i;

	if (data->txt_no == NULL || data->txt_so == NULL
		|| data->txt_we == NULL || data->txt_ea == NULL)
		return (0);
	i = 0;
	while (i < 3)
	{
		if (data->color_c[i] < 0 || data->color_c[i] > 255)
			return (0);
		if (data->color_f[i] < 0 || data->color_f[i] > 255)
			return (0);
		i++;
	}
	return (1);
}
