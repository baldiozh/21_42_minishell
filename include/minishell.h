/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmckinle <gmckinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 12:30:22 by rdrizzle          #+#    #+#             */
/*   Updated: 2022/02/19 21:12:47 by gmckinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "linked_list.h"
# include "linked_list.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>

# define CMD_APPEND 0b001
# define CMD_INSOURCE 0b010
# define CMD_SUBSHELL 0b100

// int	g_exit = 0;

typedef struct s_info
{
	char		**envp;
	char		envp_f;
	t_llist		*envp_list;
}	t_info;

typedef struct s_cmd_info
{
	char	*in_file;
	char	*out_file;
	int		flags;
	int		_shlvl; //dont touch it
}	t_cmd_info;

typedef struct s_group
{
	int			type;
	t_llist		*cmds;
}	t_group;

t_group		*ft_group_new(int type);
void		ft_group_free(void *group);

/* ============ Environment ============ */
int			ft_parse_envp(t_llist *list, char *envp[]);
char		**ft_compose_envp(t_llist *list);
/* ============ /Environment ============ */

void	handler(int sig);
void	handler_term(t_group *cmds, t_info *info);

pid_t	executing(t_group *cmds, t_info *info);
void	pipeline(t_group *cmds, t_info *info);

int		destroy(t_group *cmds, t_info *info);

/* ============ Built-ins ============ */
// int			ft_builtin_env(t_var_list *env);
/* ============ /Built-ins ============ */

#endif
