#pragma once
#include "Header.h"
#include <stdio.h>
#include <stdlib.h>

void previewGen();
void moveBase(int ptr[][2], int len);
void moveLong(int ptr[][2], int len);

void gyokusho();
void hisha();
void kakugyo();
void kinsho();
void ginsho();
void keima();
void kyosha();
void fuhyo();
void ryuo();
void ryuma();

void capture();

void* moveRule[10] = { gyokusho, hisha, kakugyo, kinsho, ginsho, keima, kyosha, fuhyo ,ryuo ,ryuma };


