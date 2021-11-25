/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 06:38:47 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 08:57:52 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

int	check_pdir(t_game *game, int x, int y)
{
	if (x == -1)
		game->p_dir = LEFT;
	else if (x == 1)
		game->p_dir = RIGHT;
	else if (y == -1)
		game->p_dir = BACK;
	else if (y == 1)
		game->p_dir = FRONT;
	if (x != 0 || y != 0)
	{
		game->movecount++;
		return (1);
	}
	return (0);
}

void	draw_exit(t_game *game, int i, int j)
{
	if (game->map[i][j] == MAPEXIT && game->collect_count)
		mlx_put_image_to_window(game->mlx, game->win, game->elock_img, \
								TILE_SIZE * j, TILE_SIZE * i);
	if (game->map[i][j] == MAPEXIT && !game->collect_count)
		mlx_put_image_to_window(game->mlx, game->win, game->eunlock_img, \
								TILE_SIZE * j, TILE_SIZE * i);
}

void	draw_field(t_game *game)
{
	int	i;
	int	j;

	i = -1;
	while (++i < game->maph)
	{
		j = -1;
		while (++j < game->mapw)
		{
			mlx_put_image_to_window(game->mlx, game->win, game->tile_img, \
									TILE_SIZE * j, TILE_SIZE * i);
			if (game->map[i][j] == WALL)
				mlx_put_image_to_window(game->mlx, game->win, game->wall_img, \
										TILE_SIZE * j, TILE_SIZE * i);
			if (game->map[i][j] == COLLECTIVE)
				mlx_put_image_to_window(game->mlx, game->win, \
										game->collect_img, \
										TILE_SIZE * j, TILE_SIZE * i);
			draw_exit(game, i, j);
		}
	}
}

void	clear_image(t_game *game)
{
	int	i;

	i = 0;
	mlx_put_image_to_window(game->mlx, game->win, game->tile_img, \
							TILE_SIZE * game->plpos.x, \
							TILE_SIZE * game->plpos.y);
	mlx_put_image_to_window(game->mlx, game->win, game->eunlock_img, \
							TILE_SIZE * game->plpos.x, \
							TILE_SIZE * game->plpos.y);
	while (game->map[0][i] != '\0')
	{
		mlx_put_image_to_window(game->mlx, game->win, game->black_img, \
								TILE_SIZE * i, TILE_SIZE * 0);
		if (i % 2)
			mlx_put_image_to_window(game->mlx, game->win, game->clear_img, \
									TILE_SIZE * i, TILE_SIZE * 0);
		i++;
	}
	game->game_clear = 1;
}

void	draw_player(t_game *game)
{
	void	*img;

	if (game->p_dir == FRONT)
		img = game->pl_f_img;
	else if (game->p_dir == BACK)
		img = game->pl_b_img;
	else if (game->p_dir == LEFT)
		img = game->pl_l_img;
	else if (game->p_dir == RIGHT)
		img = game->pl_r_img;
	mlx_put_image_to_window(game->mlx, game->win, img, \
							TILE_SIZE * game->plpos.x, \
							TILE_SIZE * game->plpos.y);
	if (game->map[game->plpos.y][game->plpos.x] == 'E' && \
		game->collect_count == 0)
		clear_image(game);
}
