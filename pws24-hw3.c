/*
 * pws24-hw3.c
 *
 *  Created on: Apr 17, 2016
 *      Author: Patrick Stevens
 */
 
#include<stdio.h>
#include<string.h>

#define ORG_RANK 0
#define TOP_NUM 100
#define YEAR_INC 10
#define MAX_NAME_LEN 20


void babyName(const char *temp, char *idvName) {
     while (*temp != ',') {
         *idvName++ = *temp++;
      }
     *idvName = 0;
}

int searchRank(char(*bbyNames)[MAX_NAME_LEN], const char *idvName) {
     int index = 0;
     while (strcmp(idvName, bbyNames[index]) != 0 && strlen(bbyNames[index]) > 0) {
         index++;
     }
     return index;
}

int processName(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], const char *idvName, int yearIndex, int rankInYear) {
     int index, x = 0;
     index = searchRank(bbyNames, idvName);
     if (strlen(bbyNames[index]) == 0) {
         strcpy(bbyNames[index], idvName);
         while (x < YEAR_INC){
             bbyRank[index][x] = ORG_RANK;
             x++;
         }
         bbyRank[index][yearIndex] = rankInYear;
         bbyNames[index + 1][0] = 0;
         return 1;
     } else {
         bbyRank[index][yearIndex] = rankInYear;
         return 0;
     }
}

int inputFile(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], int totalNum, const char *file, int yearIndex) {
     FILE *outfile;
     int x = 0;
     char idvName[MAX_NAME_LEN], temp[128];
     if (NULL == (outfile = fopen(file, "r"))) {
         return 0;
     }
     while(x < TOP_NUM) {
         fscanf(outfile, "%s", temp);
         babyName(temp, idvName);
         totalNum += processName(bbyNames, bbyRank, idvName, yearIndex, 1 + x);
         x++;
     }
     fclose(outfile);
     return totalNum;
}

int allFiles(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], char **totalFiles, unsigned fileNum) {  
     int yearNum = 0, totalNum = 0;
     while (fileNum--) {
         totalNum = inputFile(bbyNames, bbyRank, totalNum, *totalFiles, yearNum);
         yearNum++;
         totalFiles++; 
     }
     return totalNum;
}

void switchRank(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], int low, int idx) {
     char temp[MAX_NAME_LEN];
     int x = 0, pws;
     //same
     if (low == idx) {
         return;
     }
     //switch
     strcpy(temp, bbyNames[low]);
     strcpy(bbyNames[low], bbyNames[idx]);
     strcpy(bbyNames[idx], temp);
     while(x < YEAR_INC) {
         pws = bbyRank[low][x];
         bbyRank[low][x] = bbyRank[idx][x];
         bbyRank[idx][x] = pws;
         x++;
    }
}

void sortNames(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], int totalNum) {
     int x = 0, j, low;
     //sort
     while(x < totalNum) { 
         low = x;
         for (j = x + 1; j < totalNum; ++j) {
             if (strcmp(bbyNames[j], bbyNames[low]) < 0)
                low = j;
         }
         if (low != x) {
             switchRank(bbyNames, bbyRank, low, x);
         }
         x++;
    }
}

void writeToFile(char (*bbyNames)[MAX_NAME_LEN], int (*bbyRank)[YEAR_INC], int totalNum, char *csvfile) {
     int x = 0, n;
     //summary.csv
     FILE *outfile;
     outfile = fopen(csvfile, "w");
     if (!outfile) {
         printf("Problem opening te file!\n");
         return 1;
     }
     fprintf(outfile, "%s", "Name");
     while(x < YEAR_INC) {
        fprintf(outfile, ",%d", 1920 + (10 * x));
        x++;
      }
     n = 0;
     while (totalNum--) {
           fprintf(outfile, "\n");
           fprintf(outfile, "%s", bbyNames[n]);
            int x = 0;
          while(x < YEAR_INC) {
              if (ORG_RANK == bbyRank[n][x]) {
                  fprintf(outfile, ",");
              } else {
                  fprintf(outfile, ",%d", bbyRank[n][x]);
              }
              x++;
        }
        n++;
     }
     fclose(outfile);
}

int main(void) {
     int totalNum, bbyRank[TOP_NUM * YEAR_INC][YEAR_INC] = {0};
     char bbyNames[TOP_NUM * YEAR_INC][MAX_NAME_LEN] = {0};
     char *totalFiles[] = {"names/yob1920.txt", "yob1930.txt", "yob1940.txt", "yob1950.txt",
         "yob1960.txt", "yob1970.txt", "yob1980.txt", "yob1990.txt",
         "yob2000.txt", "yob2010.txt"};
   
    
     totalNum = allFiles(bbyNames, bbyRank, totalFiles, sizeof (totalFiles) / sizeof (totalFiles[0]));
     sortNames(bbyNames, bbyRank, totalNum);
     writeToFile(bbyNames, bbyRank, totalNum, "summary.csv");

     return 1;
}
