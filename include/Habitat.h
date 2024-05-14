#ifndef HABITAT_H
#define HABITAT_H

#include "Canli.h"

void Oyun(const char* filename);
void Goruntu(int rows, int cols, Canli grid[rows][cols]);
void Kazanan(int rows, int cols, Canli grid[rows][cols], int kazanan_row, int kazanan_col);
void OyunMantik(int rows, int cols, Canli grid[rows][cols]);

#endif // HABITAT_H
