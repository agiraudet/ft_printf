/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agiraude <agiraude@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:28:48 by agiraude          #+#    #+#             */
/*   Updated: 2020/12/07 18:18:34 by agiraude         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../libft/includes/libft.h"

# define LEFT 1
# define RIGHT 0

typedef struct	s_elem
{
	/*general*/
	char		type;
	char		*data;
	/*alignement*/
	int			align;
	char		pad;
	int			width;
	/*precision*/
	int			size;
	int			prec;
}				t_elem;


char			*arg_to_str(t_elem *e, char *arg);
char			*arg_to_ptr(long ptr);
void			fix_minus(char *src);
void			fix_hex(t_elem *e, char **src);
char			*elem_fill_buffer(t_elem *e);
char			*elem_print(const char **str, va_list *param);
void			elem_set_flag(const char **str, t_elem *e, va_list *param);
void			elem_set_prec(const char **str, t_elem *e, va_list *param);
void			elem_set_data(t_elem *e, va_list *param);
int				ft_printf(const char *str, ...);

#endif
