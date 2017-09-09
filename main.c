#include <ncurses.h>
#include <stdlib.h>
#include <stdio.h>

#define CAVE_WIDTH 64

void initcave(FILE * cavefile, int cave[CAVE_WIDTH][CAVE_WIDTH])
{
  for (int row = 0; row < CAVE_WIDTH; row++)
  {
    for (int col = 0; col < CAVE_WIDTH; col++)
    {
      switch (fgetc(cavefile))
      {
        case ' ':
          cave[row][col] = 0;
          break;
        case '#':
          cave[row][col] = 1;
          break;
        case 'O':
          cave[row][col] = 2;
          break;
        case 'X':
          cave[row][col] = 3;
          break;
        case '*':
          cave[row][col] = 4;
          break;
        case '!':
          cave[row][col] = 5;
          break;
        case '\n':
          // next row
          col = CAVE_WIDTH;
          break;
        case EOF:
          return;
      }
    }
  }
}

int main(int argc, char * argv[])
{
  char const * cavename = "cave1";
  if (argc > 2)
  {
    cavename = argv[1];
  }
  char cavefilepath[29];
  snprintf(cavefilepath, 30, "./caves/%s.txt", cavename);

  FILE * cavefile = fopen(cavefilepath, "r");
  if (cavefile == NULL)
  {
    perror("Yikes! There was a problem opening the cave.\nMessage");
    fprintf(stderr, "cave: %s\nfile: %s\n", cavename, cavefilepath);
    fprintf(stderr, "Press enter to exit...\n");
    getchar();
    exit(1);
  }

  int cave[CAVE_WIDTH][CAVE_WIDTH] = {0};
  initcave(cavefile, cave);

  fclose(cavefile);

  initscr();

  getch();
  endwin();

  return 0;
}
