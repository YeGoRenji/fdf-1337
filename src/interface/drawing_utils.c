/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:41:51 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 16:51:20 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

void	get_direction(t_point *pt1, t_point *pt2, t_dir *dir)
{
	dir->x = 1;
	dir->y = 1;
	if (pt2->y < pt1->y)
		dir->y = -1;
	if (pt2->x < pt1->x)
		dir->x = -1;
}

int	handle_y_x(t_point *pt1, t_point *pt2)
{
	int	y_x_flip;

	y_x_flip = 0;
	if (ft_abs(pt2->y - pt1->y) > ft_abs(pt2->x - pt1->x))
	{
		y_x_flip = 1;
		ft_swap(&pt1->x, &pt1->y);
		ft_swap(&pt2->x, &pt2->y);
	}
	return (y_x_flip);
}

void	handle_aa(t_vars *vars, t_point *to_draw,
	t_dir *dir, float percent)
{
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y - dir->y,
		get_shade(to_draw->color, percent - 0.2)}, dir->is_flipped);
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y + dir->y,
		get_shade(to_draw->color, 1 - percent)}, dir->is_flipped);
}

void	angle_points(t_vars *vars, t_point *p[3], int i, int j)
{
	p[0] = f3d_to_2d(vars, vars->pts[i][j]);
	p[1] = f3d_to_2d(vars, vars->pts[(i + 1) % vars->rows][j]);
	p[2] = f3d_to_2d(vars, vars->pts[i][(j + 1) % vars->cols]);
}
