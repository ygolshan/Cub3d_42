/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akhodara <akhodara@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 17:46:49 by ygolshan          #+#    #+#             */
/*   Updated: 2023/09/25 17:48:32 by akhodara         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"

# define WIN_SIZE_W 1080
# define WIN_SIZE_H 720

# define TILE_SIZE 64

# define MAX_MAP_PARAMS 6

# define KEY_COUNT 256

# define FOV_ANGLE 60.0

# define THREE_DEG 0.0523599

# define MOVESTEP 0.3

# define MINI_WIN_SIZE 400

typedef struct s_point
{
	double	x;
	double	y;
	double	dirx;
	double	diry;
}	t_point;

typedef struct s_ray
{
	t_point	ray_dir;
	t_point	side_dist;
	t_point	delta_dist;
	int		map_x;
	int		map_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;
	int		side;
	double	ratio;
}			t_ray;

enum e_orientations
{
	NORD = 1,
	SOUTH,
	EAST,
	WEST
} ;

typedef struct s_node
{
	int				id;
	int				status;
	char			*box;
	char			*type;
	struct s_node	*next;
	struct s_node	*prev;
}	t_node;

typedef struct s_fetch
{
	t_node		*colors;
	t_node		*map;
	t_node		*p_t;
	t_node		*checks;
	char		**paths_mtx;
	char		**map_mtx;
	char		*colors_str;
	int			len;
}	t_fetch;

typedef struct s_data
{
	void	*img;
	void	*img2;
	char	*addr;
	char	*addr2;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_player
{
	float	angle;
	double	x;
	double	y;
	double	dirx;
	double	diry;
	t_point	plane;
	float	wd;
}	t_player;

typedef struct s_img_info
{
	unsigned int	*buf;
	int				bpp;
	int				size_line;
	int				endian;
	int				width;
	int				height;

}					t_img_info;

typedef struct s_graphic_info
{
	void			*img;
	void			*texture[4];
	int				color[2];
	t_img_info		img_info;
	t_img_info		texture_info[4];
}					t_graphic_info;

typedef struct s_render_info
{
	double					tex_pos;
	int						tex_x;
	int						tex_y;
	double					ratio;
	int						line_height;
	int						start_y;
	int						end_y;
}							t_render_info;

typedef struct s_rgB {
	int	r;
	int	g;
	int	b;
}	t_rgB;

typedef struct s_cub
{
	t_fetch			*fetched;
	t_data			*data;
	int				floor_color;
	int				ceil_color;
	t_rgB			colorr;
	t_player		player_pos;
	t_graphic_info	graphic_info;
	void			*mlx;
	void			*win;
	char			*str_tmp;
	char			**mat_tmp;
	char			**map;
	char			**minimap;
	char			*wall_imgs_addrs[5];
	char			*wall_imgs[4];
	int				player_existence;
	int				key_state[KEY_COUNT];
}	t_cub;

void			start_game(t_cub *cub);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			render(t_cub *cub);
int				validate_map_file(char *map_path);
int				game_init(t_cub *cub);
void			init_fetch(t_cub *cub);
void			init_img(t_graphic_info *graphic_info, t_cub *cub);
void			setup_graphic(t_graphic_info *graphic_info, t_cub *cub);
void			*create_image(void *mlx_ptr, char *xpmFile, t_cub *cub);
void			load_images(t_cub *cub);
int				standard_map(t_cub **cub);
int				map_checks(t_cub **cub, int i);
int				validate_map(t_cub **cub);
int				render_minimap(t_cub *cub);
int				count_rows_in_matrix(char **matrix);
void			try_move(t_cub *cub, int key);
void			draw_rays(t_cub *cub, float mapw, int b_size);
void			render_ray(t_cub *cub, t_ray *ray);
void			render_line(t_player *sp, t_player *ep, t_cub *cub);
void			render_horizontal_line(t_player *sp, t_player *ep, t_cub *cub);
void			render_vertical_line(t_player *sp, t_player *ep, t_cub *cub);
int				update_information(t_node **info, t_fetch *fetched);
int				parser(int fd, t_cub *cub);
char			*process_line_spaces(char *box);
int				adjust_info_data(t_node **info, t_fetch *fetched);
int				check_data_presence(t_node *info, t_fetch *fetched);
int				check_first_and_last_wall(char *box, int *k);
int				check_wall_row(char *box);
int				valid_char(char c);
void			ft_cpychar(char c, char **out);
int				ft_strcmp(char *s1, char *s2);
void			render_player(t_cub *cub);
void			render_game_screen(t_cub *cub);
void			add_walls(t_cub *cub);
void			set_player_data(t_cub *cub);
void			set_player_orientation(t_cub *cub);
void			set_player_initial_position(t_cub *cub);
void			set_player_plane_direction(t_cub *cub);
int				end_key_motion(int key, t_cub *cub);
int				move(int key, t_cub *cub);
int				process_moves(t_cub *cub, int key);
int				check_wall_collision(t_cub *cub, int key);
void			adjust_player_position(t_cub *tmp, int key);
void			adjust_player_rotation(t_cub *cub, int key, double angle);
t_ray			calculate_raycast(t_cub *cub, char **map, double camera_x);
void			configure_ray(t_cub *cub, t_ray *ray, double camera_x);
void			set_perpendicular_distance(t_ray *ray, t_player *pos);
void			adjust_ray(t_ray *ray, int axis);
void			configure_step(t_ray *ray);
void			delta_dist(t_ray *ray);
void			calculate_side_distances(t_ray *ray, t_player pos);
t_render_info	render_info(t_ray *ray, t_player *player);
unsigned int	get_img_pixel_color(t_img_info *img_info, int x, int y);
int				calculate_texture_x(t_player *player, t_ray *ray);
void			draw_safe_pixel(t_img_info *img_info, int x, int y, int color);
void			close_and_free_resources(t_cub *cub, char *mex);
int				exit_hook(t_cub *cub);
int				validate_rgb_format(char *box);
int				skip_non_digit_characters(char *box, int *k, int *nvalue);
int				build_rgb_value(char *box, int *k, int *h, char c[4]);
int				fetch_rgb_value(t_cub **cub, char c[4], int nvalue, int i);
int				split_information(t_node *info, t_cub **cub);
void			add_head(t_node **head, t_node *newnode);
void			add_tail(t_node **head, t_node *newnode);
void			delete_head(t_node **head);
void			delete_tail(t_node **head);
char			**node_list_to_matrix(t_node **head);
t_node			*matrix_to_list(char **matrix);
t_node			*new_(char *content, int id);
void			free_list(t_node **h);
void			relist_nodes(t_node **h);
void			free_content(t_node	*h);
char			*ft_strstr(char *str, char *to_find);

#endif
