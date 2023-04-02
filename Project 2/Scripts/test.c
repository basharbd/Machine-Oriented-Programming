//
// Created by Malaz on 10-05-2022.
//
#include "ControlTheGame.h"

int Run(int minv, int maxV) {
    int val = rand() % (maxV - minv + 1) + minv;
    return val;
}
int main1() {
    int mem = Run(1, 51);
    if (mem < 52) {
        printf("passed\n");
    }
}
