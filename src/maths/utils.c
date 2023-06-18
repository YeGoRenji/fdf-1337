/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:35:50 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 15:11:17 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/maths.h"

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp  = *a;
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
