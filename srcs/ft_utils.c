/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:42:31 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 17:13:25 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*arg_to_str(t_elem *e, char *arg)
{
	if (!arg)
	{
		if (e->prec && e->size <= 5)
			return (ft_strdup(""));
		return (ft_strdup("(null)"));
	}
	return (arg);
}

char	*arg_to_ptr(long ptr)
{
	if (!ptr)
		return (ft_strdup("(nil)"));
	return (ft_itoa_base(ptr, "0123456789abcdef"));
}

char	*fix_hex(char *src)
{
	int		i;

	i = 0;
	while (src[i] == '0')
		i++;
	if (i == 1)
		return (src);
	else if (src[i] == 'x')
	{
		src[i] = '0';
		src[1] = 'x';
	}
	return (src);
}

void	fix_minus(char *src)
{
	int		i;

	i = 0;
	while (src[i] == '0')
		i++;
	if (src[i] == '-')
	{
		src[i] = '0';
		src[0] = '-';
	}
}

void	put_buffer(t_elem *e, char *buffer)
{
	int		i;

	i = 0;
	while (buffer[i])
	{
		if (e->zero_flag && buffer[i] == '.')
			ft_putchar(0);
		else
			ft_putchar(buffer[i]);
		i++;
	}
}
