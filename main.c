/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/04 18:35:34 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/31 18:53:51 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_var;

void	sig_handle(int sig)
{
	if (sig == SIGINT && g_var)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_quit(t_built flag, t_init *init)
{
	if (flag == EXT)
		write(1, "exit\n", 5);
	exit(0);
}

int	ft_set_path(t_cmd *cmd, char **myenv, t_env *env_lst)
{
	while (cmd)
	{
		if (cmd->cmd[0])
		{
			cmd->myenv = env_lst;
			if (!ft_strchr(cmd->cmd[0], '/'))
				cmd->cmd_path = ft_get_path(cmd->cmd, myenv);
			else
				cmd->cmd_path = cmd->cmd[0];
		}
		cmd = cmd->next;
	}
	return (1);
}

void	ft_execution(t_init *init, int *exit_val)
{
	int	cmd_num;

	ft_set_path(init->cmd, init->myenv, init->envlst);
	cmd_num = init->cmd->num_cmds;
	while (init->cmd)
	{
		init->cmd->tty_in = init->tmp_fd_in;
		ft_fork(init->cmd, init, exit_val);
		init->cmd = init->cmd->next;
	}
	while (cmd_num--)
		wait(&(*exit_val));
}

void	foo()
{
	system("leaks minishell");
}

int	main(int ac, char **av, char **env)
{
	t_init		*inval;
	t_collector	*collector;
	char		*s;
	int			exit_val;
	t_nrm	*nrm;

	// atexit(foo);

	g_var = 1;
	nrm = NULL;
	collector = NULL;
	ft_norm_sucks(ac, av);
	strt(&collector);
	inval = ft_init(&collector, env);
	nrm = h_malloc(&collector, sizeof(t_nrm), nrm);
	nrm->exit_val = &exit_val;
	nrm->env = &(inval->envlst);
	while (1)
	{
		reset_io(&collector, inval);
		s = prompt();
		inval->cmd = parser2(&collector \
			, parser(&collector, s, inval, nrm));
		emplify(&collector, inval->cmd);
		if (!inval->cmd)
			continue ;
		g_var = 0;
		// after_parse2(inval->cmd);
		ft_execution(inval, &exit_val);
		g_var = 1;
	}
}
