#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "examples.h"

#define FILES_NUM 17

void make_examples(void)
{

  const char *const filenames[FILES_NUM]={ "lessons/fj.txt",
                                           "lessons/kd.txt",
                                           "lessons/ls.txt",
                                           "lessons/a;.txt",
                                           "lessons/pw.txt",
                                           "lessons/pq.txt",
                                           "lessons/ik.txt",
                                           "lessons/ie.txt",
                                           "lessons/ur.txt",
                                           "lessons/ty.txt",
                                           "lessons/rtyu.txt",
                                           "lessons/asdf.txt",
                                           "lessons/iked.txt",
                                           "lessons/fghj.txt",
                                           "lessons/jn.txt",
                                           "lessons/fv.txt",
                                           "lessons/fvjn.txt"};

  const char *const chars[FILES_NUM] ={ "fjffjj",
                                        "kdkkdd",
                                        "lslsls",
                                        "a;a;a;",
                                        "pwpwpw",
                                        "pqpqpq",
                                        "ikikik",
                                        "ieieie",
                                        "ur",
                                        "ty",
                                        "rtyu",
                                        "asdf",
                                        "iked",
                                        "fghj",
                                        "jn",
                                        "fv",
                                        "fvjn"};

  FILE * fp[FILES_NUM];
  srand(time(NULL));

  for (int i=0; i < FILES_NUM; ++i) {
    fp[i]= fopen(filenames[i], "w");

    if(fp[i]==NULL){
      /*if the file cannot be oopened*/
      printf("Error opening: %s\n", filenames[i]);
      return;
    }


    for (int j=1; j <= 300; ++j) {
      uint8_t size = strlen(chars[i]);
      fputc(chars[i][rand()%size], fp[i]);

      if(j%50==0)
        fputc('\n', fp[i]);

      else if((rand())%3==0 && j%50!=49){
        fputc(' ', fp[i]);
        ++j;
      }



    }


  }

  /*close all files*/
  for (int i=0; i < FILES_NUM; ++i)
    fclose(fp[i]);

}
