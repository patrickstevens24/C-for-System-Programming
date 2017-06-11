/*
 * hw2.c
 *
 *  Created on: Apr 11, 2016
 *      Author: Patrick Stevens
 */

#include <stdio.h>
int main(void) {

	      setvbuf(stdout, NULL, _IONBF, 0);
  
        FILE *infile = fopen("test.bmp", "rb");
        FILE *reflect = fopen("reflect.bmp", "wb");
        FILE *quad = fopen("quad.bmp", "wb");

        int filesize, width, height, imagesize;    
        int first[2], second[12], third[8], fourth[16];
        
        //read in orginal image
        
        fread(first, sizeof(char) ,2 ,infile);
        fread(&filesize, sizeof(char) ,4 ,infile);
        fread(second, sizeof(char) ,12 ,infile);
        fread(&width, sizeof(char), 4, infile);
        fread(&height, sizeof(char), 4, infile);
        fread(third, sizeof(char), 8, infile);
        fread(&imagesize, sizeof(char), 4, infile);
        fread(fourth, sizeof(char), 16, infile);

        unsigned char space[height][(width * 3)]; 
        unsigned char space2[height * 2][(width * 3) * 2];        
        unsigned char space3[height][(width * 3)*2];
        
        fread(space, sizeof(char) , height * width * 3, infile); 
        
        //code for the quad image
        
        int quadFileSize = 54;
        int quadWidth = width * 2;
        int quadHeight = height * 2;
        int quadImageSize = quadWidth * quadHeight;
        
        for (int r = 0 ; r < height * 2; r++) {            
          for (int c = 0; c < (width * 3) * 2; c++) {
             char temp = space[r/2][c];  
             space2[(r+ height*2)/2][c] = space[r/2][c];                      
             space2[r/2][c] = temp;
             
            }
        } 

        fwrite(first, sizeof(char) ,2 , quad);
        fwrite(&quadFileSize, sizeof(char) ,4 ,quad);
        fwrite(second, sizeof(char) ,12 ,quad);
        fwrite(&quadWidth, sizeof(char), 4, quad);
        fwrite(&quadHeight, sizeof(char), 4, quad);
        fwrite(third, sizeof(char), 8, quad);
        fwrite(&quadImageSize , sizeof(char), 4, quad);                
        fwrite(fourth, sizeof(char), 16, quad);
        fwrite(space2, sizeof(char), (quadHeight * 2 * (quadWidth * 3) * 2), quad);
        
        fread(space, sizeof(char) , height * width * 3, infile); 
        
        
        
        
        //code for the reflect image
        
        int reflectFileSize = 54;
        int reflectWidth = width * 2;
        int reflectHeight = height;
        int reflectImageSize = reflectWidth * reflectHeight;
        
        for (int r = 0 ; r < height; r++) {             
          for (int c = 0; c < (width * 3); c++) {
             char temp = space[r][c];                       
             space3[r][c] = temp;
             space3[r][c+width*3] = space[r][-c]; 
             
            }
        } 
        
        fwrite(first, sizeof(char) ,2 , reflect);
        fwrite(&reflectFileSize, sizeof(char) ,4 ,reflect);
        fwrite(second, sizeof(char) ,12 ,reflect);
        fwrite(&reflectWidth, sizeof(char), 4, reflect);
        fwrite(&reflectHeight, sizeof(char), 4, reflect);
        fwrite(third, sizeof(char), 8, reflect);
        fwrite(&reflectImageSize , sizeof(char), 4, reflect);                
        fwrite(fourth, sizeof(char), 16, reflect);
        fwrite(space3, sizeof(char), (reflectHeight * (reflectWidth * 3)* 2), reflect);
        
        fclose(reflect);
        fclose(quad);
        

        return 0;

    }
