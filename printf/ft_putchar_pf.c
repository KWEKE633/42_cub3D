/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:34:58 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 22:13:04 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putchar_pf(char c, size_t *count)
{
	int	ret;

	ret = write(1, &c, 1);
	if (ret == -1)
	{
		(*count) = -1;
		return ;
	}
	*count += ret;
}
