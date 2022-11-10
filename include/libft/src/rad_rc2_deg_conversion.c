/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rad_rc2_deg_conversion.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mraymond <mraymond@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 13:33:49 by mraymond          #+#    #+#             */
/*   Updated: 2022/08/09 12:59:41 by mraymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../header/libft.h"

double	craddeg(double radian)
{
	return (radian * (180 / PI));
}

double	cdegrad(double degree)
{
	return ((degree * PI) / 180);
}

double	cradrc2(double radian)
{
	return (radian / PI);
}

double	crc2rad(double rc2)
{
	return (rc2 * PI);
}
