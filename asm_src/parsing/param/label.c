/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:51 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 15:12:34 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	lbl_reset(t_prog *prog, t_vars *vars)
{
	if (vars->index < vars->op.nb_arg)
	{
		debug(ERROR, prog, (vars->op.nb_arg - vars->index) == 2
			? MISSING_2_PARAM : MISSING_1_PARAM,
			((long)(vars->i + vars->j - 1)) << 32);
		gotonxl(prog->content, &vars->i);
		vars->index = 0;
		return (-1);
	}
	else
		return ((vars->index = 0));
	return (1);
}

static int	lbl_init(t_prog *prog, t_vars *vars, unsigned short jump)
{
	unsigned int	l;

	l = 0;
	while (prog->content[vars->i + jump + l] != SEPARATOR_CHAR
		&& !ft_isnl(prog->content[vars->i + jump + l])
		&& !ft_isblank(prog->content[vars->i + jump + l])
		&& prog->content[vars->i + jump + l] != '\0')
	{
		if (!isoneof(prog->content[vars->i + jump + l], LABEL_CHARS))
		{
			debug(ERROR, prog, BAD_CHAR_LABEL, ((long)vars->i) << 32
				| (vars->j - 1));
			gotonxl(prog->content, &vars->i);
			vars->index = 0;
			return (SORC);
		}
		l++;
	}
	if (l != 0)
		return (l);
	debug(ERROR, prog, LABEL_EMPTY, ((long)vars->i) << 32 | 1);
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}

int			label_param(t_asm *env, t_prog *prog, t_vars *vars,
				unsigned short jump)
{
	int	ret;
	int	l;

	if ((l = lbl_init(prog, vars, jump)) < 0)
		return (l);
	vars->code->argt[vars->index] = vars->type;
	vars->code->pos[vars->index] = vars->i + jump;
	if (!(vars->code->refs[vars->index] = ft_strsub(prog->content,
			vars->i + jump, l)))
		quit(env, MALLOC_ERROR);
	vars->index++;
	if ((ft_isnl(prog->content[vars->i + vars->k])
		|| prog->content[vars->i + vars->k] == '\0'))
	{
		if ((ret = lbl_reset(prog, vars)) < 1)
			return (ret);
	}
	else
		vars->i += vars->k + 1;
	return (1);
}
