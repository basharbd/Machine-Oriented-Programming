#include "Game.h"
#include <unistd.h>
//Created by Bashar
#define printf_s printf


void SW(struct Spil *spil, char Besked[10]) {

    for (int i = 0; i < 7; i++) {
        VendtKort(spil->Piles[i].KortListe);
    }
    strcpy(Besked, "OK");
}


static bool isValid = false;

void Loading(char filNavn[], struct Spil *spil, char Besked[4], int flag) {
    char LaesFelter[53][4];
    LeasFraFil(filNavn, "r", LaesFelter, Besked);
    int filCou = FilCou(filNavn, 0);

    if (filCou < 52 || filCou > 52) {
        strcpy(Besked, "mislykkedes");
    }


    if (strcmp(Besked, "OK") == 0) {

        if (flag == 0) {


            int KortCount = 0;
            while (true) {
                for (int j = 0; j < 7; j++) {

                    if (KortCount < 7) {

                        spil->Piles[j].KortListe = (struct Kort *) malloc(sizeof(struct Kort));
                        spil->Piles[j].KortListe->Naeste = NULL;
                        char l[3];
                        l[0] = LaesFelter[KortCount][0];
                        l[1] = LaesFelter[KortCount][1];
                        l[2] = '\0';
                        spil->Piles[j].KortListe->Vendt = false;
                        strcpy(spil->Piles[j].KortListe->Vardi, l);
                        spil->Piles[j].KortListe->Farve = spil->Piles[j].KortListe->Vardi[1];

                    } else {
                        if (KortCount > 52 - 1) {
                            return;
                        }

                        struct Kort *kort = (struct Kort *) malloc(sizeof(struct Kort));
                        kort->Naeste = NULL;

                        char loa[3];
                        loa[0] = LaesFelter[KortCount][0];
                        loa[1] = LaesFelter[KortCount][1];
                        loa[2] = '\0';


                        strcpy(kort->Vardi, loa);
                        kort->Farve = kort->Vardi[1];


                        kort->Vendt = false;

                        TilfojeTilListe1(spil->Piles[j].KortListe, kort);

                    }

                    KortCount++;
                }
            }
        } else if (flag == 1) {


            TilfojKortTilPile(spil->Piles, LaesFelter, 0, 0, 0, 0);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 1, 1, 6, 1);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 2, 7, 13, 2);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 3, 14, 21, 3);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 4, 22, 30, 4);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 5, 31, 40, 5);
            VisPiles(spil);
            TilfojKortTilPile(spil->Piles, LaesFelter, 6, 41, 51, 6);
            VisPiles(spil);
        }

    }


}


void IndlasSpil() {

    struct Spil *_spil = (struct Spil *) malloc(sizeof(struct Spil));
    Initialiser(_spil);

    Udfore(_spil);
}


static struct Spil *hukommelse;
static int ErSpilAktiv = false;

void Udfore(struct Spil *spil) {
    char inputStr[50];
    NyLinje(3);
    bool ErSpilAktiv = false;
    char SidsteKomand[50];
    strcpy(SidsteKomand, "");
    while (true) {
        printf("Indlaese:");
        fgets(inputStr, 50, stdin);

        SpilAktion(inputStr, spil, SidsteKomand, ErSpilAktiv);
    }

}


