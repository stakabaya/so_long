/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_get_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/03 11:01:11 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 00:33:31 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

void	check_filename(int argc, char **argv, t_game *game)
{
	int		len;

	if (argc != 2)
		put_error("invalid argument", game);
	len = ft_strlen(argv[1]);
	if (ft_memcmp((argv[1] + (len - 4)), ".ber", 4))
		put_error("invalid file extention", game);
}

void	free_map(char ***map, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->maph)
	{
		if ((*map)[i])
			free((*map)[i]);
		i++;
	}
	if (*map)
	{
		free(*map);
		*map = NULL;
	}
}

void	dfs_map(t_game *game, char ***cmap, int x, int y)
{
	if (x < 0 || y < 0 || y >= game->maph || \
		(*cmap)[y][x] == '\0' || (*cmap)[y][x] == ' ')
	{
		free_map(cmap, game);
		put_error("Wall has Hole", game);
	}
	if ((*cmap)[y][x] == '1' || (*cmap)[y][x] == 'g')
		return ;
	(*cmap)[y][x] = 'g';
	dfs_map(game, cmap, x + 1, y);
	dfs_map(game, cmap, x - 1, y);
	dfs_map(game, cmap, x, y + 1);
	dfs_map(game, cmap, x, y - 1);
}

void	get_map(int argc, char **argv, t_game *game)
{
	check_filename(argc, argv, game);
	read_mapfile(argv[1], game);
	read_elements(game);
	dfs_map(game, &(game->cmap), game->plpos.x, game->plpos.y);
	free_map(&game->cmap, game);
}
