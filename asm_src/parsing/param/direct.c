/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   direct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twalpert <twalpert@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 11:59:46 by jroussel          #+#    #+#             */
/*   Updated: 2019/01/28 15:12:16 by twalpert         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

static int	check_type(t_prog *prog, t_vars *vars)
{
	if (vars->op.args[vars->index] & T_DIR)
		return (0);
	if ((vars->op.args[vars->index] & T_REG) && (vars->op.args[vars->index]
			& T_IND))
		debug(ERROR, prog, PARAM_REG_IND, ((long)vars->i) << 32
			| (vars->j - 1));
	else if (vars->op.args[vars->index] & T_REG)
		debug(ERROR, prog, PARAM_REG, ((long)vars->i) << 32 | (vars->j - 1));
	else if (vars->op.args[vars->index] & T_IND)
		debug(ERROR, prog, PARAM_IND, ((long)vars->i) << 32 | (vars->j - 1));
	gotonxl(prog->content, &vars->i);
	vars->index = 0;
	return (SORC);
}

static int	body(t_prog *prog, t_vars *vars, long val)
{
	vars->code->argt[vars->index] = T_DIR;
	vars->code->args[vars->index].l = val;
	vars->index++;
	if ((ft_isnl(prog->content[vars->i + vars->k])
		|| prog->content[vars->i + vars->k] == '\0'))
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
	}
	else
		vars->i += vars->k + 1;
	return (1);
}

static int	dir_val(t_prog *prog, t_vars *vars)
{
	long	val;
	int		size;

	size = 0;
	val = vtoi(prog->content + vars->i + 1, &size);
	if (size == 0 || size == EMPTY_VAL)
		return (error(prog, PARAM_EMPTY, vars, ((long)vars->i) << 32));
	else if (size == VAL_OOB)
		return (error(prog, PARAM_OOB, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == NEG_IN_NO_B10)
		return (error(prog, PARAM_BASE_ERROR, vars, ((long)vars->i) << 32
			| (vars->j - 1)));
	else if (size == VAL_OIMAX || (val > UINT16_MAX && vars->op.index))
		return (error(prog, vars->op.index ? OF_MAX_SHORT : OF_MAX_INT, vars,
			((long)vars->i) << 32 | (vars->j - 1)));
	else if (size == VAL_OIMIN || (val < INT16_MIN && vars->op.index))
		return (error(prog, vars->op.index ? OF_MIN_SHORT : OF_MAX_INT, vars,
			((long)vars->i) << 32 | (vars->j - 1)));
	else
		return (body(prog, vars, val));
	return (2);
}

int			parse_dir(t_asm *env, t_prog *prog, t_vars *vars)
{
	int		ret;

	if ((ret = check_type(prog, vars)))
		return (ret);
	if (prog->content[vars->i + 1] == LABEL_CHAR)
	{
		vars->type = T_DIR;
		return (label_param(env, prog, vars, 2));
	}
	else if ((ret = dir_val(prog, vars)) != 2)
		return (ret);
	return (2);
}
