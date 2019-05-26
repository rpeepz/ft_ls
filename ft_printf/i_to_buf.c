/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   i_to_buf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/25 23:12:09 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/26 01:35:39 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_sprintf.h"

static int		pad_width(char *buf, int len, int nbyte, t_mod mod)
{
	char	*pad_char;

	pad_char = " ";
	if (len > mod.prcsn || mod.prcsn == -1)
	{
		if (mod.width > len)
		{
			IF_THEN(mod.fl.fzero && mod.prcsn == -1, pad_char = "0");
			if (nbyte == 0)
			{
				if (mod.fl.space && mod.fl.fzero)
				{
					ADD_ONE_TO_BUFF(buf, pad_char, nbyte);
				}
				while (mod.width - len - mod.neg > nbyte)
				{
					ADD_ONE_TO_BUFF(buf, pad_char, nbyte);
				}
			}
			else
				while (mod.width - len > nbyte)
				{
					ADD_ONE_TO_BUFF(buf, pad_char, nbyte);
				}
		}
	}
	else
		while (mod.width - mod.prcsn - mod.neg > nbyte)
		{
			ADD_ONE_TO_BUFF(buf, pad_char, nbyte);
		}
	return (nbyte);
}

static int		right_justify(char *buf, char *num, t_mod mod)
{
	int		len;
	int		nbyte;

	nbyte = 0;
	len = LEN(num);
	if (mod.neg == 1)
	{
		if (mod.fl.fzero && mod.prcsn < 0 && mod.width > len)
		{
			ADD_ONE_TO_BUFF(buf, "-", nbyte);
		}
		nbyte = pad_width(buf, len, nbyte, mod);
		if (!mod.fl.fzero || mod.prcsn > 0 || !nbyte)
		{
			ADD_ONE_TO_BUFF(buf, "-", nbyte);
		}
	}
	else if (mod.neg == 0)
	{
		if (mod.fl.fplus && mod.fl.fzero && mod.prcsn < 0 &&
			mod.width > len && (mod.fl.space = -1))
		{
			ADD_ONE_TO_BUFF(buf, "+", nbyte);
		}
		mod.neg = mod.fl.fplus;
		nbyte = pad_width(buf, len, nbyte, mod);
		if ((mod.fl.fplus && mod.fl.space != -1))
		{
			ADD_ONE_TO_BUFF(buf, "+", nbyte);
		}
		if (!mod.fl.fplus && mod.fl.space && !nbyte)
		{
			ADD_ONE_TO_BUFF(buf, " ", nbyte);
		}
	}
	if (mod.prcsn > len)
		while ((mod.prcsn--) - len > 0)
		{
			ADD_ONE_TO_BUFF(buf, "0", nbyte);
		}
	ADD_TO_BUFF(buf, num, nbyte, len);
	return (nbyte);
}

static	int		left_justify(char *buf, char *num, t_mod mod)
{
	int		nbyte;
	int		len;

	nbyte = 0;
	len = (int)ft_strlen(num);
	if (mod.neg == 1)
	{
		ADD_ONE_TO_BUFF(buf, "-", nbyte);
	}
	else if (mod.neg == 0)
	{
		if (mod.fl.fplus)
		{
			ADD_ONE_TO_BUFF(buf, "+", nbyte);
		}
		else if (mod.fl.space)
		{
			ADD_ONE_TO_BUFF(buf, " ", nbyte);
		}
	}
	while (mod.prcsn-- > len)
	{
		ADD_ONE_TO_BUFF(buf, "0", nbyte);
	}
	ADD_TO_BUFF(buf, num, nbyte, len);
	while (nbyte < mod.width)
	{
		ADD_ONE_TO_BUFF(buf, " ", nbyte);
	}
	return (nbyte);
}

static int64_t	convert_length(int length, va_list ap)
{
	int64_t		d;

	if (length == 'h')
	{
		d = va_arg(ap, int);
		return ((short)d);
	}
	else if (length / 2 == 'h')
	{
		d = va_arg(ap, int);
		return ((signed char)d);
	}
	else if (length == 'l')
		d = va_arg(ap, long);
	else if (length / 2 == 'l' || length == 'z')
		d = va_arg(ap, long long);
	else
		d = va_arg(ap, int);
	return (d);
}

int				i_to_buf(char *buf, t_mod modifiers, va_list ap)
{
	int64_t	num;
	int		nbyte;
	char	*str;

	nbyte = 0;
	num = convert_length(modifiers.length, ap);
	modifiers.neg = (num < 0) ? 1 : 0;
	IF_THEN(modifiers.neg == 1, num *= -1);
	str = num_string_base(num, 10);
	IF_THEN(str[0] == '0' && modifiers.prcsn == 0, str[0] = '\0');
	if (modifiers.fl.minus == 1)
		nbyte += left_justify(buf, str, modifiers);
	else
		nbyte += right_justify(buf, str, modifiers);
	free(str);
	return (nbyte);
}
