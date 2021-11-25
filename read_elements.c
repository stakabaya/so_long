/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_elements.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 19:13:47 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:16:58 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

void	check_rectangular(t_game *game)
{
	int	i;
	int	len;
	int	should_len;

	i = 0;
	len = 0;
	should_len = 0;
	should_len = ft_strlen(game->map[i]);
	while (i < game->maph)
	{
		len = ft_strlen(game->map[i]);
		if (should_len != len)
			put_error("map is not rectangular", game);
		i++;
	}
	if ((game->maph * should_len) > (30 * 30))
		put_error("map is too big", game);
	i = 0;
	len = 0;
	mlx_get_screen_size(game->mlx, &len, &i);
	if (should_len * TILE_SIZE > len || game->maph * TILE_SIZE > i)
		put_error("map is bigger than screen size", game);
	game->mapw = should_len;
}

void	cut_space(t_game *game)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < game->maph)
	{
		tmp = ft_strtrim(game->map[i], " ");
		if (!tmp)
			put_error("malloc error", game);
		free(game->map[i]);
		free(game->cmap[i]);
		game->map[i] = ft_strdup(tmp);
		game->cmap[i] = ft_strdup(tmp);
		if (!game->map[i] || !game->cmap[i])
			put_error("malloc error", game);
		free(tmp);
		i++;
	}
	game->mapw = ft_strlen(game->map[0]);
}

void	keep_player_pos(t_game *game, int x, int y)
{
	game->player_count++;
	game->plpos.x = x;
	game->plpos.y = y;
	game->map[y][x] = '0';
}

void	count_elements(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (i < game->maph)
	{
		j = 0;
		while (game->map[i][j])
		{
			if (game->map[i][j] == PLAYER)
				keep_player_pos(game, j, i);
			if (game->map[i][j] == COLLECTIVE)
				game->collect_count++;
			if (game->map[i][j] == MAPEXIT)
				game->exit_count++;
			if (!ft_strchr("01PCE", game->map[i][j]))
				put_error("map has irregular input", game);
			j++;
		}
		i++;
	}
	if (game->player_count != 1)
		put_error("num of player error", game);
	if (game->collect_count < 1 || game->exit_count < 1)
		put_error("no collective or exit", game);
}

void	read_elements(t_game *game)
{
	check_rectangular(game);
	cut_space(game);
	count_elements(game);
}