void SpilAktion(char Kommando[20], struct Spil *spil, char SidsteKommando[50], bool ErSpilAktiv) {

    char SpillerKommando[2][50];
    char splittelse[] = " ";


    char Besked[10];


    Dele(SpillerKommando, Kommando, splittelse);
    char cr = ' ';
    if (KanDele(Kommando, cr) == true) {
        isValid = true;

    } else {
        isValid = false;

    }


    if (strstr(SpillerKommando[0], "LD") != NULL && ErSpilAktiv == false) {
        if (strlen(SpillerKommando[1]) > 4) {

            Loading(SpillerKommando[0], spil, Besked, 0);
        } else {
            Loading("Kort.txt", spil, Besked, 0);
        }
//Strcmp() sammenligner to strenge tegn for tegn. Hvis strengene er ens, returnerer funktionen 0.
// og hvis den er equal til 0 så skal fanktion visPile vises

        if (strcmp(Besked, "OK") == 0) {
            VisPiles(spil);
        }

        printf("sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(SpillerKommando[0], "SW") != NULL && ErSpilAktiv == false) {
        SW(spil, Besked);
        if (strcmp(Besked, "OK") == 0) {
            VisPiles(spil);
        }


        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(SpillerKommando[0], "SI") != NULL && ErSpilAktiv == false) {
        int nsplitNumber = 0;
        nsplitNumber = Randomiser(1, 51);
        if (strcmp(SpillerKommando[1], "") != 0) {
            char *ptr;
            nsplitNumber = strtol(SpillerKommando[1], &ptr, 10);

        }

        SplitDeck(spil, nsplitNumber, Besked);


        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(SpillerKommando[0], "SR") != NULL && ErSpilAktiv == false) {

        TilfaeldigBlanding(spil, Besked);


        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(SpillerKommando[0], "SD") != NULL && ErSpilAktiv == false) {
        GemDekKort(spil, SpillerKommando[1], Besked);

        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);

    } else if (strstr(SpillerKommando[0], "QQ") != NULL || ErSpilAktiv == true) {
        printf("Afslutter....");
        sleep(5);
        AfslutSpil();

    } else if (strstr(SpillerKommando[0], "P") != NULL && ErSpilAktiv == false) {
        ErSpilAktiv = true;
        Loading("Kort.txt", spil, Besked, 1);
        hukommelse = spil;
        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(SpillerKommando[0], "Q") != NULL || ErSpilAktiv == true) {

        NulstilSpil(hukommelse, Besked);
        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", Besked);
        strcpy(SidsteKommando, Kommando);
    } else if (strstr(Kommando, "->") != NULL && ErSpilAktiv == true) {
        char PlayKommando[2][50];
        char splitc1[] = "->";
        Dele(PlayKommando, Kommando, splitc1);

        char t[3];
        t[0] = PlayKommando[1][0];
        t[1] = PlayKommando[1][1];
        t[2] = '\0';


        if (strcmp("C1", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';
            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }
        if (strcmp("C2", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }
        if (strcmp("C3", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';
            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }


        if (strcmp("C4", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';
            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }


        if (strcmp("C5", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';
            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }
        if (strcmp("C6", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';
            if (FlytKortTilPile(spil, koloNummer - 1, tw) == true) {
                VisPiles(spil);
            }
        }
        if (strcmp("C7", t) == 0) {

            int KoloNummer = 0;
            KoloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilPile(spil, KoloNummer - 1, tw) == true) {
                VisPiles(spil);
            }

        }

        if (strcmp("F4", t) == 0) {

            int Kolonummer = 0;
            Kolonummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilFund(spil, Kolonummer - 1, tw) == true) {
                VisFundamenter1(spil);
            }

        }

        if (strcmp("F3", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilFund(spil, koloNummer - 1, tw) == true) {
                VisFundamenter1(spil);
            }

        }

        if (strcmp("F2", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilFund(spil, koloNummer - 1, tw) == true) {
                VisFundamenter1(spil);
            }

        }
        if (strcmp("F1", t) == 0) {

            int koloNummer = 0;
            koloNummer = CharTilInt(PlayKommando[1][1]);

            char tw[3];
            tw[0] = PlayKommando[0][0];
            tw[1] = PlayKommando[0][1];
            tw[2] = '\0';

            if (FlytKortTilFund(spil, koloNummer - 1, tw) == true) {
                VisFundamenter1(spil);
            }

        }


        printf("Sidste Kommando:%s \n", SidsteKommando);
        printf("Besked:%s \n\n", "OK");
        strcpy(SidsteKommando, Kommando);
    } else {

        if (ErSpilAktiv) {

            printf("Kommandoen er ikke tilgængelig\n");
        } else {
            printf("forkert kommando\n");
        }

        strcpy(SidsteKommando, Kommando);
    }


}


char *RandomCardValue1() {
    char kort[3];
    //Generer et tilfældigt kort fra de 12 kabalekort
    kort[0] = soliKort[Randomiser(0, 12)];
    //Generer en tilfældig dragt fra 4 kabaledragter
    kort[1] = SoliDragter[Randomiser(0, 3)];
    kort[2] = '\0';
    char *NyKort = (char *) malloc(sizeof(char) * 2);
    strcpy(NyKort, kort);

    return NyKort;
}


bool erKortIPile(struct Kort *kort, char KortVaerdi[2]) {
    struct Kort *next = kort;
    bool kortFindes = false;
    while (next != NULL) {
        if (strcmp(next->Vardi, KortVaerdi) == 0) {
            kortFindes = true;
            return kortFindes;

        }


        next = next->Naeste;
    }
    return kortFindes;
}


void VendtKort(struct Kort *KortListe) {
    struct Kort *kort = KortListe;
    while (kort != NULL) {
        if (kort->Vendt == false) {
            kort->Vendt = true;
        }
        kort = kort->Naeste;
    }

}


struct Kort *faKort(struct Kort *List, int Index) {
    struct Kort *kort = List;
    int listCounter = 0;
    while (listCounter != Index) {
        kort = kort->Naeste;
        listCounter++;
    }
    return kort;
}


struct Kort *faKort3(struct Kort *List) {

    struct Kort *kort = List;

    struct Kort *kort1;
    while (kort != NULL) {
        if (kort != NULL) {
            kort1 = kort;

        }
        kort = kort->Naeste;

    }


    return kort1;
};


struct Kort *faKort1(struct Kort *kortListe, char Kortvaerdi[2]) {

    bool kortFindes = false;
    struct Kort *kort = NULL;
    kortFindes = erKortIPile(kortListe, Kortvaerdi);
    if (kortFindes) {
        kort = kortListe;

        while (strcmp(kort->Vardi, Kortvaerdi) != 0 && kort->Naeste != NULL) {
            kort = kort->Naeste;

        }
    }
    return kort;
}


void TilfojeTilListe1(struct Kort *KortListe, struct Kort *KortTilTilfoje) {

    if (KortListe != NULL) {
        struct Kort *kort = NULL;

        kort = faKort3(KortListe);

        if (kort != NULL) {
            kort->Naeste = KortTilTilfoje;
        }
    } else {
        KortListe = KortTilTilfoje;
    }

}


void TilfojeTilListe2(struct Spil *spil, struct Kort *TilfojeKort, int pNummer) {

    if (spil->Piles[pNummer].KortListe != NULL) {
        struct Kort *kort = NULL;

        kort = faKort3(spil->Piles[pNummer].KortListe);

        if (kort != NULL) {
            kort->Naeste = TilfojeKort;

        }

    } else {
        spil->Piles[pNummer].KortListe = TilfojeKort;
    }

}


int ListeCou(struct Kort *fListe) {

    int listCounter = 0;
    if ((fListe != NULL)) {
        struct Kort *kort = fListe;
        while (kort != NULL) {
            kort = kort->Naeste;
            listCounter++;
        }

    }

    return listCounter;

}


void Initialiser(struct Spil *spil) {
    InitialiserPiles(spil->Piles);
    InitialiserFoundations(spil->Fundamenter);
    printf_s("Fundamenter\n\n");
    VisFundamenter(spil->Fundamenter);
    VisPiles(spil);


}


void InitialiserFoundations(struct Fundament Foundations[]) {

    for (int j = 0; j < 4; j++) {
        Foundations[j].FoundationLetter = SoliDragter[j];
        Foundations[j].KortListe = NULL;
    }

}


void InitialiserPiles(struct Pile Piles[]) {
    for (int i = 0; i < 7; i++) {
        Piles[i].KortListe = NULL;
    }


}


void VisFundamenter(struct Fundament Foundations[]) {


    char VisGrid[4][13][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strcpy(VisGrid[i][j], "");

        }
    }
    for (int i = 0; i < 4; i++) {

        TilfojDisFound(Foundations, VisGrid, i);
    }


    for (int i = 0; i < 4; i++) {
        printf_s("%c\t", Foundations[i].FoundationLetter);
        for (int j = 0; j < 13; j++) {
            printf_s("%s\t", VisGrid[i][j]);

        }
        printf_s("\n\n");
    }

}


void VisFundamenter1(struct Spil *spil) {

    char VisGrid[4][13][2];

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            strcpy(VisGrid[i][j], "");

        }
    }
    for (int i = 0; i < 4; i++) {

        TilfojDisFound(spil->Fundamenter, VisGrid, i);
    }


    for (int i = 0; i < 4; i++) {
        printf_s("%c\t", spil->Fundamenter[i].FoundationLetter);
        for (int j = 0; j < 13; j++) {
            printf_s("%s\t", VisGrid[i][j]);

        }
        printf_s("\n");
    }

}


struct Bevagelsesoversigt IsValidMove(struct Kort *SidsteKort, struct Kort *tilfojeKort) {


    struct Bevagelsesoversigt movesummary;
    movesummary.ErGyldig = true;

    strcpy(movesummary.Besked, "valid move");
    int curKortIndex = 0;
    int SidsteKortIndx = 0;

    if (tilfojeKort == NULL || SidsteKort == NULL) {

        movesummary.ErGyldig = true;

        strcpy(movesummary.Besked, "Pile eller kort findes ikke");

    } else {

        for (int i = 0; i < 13; i++) {

            if (soliKort[i] == SidsteKort->Vardi[0]) {
                SidsteKortIndx = i;
            }
            if (soliKort[i] == tilfojeKort->Vardi[0]) {
                curKortIndex = i;
            }
        }
        if (SidsteKort->Farve == tilfojeKort->Farve) {

            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "Farve match");
        } else if (strcmp(SidsteKort->Vardi, tilfojeKort->Vardi) == 0) {

            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "Kort match");
        } else if (tilfojeKort->Vendt == false) {
            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "Kort ikke synligt");
        } else if (SidsteKortIndx < curKortIndex) {
            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "kortet er større");
        }

    }


    return movesummary;

}


