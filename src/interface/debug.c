/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 02:54:15 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 16:03:26 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/drawing.h"

void	clear_console(void)
{
	write(1, "\e[1;1H\e[2J", 10);
}

// ! Debug purposes
// void	print_info(t_vars *vars)
// {
// 	printf("Dimensions: (%d, %d)\n", vars->rows, vars->cols);
// 	printf("Rotation: (%.2f, %.2f, %.2f)\n",
// 	rad_to_deg(vars->alpha), rad_to_deg(vars->beta), rad_to_deg(vars->gamma));
// 	printf("Position: (%.2f, %.2f, %.2f)\n", vars->x, vars->y, vars->dist);
// 	printf("Scale: %d, Fov: %f\n", vars->scale, vars->fov);
// 	printf("Max : %d, Min: %d\n", vars->max, vars->min);
// }
