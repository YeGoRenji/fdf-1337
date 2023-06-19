/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:18:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/19 19:11:01 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/maths.h"

int	mod(int x, int n)
{
	if (x < 0)
		x = -x;
	return (x % n);
}

float	get_error(t_point *to_draw, t_point *pt1, t_point *pt2)
{
	float	actual_y;
	float	our_y;

	actual_y = pt2->y * (to_draw->x - pt1->x) - pt1->y * (to_draw->x - pt2->x);
	our_y = to_draw->y * (pt2->x - pt1->x);
	return (actual_y - our_y);
}

float	lerp(uint32_t a, uint32_t b, float t)
{
	return (a * (1 - t) + b * t);
}

float	inv_lerp(int16_t a, int16_t b, uint32_t x)
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