struct Bevagelsesoversigt IsValidMove2(struct Kort *SidsteKort, struct Kort *tilfojeKort) {


    struct Bevagelsesoversigt movesummary;
    movesummary.ErGyldig = true;

    strcpy(movesummary.Besked, "valid move");
    int curKortIndx = 0;
    int SidsteKortIndx = 0;

    if (tilfojeKort == NULL || SidsteKort == NULL) {

        movesummary.ErGyldig = false;

        strcpy(movesummary.Besked, "Pile eller kort findes ikke");

    } else {

        for (int i = 0; i < 13; i++) {

            if (soliKort[i] == SidsteKort->Vardi[0]) {
                SidsteKortIndx = i;
            }
            if (soliKort[i] == tilfojeKort->Vardi[0]) {
                curKortIndx = i;
            }
        }
        if (SidsteKort->Farve != tilfojeKort->Farve) {

            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "Farve ikke match");
        } else if (SidsteKortIndx != curKortIndx - 1) {
            movesummary.ErGyldig = false;
            strcpy(movesummary.Besked, "kortet ikke i den rigtige rækkefølge");
        }

    }


    return movesummary;

}


void TilfojDisFound(struct Fundament Foundations[], char PileGrid[][13][2], int kolonne) {
    struct Kort *kort = Foundations[kolonne].KortListe;
    int taeller = 0;
    while (kort != NULL) {
        if (kort->Vendt == true) {

            strcpy(PileGrid[kolonne][taeller], kort->Vardi);
        } else {
            strcpy(PileGrid[kolonne][taeller], "[]");

        }

        kort = kort->Naeste;
        taeller++;
    }
}


