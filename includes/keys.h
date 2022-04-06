/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/10 23:33:57 by conobi            #+#    #+#             */
/*   Updated: 2022/01/17 14:22:37 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# if __APPLE__
/* Keys */
#  define CLOSE_EVENT		17
#  define CLOSE_MASK		131072L

/* Function Keys */
#  define KB_ESC			53
#  define KB_ENTER			76
#  define KB_LEFT_SHIFT		57
#  define KB_RIGHT_SHIFT	60
#  define KB_CTRL_LEFT		59
#  define KB_CTRL_RIGHT		59
#  define KB_SPACE			49
#  define KB_BACKSPACE		51

/* Numeric Keys */
#  define KB_PAD_0			82
#  define KB_PAD_1			83
#  define KB_PAD_2			84
#  define KB_PAD_3			85
#  define KB_PAD_4			86
#  define KB_PAD_5			87
#  define KB_PAD_6			88
#  define KB_PAD_7			89
#  define KB_PAD_8			91
#  define KB_PAD_9			92
#  define KB_PAD_PLUS		69
#  define KB_PAD_MINUS		78
#  define KB_PAD_DOT		65
#  define KB_PAD_DIVIDE		75
#  define KB_PAD_MULTIPLY	67

/* Characters */
#  define KB_W				13
#  define KB_A				0
#  define KB_S				1
#  define KB_D				2

/* Navigation Keys */
#  define KB_UP 			126
#  define KB_DOWN			125
#  define KB_LEFT			123
#  define KB_RIGHT			124
#  define KB_PAGE_UP		116
#  define KB_PAGE_DOWN		121

# elif __linux__
/* Keys */
#  define CLOSE_EVENT		33
#  define CLOSE_MASK		131072L

/* Function Keys */
#  define KB_ESC			65307
#  define KB_ENTER			65293
#  define KB_LEFT_SHIFT		65505
#  define KB_RIGHT_SHIFT	65506
#  define KB_CTRL_LEFT		65507
#  define KB_CTRL_RIGHT		65508
#  define KB_SPACE			32
#  define KB_BACKSPACE		65288

/* Numeric Keys */
#  define KB_PAD_0			65438
#  define KB_PAD_1			65436
#  define KB_PAD_2			65433
#  define KB_PAD_3			65435
#  define KB_PAD_4			65430
#  define KB_PAD_5			65437
#  define KB_PAD_6			65432
#  define KB_PAD_7			65429
#  define KB_PAD_8			65431
#  define KB_PAD_9			65434
#  define KB_PAD_PLUS		65451
#  define KB_PAD_MINUS		65453
#  define KB_PAD_DOT		65439
#  define KB_PAD_DIVIDE     65455
#  define KB_PAD_MULTIPLY   65450

/* Characters */
#  define KB_W				119
#  define KB_A				97
#  define KB_S				115
#  define KB_D				100

/* Navigation Keys */
#  define KB_UP				65362
#  define KB_DOWN			65364
#  define KB_LEFT			65361
#  define KB_RIGHT			65363
#  define KB_PAGE_UP		65365
#  define KB_PAGE_DOWN		65366
# endif
#endif
