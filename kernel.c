void printk(char * my_string, unsigned short int line);
void push_line(char * line, unsigned char * vid_buffer);
void flush_video(char c, unsigned char * vid_buffer);
void write_buff(unsigned char * vid_buffer);

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
 

  /* Write your kernel here. */
  unsigned char vid_buffer[2000];
  flush_video(' ', vid_buffer);
  
  printk("Hello World", 0);
  printk("Hello World", 0);  
  
  push_line("Hello World", vid_buffer);
  push_line("This is a test", vid_buffer);
  push_line("Hello World", vid_buffer);
  
  //unsigned char *videoram = (unsigned char *) 0xb8000;
  //videoram[1920 * 2] = 'A';
}

void push_line(char * line, unsigned char * vid_buffer)
{

  for(int i = 0; i < 25; i++)
    {
      for(int j = 0; j < 80; j++)
	{
	  
	}
    }

  //write_buff();
  printk(line, (80 * 24) * 2);
}

void write_buff(unsigned char * vid_buffer)
{
  unsigned char * videoram = (unsigned char *) 0xb8000;
  for(int i = 0; i < 4000; i++)
    videoram[i] = vid_buffer[i];
}

void flush_video(char c, unsigned char * vid_buffer)
{
  unsigned short int i = 0;
  unsigned char * videoram = (unsigned char *) 0xb8000;
  while(i < (2000 * 2))
    {
      //vid_buffer = c;
      videoram[i] = c;
      videoram[i + 1] = 0x07;
      i += 2;
    }    
}

void printk(char * my_string, unsigned short int start_i)
{
  unsigned short int i, str_count_i = 0;
  unsigned char *videoram = (unsigned char *) 0xb8000 + start_i;
  while((my_string[str_count_i] != '\0') && (str_count_i < 80))
    {
      videoram[i] = my_string[str_count_i];
      videoram[i + 1] = 0x07;      
    
      i += 2;
      str_count_i++;
    }
  return;
}