void VisPiles(struct Spil *spil) {

    int PileTaller[7];

    for (int i = 0; i < 7; i++) {
        PileTaller[i] = ListeCou(spil->Piles[i].KortListe);

    }

    int hojesteRaekke = MaxVal(PileTaller, 7);


    char DisGrid[hojesteRaekke][7][3];
    for (int i = 0; i < hojesteRaekke; i++) {
        for (int j = 0; j < 7; j++) {
            char tmp[2] = "";
            strcpy(DisGrid[i][j], tmp);
        }

    }

    for (int i = 0; i < 7; i++) {

        TilfojeDisPile(spil->Piles[i], DisGrid, i);
    }
    printf_s("\n");
    for (int i = 0; i < 7; i++) {
        printf_s("C%d\t", i + 1);
    }

    printf_s("\n\n");

    for (int i = 0; i < hojesteRaekke; i++) {
        for (int j = 0; j < 7; j++) {
            printf_s("%s\t", DisGrid[i][j]);

        }
        printf_s("\n");
    }


}


void TilfojeDisPile(struct Pile _Pile, char PGrid[][7][3], int kolonne) {
    if (_Pile.KortListe != NULL) {

        struct Kort *kort = _Pile.KortListe;
        int taeller = 0;
        while (kort != NULL) {
            if (kort->Vendt == true) {

                strcpy(PGrid[taeller][kolonne], kort->Vardi);
            } else {
                char tmp[3] = "[]";
                tmp[2] = '\0';

                strcpy(PGrid[taeller][kolonne], tmp);

            }

            kort = kort->Naeste;
            taeller++;
        }
    }

}


