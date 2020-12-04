/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 14:46:24 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/04 23:55:43 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_printf.h"

t_elem	elem_init(void)
{
	t_elem	e;

	e.align = RIGHT;
	e.pad = ' ';
	e.width = 0;
	e.prec = 0;
	e.size = 0;
	return (e);
}

char	*elem_put_str(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		ii;
	int		datalen;
	int		padlen;

	src = e->data;
	datalen = ft_strlen(src);
	datalen = (e->size < datalen && e->prec) ? e->size : datalen;
	padlen = (e->width > datalen) ? e->width - datalen : 0;
	e->pad = ' ';
	ret = (char*)malloc(sizeof(char) * (e->size + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	if (e->align == RIGHT)
		while (i < padlen)
			ret[i++] = e->pad;
	ii = i;
	while (*src && i - ii < datalen)
		ret[i++] = *src++;
	while (i - ii < e->size)
		ret[i++] = e->pad;
	return (ret);
}

char	*elem_put_nbr(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;
	int		padlen;

	src = e->data;
	datalen = ft_strlen(src);
	padlen = 0;
	if ((e->prec && e->size > datalen))
	{
		padlen = e->size - datalen;
		datalen = e->size;
		e->pad = '0';
	}
	if (e->prec && e->size == 0 && ft_atoi(src) == 0)
	{
		datalen = 0;
		padlen = 0;
		e->pad = '0';
	}
	else if (e->width > datalen)
	{
		padlen = e->width - datalen;
		datalen = e->width;
	}
	ret = (char*)malloc(sizeof(char) * (datalen + 1));
	if (!ret)
		return (0);
	i = 0;
	if (e->align == RIGHT)
		while (i < padlen)
			ret[i++] = e->pad;
	while (*src && i < datalen)
		ret[i++] = *src++;
	if (e->align == LEFT)
		while (i < datalen)
			ret[i++] = e->pad;
	ret[i] = '\0';
	return (ret);
}

void	elem_destroy(t_elem *e)
{
	free(e->data);
	free(e);
}

void	elem_show(t_elem *e)
{
	printf("{\n\ttype: %c\n\tdata: %s\n\talgn: %d\n\tpad : '%c'\n\twidt: %d\n\tsize: %d\n\tprec: %d\n}\n", e->type, e->data, e->align, e->pad, e->width, e->size, e->prec);
}

char	*elem_print(const char **str, va_list *param)
{
	char	*buffer;
	t_elem	*e;

	e = elem_create(str, param);
	if (ft_strchr("sc%", e->type))
		buffer = nbr_put_align(e);
	if (ft_strchr("pdiuxX", e->type))
		buffer = nbr_put_align(e);
	elem_destroy(e);
	return (buffer);
}
