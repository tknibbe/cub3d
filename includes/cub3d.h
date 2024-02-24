/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tknibbe <tknibbe@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:23:25 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/15 17:19:31 by tknibbe          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1920
# define HEIGHT 1080
# define HALF_HEIGHT 540.0
# define HALF_WIDTH 960.0
# define PI 3.1415926

# include "MLX42.h"
# include "minimap.h"
# include "sprites.h"
# include <stdio.h>
# include <stdlib.h>

typedef enum e_state
{
	NORMAL = 0,
	FLYING = 4,
	CROUCHING = 8
}	t_state;

typedef struct s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*icon;
	mlx_texture_t	*door;
	int				floor;
	int				ceiling;
}	t_textures;

typedef struct s_player
{
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
	double		fov;
	bool		has_moved;
	bool		is_dead;
	t_state		state;
}	t_player;

typedef struct s_images
{
	mlx_image_t	*minimap;
	mlx_image_t	*maze;
	mlx_image_t	*fps;
	mlx_image_t	*door_open_text;
	mlx_image_t	*door_close_text;
	mlx_image_t	*player;
	mlx_image_t	*game_over;
}	t_images;

typedef struct s_ray
{
	t_vector		ray;
	double			camerax;
	int				map_x;
	int				map_y;
	t_vector		side_dist;
	t_vector		block_dist;
	int				step_dir_x;
	int				step_dir_y;
	int				side;
	double			dist_to_wall;
	//-------------
	int				wall_height;
	int				wall_start;
	int				wall_end;
	int				tex_height;
	int				tex_width;
	double			wallx;
	int				texx;
	double			step;
	double			texpos;
	int				texy;
	int				y;
	uint32_t		colour;
	mlx_texture_t	*texture;
	uint8_t			door;
	//-------------
}	t_ray;

typedef struct s_game
{
	char		**map;
	int			map_cols;
	int			map_rows;
	int			sprite_nr;
	double		*wall_distances;
	int			*img_buffer;
	int			camera_height;
	t_textures	textures;
	t_player	player;
	t_images	images;
	t_minimap	minimap;
	t_sprite	*sprites;
	mlx_t		*mlx;
}	t_game;

void	loop_hook(void *param);
void	key_hook(mlx_key_data_t keydata, void *param);
void	fps_counter(void *mlxshit);
void	initialise_game(t_game *game, char *title);
void	initialise_player(t_game *game);
void	ft_mlx_error_and_exit(t_game *game);
void	ft_error_and_exit(char *error_str);
void	free_game_struct(t_game *game);
void	ray_caster(t_game *game);
void	movement(t_player *player, t_game *game);
void	cursor_hook(double xpos, double ypos, void *param);
void	rotate(t_player *player, int rotation);
void	setup_ray_vars(t_ray *ray_vars, t_player player, int screen_x);
double	fov(double a, double b);
void	line_to_buffer(t_game *game, t_ray ray_vars, int x);
void	check_door(void *game);
void	fix_textures(t_game *game);
bool	door_status(char **map, t_vector pos, char stat);
void	close_door(char **map, t_vector pos);
void	open_door(char **map, t_vector pos);
void	change_textures(t_game *game);
bool	check_death(t_game *game);
void	ft_exit_with_perror(void);

#endif