void
TilfojKortTilPile(struct Pile Piles[], char data[53][4], int Pilekolonne, int startIndx, int endIndx, int vendeCou) {
    int vendeCounting = 0;

    for (int i = startIndx; i <= endIndx; i++) {

        if (i == startIndx) {
            Piles[Pilekolonne].KortListe = (struct Kort *) malloc(sizeof(struct Kort));
            Piles[Pilekolonne].KortListe->Naeste = NULL;
            char lo[3];
            lo[0] = data[i][0];
            lo[1] = data[i][1];
            lo[2] = '\0';

            strcpy(Piles[Pilekolonne].KortListe->Vardi, lo);
            Piles[Pilekolonne].KortListe->Farve = Piles[Pilekolonne].KortListe->Vardi[1];
            if (Pilekolonne != 0) {
                Piles[Pilekolonne].KortListe->Vendt = false;
            } else {
                Piles[Pilekolonne].KortListe->Vendt = true;
            }

        } else {
            struct Kort *kort = (struct Kort *) malloc(sizeof(struct Kort));
            kort->Naeste = NULL;

            char loa[3];
            loa[0] = data[i][0];
            loa[1] = data[i][1];
            loa[2] = '\0';
            strcpy(kort->Vardi, loa);
            kort->Farve = kort->Vardi[1];


            if ((vendeCounting + 1) < vendeCou) {
                kort->Vendt = false;
                vendeCounting++;
            } else {
                kort->Vendt = true;
            }
            TilfojeTilListe1(Piles[Pilekolonne].KortListe, kort);
        }

    }


}


void SplitDeck(struct Spil *spil, int SNummer, char Besked[]) {

    int iIndex = 0;

    while (SNummer > 0) {

        int ListeCoun = ListeCou(spil->Piles[iIndex].KortListe);
        while (ListeCoun > 0) {
            FlytKortTilPile1(spil, 6, iIndex);
            VisPiles(spil);
            ListeCoun--;

            SNummer--;
            if (SNummer < 1) {
                ListeCoun = -1;
            }


        }
        if (iIndex < 7) {
            iIndex++;
        }


    }

    for (int i = 0; i < 5; i++) {
        if (spil->Piles[i].KortListe != NULL) {
            int ListCo = ListeCou(spil->Piles[i].KortListe);
            while (ListCo > 0) {
                FlytKortTilPile1(spil, 5, i);
                VisPiles(spil);
                ListCo--;
            }
        }

    }
    strcpy(Besked, "OK");
}


void TilfaeldigBlanding(struct Spil *spil, char Besked[]) {
    int RandomPile = Randomiser(0, 4);

    int Index = 5;
    while (Index < 7) {

        int ListCou = ListeCou(spil->Piles[Index].KortListe);
        while (ListCou > 0) {
            FlytKortTilPile2(spil, RandomPile, Index);
            VisPiles(spil);
            ListCou--;


        }
        Index++;
    }
    strcpy(Besked, "OK");
}

void GemDekKort(struct Spil *spil, char filnavn[], char Besked[]) {
    if (filnavn[0] == '\0' || strlen(filnavn) < 5) {
        strcpy(filnavn, "NyFil.txt");
        RydFil(filnavn);

    }

    for (int i = 0; i < 7; i++) {
        int Indx = 0;
        int ListCon = ListeCou(spil->Piles[i].KortListe);
        while (Indx < ListCon) {
            struct Kort *kort = faKort(spil->Piles[i].KortListe, Indx);
            SkrivTilFil(filnavn, "a", kort->Vardi);
            Indx++;
        }
    }
    strcpy(Besked, "OK");
}


