/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:41:51 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 02:42:38 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

void	get_direction(t_point *pt1, t_point *pt2, t_point *dir)
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
	t_point *dir, float percent, int flip)
{
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y - dir->y,
		get_shade(to_draw->color, percent - 0.2)}, flip);
	my_mlx_point_put(vars->img,
		&(t_point){to_draw->x - dir->x, to_draw->y + dir->y,
		get_shade(to_draw->color, 1 - percent)}, flip);
}
