#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <Windows.h>
#include "Canli.h"
#include "Habitat.h"
#include "Bitki.h"
#include "Bocek.h"
#include "Sinek.h"
#include "Pire.h"


void Goruntu(int rows, int cols, Canli grid[rows][cols]){

    //sleep(1); // linux
    Sleep(500); // windows
    printf("\e[1;1H\e[2J");

    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {
            if (grid[x][y] != NULL) {
                int tmp_tip = 0;
                Bitki redundant_cast = (Bitki)grid[x][y];
                tmp_tip = redundant_cast->base->tip;

                if(tmp_tip == 1){
                    Bitki tmp_b = (Bitki)grid[x][y];
                    printf("%s", tmp_b->base->gorunum());
                }else if(tmp_tip == 2){
                    Bocek tmp_c = (Bocek)grid[x][y];
                    printf("%s", tmp_c->base->gorunum());
                }else if(tmp_tip == 3){
                    Sinek tmp_s = (Sinek)grid[x][y];
                    printf("%s", tmp_s->base->gorunum());
                }else if(tmp_tip == 4){
                    Pire tmp_p = (Pire)grid[x][y];
                    printf("%s", tmp_p->base->gorunum());
                }else
                    printf("  ");
            }else
                printf("X ");
        }
        printf("\n");
    }
}


void Kazanan(int rows, int cols, Canli grid[rows][cols], int kazanan_row, int kazanan_col){
    Bitki b_kazanan; Bocek c_kazanan; Sinek s_kazanan; Pire p_kazanan;
    Bitki check_tip = (Bitki)grid[kazanan_row][kazanan_col];
    int typ = check_tip->base->tip;
    if(typ == 1){
        b_kazanan = (Bitki)grid[kazanan_row][kazanan_col];
        printf("Kazanan: %s : (%d,%d)\n", b_kazanan->base->gorunum(), kazanan_row, kazanan_col);
        b_kazanan->yoket(b_kazanan);
    }else if(typ == 2){
        c_kazanan = (Bocek)grid[kazanan_row][kazanan_col];
        printf("Kazanan: %s : (%d,%d)\n", c_kazanan->base->gorunum(), kazanan_row, kazanan_col);
        c_kazanan->yoket(c_kazanan);
    }else if(typ == 3){
        s_kazanan = (Sinek)grid[kazanan_row][kazanan_col];
        printf("Kazanan: %s : (%d,%d)\n", s_kazanan->base->gorunum(), kazanan_row, kazanan_col);
        s_kazanan->yoket(s_kazanan);
    }else if(typ == 4){
        p_kazanan = (Pire)grid[kazanan_row][kazanan_col]; 
        printf("Kazanan: %s : (%d,%d)\n", p_kazanan->base->gorunum(), kazanan_row, kazanan_col);
        p_kazanan->yoket(p_kazanan);
    }
}


void Oyun(const char* filename) {
    
    FILE *file = fopen("Veri.txt", "r");
    if (!file) {
        perror("Dosyayi acarken hata olustu!");
        return;
    }

    char line[1024];
    int cols = 0, rows = 0;
    if (fgets(line, sizeof(line), file)) {
        int num;
        char *ptr = line;
        while (sscanf(ptr, "%d", &num) == 1) {
            cols++;
            ptr = strchr(ptr, ' ');
            if (!ptr) break;
            while (*ptr == ' ') ptr++;
        }
        rows = 1;
    }

    while (fgets(line, sizeof(line), file))
        rows++;
    fclose(file);

    file = fopen(filename, "r");
    if (!file) {
        perror("Dosyayi acarken hata olustu!");
        return;
    }

    int num;
    Canli grid[rows][cols];
    int i = 0, j = 0;
    Canli canli;
    while (fscanf(file, "%d", &num) != EOF) {

        canli = NULL;

        if (num >= 1 && num <= 9) { // Bitki
            canli = (Canli)OlusturucuBitki(num, 1);
        } else if (num >= 10 && num <= 20) { // Bocek
            canli = (Canli)OlusturucuBocek(num, 2);
        } else if (num >= 21 && num <= 50) { // Sinek
            canli = (Canli)OlusturucuSinek(num, 3);
        } else if (num >= 51 && num <= 99) { // Pire
            canli = (Canli)OlusturucuPire(num, 4);
        }

        if(canli)
            grid[i][j] = canli;

        j++;
        if (j == cols) { i++; j = 0; }
    }

    fclose(file);

    Goruntu(rows, cols, grid);

    printf("\nBaslatmak icin bir tusa basin: ");
    getchar();

    OyunMantik(rows, cols, grid);
}


