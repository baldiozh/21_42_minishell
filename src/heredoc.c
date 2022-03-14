/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gmckinle <gmckinle@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 21:34:21 by gmckinle          #+#    #+#             */
/*   Updated: 2022/03/14 16:55:42 by gmckinle         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "utils.h"

static int	heredoc_dstr(const char *msg, char *f, char *s, int fd)
{
	if (msg && f)
		free(f);
	if (s)
		free(s);
	if (fd != -1)
		close(fd);
	if (msg)
		return (ft_error(1, msg, 1));
	return (0);
}

static int	heredoc_fmanip(char *f, t_cmd_info *info, t_llist *files)
{
	if (llist_push(files, 0, f))
		return (1);
	info->delim = info->in_file;
	info->in_file = f;
	return (NULL == info->in_file);
}

static int	heredoc_input(t_cmd_info *c_info, int fd)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		debug_log("HEREDOC STR: <%s>\n", str);
		if (str == NULL || ft_strcmp(str, c_info->delim) == 0)
			break ;
		if (write(fd, str, ft_strlen(str)) == -1)
			return (1);
		if (write(fd, "\n", 1) == -1)
			return (1);
		free(str);
	}
	free(str);
	return (0);
}

int	create_heredoc(t_cmd_info *c_info, t_llist *files)
{
	int		fd;
	char	*f;
	char	*s;

	f = NULL;
	s = ft_uitoa(files->size);
	fd = -1;
	if (NULL == s)
		return (heredoc_dstr("minishell: <<: to string conversion", f, s, fd));
	f = ft_strjoin2("/var/tmp/minishell.tmp.", s, 0, 0);
	debug_log("HEREDOC tmpfile %s\n", f);
	if (NULL == f)
		return (heredoc_dstr("minishell: <<: malloc", f, s, fd));
	if (access(f, F_OK) == 0 && unlink(f) == -1)
		return (heredoc_dstr("minishell: <<: tmp f already exists", f, s, fd));
	fd = open(f, O_CREAT | O_WRONLY, 0644);
	if (fd == -1)
		return (heredoc_dstr("minishell: <<: open", f, s, fd));
	if (heredoc_fmanip(f, c_info, files))
		return (heredoc_dstr("minishell: <<: filename manip", f, s, fd));
	int pid = fork ();
	if (pid == 0)
	{
		signal(SIGINT, handler_in_heredoc);
		signal(SIGQUIT, SIG_IGN);
		if (heredoc_input(c_info, fd))
			return (heredoc_dstr("minishell: <<: input", f, s, fd));
	}
	if (pid != 0)
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
	}
	wait(NULL);
	return (heredoc_dstr(NULL, f, s, fd));
}
