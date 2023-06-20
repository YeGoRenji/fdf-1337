/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:18:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 16:38:44 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/maths.h"

int	mod(int x, int n)
{
	while (x < 0)
		x += n;
	return (x % n);
}

float	err(t_point *to_draw, t_point *pt1, t_point *pt2)
{
	float	actual_y;
	float	our_y;

	actual_y = pt2->y * (to_draw->x - pt1->x) - pt1->y * (to_draw->x - pt2->x);
	our_y = to_draw->y * (pt2->x - pt1->x);
	return (actual_y - our_y);
}

uint8_t	lerp(uint8_t a, uint8_t b, float t)
{
	return (a * (1 - t) + b * t);
}

float	inv_lerp(int64_t a, int64_t b, int64_t x)
{
	if (b == a)
		return (0);
	return ((float)(x - a) / (b - a));
}

void	set_max_min(t_vars *vars, int val)
{
	if (val > vars->max)
		vars->max = val;
	if (val < vars->min)
		vars->min = val;
}
