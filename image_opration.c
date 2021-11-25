/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   10_image_opration.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stakabay <stakabay@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 09:01:11 by stakabay          #+#    #+#             */
/*   Updated: 2021/11/25 09:01:13 by stakabay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./include/constants.h"

void	file_to_image(t_game *g)
{
	g->tile_img = mlx_xpm_file_to_image(g->mlx, GRASS, &g->imgw, &g->imgh);
	g->pl_r_img = mlx_xpm_file_to_image(g->mlx, CAT_R, &g->imgw, &g->imgh);
	g->pl_l_img = mlx_xpm_file_to_image(g->mlx, CAT_L, &g->imgw, &g->imgh);
	g->pl_f_img = mlx_xpm_file_to_image(g->mlx, CAT_F, &g->imgw, &g->imgh);
	g->pl_b_img = mlx_xpm_file_to_image(g->mlx, CAT_B, &g->imgw, &g->imgh);
	g->collect_img = mlx_xpm_file_to_image(g->mlx, PUMP, &g->imgw, &g->imgh);
	g->wall_img = mlx_xpm_file_to_image(g->mlx, TREE, &g->imgw, &g->imgh);
	g->elock_img = mlx_xpm_file_to_image \
					(g->mlx, EX_STAIR_LOCK, &g->imgw, &g->imgh);
	g->eunlock_img = mlx_xpm_file_to_image \
					(g->mlx, EX_STAIR_UNLOCK, &g->imgw, &g->imgh);
	g->clear_img = mlx_xpm_file_to_image(g->mlx, CLEAR, &g->imgw, &g->imgh);
	g->black_img = mlx_xpm_file_to_image(g->mlx, BLACK, &g->imgw, &g->imgh);
	if (!g->tile_img || !g->pl_f_img || !g->pl_b_img || \
		!g->pl_l_img || !g->pl_r_img || !g->collect_img || \
		!g->wall_img || !g->elock_img || !g->clear_img || !g->black_img || \
		!g->eunlock_img)
		put_error("image init error", g);
}

void	ft_free_image(t_game *game, void *ptr)
{
	if (ptr)
	{
		mlx_destroy_image(game->mlx, ptr);
		ptr = NULL;
	}
}

void	ft_destroy_images(t_game *game)
{
	ft_free_image(game, game->tile_img);
	ft_free_image(game, game->pl_f_img);
	ft_free_image(game, game->pl_l_img);
	ft_free_image(game, game->pl_r_img);
	ft_free_image(game, game->pl_b_img);
	ft_free_image(game, game->black_img);
	ft_free_image(game, game->collect_img);
	ft_free_image(game, game->wall_img);
	ft_free_image(game, game->elock_img);
	ft_free_image(game, game->eunlock_img);
	ft_free_image(game, game->clear_img);
}
