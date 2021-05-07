#include "lib/video.h"
#include "lib/keys.h"

#define UNUSED(x) (void)(x)

extern void init_pic();
extern int dbg_is_kbd_ready();
extern char dbg_kbd_get_scancode();

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

  init_pic();

  printk("iKern test> ", (VIDEO_ROWS * (VIDEO_COLS -1)) * 2);

  // for (int i = 0; i < 100; i++)
  // while(1)
  // {
  // change_term_color(0x07);
  // change_term_color(0x1f);
  // change_term_color(0x2a);
  // }

  initilize_keymap();
  unsigned char * videoram = (unsigned char *) 0xb8000;
  int pos = 0;
  while (1) {
    if (dbg_is_kbd_ready() == 1) {
      const char c = dbg_kbd_get_scancode();

      if (c == 0x01) {
        pos = 0;
        videoram = (unsigned char *) VIDEO_RAM_START;
        flush_video(' ');
        continue;
      } else if ((int)c == 0x1c) {
        videoram += (VIDEO_ROWS * 2);
        pos = 0;
        continue;
      } else if ((int)c == 0x0e) {
        pos -= 2;
        videoram[pos] = ' ';
        continue;
      }

      const char mapped = keymap[(int)c];
      if (mapped > 0) {
        videoram[pos] = mapped;
        pos += 2;
        continue;
      }
    }
  }

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
