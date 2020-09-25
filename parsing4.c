/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 12:54:18 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/25 12:56:10 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//je remplace les doubles quotes par un caractere ascii neutre
// et lorsque je traiterai ma commande
//je remplacerai mon caractere par un espace  

void    double_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq) //ouverture des doubles quotes
    {
        *dq = 1;
        *c = REPLACED;
    }
    else if (!*q && *dq)         //fermetures des doubles quotes
    {
        *dq = 0;
        *c = REPLACED;
    }
}

void    simple_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq) //ouverture des simples quotes
    {
        *q = 1;
        *c = REPLACED;
    }
    else if (*q && !*dq) //fermetures des simples quotes
    {
        *q = 0;
        *c = REPLACED;
    }
}