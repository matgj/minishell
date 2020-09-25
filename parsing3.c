/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Mathis <Mathis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/24 10:49:58 by Mathis            #+#    #+#             */
/*   Updated: 2020/09/25 10:58:08 by Mathis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"


void    insert_actions(char *s)
{
    int i;

    i = 0;
    while (s[i])
    {
        if (s[i] == PIPE)
            s[i] = '|';
        if (s[i] == SEMI)
            s[i] = ';';
        if (s[i] == R_OUT)
            s[i] = '>';
        if (s[i] == R_IN)
            s[i] = '<';
        if (s[i] == VAR)
            s[i] = '$';
        i++;
    } 
}

//TODO: how to manage >> ?
void    clean_actions(char *c, int *q, int *dq)
{
    if (*q || *dq)
    {
        if (*c == '|')
            *c = PIPE;
        if (*c == ';')
            *c = SEMI;
        if (*c == '>')
            *c = R_OUT;
        //if (c == '>>')
          //  c = R_OUT_A;
        if (*c == '<')
            *c = R_IN;
        if (*c == '$')
            *c = VAR;
    } 
}

//je remplace les quotes par un chiffre, et lorsque je traiterai ma commande
//je remplacerai mon chiffre par un espace  

void    double_quotes(char *c, int *q, int *dq)
{
    if (!*q && !*dq) //ouverture des doubles quotes
    {
        *dq = 1;
        *c = REPLACED;
    }
    if (*dq)         //fermetures des doubles quotes
    {
        *dq = 0;
        *c = REPLACED;
    }
}

//check si y a un backslash, je remplace le caractere par un caractere neutre pour ne pas
//affecter mon programme 

void    backslash(char *line, int *i, int *q, int *dq)
{
   if (line[*i] == '\\' && line[*i + 1] == '|')
   {
       line[*i] = BS;
       line[*i + 1] = PIPE;
   }
  else if (line[*i] == '\\' && line[*i + 1] == ';')
   {
       line[*i] = BS;
       line[*i + 1] = SEMI;
   }
   else if (line[*i] == '\\' && line[*i + 1] == '>')
   {
       line[*i] = BS;
       line[*i + 1] = R_OUT;
   }

   else if (line[*i] == '\\' && line[*i + 1] == '<')
   {
       line[*i] = BS;
       line[*i + 1] = R_IN;
   }
   else if (line[*i] == '\\' && line[*i + 1] == '$')
   {
       line[*i] = BS;
       line[*i + 1] = VAR;
   }
}

//analyse si ya des quotes ou backslash, quel type de quote et remplace 
//par un caractere qui ne va pas influencer le split en plusieurs commandes
//le backslash permet dannuler laction qui suit, par exemple 
//echo "$USER" va sortir Mathis alors que echo "/$USER" va sortir USER
//idem pour echo bitch > ok va creer un fichier ok et ecrire bitch alors que echo bitch />ok ecrit bitch en stdout
void    quotes(char *line)
{
    int i;
    int q;
    int dq;

    i = 0;
    q = 0;
    dq = 0;
    while (line[i])
    {
        //TODO: detecter si y a un dq + \ cela annule la " et on passe en '
        backslash(line, &i, &q, &dq);
        if (line[i] == '"')
           double_quotes(&line[i], &q, &dq);
       // else if (line[i] == '''');
         //   simple_quotes(&line[i]), &q, &dq);
        else 
            clean_actions(&line[i], &q, &dq); 
        i++;
    }
}