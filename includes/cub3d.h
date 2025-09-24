/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pespana <pespana@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:35:38 by vielblin          #+#    #+#             */
/*   Updated: 2025/09/23 18:52:09 by pespana          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

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
char	*get_next_line(int fd);
char	*ft_strchr2(const char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(const char *s);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
void	*ft_calloc2(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);

#endif