/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aux_pf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enkwak <enkwak@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 19:59:49 by enkwak            #+#    #+#             */
/*   Updated: 2024/11/08 13:11:45 by enkwak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen_pf(const char *s)
{
	size_t	length;

	length = 0;
	while (s[length] != '\0')
	{
		length++;
	}
	return (length);
}

void	ft_bzero_pf(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n > 0)
	{
		*ptr = 0;
		ptr++;
		n--;
	}
}

void	*ft_calloc_pf(size_t count, size_t size)
{
	void	*arr;
	size_t	total_len;

	if (count == 0 || size == 0)
		return (malloc(0));
	total_len = count * size;
	if (total_len / size != count)
		return (NULL);
	arr = (void *)malloc(total_len);
	if (!arr)
		return (NULL);
	ft_bzero_pf(arr, (total_len));
	return (arr);
}

static size_t	ft_digit_len(unsigned long long n, char *base)
{
	size_t				len;
	unsigned long long	base_len;

	len = 1;
	base_len = ft_strlen_pf(base);
	while (n >= base_len)
	{
		n /= base_len;
		len++;
	}
	return (len);
}

char	*ft_aux_pf(unsigned long long n, char *base)
{
	char	*str;
	int		num_len;
	int		base_len;

	num_len = ft_digit_len(n, base);
	base_len = ft_strlen_pf(base);
	str = ft_calloc_pf((num_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	while (num_len)
	{
		num_len--;
		str[num_len] = base[n % base_len];
		n /= base_len;
	}
	return (str);
}
