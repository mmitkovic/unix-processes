/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmitkovi <mmitkovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 10:46:23 by mmitkovi          #+#    #+#             */
/*   Updated: 2025/09/05 10:54:16 by mmitkovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int n = fork();
	if (n == 0)
		printf("Ciao, da un processo bambino\n");
	else
		printf("Ciao, da parente\n");
	return 0;
}
