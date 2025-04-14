/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:42:14 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 19:47:29 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr_pf(int num, size_t *count)
{
	if (num == -2147483648)
	{
		ft_putchar_pf('-', count);
		ft_putchar_pf('2', count);
		ft_putnbr_pf(147483648, count);
	}
	else if (num < 0)
	{
		ft_putchar_pf('-', count);
		ft_putnbr_pf((num * -1), count);
	}
	else if (num > 9)
	{
		ft_putnbr_pf((num / 10), count);
		ft_putnbr_pf((num % 10), count);
	}
	else
		ft_putchar_pf((num % 10) + '0', count);
}
