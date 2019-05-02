/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpapagna <rpapagna@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/30 19:04:29 by rpapagna          #+#    #+#             */
/*   Updated: 2019/05/01 20:22:37 by rpapagna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/ft_printf.h"

/*
**  f, F    The double argument is rounded and converted to decimal notation in
**          the style [-]ddd.ddd, where the number of digits after the
**          decimal-point character is equal to the precision specification.
**          If the precision is missing, it is taken as 6; if the precision is
**          explicitly zero, no decimal-point character appears.
**          If a decimal point appears, at least one digit appears before it.
*/

static int		pad_width(t_mods mod, int len, int nbyte, int neg)
{
	char	*pad_char;

	pad_char = " ";
	if (len > mod.prcsn || mod.prcsn == -1)
	{
		if (mod.width > len)
		{
			IF_THEN(mod.flags.fzero && mod.prcsn == -1, pad_char = "0");
			if (nbyte == 0)
			{
				if (mod.flags.space && mod.flags.fzero)
					nbyte += write(1, " ", 1);
				while (mod.width - len - neg > nbyte)
					nbyte += (int)write(1, pad_char, 1);
			}
			else
				while (mod.width - len > nbyte)
					nbyte += (int)write(1, pad_char, 1);
		}
	}
	else
		while (mod.width - mod.prcsn - neg > nbyte)
			nbyte += (int)write(1, pad_char, 1);
	return (nbyte);
}

static	int		right_justify(t_mods mod, char **num, int nbyte, int neg)
{
	int		len;

	if ((len = LEN(num[0]) + LEN(num[1]) + 1) && neg == 1)
	{
		if (mod.flags.fzero && mod.prcsn < 0 && mod.width > len)
			nbyte += (int)write(1, "-", 1);
		nbyte = pad_width(mod, len, nbyte, neg);
		if (!mod.flags.fzero || mod.prcsn > 0 || !nbyte)
			nbyte += (int)write(1, "-", 1);
	}
	else if (neg == 0)
	{
		if (mod.flags.fplus && mod.flags.fzero && mod.prcsn < 0 &&
			mod.width > len && (mod.flags.space = -1))
			nbyte += (int)write(1, "+", 1);
		nbyte = pad_width(mod, len, nbyte, mod.flags.fplus);
		if ((mod.flags.fplus && mod.flags.space != -1))
			nbyte += (int)write(1, "+", 1);
		if (!mod.flags.fplus && mod.flags.space && !nbyte)
			nbyte += (int)write(1, " ", 1);
	}
	if (mod.prcsn > len)
		while ((mod.prcsn--) - len > 0)
			nbyte += (int)write(1, "0", 1);
	return (nbyte += write(1, num[0], LEN(num[0])));
}

/*
**	nbyte += (int)write(1, num[0], len - 1 - LEN(num[1]));
**	nbyte += (int)write(1, ".", 1);
**	nbyte += (int)write(1, num[1], len - 1 - LEN(num[0]));
*/

static	int		left_justify(t_mods mod, char **num, int nbyte, int neg)
{
	int		len;

	len = (int)ft_strlen(num[0]) + (int)ft_strlen(num[1]) + 1;
	if (neg == 1)
		nbyte += (int)write(1, "-", 1);
	else if (neg == 0)
	{
		if (mod.flags.fplus)
			nbyte += (int)write(1, "+", 1);
		else if (mod.flags.space)
			nbyte += (int)write(1, " ", 1);
	}
	while (mod.prcsn-- > len)
		nbyte += (int)write(1, "0", 1);
	nbyte += (((int)write(1, num[0], len - (int)ft_strlen(num[1] + 1))) +
	((int)write(1, ".", 1)) +
			((int)write(1, num[1], len - (int)ft_strlen(num[0] + 1))));
	while (nbyte < mod.width)
		nbyte += (int)write(1, " ", 1);
	return (nbyte);
}

int				convert_f(t_mods modifiers, va_list ap, int i)
{
	long double		num;
	int				nbyte;
	int				neg;
	char			**str;

	if (modifiers.length == 'L' || i == 19)
		num = va_arg(ap, long double);
	else
		num = va_arg(ap, double);
	neg = (num < 0.0) ? 1 : 0;
	IF_THEN(neg == 1, num *= -1);
	str = num_string_modld(num, modifiers);
	if ((nbyte = 0) && modifiers.flags.minus == 1)
		nbyte = left_justify(modifiers, str, nbyte, neg);
	else
		nbyte = right_justify(modifiers, str, nbyte, neg);
	ft_pipewrench("--s", str);
	return (nbyte);
}
