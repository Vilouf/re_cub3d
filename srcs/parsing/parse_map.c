/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 14:32:29 by vielblin          #+#    #+#             */
/*   Updated: 2025/11/14 00:52:02 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*set_map_line(char *line, int x, t_gc *gc)
{
	char	*ret;
	int		i;

	i = 0;
	ret = gc_malloc(gc, (x + 1) * sizeof(char));
	while (i < x)
	{
		if (i < ft_strlen(line) && line[i] != ' ')
			ret[i] = line[i];
		else
			ret[i] = '1';
		i++;
	}
	ret[i] = 0;
	return (ret);
}

static void	set_map(t_struct *data, int x)
{
	t_list	*tmp;
	int		i;

	tmp = data->lst_map;
	i = 0;
	while (tmp)
	{
		data->map[i] = set_map_line(tmp->data, x, data->gc);
		i++;
		tmp = tmp->next;
	}
	data->map[i] = NULL;
}

void	parse_map(t_struct *data)
{
	int		i;
	int		x;
	int		y;
	t_list	*tmp;

	tmp = data->lst_map;
	x = 0;
	y = 0;
	i = 0;
	while (tmp)
	{
		while (tmp->data[i])
			i++;
		if (i > x)
			x = i;
		i = 0;
		y++;
		tmp = tmp->next;
	}
	data->map = gc_malloc(data->gc, (y + 1) * sizeof(char *));
	set_map(data, x);
}
