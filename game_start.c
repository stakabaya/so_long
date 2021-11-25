/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_start.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 21:27:35 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:37:34 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

int	main_loop(t_game *game)
{
	char	*num;

	if (game->game_key == 1)
	{
		mlx_clear_window(game->mlx, game->win);
		draw_field(game);
		draw_player(game);
		num = ft_itoa(game->movecount);
		if (!num)
			put_error("malloc error", game);
		write(1, "\r", 1);
		write(1, "move = ", 7);
		write(1, num, ft_strlen(num));
		free(num);
	}
	game->game_key = 0;
	return (0);
}

void	check_move(t_game *g, int key)
{
	if (g->collect_count != 0)
	{
		if (key == K_W && ft_strchr("0C", g->map[g->plpos.y - 1][g->plpos.x]))
			g->plpos.y -= 1;
		if (key == K_S && ft_strchr("0C", g->map[g->plpos.y + 1][g->plpos.x]))
			g->plpos.y += 1;
		if (key == K_A && ft_strchr("0C", g->map[g->plpos.y][g->plpos.x - 1]))
			g->plpos.x -= 1;
		if (key == K_D && ft_strchr("0C", g->map[g->plpos.y][g->plpos.x + 1]))
			g->plpos.x += 1;
	}
	else
	{
		if (key == K_W && ft_strchr("0EC", g->map[g->plpos.y - 1][g->plpos.x]))
			g->plpos.y -= 1;
		if (key == K_S && ft_strchr("0EC", g->map[g->plpos.y + 1][g->plpos.x]))
			g->plpos.y += 1;
		if (key == K_A && ft_strchr("0EC", g->map[g->plpos.y][g->plpos.x - 1]))
			g->plpos.x -= 1;
		if (key == K_D && ft_strchr("0EC", g->map[g->plpos.y][g->plpos.x + 1]))
			g->plpos.x += 1;
	}
}

int	deal_key(int key, t_game *g)
{
	int	prex;
	int	prey;

	prex = g->plpos.x;
	prey = g->plpos.y;
	if (key == K_ESC)
		ft_close(g);
	else if (g->game_clear == 0)
		check_move(g, key);
	if (check_pdir(g, g->plpos.x - prex, g->plpos.y - prey))
		g->game_key = 1;
	if (g->map[g->plpos.y][g->plpos.x] == 'C')
	{
		g->collect_count--;
		g->map[g->plpos.y][g->plpos.x] = '0';
	}
	return (0);
}

int	ft_rerendering(t_game *game)
{
	mlx_clear_window(game->mlx, game->win);
	draw_field(game);
	draw_player(game);
	return (0);
}

void	game_start(t_game *game)
{
	game->win = mlx_new_window(game->mlx, TILE_SIZE * game->mapw, \
							TILE_SIZE * game->maph, "solong");
	file_to_image(game);
	mlx_loop_hook(game->mlx, &main_loop, game);
	mlx_hook(game->win, X_EVENT_KEY_PRESS, (1L << 0), &deal_key, game);
	mlx_hook(game->win, X_EVENT_KEY_EXIT, (1L << 17), &ft_close, game);
	mlx_hook(game->win, EVENT_FOCUSIN, (1 << 21), &ft_rerendering, game);
	mlx_loop(game->mlx);
}
