/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 18:24:41 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/20 17:03:28 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H
# include <stdlib.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>

typedef struct s_dir
{
	int	x;
	int	y;
	int	is_flipped;
}				t_dir;

typedef struct s_point {
	int64_t		x;
	int64_t		y;
	uint32_t	color;
}				t_point;

typedef struct s_vect3d
{
	double		x;
	double		y;
	double		z;
	uint32_t	color;
}				t_vect3d;

typedef struct s_color
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
}				t_color;

typedef struct s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_data		*img;
	t_vect3d	**pts;
	int			rows;
	int			cols;

	double		x;
	double		y;
	double		dist;

	double		alpha;
	double		beta;
	double		gamma;

	double		fov;

	int			scale;

	int			is_color_gradient;
	int			max;
	int			min;
	int			is_pres;
	int			is_aa;
}				t_vars;

#endif
