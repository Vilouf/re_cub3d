/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vielblin <vielblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 11:35:38 by vielblin          #+#    #+#             */
/*   Updated: 2025/10/31 10:443:566 by vielblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

# ifndef WIN_WIDTH
#  define WIN_WIDTH 1024
# endif

# ifndef MOVE_SPEED
#  define MOVE_SPEED 0.05
# endif

# ifndef ROT_SPEED
#  define ROT_SPEED 0.03
# endif

# ifndef WIN_HEIGHT
# define WIN_HEIGHT 768
# endif

# ifndef KEY_ESC
#  define KEY_ESC 65307
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <MLX42/MLX42.h>
# include <math.h>

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

typedef struct s_list
{
	char			*data;
	struct s_list	*next;
}	t_list;

typedef struct s_ray
{
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	float	camera_x;
	float	ray_dir_x;
	float	ray_dir_y;
	float	side_dist_x;
	float	side_dist_y;
	float	delta_dist_x;
	float	delta_dist_y;
	float	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int32_t	color;
}	t_ray;

typedef struct s_struct
{
	t_gc		*gc;
	t_list		*lst_map;
	int			fd;
	char		*txt_no;
	char		*txt_so;
	char		*txt_we;
	char		*txt_ea;
	int			color_f[3];
	int			color_c[3];
	char		**map;
	mlx_t		*mlx;
	mlx_image_t	*img;
	float		x_pos;
	float		y_pos;
	float		dir_x;
	float		dir_y;
	float		plane_x;
	float		plane_y;
}	t_struct;

//garbage collector
void		gc_addback(t_gc_leaf **gc, t_gc_leaf *new);
void		*gc_malloc(t_gc *gc, size_t size);
void		gc_clear(t_gc_leaf **gc);
void		init_gc(t_gc **gc);
void		free_exit(t_gc *gc, int exit_status, char *message);
t_gc_leaf	*gc_lstnew(void *data);

//libft
void	ft_free(void *ntpr);
void	*ft_memset(void *s, int c, size_t n);
char	*get_next_line(int fd);
char	*ft_strchr2(const char *s, int c);
char	*ft_strjoin2(char *s1, char *s2);
size_t	ft_strlen2(const char *s);
int		ft_strlen(char *s);
char	*ft_substr2(char const *s, unsigned int start, size_t len);
void	*ft_calloc2(size_t count, size_t size);
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(t_gc *gc, char const *s, unsigned int start, size_t len);
char	**ft_split(char const *s, char c, t_gc *gc);
int		ft_strcmp(char *s1, char *s2);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *nptr);
char	*ft_strdup(t_gc *gc, const char *s);
t_list	*ft_lstnew(t_gc *gc, void *content);
void	ft_lstadd_back(t_list **lst, t_list *new);

// parsing
void	parsing(t_struct *data, char *file);
int		check_id(t_struct *data, char **words);
int		check_data(t_struct *data);
int		get_color(t_struct *data, char **tab, int type);
int		is_spawn_point(char c);
void	parse_map(t_struct *data);
int		is_map_valid(t_struct *data);

// game
void	game_hook(void *param);

#endif