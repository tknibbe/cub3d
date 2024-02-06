/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tymonknibbe <tymonknibbe@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 15:23:25 by tknibbe           #+#    #+#             */
/*   Updated: 2024/02/05 15:20:40 by tymonknibbe      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define WIDTH 1080
# define HEIGHT 720
# define PI 3.1415926

# include "MLX42.h"
# include "minimap.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct	s_vector
{
	double	x;
	double	y;
}	t_vector;

typedef struct	s_sprite
{
	double	x;
	double	y;
}	t_sprite;

typedef struct s_textures
{
	mlx_texture_t	*north;
	mlx_texture_t	*east;
	mlx_texture_t	*south;
	mlx_texture_t	*west;
	mlx_texture_t	*icon;
	mlx_texture_t	*door;
	int	floor;
	int	ceiling;
}	t_textures;

typedef struct	s_player
{
	t_vector	pos; //decide on what kind of varbiable this shoudl be
	t_vector	dir;
	t_vector	plane;
	double		move_speed;
	double		rot_speed;
	double		fov;
	bool		has_moved;
}	t_player;

typedef struct	s_images
{
	mlx_image_t	*minimap;
	mlx_image_t	*maze;
	mlx_image_t	*fps;
	mlx_image_t *door_help;
	mlx_image_t	*player;
}	t_images;

typedef struct	s_ray
{
	t_vector	ray;
	double		camerax;
	int			map_x;
	int			map_y;
	t_vector	side_dist;
	t_vector	block_dist;
	int			step_dir_x;
	int			step_dir_y;
	int			side;
	double		dist_to_wall;
	//-------------
	int				wall_height;
	int				wall_start;
	int				wall_end;
	int				tex_height;
	int				tex_width;
	mlx_texture_t	*texture;
	uint8_t			door;
	//-------------
}	t_ray;

typedef struct	s_game
{
	char		**map;
	int			map_cols;
	int			map_rows;
	t_textures	textures;
	t_player	player;
	t_images	images;
	t_minimap	minimap;
	mlx_t		*mlx;
}	t_game;

void	key_hook(void *param);
void	fps_counter(void *mlxshit);
void	initialise_game(t_game *game, char *title);
void	ft_mlx_error_and_exit(t_game *game);
void	ft_error_and_exit(char *error_str);
void	free_game_struct(t_game *game);
void	initialise_player(t_game *game);
void	put_player_to_window(t_game *game);
void	draw_rays(t_game *game);
void	ray_caster(t_game *game);
void	movement(t_player *player, t_game *game);
void	cursor_hook(double xpos, double ypos, void *param);
void	rotate(t_player *player, int rotation);
void	setup_ray_vars(t_ray *ray_vars, t_player player, int screen_x);
double	fov(double a, double b);
void	line_to_buffer(int *buffer, t_game *game, t_ray ray_vars, int x);
void	buffer_to_img(int *buffer, mlx_image_t *img);
void	draw_sprites(t_game *game);
double	get_player_angle(t_vector dir);
void	load_door(t_game *game);
void	check_door(void *game);
void	open_door(t_game *game);
#endif