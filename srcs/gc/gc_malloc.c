/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 03:45:49 by pespana           #+#    #+#             */
/*   Updated: 2025/09/22 13:57:33 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_gc_leaf	*gc_lstnew(void *data)
{
	t_gc_leaf	*gc;

	if (!data)
		return (NULL);
	gc = malloc(sizeof(t_gc_leaf));
	if (!gc)
		return (NULL);
	gc->data = data;
	gc->next = NULL;
	return (gc);
}

static void	*gc_malloc2(t_gc_leaf **leaf, size_t size)
{
	void		*ret;
	t_gc_leaf	*node;

	if (size < 1)
		return (NULL);
	ret = malloc(size);
	if (!ret)
		return (NULL);
	node = gc_lstnew(ret);
	if (!node)
		return (ft_free(ret), NULL);
	gc_addback(leaf, node);
	return (ret);
}

void	*gc_malloc(t_gc *gc, size_t size)
{
	void	*ret;
	t_gc	*head;

	head = gc;
	ret = gc_malloc2(&(gc->leaf), size);
	if (!ret)
		free_exit(gc, 1);
	return (ret);
}
