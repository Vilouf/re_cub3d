/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_init_free.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 04:58:24 by pespana           #+#    #+#             */
/*   Updated: 2025/09/22 13:58:18 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_exit(t_gc *gc, int exit_status)
{
	if (gc != NULL)
	{
		gc_clear(&(gc->leaf));
		ft_free(gc);
	}
	exit(exit_status);
}

void	init_gc(t_gc **gc)
{
	t_gc	*current;

	current = NULL;
	current = malloc(sizeof(t_gc));
	if (!current)
		free_exit(*gc, 1);
	ft_memset(current, 0, sizeof(t_gc));
	*gc = current;
}
