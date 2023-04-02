#ifndef CONTROLLER_H_INCLUDED
#define CONTROLLER_H_INCLUDED
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include<stdio.h>
#include <stdbool.h>
#include <ctype.h>
int Randomiser(int minVal, int maxval);
void SkrivTilFil(char filNavn[], char filtilstand[2], char data[3]);
int FilCou(char filNavn[], int Cou);
void LeasFraFil(char filNavn[], char filtilstand[2], char felter [][4], char Besked[10]);
int MaxVal(const int Val[], int laengde);
// Læsning af Værdi fra fil
void Dele(char dele[][50], char val[], char* deleChar);
void NyLinje(int linjeNummer);
void RydFil(char filNavn[]);
bool KanDele(char data[], char splitChar);
int CharTilInt(char ch);

#endif // CONTROLLER_H_INCLUDED
