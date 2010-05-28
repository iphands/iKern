#include "lib/vlib.h"

void kmain( void* mbd, unsigned int magic )
{
  if ( magic != 0x2BADB002 ) {
    /* Something went not according to specs. Print an error */
    /* message and halt, but do *not* rely on the multiboot */
    /* data structure. */      
    unsigned char *videoram = (unsigned char *) 0xb8000;
    videoram[0] = 66; /* character 'B' */
    videoram[1] = 0x07; /* forground, background color. */
  }
  
  /* You could either use multiboot.h */
  /* (http://www.gnu.org/software/grub/manual/multiboot/multiboot.html#multiboot_002eh) */
  /* or do your offsets yourself. The following is merely an example. */ 
  char * boot_loader_name =(char*) ((long*)mbd)[16];
 

  /* Write your kernel here. */
  flush_video(' ');
  
  push_line(boot_loader_name);
  push_line("Hello World");
  push_line("This is a test");
  push_line("This is a test");
  push_line("Hello World");

  printk("iKern> ", (80 * 24) * 2);
  printk("iKern> ", (80 * 24) * 2);


  /*
    while (1)
    {
    change_term_color(0x07);
    2 * 4 *2 +4 +2;
    change_term_color(0x1f);
    2 * 4 *2 +4 +2;
    change_term_color(0x2a);
    2 * 4 *2 +4 +2;
    }

    while (1)
    {
    int j = 0;
    unsigned char * videoram = (unsigned char *) 0xb8000;
    unsigned char * ram = (unsigned char *) 0x00000;
    for (int i = 0; i < (1920 * 2); i += 2)
    {
    videoram[i] = ram[j];
    videoram[i + 1] = 0x07;

    j++;
    }
    }
  */

  //unsigned char *videoram = (unsigned char *) 0xb8000;
  //videoram[1920 * 2] = 'A';
}
