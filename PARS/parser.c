/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idouni <idouni@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 16:46:45 by idouni            #+#    #+#             */
/*   Updated: 2023/05/31 18:45:17 by idouni           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer	*parser(t_collector	**collector, char *s, t_init *init, t_nrm *nrm)
{
	t_lexer	*h_lexer;

	if (check_syntax(collector, s, init))
		return (NULL);
	h_lexer = lexer(collector, s);
	expander(collector, nrm->env, &h_lexer, nrm->exit_val);
	if (check_syntax2(&h_lexer))
		return (NULL);
	return (h_lexer);
}

t_cmd	*parser2(t_collector	**collector, t_lexer *node)
{
	t_files		*files;
	char		**full_cmd;
	t_file		*out_files;
	t_file		*in_files;
	t_cmd		*cmd;

	if (!node)
		return (NULL);
	cmd = NULL;
	files = NULL;
	files = h_malloc(collector, sizeof(t_files), files);
	parser_init(&out_files, &in_files, &full_cmd);
	while (node)
	{
		check_for_out_files(collector, &out_files, node);
		check_for_in_files(collector, &in_files, node);
		get_full_cmd(collector, &node, &full_cmd);
		if (node && node->type == PIP)
			node = node->next;
		files->out_files = out_files;
		files->in_files = in_files;
		add_to_cmd(collector, &cmd, full_cmd, files);
		parser_init(&out_files, &in_files, &full_cmd);
	}
	return (cmd);
}

void	get_full_cmd(t_collector **collector, t_lexer **n, char ***full_cmd)
{
	int	j;

	j = 1;
	while ((*n) && (*n)->type != PIP)
	{
		if ((*n)->type == WH_SP)
			j = 0;
		else if ((*n)->type == SCMD || (*n)->type == ST_SQ \
		|| (*n)->type == ST_DQ)
		{
			add_to_fullcmd(collector, full_cmd, (*n), j);
			j = 1;
		}
		(*n) = (*n)->next;
	}
}

void	check_for_in_files(t_collector **collector, t_file **in_files, \
t_lexer *n)
{
	while (n && n->type != PIP)
	{
		if (n->cmd && n->type == R_IN && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, in_files, n->cmd, O_TRUNC);
		}
		if (n->cmd && n->type == R_HD && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, in_files, n->cmd, O_APPEND);
		}
		n = n->next;
	}
}

void	check_for_out_files(t_collector **collector, t_file **out_files, \
t_lexer *n)
{
	while (n && n->type != PIP)
	{
		if (n->cmd && n->type == R_OT && n->next)
		{
			n = n->next;
			while (n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, out_files, n->cmd, O_TRUNC);
		}
		if (n->cmd && n->type == R_OA && n->next)
		{
			n = n->next;
			while (n && n->type == WH_SP)
				n = n->next;
			n->type = FIL_NM;
			add_file_node(collector, out_files, n->cmd, O_APPEND);
		}
		n = n->next;
	}
}
