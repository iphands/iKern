void printk(char * my_string);
void video_test();

void kmain( void* mbd, unsigned int magic )
{
  if ( magic != 0x2BADB002 )
    {
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
 
  /* Print a letter to screen to see everything is working: */
  unsigned char *videoram = (unsigned char *) 0xb8000;

  //videoram[0] = 65; /* character 'A' */
  //printk("Hello World\nHello World");
  video_test();
  videoram[1] = 0x07; /* forground, background color. */
 
  /* Write your kernel here. */
}

void video_test()
{
  unsigned short int i = 0;
  unsigned char *videoram = (unsigned char *) 0xb8000;
  while(i < 2000)
    {
      videoram[0 + i] = 'A';
      i++;
    }
    
}

void printk(char * my_string)
{
  unsigned short int i = 0;
  unsigned char *videoram = (unsigned char *) 0xb8000;
  while(my_string[i] != '\0')
    {
      videoram[0 + i] = my_string[i];
      i++;
    }
  return;
}
