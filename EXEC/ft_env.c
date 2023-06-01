/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msamhaou <msamhaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/20 08:04:05 by msamhaou          #+#    #+#             */
/*   Updated: 2023/05/30 21:08:08 by msamhaou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*new_env(char *str)
{
	t_env	*lst;

	lst = malloc(sizeof(t_env));
	if (!lst)
		return (NULL);
	lst->str = ft_strdup(str);
	lst->next = NULL;
	return (lst);
}

void	env_add_back(t_env **env, t_env *toadd)
{
	t_env	*head;

	head = *env;
	if (!toadd && env)
		ft_free_env_lst(env);
	if (!(*env))
	{
		*env = toadd;
		head = *env;
		return ;
	}
	while ((*env)->next)
		(*env) = (*env)->next;
	(*env)->next = toadd;
	*env = head;
}

char	**ft_set_env(t_env *env_lst)
{
	char	**res;
	int		i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (ft_env_size(env_lst) + 1));
	while (env_lst)
	{
		res[i] = ft_strdup(env_lst->str);
		env_lst = env_lst->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
