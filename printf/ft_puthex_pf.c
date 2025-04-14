/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_pf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:39:05 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 19:42:07 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_pf(unsigned int num, size_t *count, char *base)
{
	char	*str;

	str = ft_aux_pf(num, base);
	ft_putstr_pf(str, count);
	free(str);
}
