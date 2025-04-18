/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:33:55 by enkwak            #+#    #+#             */
/*   Updated: 2024/10/31 20:38:00 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

# define HEX_UPP_BASE "0123456789ABCDEF"
# define HEX_LOW_BASE "0123456789abcdef"

int		ft_printf(const char *format, ...);

void	ft_putchar_pf(char c, size_t *count);
void	ft_putstr_pf(char *str, size_t *count);
void	ft_putnbr_pf(int num, size_t *count);
void	ft_putuint_pf(unsigned int num, size_t *count);
void	ft_puthex_pf(unsigned int num, size_t *count, char *base);
void	ft_putptr_pf(void *ptr, size_t *count);

char	*ft_aux_pf(unsigned long long n, char *base);

#endif