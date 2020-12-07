/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 17:42:31 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/07 18:17:58 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

char	*arg_to_str(t_elem *e, char *arg)
{
	if (!arg)
	{
		if (e->prec)
			return (ft_strdup(""));
		return (ft_strdup("(null)"));
	}
	return (arg);
}

char	*arg_to_ptr(long ptr)
{
	char	*hex;
	char	*ret;

	if (!ptr)
		return (ft_strdup("(nil)"));
	hex = ft_itoa_base(ptr, "0123456789abcdef");
	ret = ft_strjoin("0x", hex);
	(void)ret;
	/*
	free(hex);
	return (ret);
	*/
	return (ft_itoa_base(ptr, "0123456789abcdef"));
}

void	fix_hex(t_elem *e, char	**src)
{
	char	*tmp;

	if (!src)
		return ;
	if (e->type == 'p')
	{
		tmp = *src;
		*src = ft_strjoin("0x", tmp);
		free(tmp);
	}
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
