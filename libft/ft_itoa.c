/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tmurase <tmurase@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/02 20:26:29 by tmurase           #+#    #+#             */
/*   Updated: 2021/03/31 19:14:02 by mitchiwak        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_digit(long n)
{
	int	count;

	count = 1;
	if (n < 0)
	{
		n *= -1;
		count++;
	}
	while (n > 9)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*conver_to_char(char *str, int n_digit, long n)
{
	int	m_flag;

	m_flag = 0;
	if (n < 0)
	{
		n = n * -1;
		m_flag++;
	}
	str[n_digit] = '\0';
	while (n_digit-- >= 0)
	{
		str[n_digit] = (n % 10 + 48);
		n /= 10;
	}
	if (m_flag)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		n_digit;

	n_digit = check_digit((long)n);
	if (n_digit == 0)
		return (NULL);
	str = ((char *)malloc((n_digit + 1) * sizeof(char)));
	if (!str)
		return (NULL);
	str = conver_to_char(str, n_digit, (long)n);
	return (str);
}

/*
** 【概要】
** 	intの値をcharへ変換する関数。
** 【処理】
** 	check_digit関数で引数の値の桁数を確認。桁数分のメモリを確保。conver_to_char関数で桁数
** 	分char型へ変換する。
*/
