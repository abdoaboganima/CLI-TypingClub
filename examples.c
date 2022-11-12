#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "examples.h"

#define FILES_NUM 23

const int files_num=FILES_NUM;

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
                                         "lessons/fvjn.txt",
                                         "lessons/az.txt",
                                         "lessons/ws.txt",
                                         "lessons/jkluiop.txt",
                                         "lessons/ex.txt",
                                         "lessons/sch.txt",
                                         "lessons/olp.txt"};

void make_examples(void)
{


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
                                        "fvjn",
                                        "az",
                                        "ws",
                                        "jkluiop",
                                        "ex",
                                        "sch",
                                        "olp"};

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
