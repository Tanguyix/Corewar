/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:54 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 14:57:10 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static void		check_nbargs(t_prog *prog, t_vars *vars)
{
	if (vars->index < g_op_tab[vars->code->index].nb_arg)
	{
		if (g_op_tab[vars->code->index].nb_arg == 1)
			debug(ERROR, prog, REQ_1_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
		else if (g_op_tab[vars->code->index].nb_arg == 2)
			debug(ERROR, prog, REQ_2_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
		else
			debug(ERROR, prog, REQ_3_PARAM, ((long)vars->i) << 32
				| (vars->j - 1));
		prog->wrong = TRUE;
	}
}

static int		ignore_spaces(t_prog *prog, t_vars *vars)
{
	vars->s = vars->i;
	while (ft_isblank(prog->content[vars->i]))
		vars->i++;
	if (is_comment(prog->content[vars->i]))
	{
		check_nbargs(prog, vars);
		return (0);
	}
	vars->j = 0;
	while (prog->content[vars->i + vars->j] != SEPARATOR_CHAR
			&& !ft_isnl(prog->content[vars->i + vars->j])
			&& prog->content[vars->i + vars->j] != '\0'
			&& !is_comment(prog->content[vars->i + vars->j]))
		vars->j++;
	if (is_comment(prog->content[vars->i + vars->j]))
		vars->j--;
	vars->k = vars->j;
	while (ft_isblank(prog->content[vars->i + vars->j - 1]))
		vars->j--;
	return (1);
}

static int		check_unused(t_asm *env, t_prog *prog, t_vars *vars)
{
	if (vars->index > vars->op.nb_arg - 1)
	{
		vars->j = 0;
		while (!is_comment(prog->content[vars->i + vars->j]) && !ft_isnl(
				prog->content[vars->i + vars->j]) && prog->content[vars->i
				+ vars->j] != '\0')
			vars->j++;
		while (ft_isblank(prog->content[vars->i + vars->j - 1]))
			vars->j--;
		debug(env->flags & FLAG_WERROR ? ERROR : WARNING, prog, UNUSED_PARAM,
			((long)(vars->s - 1)) << 32 | ((vars->i - vars->s) + vars->j));
		vars->index = 0;
		if (env->flags & FLAG_WERROR)
		{
			gotonxl(prog->content, &vars->i);
			return (SORC);
		}
		return (0);
	}
	return (1);
}

int				next_param(t_asm *env, t_prog *prog, t_vars *vars)
{
	int				ret;

	vars->op = g_op_tab[vars->code->index];
	if (!(ret = ignore_spaces(prog, vars)))
		return (ret);
	if ((ret = check_unused(env, prog, vars)) < 1)
		return (ret);
	if ((prog->content[vars->i] == 'r') && (ret = parse_reg(prog, vars)) != 2)
		return (ret);
	else if ((prog->content[vars->i] == DIRECT_CHAR) && (ret = parse_dir(
			env, prog, vars)) != 2)
		return (ret);
	else if ((ft_isdigit(prog->content[vars->i]) || prog->content[vars->i]
			== '-' || prog->content[vars->i] == LABEL_CHAR) && (ret = parse_ind(
			env, prog, vars)) != 2)
		return (ret);
	else
	{
		return (error(prog, INVALID_PARAM, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	}
	return ((vars->index = 0));
}
