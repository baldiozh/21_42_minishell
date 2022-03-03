/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/12 13:02:40 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/03/03 18:13:04 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "utils.h"
#include "minishell.h"

int	ft_error(int ret, const char *msg, char liberr)
{
	static const char	*invcall = "*** THIS SHOULD NOT OCCUR ***";

	if (msg && *msg && !liberr)
	{
		write(STDERR_FILENO, msg, ft_strlen(msg));
		write(STDERR_FILENO, "\n", 1);
		return (ret);
	}
	if (errno != 0 && liberr)
	{
		if (msg && *msg)
			perror(msg);
		else
			perror("minishell: ");
		g_exit = errno;
	}
	else if (errno != 0)
		perror(invcall);
	return (ret);
}

char	*ft_uint_to_str(unsigned int n)
{
	char			*s;
	unsigned int	cnt;
	unsigned int	i;

	cnt = 0;
	i = n;
	while(n)
	{
		++cnt;
		i /= 10;
	}
	if (cnt == 0)
		cnt = 1;
	s = (char *)malloc(sizeof(char) * (cnt + 1));
	if (NULL == s)
		return (NULL);
	s[cnt] = '\0';
	while (cnt--)
	{
		s[cnt] = '0' + n % 10;
		n /= 10;
	}
	return (s);
}

// DEBUG
#include <stdarg.h>
void	debug_log(const char *fmt, ...) {
	va_list args;
	va_start(args, fmt);
	write(STDOUT_FILENO, DEBUG_COLOUR, 8);
	vprintf(fmt, args);
	write(STDOUT_FILENO, RESET_COLOUR, 5);
	va_end(args);
}
