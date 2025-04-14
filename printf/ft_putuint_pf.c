/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putuint_pf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:56:59 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/07 19:59:41 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putuint_pf(unsigned int num, size_t *count)
{
	char	*str;

	str = ft_aux_pf(num, "0123456789");
	ft_putstr_pf(str, count);
	free(str);
}
