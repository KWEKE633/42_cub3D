/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:47:42 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 21:58:46 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_pf(void *ptr, size_t *count)
{
	char			*str;
	unsigned long	ptr_address;

	if (!ptr)
		ft_putstr_pf("(nil)", count);
	else
	{
		ptr_address = (unsigned long)ptr;
		ft_putstr_pf("0x", count);
		str = ft_aux_pf(ptr_address, HEX_LOW_BASE);
		ft_putstr_pf(str, count);
		free(str);
	}
}
