/*
//////////////////////////////////////////////////////////////////////
                        INTERFACE.H

    FUNĆOES PARA COMUNICAĆÃO ENTRE O CLIENTE E INTERFACE.

\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
*/

#ifndef _interface_h
#define _interface_h

void STstart();
void STinsertion(char *,char *, int );
void STsearchLemma(char *,char);
void STsearchWord(char *,char);
void STannotated(char *);
void clear_newlines();

#endif