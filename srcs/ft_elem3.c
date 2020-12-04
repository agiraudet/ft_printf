/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_elem3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 22:51:34 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/05 00:07:11 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/ft_printf.h"

char	*nbr_put_prec(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		minus;
	int		datalen;
	int		padlen;

	src = e->data;
	minus = 0;
	if (*src == '-')
	{
		minus = 1;
		src++;
	}
	datalen = ft_strlen(src);
	padlen = 0;
	if (e->prec && e->size > datalen)
	{
		padlen = e->size - datalen;
		datalen = e->size;
	}
	else if (e->prec && e->size == 0 && ft_atoi(src) == 0)
	{
		datalen = 0;
		padlen = 0;
	}
	datalen += minus;
	ret = (char*)malloc(sizeof(char) * (datalen + 1));
	if (!ret)
		return (0);
	i = 0;
	if (minus)
		ret[i++] = '-';
	while(i < padlen + minus)
		ret[i++] = '0';
	while (i < datalen)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

char	*str_put_prec(t_elem *e)
{
	char	*ret;
	char	*src;
	int		i;
	int		datalen;

	src = e->data;
	datalen = ft_strlen(src);
	if (e->prec && e->size < datalen)
		datalen = e->size;
	ret = (char*)malloc(sizeof(char) * (datalen + 1));
	if (!ret)
		return (0);
	i = 0;
	while (i < datalen)
		ret[i++] = *src++;
	ret[i] = '\0';
	return (ret);
}

char	*nbr_put_align(t_elem *e)
{
	char	*ret;
	char	*prec;
	int		i;
	int		ii;
	int		datalen;
	int		padlen;

	if (ft_strchr("pdiuxX", e->type))
		prec = nbr_put_prec(e);
	else
		prec = str_put_prec(e);
	if (!prec)
		return (0);
	datalen = ft_strlen(prec);
	padlen = 0;
	if (e->width > datalen)
		padlen = e->width - datalen;
	ret = (char*)malloc(sizeof(char) * (datalen + padlen + 1));
	if (!ret)
		return (0);
	i = 0;
	ii = 0;
	if (e->align == RIGHT)
		while (i < padlen)
			ret[i++] = e->pad;
	while (ii < datalen)
		ret[i++] = prec[ii++];
	while (i < padlen + datalen)
		ret[i++] = ' ';
	free(prec);
	return (ret);
}
