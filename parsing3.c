/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:58 by Mathis            #+#    #+#             */
/*   Updated: 2020/10/06 13:06:32 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//juste avant d afficher la commande je remplace les caracteres par les vrai pour que cela corresponde a ce qui a ete ecrit

void    insert_actions(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == SPACE)
            s[i] = ' ';
        else if (s[i] == PIPE)
            s[i] = '|';
        else if (s[i] == SEMI)
            s[i] = ';';
        else if (s[i] == R_OUT)
            s[i] = '>';
        else if (s[i] == R_IN)
            s[i] = '<';
        else if (s[i] == VAR)
            s[i] = '$'; 
        if (s[i] == 6) //TODO:number 6 seems interesting
             s[i] = ' '; 
        i++;
    } 
}

//si y a des quotes je remplace les actions par des caracteres qui n affectent pas le parsing
void    clean_actions(char *c, int q, int dq)
{
     if ((dq || q) && *c == ' ')
         *c = SPACE;
     else if ((dq || q) && *c == '|')
         *c = PIPE;
     else if ((dq || q) && *c == ';')
         *c = SEMI;
     else if ((dq || q) && *c == '>')
         *c = R_OUT;
     //if (c == '>>')
       //  c = R_OUT_A;
     else if ((dq || q) && *c == '<')
         *c = R_IN;
     else if ((q) && *c == '$')
         *c = VAR;
}

void	replace(char *line, int i, char c, int *flag)
{
	if (line[i] == '\\' && line[i - 1] == '\\')
		line[i] = REPLACED;
	else
	{
		line[i - 1] = REPLACED;
		line[i] = c;
	}
	*flag = 1;
}


//check si y a un backslash, je remplace le caractere par un caractere neutre pour ne pas
//affecter mon programme 

int		backslash(int i, char *line, int q, int dq)
{
	int flag;

	flag = 0;
	if (line[i - 1] == '\\' && line[i] == '\\' && !q && i > 0)
		replace(line, i, REPLACED, &flag);
	else if (line[i - 1] == '\\' && line[i] == '$' && !q && i > 0)
		replace(line, i, VAR, &flag);
	else if (line[i - 1] == '\\' && line[i] == ';' && !q && !dq && i > 0)
		replace(line, i, SEMI, &flag);
	else if (line[i - 1] == '\\' && line[i] == '|' && !q && !dq && i > 0)
		replace(line, i, PIPE, &flag);
	else if (line[i - 1] == '\\' && line[i] == ' ' && !q && !dq && i > 0)
		replace(line, i, SPACE, &flag);
	else if (line[i - 1] == '\\' && line[i] == '>' && !q && !dq && i > 0)
		replace(line, i, R_OUT, &flag);
	else if (line[i - 1] == '\\' && line[i] == '<' && !q && !dq && i > 0)
		replace(line, i, R_IN, &flag);
	else if (line[i - 1] == '\\' && !q && !dq && i > 0)
		replace(line, i, line[i], &flag);
	return (flag);
}

//analyse si ya des quotes ou backslash, quel type de quote et remplace 
//par un caractere qui ne va pas influencer le split en plusieurs commandes
//le backslash permet dannuler laction qui suit, par exemple 
//echo "$USER" va sortir Mathis alors que echo "/$USER" va sortir USER
//idem pour echo bitch > ok va creer un fichier ok et ecrire bitch alors que echo bitch />ok ecrit bitch en stdout
void	quotes(char *line)
{
	int	q;
	int	dq;
	int	i;

	q = 0;
	dq = 0;
	i = 0;
	while (line[i])
	{
		if (line[i - 1] == '\\' && i > 0 && ((line[i] == '\'' && !dq && !q) || (line[i] == '"' && !q)))
			line[i - 1] = REPLACED;
		else if (backslash(i, line, q, dq))
			(void)i;
		else if (line[i] == '\'')
			simple_quotes(&line[i], &q, &dq);
		else if (line[i] == '"')
			double_quotes(&line[i], &q, &dq);
		else
			clean_actions(&line[i], q, dq);
        i++;
	}
}