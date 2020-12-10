/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/02 19:12:01 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/10 14:35:57 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_printf(const char *str, ...)
{
	va_list	param;
	int		nbchar;

	va_start(param, str);
	nbchar = 0;
	while (*str != '\0')
	{
		if (*str != '%')
		{
			ft_putchar(*str++);
			nbchar++;
			continue ;
		}
		str++;
		nbchar += elem_print(&str, &param);
	}
	return (nbchar);
}
