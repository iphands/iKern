void printk(char * my_string, unsigned short int line);
void push_line(char * line);
void flush_video(char c);
void change_term_color(unsigned char color);
//void write_buff(unsigned char * vid_buffer);

#define VIDEO_RAM_START 0xb8000
#define VIDEO_ROWS 80
#define VIDEO_COLS 25

void change_term_color(unsigned char color)
{
  unsigned char * videoram = (unsigned char *) VIDEO_RAM_START;
  for (int i = 0; i < 4000; i++)
    {
      i++;
      videoram[i] = color;
    }

  return;
}

void push_line(char * line)
{
  unsigned char *videoram = (unsigned char *) VIDEO_RAM_START;
  for(int i = 0; i <= 24; i++)
    {
      for(int j = 0; j < 160; j++)
	{
	  videoram[(i * 160) + j] = videoram[((i + 1) * 160) + j];
	}
    }

  printk(line, (VIDEO_ROWS * (VIDEO_COLS - 2)) * 2);
}

void flush_video(char c)
{
  unsigned short int i = 0;
  unsigned char * videoram = (unsigned char *) VIDEO_RAM_START;
  while(i < (VIDEO_ROWS * VIDEO_COLS * 2))
    {
      //vid_buffer = c;
      videoram[i] = c;
      videoram[i + 1] = 0x07;
      i += 2;
    }
}

void printk(char * my_string, unsigned short int start_i)
{
  unsigned short int str_count_i = 0;
  unsigned char *videoram = (unsigned char *) VIDEO_RAM_START;

  /*
    for(int i = 1; i < VIDEO_ROWS; i++)
    {
    videoram[i + start_i] = ' ';
    videoram[i + start_i + 1] = 0x07;
    }
  */

  unsigned short int i = start_i;
  while((my_string[str_count_i] != '\0') && (str_count_i < VIDEO_ROWS))
    {
      const char c = my_string[str_count_i];

      if (c > 32 && c < 127) {
        videoram[i] = c;
        videoram[i + 1] = 0x07;
      }

      i += 2;
      str_count_i++;
    }
  return;
}
