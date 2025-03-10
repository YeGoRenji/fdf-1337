/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:35:50 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 14:57:53 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/maths.h"

void	ft_swap(int64_t *a, int64_t *b)
{
	int64_t	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

float	check_zero(float arith)
{
	if (arith == 0)
		return (1);
	return (arith);
}

double	rad_to_deg(double angle)
{
	return (mod(angle * 360 / TAU, 360));
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int64_t	ft_abs(int64_t x)
{
	if (x >= 0)
		return (x);
	return (-x);
}
