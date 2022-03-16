/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdrizzle <rdrizzle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 19:02:12 by gmckinle          #+#    #+#             */
/*   Updated: 2022/03/16 16:50:40 by rdrizzle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

void	handler(int sig)
{
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	write(1, "  \b\b\n", 5);
	rl_on_new_line();
	rl_replace_line("", 1);
	rl_redisplay();
}

void	handler_in_executor(int sig)
{
	(void)sig;
	write(2, "Quit: 3\n", 8);
}

void	handler_in_heredoc(int sig)
{
	(void)sig;
	write(2, "\n", 1);
	exit(130);
}