void OyunMantik(int rows, int cols, Canli grid[rows][cols]){
    int kazanan_row = 0, kazanan_col = 0;
    for (int x = 0; x < rows; x++) {
        for (int y = 0; y < cols; y++) {

                int tmp_tip = 0, tmp_tip_next = 0, next_row_flag = 0;
                Bitki redundant_cast = (Bitki)grid[kazanan_row][kazanan_col];
                tmp_tip = redundant_cast->base->tip;

                if(y + 1 != cols){
                    redundant_cast = (Bitki)grid[x][y + 1];
                }else if(x + 1 != rows){
                    redundant_cast = (Bitki)grid[x + 1][0];
                    next_row_flag++;
                }else{
                    break;
                }
                tmp_tip_next = redundant_cast->base->tip;
                
                switch(tmp_tip){
                    case 1:
                        // Bitki -> Pire ya da Bitki -> Sinek
                        if(tmp_tip_next == 3){
                            Sinek s;
                            if(next_row_flag == 0){
                                s = (Sinek)grid[x][y + 1];
                                s->yoket(s);
                                grid[x][y + 1] = NULL;
                            }else{
                                s = (Sinek)grid[x + 1][0];
                                s->yoket(s);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 4){
                            Pire p;
                            if(next_row_flag == 0){
                                p = (Pire)grid[x][y + 1];
                                p->yoket(p);
                                grid[x][y + 1] = NULL;
                            }else{
                                p = (Pire)grid[x + 1][0];
                                p->yoket(p);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 1){

                            Bitki b_kazanan, b_next;
                            b_kazanan = (Bitki)grid[kazanan_row][kazanan_col];
                            if(next_row_flag == 0)
                                b_next = (Bitki)grid[x][y + 1];
                            else
                                b_next = (Bitki)grid[x + 1][0];

                            if(b_kazanan->base->guc >= b_next->base->guc){
                                b_next->yoket(b_next);
                                if(next_row_flag == 0)
                                    grid[x][y + 1] = NULL;
                                else
                                    grid[x + 1][0] = NULL;
                            }else if(b_kazanan->base->guc < b_next->base->guc){
                                b_kazanan->yoket(b_kazanan);
                                grid[kazanan_row][kazanan_col] = NULL;
                                if(next_row_flag == 0){
                                    kazanan_row = x;
                                    kazanan_col = y + 1;
                                }else{
                                    kazanan_row = x + 1;
                                    kazanan_col = 0;
                                }
                            }

                        }else{
                            Bitki b = (Bitki)grid[kazanan_row][kazanan_col];
                            b->yoket(b);
                            grid[kazanan_row][kazanan_col] = NULL;
                            if(next_row_flag == 0){
                                kazanan_row = x;
                                kazanan_col = y + 1;
                            }else{
                                kazanan_row = x + 1;
                                kazanan_col = 0;
                                next_row_flag = 0;
                            }
                        }
                        break;

                    case 2:
                        // Bocek -> Bitki ya da Bocek -> Pire
                        if(tmp_tip_next == 1){
                            Bitki b;
                            if(next_row_flag == 0){
                                b = (Bitki)grid[x][y + 1];
                                b->yoket(b);
                                grid[x][y + 1] = NULL;
                            }else{
                                b = (Bitki)grid[x + 1][0];
                                b->yoket(b);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 4){
                            Pire p;
                            if(next_row_flag == 0){
                                p = (Pire)grid[x][y + 1];
                                p->yoket(p);
                                grid[x][y + 1] = NULL;
                            }else{
                                p = (Pire)grid[x + 1][0];
                                p->yoket(p);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 2){

                            Bocek c_kazanan, c_next;
                            c_kazanan = (Bocek)grid[kazanan_row][kazanan_col];
                            if(next_row_flag == 0)
                                c_next = (Bocek)grid[x][y + 1];
                            else
                                c_next = (Bocek)grid[x + 1][0];

                            if(c_kazanan->base->guc >= c_next->base->guc){
                                c_next->yoket(c_next);
                                if(next_row_flag == 0)
                                    grid[x][y + 1] = NULL;
                                else
                                    grid[x + 1][0] = NULL;
                            }else if(c_kazanan->base->guc < c_next->base->guc){
                                c_kazanan->yoket(c_kazanan);
                                grid[kazanan_row][kazanan_col] = NULL;
                                if(next_row_flag == 0){
                                    kazanan_row = x;
                                    kazanan_col = y + 1;
                                }else{
                                    kazanan_row = x + 1;
                                    kazanan_col = 0;
                                }
                            }

                        }else{
                            Bocek c = (Bocek)grid[kazanan_row][kazanan_col];
                            c->yoket(c);
                            grid[kazanan_row][kazanan_col] = NULL;
                            if(next_row_flag == 0){
                                kazanan_row = x;
                                kazanan_col = y + 1;
                            }else{
                                kazanan_row = x + 1;
                                kazanan_col = 0;
                                next_row_flag = 0;
                            }
                        }
                        break;

                    case 3:
                        // Sinek -> Bocek ya da Sinek -> Pire
                        if(tmp_tip_next == 2){
                            Bocek c;
                            if(next_row_flag == 0){
                                c = (Bocek)grid[x][y + 1];
                                c->yoket(c);
                                grid[x][y + 1] = NULL;
                            }else{
                                c = (Bocek)grid[x + 1][0];
                                c->yoket(c);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 4){
                            Pire p;
                            if(next_row_flag == 0){
                                p = (Pire)grid[x][y + 1];
                                p->yoket(p);
                                grid[x][y + 1] = NULL;
                            }else{
                                p = (Pire)grid[x + 1][0];
                                p->yoket(p);
                                grid[x + 1][0] = NULL;
                                next_row_flag = 0;
                            }
                        }else if(tmp_tip_next == 3){

                            Sinek s_kazanan, s_next;
                            s_kazanan = (Sinek)grid[kazanan_row][kazanan_col];
                            if(next_row_flag == 0)
                                s_next = (Sinek)grid[x][y + 1];
                            else
                                s_next = (Sinek)grid[x + 1][0];

                            if(s_kazanan->base->guc >= s_next->base->guc){
                                s_next->yoket(s_next);
                                if(next_row_flag == 0)
                                    grid[x][y + 1] = NULL;
                                else
                                    grid[x + 1][0] = NULL;
                            }else if(s_kazanan->base->guc < s_next->base->guc){
                                s_kazanan->yoket(s_kazanan);
                                grid[kazanan_row][kazanan_col] = NULL;
                                if(next_row_flag == 0){
                                    kazanan_row = x;
                                    kazanan_col = y + 1;
                                }else{
                                    kazanan_row = x + 1;
                                    kazanan_col = 0;
                                }
                            }

                        }else{
                            Sinek s = (Sinek)grid[kazanan_row][kazanan_col];
                            s->yoket(s);
                            grid[kazanan_row][kazanan_col] = NULL;
                            if(next_row_flag == 0){
                                kazanan_row = x;
                                kazanan_col = y + 1;
                            }else{
                                kazanan_row = x + 1;
                                kazanan_col = 0;
                                next_row_flag = 0;
                            }
                        }
                        break;

                    case 4:
                        // Pire hicbir canliyi yiyemiyor
                        if(tmp_tip_next == 4){

                            Pire p_kazanan, p_next;
                            p_kazanan = (Pire)grid[kazanan_row][kazanan_col];
                            if(next_row_flag == 0)
                                p_next = (Pire)grid[x][y + 1];
                            else
                                p_next = (Pire)grid[x + 1][0];

                            if(p_kazanan->base->guc >= p_next->base->guc){
                                p_next->yoket(p_next);
                                if(next_row_flag == 0)
                                    grid[x][y + 1] = NULL;
                                else
                                    grid[x + 1][0] = NULL;
                            }else if(p_kazanan->base->guc < p_next->base->guc){
                                p_kazanan->yoket(p_kazanan);
                                grid[kazanan_row][kazanan_col] = NULL;
                                if(next_row_flag == 0){
                                    kazanan_row = x;
                                    kazanan_col = y + 1;
                                }else{
                                    kazanan_row = x + 1;
                                    kazanan_col = 0;
                                }
                            }

                        }else{
                            Pire p = (Pire)grid[kazanan_row][kazanan_col];
                            p->yoket(p);
                            grid[kazanan_row][kazanan_col] = NULL;
                            if(next_row_flag == 0){
                                kazanan_row = x;
                                kazanan_col = y + 1;
                            }else{
                                kazanan_row = x + 1;
                                kazanan_col = 0;
                                next_row_flag = 0;
                            }
                        }
                        break;

                    default:
                        break;
                }
                Goruntu(rows, cols, grid);
                printf("\n");
        }
    }

    Kazanan(rows, cols, grid, kazanan_row, kazanan_col);
}


