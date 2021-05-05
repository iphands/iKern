#include "lib/video.h"
#define UNUSED(x) (void)(x)


void _start( void* _mbd, unsigned int magic )
{
  UNUSED(_mbd);

  if ( magic != 0x2BADB002 )
    {
      /* Something went not according to specs. Print an error */
      /* message and halt, but do *not* rely on the multiboot */
      /* data structure. */
      unsigned char *videoram = (unsigned char *) 0xb8000;
      videoram[0] = 66; /* character 'B' */
      videoram[1] = 0x07; /* forground, background color. */
    }

  flush_video(' ');
  push_line("Hello World");
  push_line((char *) 0x0001);
  printk("iKern test> ", (VIDEO_ROWS * (VIDEO_COLS -1)) * 2);

  // for (int i = 0; i < 100; i++)
  // while(1)
  // {
  // change_term_color(0x07);
  // change_term_color(0x1f);
  // change_term_color(0x2a);
  // }
  
  while (1) {}

  /* while (1) */
  /*   { */
  /*     int j = 0; */
  /*     unsigned char * videoram = (unsigned char *) 0xb8000; */
  /*     unsigned char * ram = (unsigned char *) 0x00000; */
  /*     for (int i = 0; i < (1920 * 2); i += 2) */
  /*       { */
  /*         videoram[i] = ram[j]; */
  /*         videoram[i + 1] = 0x07; */
  /*         j++; */
  /*       } */
  /*   } */

  //unsigned char *videoram = (unsigned char *) 0xb8000;
  //videoram[1920 * 2] = 'A';
}
