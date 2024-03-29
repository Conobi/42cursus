/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: conobi                                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/14 13:33:05 by conobi            #+#    #+#             */
/*   Updated: 2021/11/16 19:24:30 by conobi           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>

/* ft_printf_utils.c */
int		counter(int n);
size_t	n_write(int fd, const void *buf, size_t n);
void	f_puthexa(unsigned long long nb, short upper);

/* ft_printf.c */
int		ft_printf(const char *format, ...);

/* custom_libft.c */
size_t	f_strlen(const char *s);
void	f_putchar(char n);
void	f_putstr(char *s);
void	f_putnbr(long n, short un);
void	f_putnbr_u(unsigned int n);
void	f_putnbr_base(unsigned long long nb, char *base);

#endif
