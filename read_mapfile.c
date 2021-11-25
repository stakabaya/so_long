/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_read_mapfile.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 13:10:42 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:04:58 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

int	is_first_line(char **tmp, t_game *game)
{
	if (!game->is_first && (*tmp)[0] == '\0')
	{
		free(*tmp);
		return (0);
	}
	else
		game->is_first = 1;
	return (1);
}

void	count_maph_and_malloc_map(t_game *game, char *filename)
{
	int		fd;
	int		eol;
	char	*tmp;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		put_error("file can't open", game);
	eol = 1;
	while (eol == 1)
	{
		eol = get_next_line(fd, &tmp);
		if (eol < 0)
			put_error("GNL error", game);
		game->maph++;
		free(tmp);
	}
	game->map = malloc(sizeof(char *) * (game->maph + 1));
	game->cmap = malloc(sizeof(char *) * (game->maph + 1));
	if (!game->map || !game->cmap)
		put_error("malloc error", game);
	game->map[game->maph] = NULL;
	game->cmap[game->maph] = NULL;
	close(fd);
}

void	read_mapfile(char *filename, t_game *game)
{
	int		fd;
	int		eol;
	char	*tmp;

	eol = 1;
	count_maph_and_malloc_map(game, filename);
	game->maph = 0;
	fd = open(filename, O_RDONLY);
	while (eol == 1)
	{
		eol = get_next_line(fd, &tmp);
		if (eol == -1)
			put_error("GNL error", game);
		if (!is_first_line(&tmp, game))
			continue ;
		game->map[game->maph] = ft_strdup(tmp);
		game->cmap[game->maph] = ft_strdup(tmp);
		if (!game->map[game->maph] || !game->cmap[game->maph])
			put_error("malloc error", game);
		free(tmp);
		game->maph++;
	}
	close(fd);
}
