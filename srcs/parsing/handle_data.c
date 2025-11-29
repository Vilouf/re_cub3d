/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:18:50 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/29 18:15:23 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	set_texture(t_struct *data, char **target, char *path)
{
	if (*target != NULL)
	{
		*target = NULL;
		return (0);
	}
	*target = ft_strdup(data->gc, path);
	return (1);
}

static int	check_direction(t_struct *data, char **words)
{
	if (!ft_strcmp(words[0], "NO"))
		return (set_texture(data, &data->txt_no, words[1]));
	else if (!ft_strcmp(words[0], "SO"))
		return (set_texture(data, &data->txt_so, words[1]));
	else if (!ft_strcmp(words[0], "WE"))
		return (set_texture(data, &data->txt_we, words[1]));
	else if (!ft_strcmp(words[0], "EA"))
		return (set_texture(data, &data->txt_ea, words[1]));
	return (0);
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
