#ifndef GAMELOGIC_H_INCLUDED
#define GAMELOGIC_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>
#include "ControlTheGame.h"

static const char SoliDragter[5] = {'H', 'D', 'S', 'C', '\0'};
static const char soliKort[14] = {'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'A', '\0'};
struct Kort {
    //Dette holder vores kort
    //Første char gemmer vores kort Vardi f.eks. A for Ace og D for diamanter
    //The second char stores our card Fundament e.g Q for Queen and K for King
    char Vardi[3];
    //Denne Pointer repræsenterer en hukommelsesadresse på det næste kort på vores linkede liste
    struct Kort *Naeste;
    bool Vendt;
    char Farve;

};


struct Pile {

    struct Kort *KortListe;

};

struct Fundament {
    char FoundationLetter;
    struct Kort *KortListe;
};

struct Spil {

    struct Pile Piles[7];
    struct Fundament Fundamenter[4];
//
};

struct Bevagelsesoversigt {
    bool ErGyldig;
    char Besked[50];
};
//Kort vil blive brugt til at repræsentere cardItem og dets række/kolonne


//Prototyper
void Initialiser(struct Spil *spil);
void InitialiserPiles(struct Pile Piles[]);
void InitialiserFoundations(struct Fundament Foundations[]);
void IndlasSpil();
void SW(struct Spil *spil, char Besked[10]);
void VendtKort(struct Kort *KortListe);
void Loading(char filNavn[], struct Spil *spil, char Besked[4], int flag);
void VisPiles(struct Spil *spil);
void VisFundamenter(struct Fundament Foundations[]);
void Udfore(struct Spil *spil);
void TilfojDisFound(struct Fundament Foundations[], char PileGrid[][13][2], int kolonne);
void TilfojeDisPile(struct Pile _Pile, char PGrid[][7][3], int kolonne);
bool erKortIPile(struct Kort *kort, char KortVaerdi[2]);
struct Kort *faKort(struct Kort *List, int Index);
struct Kort *faKort1(struct Kort *kortListe, char Kortvaerdi[2]);
int ListeCou(struct Kort *fListe);
void TilfojeTilListe1(struct Kort *KortListe, struct Kort *KortTilTilfoje);
struct Bevagelsesoversigt IsValidMove(struct Kort *SidsteKort, struct Kort *tilfojeKort);
void TilfojKortTilPile(struct Pile Piles[], char data[53][4], int Pilekolonne, int startIndx, int endIndx, int vendeCou);
void SpilAktion(char Kommando[20], struct Spil *spil, char SidsteKommando[50], bool ErSpilAktiv);
bool FlytKortTilPile(struct Spil *spil, int EndeligPileKolonne, char data[2]);
bool FlytKortTilFund(struct Spil *spil, int SidstePileKolonne, char data[2]);
void VisFundamenter1(struct Spil *spil);
void FjernSidsteKort(struct Spil *spil, int PileNummer);
void FlytKortTilPile1(struct Spil *spil, int EndligPileKolonne, int curPilekolonne);
void SplitDeck(struct Spil *spil, int SNummer, char Besked[]);
void TilfaeldigBlanding(struct Spil *spil, char Besked[]);
void GemDekKort(struct Spil *spil, char filnavn[], char Besked[]);
void NulstilSpil(struct Spil *spil, char message[]);
void FlytKortTilPile2(struct Spil *spil, int EndeligPileKolonne, int curPileKolonne);
void AfslutSpil();
void TilfojeTilListe2(struct Spil *spil, struct Kort *TilfojeKort, int pNummer);
void TilfojeTilListe3(struct Spil *spil, struct Kort *CardToAdd, int PNumber);
struct Bevagelsesoversigt IsValidMove2(struct Kort *SidsteKort, struct Kort *tilfojeKort);
#endif // GAMELOGIC_H_INCLUDED
