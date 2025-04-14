/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 20:40:02 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 22:12:28 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_format(va_list va, const char *str, size_t *count)
{
	if (*str == 'c')
		ft_putchar_pf(va_arg(va, int), count);
	else if (*str == 's')
		ft_putstr_pf(va_arg(va, char *), count);
	else if (*str == 'p')
		ft_putptr_pf(va_arg(va, void *), count);
	else if (*str == 'i' || *str == 'd')
		ft_putnbr_pf(va_arg(va, int), count);
	else if (*str == 'u')
		ft_putuint_pf(va_arg(va, unsigned int), count);
	else if (*str == 'x' || *str == 'X')
	{
		if (*str == 'x')
			ft_puthex_pf(va_arg(va, unsigned int), count, HEX_LOW_BASE);
		else
			ft_puthex_pf(va_arg(va, unsigned int), count, HEX_UPP_BASE);
	}
	else if (*str == '%')
		ft_putchar_pf(*str, count);
	else
	{
		ft_putchar_pf('%', count);
		ft_putchar_pf(*str, count);
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	va;
	size_t	count;

	if (!str)
		return (0);
	count = 0;
	va_start(va, str);
	while (*str)
	{
		if (*str == '%')
		{
			str++;
			if (*str)
				ft_format(va, str, &count);
			else
				ft_putchar_pf('%', &count);
		}
		else
			ft_putchar_pf(*str, &count);
		str++;
	}
	va_end(va);
	return (count);
}
