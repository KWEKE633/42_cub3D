/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:53:56 by enkwak            #+#    #+#             */
/*   Updated: 2025/04/14 16:55:46 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putstr_pf(char *str, size_t *count)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		ft_putchar_pf(*str, count);
		str++;
	}
}
