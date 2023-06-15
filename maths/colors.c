/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 18:19:04 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/15 18:42:51 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/maths.h"

uint32_t	f(uint16_t x, uint16_t a)
{
	x = a + mod(x - a, 360);
	if (a <= x && x < a + 60)
		return (255 * (x - a) / 60);
	if (a + 60 <= x && x < a + 180)
		return (255);
	if (a + 180 <= x && x < a + 240)
		return (255 - 255 * (x - 180 - a) / 60);
	else
		return (0);
}

uint32_t	hueToRGB(uint16_t hue)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;

	hue = hue % 360;
	r = f(hue, 240) << 16;
	g = f(hue, 0) << 8;
	b = f(hue, 120) << 0;
	return (r | g | b);
}

uint32_t	get_shade(uint32_t color, float shade)
{
	uint32_t r = (color & 0xFF0000) >> 16;
	uint32_t g = (color & 0x00FF00) >> 8;
	uint32_t b = (color & 0x0000FF) >> 0;

	if (shade < 0)
		shade = 0;
	if (shade > 1)
		shade = 1;
	r *= shade;
	g *= shade;
	b *= shade;
	return (r << 16 | g << 8 | b);
}

uint32_t	lerp_color(uint32_t c1, uint32_t c2, float t)
{
	t_color	co1;
	t_color	co2;
	t_color	result;

	co1 = (t_color){
		(c1 & 0xFF0000) >> 16,
		(c1 & 0x00FF00) >> 8,
		(c1 & 0x0000FF) >> 0
	};
	co2 = (t_color){
		(c2 & 0xFF0000) >> 16,
		(c2 & 0x00FF00) >> 8,
		(c2 & 0x0000FF) >> 0
	};
	result = (t_color){
		lerp(co1.r, co2.r, t),
		lerp(co1.g, co2.g, t),
		lerp(co1.b, co2.b, t)
	};
	return (result.r << 16 | result.g << 8 | result.b);
}
