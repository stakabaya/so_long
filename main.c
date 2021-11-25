/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:04:23 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:23:23 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

void	put_error(char *str, t_game *game)
{
	write(2, "Error\n", 6);
	write(2, str, ft_strlen(str));
	ft_close(game);
}

void	init_images(t_game *g)
{
	g->tile_img = 0;
	g->pl_f_img = 0;
	g->pl_b_img = 0;
	g->pl_r_img = 0;
	g->pl_l_img = 0;
	g->collect_img = 0;
	g->wall_img = 0;
	g->elock_img = 0;
	g->eunlock_img = 0;
	g->clear_img = 0;
	g->black_img = 0;
}

void	init(t_game *g)
{
	g->mlx = 0;
	g->win = 0;
	g->imgh = 0;
	g->imgw = 0;
	g->maph = 0;
	g->mapw = 0;
	g->map = NULL;
	g->cmap = NULL;
	g->player_count = 0;
	g->collect_count = 0;
	g->exit_count = 0;
	g->game_key = 1;
	g->movecount = 0;
	g->is_first = 0;
	g->game_clear = 0;
	g->p_dir = FRONT;
	init_images(g);
	g->mlx = mlx_init();
	if (!g->mlx)
		put_error("mlx init error", g);
}

int	ft_close(t_game *game)
{
	ft_destroy_images(game);
	free_map(&game->map, game);
	if (game->cmap)
		free_map(&game->cmap, game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
		free(game->mlx);
	write(1, "\n", 1);
	exit(0);
	return (0);
}

int	main(int argc, char **argv)
{
	t_game	game;

	init(&game);
	get_map(argc, argv, &game);
	game_start(&game);
	return (1);
}
