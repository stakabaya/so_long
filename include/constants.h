/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:25:29 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:27:46 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONSTANTS_H
# define CONSTANTS_H

# include "../GNL/get_next_line.h"
# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

# define TILE_SIZE				64

# define X_EVENT_KEY_PRESS		2
# define X_EVENT_KEY_EXIT		17
# define EVENT_FOCUSIN			9

# define K_A 					97
# define K_S 					115
# define K_D 					100
# define K_W 					119
# define K_R 					65363
# define K_L 					65361
# define K_ESC					65307

# define WALL					'1'
# define SPACE					'0'
# define COLLECTIVE				'C'
# define MAPEXIT				'E'
# define PLAYER					'P'

# define FRONT					0
# define BACK					1
# define LEFT					2
# define RIGHT					3

# define CAT_F "./assets/cat_center.xpm"
# define CAT_L "./assets/cat_left.xpm"
# define CAT_R "./assets/cat_right.xpm"
# define CAT_B "./assets/cat_back.xpm"
# define GRASS "./assets/grass.xpm"
# define PUMP "./assets/pumpkin.xpm"
# define TREE "./assets/tree.xpm"
# define EX_TREE "./assets/tree_exit.xpm"
# define CLEAR "./assets/game_clear.xpm"
# define EX_STAIR_LOCK "./assets/tree_exit.xpm"
# define EX_STAIR_UNLOCK "./assets/stair_exit.xpm"
# define BLACK "./assets/black.xpm"

typedef struct s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	int		w;
	int		h;

	int		imgh;
	int		imgw;
	void	*tile_img;
	void	*pl_f_img;
	void	*pl_l_img;
	void	*pl_b_img;
	void	*pl_r_img;
	void	*collect_img;
	void	*wall_img;
	void	*elock_img;
	void	*eunlock_img;
	void	*clear_img;
	void	*black_img;

	char	**map;
	char	**cmap;
	int		maph;
	int		mapw;
	int		player_count;
	t_pos	plpos;
	int		collect_count;
	t_pos	*colpos;
	int		exit_count;
	t_pos	*exitpos;
	int		game_key;
	int		movecount;
	int		is_first;
	int		game_clear;
	int		p_dir;
}				t_game;

void	check_filename(int argc, char **argv, t_game *game);
void	read_mapfile(char *filename, t_game *game);
void	get_map(int argc, char **argv, t_game *game);
void	read_mapfile(char *filename, t_game *game);
void	read_elements(t_game *game);
void	file_to_image(t_game *game);
void	put_error(char *str, t_game *game);
int		main_loop(t_game *game);
int		ft_close(t_game *game);
void	ft_destroy_images(t_game *game);
void	draw_player(t_game *game);
void	draw_field(t_game *game);
int		check_pdir(t_game *game, int x, int y);
void	free_map(char ***map, t_game *game);
void	game_start(t_game *game);

#endif
