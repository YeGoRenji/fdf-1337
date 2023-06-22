/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylyoussf <ylyoussf@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 03:24:26 by ylyoussf          #+#    #+#             */
/*   Updated: 2023/06/18 03:06:25 by ylyoussf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H

# ifdef __linux__
#  define X_MASK 1L<<0
#  include <X11/keysym.h>
#  define KEY_Q XK_q
#  define KEY_A XK_a
#  define KEY_W XK_w
#  define KEY_S XK_s
#  define KEY_E XK_e
#  define KEY_D XK_d
#  define KEY_R XK_r
#  define KEY_F XK_f
#  define KEY_T XK_t
#  define KEY_G XK_g
#  define KEY_Y XK_y
#  define KEY_H XK_h
#  define KEY_Z XK_z
#  define KEY_X XK_x
#  define KEY_O XK_o
#  define KEY_P XK_p
#  define KEY_LEFT XK_Left
#  define KEY_RIGHT XK_Right
#  define KEY_DOWN XK_Down
#  define KEY_UP XK_Up
#  define KEY_ESC XK_Escape
#  define SCROLL_UP 4
#  define SCROLL_DOWN 5
# else
#  define X_MASK 0
#  define KEY_Q 12
#  define KEY_A 0
#  define KEY_W 13
#  define KEY_S 1
#  define KEY_E 14
#  define KEY_D 2
#  define KEY_R 15
#  define KEY_F 3
#  define KEY_T 17
#  define KEY_G 5
#  define KEY_Y 16
#  define KEY_H 4
#  define KEY_Z 6
#  define KEY_X 7
#  define KEY_LEFT 123
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_UP 126
#  define KEY_ESC 53
#  define SCROLL_UP 4
#  define SCROLL_DOWN 5
# endif

#endif