bool FlytKortTilFund(struct Spil *spil, int SidstePileKolonne, char data[2]) {


    struct Kort *Kort1 = faKort3(spil->Fundamenter[SidstePileKolonne].KortListe);
    int curPileKol = 0;


    struct Kort *l = NULL;
    for (int i = 0; i < 7; i++) {
        struct Kort *kort3 = faKort1(spil->Piles[i].KortListe, data);

        if (kort3 != NULL) {

            curPileKol = i;

        }
    }
    l = faKort1(spil->Piles[curPileKol].KortListe, data);

    struct Bevagelsesoversigt flytSum = IsValidMove2(Kort1, l);

    if (flytSum.ErGyldig == false) {
        printf("%s\n", flytSum.Besked);
        return false;
    } else {
        FjernSidsteKort(spil, curPileKol);


        TilfojeTilListe3(spil, l, SidstePileKolonne);


        struct Kort *kortA = faKort3(spil->Piles[curPileKol].KortListe);


        return true;

    }


}


void TilfojeTilListe3(struct Spil *spil, struct Kort *CardToAdd, int PNumber) {

    if (spil->Fundamenter[PNumber].KortListe != NULL) {
        struct Kort *kort = NULL;

        kort = faKort3(spil->Fundamenter[PNumber].KortListe);

        if (kort != NULL) {
            kort->Naeste = CardToAdd;

        }

    } else {
        spil->Fundamenter[PNumber].KortListe = CardToAdd;
    }

}


void FlytKortTilPile1(struct Spil *spil, int EndligPileKolonne, int curPilekolonne) {

    struct Kort *kort = faKort3(spil->Piles[curPilekolonne].KortListe);
    FjernSidsteKort(spil, curPilekolonne);
    kort->Naeste = NULL;
    TilfojeTilListe1(spil->Piles[EndligPileKolonne].KortListe, kort);

}

void FlytKortTilPile2(struct Spil *spil, int EndeligPileKolonne, int curPileKolonne) {

    struct Kort *kort = faKort3(spil->Piles[curPileKolonne].KortListe);
    FjernSidsteKort(spil, curPileKolonne);
    kort->Naeste = NULL;
    if (spil->Piles[EndeligPileKolonne].KortListe == NULL) {
        spil->Piles[EndeligPileKolonne].KortListe = kort;
    } else {
        TilfojeTilListe1(spil->Piles[EndeligPileKolonne].KortListe, kort);
    }

}


bool FlytKortTilPile(struct Spil *spil, int EndeligPileKolonne, char data[2]) {
    struct Kort *kort1 = faKort3(spil->Piles[EndeligPileKolonne].KortListe);
    int curPilekolonne = 0;


    struct Kort *lo = NULL;
    for (int i = 0; i < 7; i++) {
        struct Kort *kort3 = faKort1(spil->Piles[i].KortListe, data);

        if (kort3 != NULL) {

            curPilekolonne = i;

        }
    }
    lo = faKort1(spil->Piles[curPilekolonne].KortListe, data);

    struct Bevagelsesoversigt moveSum = IsValidMove(kort1, lo);

    if (moveSum.ErGyldig == false) {
        printf("%s\n", moveSum.Besked);
        return false;
    } else {
        FjernSidsteKort(spil, curPilekolonne);


        TilfojeTilListe2(spil, lo, EndeligPileKolonne);

        struct Kort *kortA = faKort3(spil->Piles[curPilekolonne].KortListe);
        if (kortA != NULL) {
            if (kortA->Vendt == false) {
                kortA->Vendt = true;
            }
        }

        return true;

    }
}


void FjernSidsteKort(struct Spil *spil, int PileNummer) {

    int listCounter = ListeCou(spil->Piles[PileNummer].KortListe);
    int EndeligeIndex = listCounter - 2;
    if (listCounter > 1) {
        struct Kort *Kort3 = faKort(spil->Piles[PileNummer].KortListe, EndeligeIndex);
        if (EndeligeIndex >= 0) {

            Kort3->Naeste = NULL;
        } else {
            Kort3 = NULL;
        }
    } else {
        spil->Piles[PileNummer].KortListe = NULL;
    }
}


void NulstilSpil(struct Spil *spil, char message[]) {
    strcpy(message, "mislykkedes");
    VisPiles(spil);


    strcpy(message, "Ok");

}


void AfslutSpil() {

    exit(0);
}
