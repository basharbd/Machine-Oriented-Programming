#include "ControlTheGame.h"

#define printf_s printf

int Randomiser(int minVal, int maxval) {
//int rand(void) returnerer et pseudo-tilfældigt tal i intervallet 0 til RAND_MAX.
    int value = rand() % (maxval - minVal + 1) + minVal;
    return value;

}

void SkrivTilFil(char filNavn[], char filtilstand[2], char data[3]) {
    FILE *stream;
    //for at oprette en ny fil eller for at åbne en eksisterende fil. Dette kald vil initialisere et
    // objekt af typen FILE, som indeholder al den information, der er nødvendig for at styre strømmen.
    stream = fopen(filNavn, filtilstand);
    char nyData[4];
    // strcpy() to copy strings
    strcpy(nyData, data);
    //sammenkæder (forbinder) funktionen strcat() to strenge.
    strcat(nyData, "\n");
    //skriver data fra det array, der peges på, ved ptr til den givne stream.
    fwrite(nyData, sizeof(char), strlen(nyData), stream);
//Lukker stream
    fclose(stream);
}

void NyLinje(int linjeNummer) {

    for (int i = 0; i < linjeNummer; i++) {

        printf_s("\n");
    }
}

int FilCou(char filNavn[], int Cou) {
    FILE *stream;
    int FilCou = 0;
    char buf[5];

    stream = fopen(filNavn, "r");//r
    if (stream != NULL) {


        while (fread(buf, sizeof(char), 3, stream) > 0) {
            FilCou++;
        }
    }


    fclose(stream);
    return FilCou;
}

void RydFil(char filNavn[]) {
    FILE *stream;
    stream = fopen(filNavn, "w");
    fclose(stream);

}

int MaxVal(const int Val[], int laengde) {
    int maxval = 0;

    for (int j = 0; j < laengde; j++) {
        if (Val[j] > maxval) {
            maxval = Val[j];
        }
    }
    return maxval;
}


void LeasFraFil(char filNavn[], char filtilstand[2], char felter[][4], char Besked[10]) {
    FILE *stream;

    char buf[4];

    int leaseCou = 0;
    stream = fopen(filNavn, filtilstand);
    if (stream != NULL) {
        //læser data fra den givne stream ind i det array, der peges på, af ptr.
        while (fread(buf, sizeof(char), 3, stream) > 0 && leaseCou < 52) {
            strcpy(felter[leaseCou], buf);

            leaseCou++;

        }
        strcpy(Besked, "OK");
    }
    {
        if (leaseCou != 52) {
            strcpy(Besked, "Mislykkedes");
        }

    }

    fclose(stream);

}


void Dele(char dele[][50], char val[], char *deleChar) {
    int Coun = 0;

    char *temp;
//opdeler streng str i en række tokens ved hjælp af afgrænsningstegnet delim
    temp = strtok(val, deleChar);

    while (temp != NULL) {
        strcpy(dele[Coun], temp);
        temp = strtok(NULL, deleChar);

        Coun++;
    }

}

int CharTilInt(char ch) {
    int hh = ch - '0';

    return hh;
}

bool KanDele(char data[], char splitChar) {


    bool kanDeles = false;
    char *pos = strchr(data, splitChar);
    if (pos != NULL) {
        kanDeles = true;
    }
    for (int i = 0; data[i] != '\0'; i++) {
        if (data[i] == splitChar) {
            kanDeles = true;
        }
    }
    return kanDeles;
}