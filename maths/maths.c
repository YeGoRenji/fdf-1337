/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:18:54 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 03:11:19 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/maths.h"

int	mod(int x, int n)
{
	while (x < 0)
		x += n;
	return (x % n);
}

int	clamp(int a, int min, int max)
{
	if (a > max)
		return (max);
	if (a < min)
		return (min);
	return (a);
}

float	lerp(uint32_t a, uint32_t b, float t)
{
	return (a * (1 - t) + b * t);
}

float	inv_lerp(uint32_t a, uint32_t b, uint32_t x)
{
	if (b == a)
		return (0);
	return ((float)(x - a) / (b - a));
}
