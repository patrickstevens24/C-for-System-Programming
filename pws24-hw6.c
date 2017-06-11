/*
 * pws24-hw6.c
 *
 *  Created on: May 22, 2016
 *      Author: Patrick Stevens
 */
 
#include "aidb.h"
#include <stdio.h>

 
int main(void) {

   int count, size;
   FILE *infile = fopen("aidb.bin", "rb");
   
   AIDB_FileHeader head;
   fread(&head, sizeof(AIDB_FileHeader), 1,infile);
   
   count = head.section_count;
   
   int offset = head.section_table_offset;
   size = head.file_size;

   SectionHeader data[count];
   
   int sectionStart = offset - 16;   
   int newSize = size - 16; 
   char bigArray[newSize];

   
   fread(bigArray, sizeof(char), newSize, infile);
   

   
   SectionHeader *secArr = (SectionHeader *)&bigArray[sectionStart];

   for (int i = 0; i < count; i++) {
       data[i] = secArr[i];
   }
   
   //TYPE 0 student, 1 crs, 2 enroll, 3 string
   
   //------------------------------------------------
   char *arr;
   int stringEntry, stringStart;
   int studentEntry, studentStart;
   int enrollEntry, enrollStart;
   int courseEntry, courseStart;
   
   
   for (int i = 0; i < count; i++) {
   
      //student
      if (data[i].type == 0) {
          studentEntry = data[i].num_entries;
          studentStart = data[i].offset - 16;
          //printf("%d\n", studentEntry);
          
          
      //string
      } else if (data[i].type == 3) {
          stringEntry = data[i].num_entries;
          stringStart = data[i].offset - 16;

      //enroll   
      } else if (data[i].type == 2) {
          enrollEntry = data[i].num_entries;
          enrollStart = data[i].offset - 16;
         
      //courses
      } else if (data[i].type == 1)  {
          courseEntry = data[i].num_entries;
          courseStart = data[i].offset - 16;
          
      }
   } //end for loop
   
   
    char (*strArr)[stringEntry];
    
    
   // strArr = &bigArray[stringStart];
   
    Student *stuArr = (Student *)&bigArray[studentStart];
    Student stud[studentEntry];
    for (int s = 0; s < studentEntry; s++) {
         stud[s] = stuArr[s]; 
    }
   
    Enroll *enrArr = (Enroll *)&bigArray[enrollStart];
    Enroll enroll[enrollEntry];
    for (int s = 0; s < enrollEntry; s++) {
          enroll[s] = enrArr[s]; 
    }
    
    Course *couArr = (Course *)&bigArray[courseStart];
          
    Course course[courseEntry];
    for (int s = 0; s < courseEntry; s++) {
         course[s] = couArr[s]; 
    }
    printf("\n%s\n\n", "AIDB Tables");
    printf("%s\n", "Students");
   
    
   //print students
    for (int c = 0; c < studentEntry; c++) {
          //format to 4 int
         
         printf("%-2.4d", stud[c].id_num);
         int counter = 0;
         int letter = 0;
         printf("%2c", ' ');
         
         //names
         int text = 0;
         while (counter < 1) {
              if (!bigArray[stringStart + stud[c].name + letter] == '\0') {
                  printf("%c", bigArray[stringStart + stud[c].name + letter]);
                  text++;
                  letter = letter + 1;
              } else {
                  
                  counter = counter + 1;
              }
          }
          text = 40 - text;
          //majors
          
          if (stud[c].major == 0) {
               printf("%*s\n",text-6, "CS");
          } else if (stud[c].major == 1) {
               printf("%*s\n",text-6, "CE");
          } else if (stud[c].major == 2) {
               printf("%*s\n",text-4, "MATH");
          } else if (stud[c].major == 3) {
               printf("%*s\n",text, "SOC WORK");
          } else {
               printf("%*s\n",text-1, "NURSING");
          }
    }
    printf("\n%s\n", "Courses");
    
    //print courses
    for (int c = 0; c < courseEntry; c++) {
         int counter = 0;
         int letter = 0;
         int text = 0;
          while (counter < 1) {
              if (!bigArray[stringStart + course[c].name + letter] == '\0') {
                  printf("%c", bigArray[stringStart + course[c].name + letter]);
                  letter = letter + 1;
                  text++;
              } else {
                  
                  counter = counter + 1;
              }
          }
          text = 30-text;
          printf("%*d", text, course[c].max_enroll);
          printf("%c\n", ' ');   
    }
    printf("\n%s\n", "Enrollments");
    
    for (int c = 0; c < enrollEntry; c++) {
         int counter = 0;
         int letter = 0;
         int text = 0;
          while (counter < 1) {
              if (!bigArray[stringStart + stud[enroll[c].student].name + letter] == '\0') {
                  printf("%c", bigArray[stringStart + stud[enroll[c].student].name + letter]);
                  letter = letter + 1;
                  text++;
              } else {
                  
                  counter = counter + 1;
              }
          }
          text = 30-text;
          printf("%*c", text, ' ');
          int counter1 = 0;
         int letter1 = 0;
          while (counter1 < 1) {
              if (!bigArray[stringStart + course[enroll[c].course].name + letter1] == '\0') {
                  printf("%c", bigArray[stringStart + course[enroll[c].course].name + letter1]);
                  letter1 = letter1 + 1;
              } else {
                  
                  counter1 = counter1 + 1;
              }
          }
          
          printf("%c\n", ' ');
   
         
         
         
         
         
         
   }

   return 0;

}
