/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:35:38 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/22 13:56:51 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct s_gc_leaf
{
	void				*data;
	struct s_gc_leaf	*next;
}	t_gc_leaf;

typedef struct s_gc
{
	t_gc_leaf	*leaf;
	int			id;
}	t_gc;

typedef struct s_struct
{
	t_gc	*gc;
}	t_struct;

//garbage collector
void	gc_addback(t_gc_leaf **gc, t_gc_leaf *new);
void	*gc_malloc(t_gc *gc, size_t size);
void	gc_clear(t_gc_leaf **gc);
void	init_gc(t_gc **gc);
void	free_exit(t_gc *gc, int exit_status);

//libft
void	ft_free(void *ntpr);
void	*ft_memset(void *s, int c, size_t n);

#endif