/**************************************************************************
 * This work originally copyright David J. Malan of Harvard University, or-
 * iginally released under:
 * CC BY-NC-SA 3.0  http://creativecommons.org/licenses/by-nc-sa/3.0/
 * licensing.
 *
 * It has been adapted for use in csci 1730.  Per the share-alike
 * clause of this license, this document is also released under the
 * same license.
 **************************************************************************/
 /**
  * fifteen.c
  *
  * Implements Game of Fifteen (generalized to d x d).
  *
  * Usage: fifteen d
  *
  * whereby the board's dimensions are to be d x d,
  * where d must be in [DIM_MIN,DIM_MAX]
  *
  * Note that usleep is obsolete, but it offers more granularity than
  * sleep and is simpler to use than nanosleep; `man usleep` for more.
  */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

  // constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (1)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("win!\n");
            break;
        }

        // prompt for move
        printf("Tile to move (0 to exit): ");
        int tile;
        scanf("%d", &tile);
        getchar();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(200000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */
void init(void)
{
  int totalTiles = (d * d) - 1;
    for (int i = 0; i < d; i++) {
        for (int j = 0; j < d; j++) {
            board[i][j] = totalTiles;
            totalTiles--;
        }
    }
    if (d % 2 == 0) {
        int save = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = save;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // repeats for the amount of rows that exist on the board
    for (int i = 0; i < d; i++) {
        // prints the lines above the numbers
        for (int k = 0; k < (d * 4) + 1; k++) {
            printf("_");
        }
        // prints the numbers along with the | to split the sections
        printf("\n|");
        for (int j = 0; j < d; j++) {
            printf("%3d|", board[i][j]);
        }
        printf("\n");
    }
    // prints the bottom line
    for (int i = 0; i < (d * 4) + 1; i++) {
        printf("-");
    }
    printf("\n");
}

/**
 * If tile borders empty space, moves tile and returns 1 (true), else
 * returns 0 (false).
 */
bool move(int tile)
{
    // Check if that tile exist on the board
    if (tile > d * d - 1 || tile < 1)
    {
        return false;
    }

    int x = 0;
    int y = 0;

    // finds the row and column of the tile
    for (int i = 0; i < d; i++)
    {
        for (int j = 0; j < d; j++)
        {
            if (board[i][j] == tile)
            {
                x = i;
                y = j;
            }
        }
    }

    // Checks if a tile exist under the current tile we are looking at and if that tile is empty
    if (x - 1 >= 0 && board[x - 1][y] == 0)
    {
        //swaps the tiles
        board[x - 1][y] = board[x][y];
        board[x][y] = 0;
        return true;
    }
    // Checks if a tile exist above the current tile we are looking at and if that tile is empty
    else if (x + 1 < d && board[x + 1][y] == 0)
    {
        //swaps the tiles
        board[x + 1][y] = board[x][y];
        board[x][y] = 0;
        return true;
    }
    // Checks if a tile exist to the right of the current tile we are looking at and if that tile is empty
    else if (y - 1 >= 0 && board[x][y - 1] == 0)
    {
        //swaps the tiles
        board[x][y - 1] = board[x][y];
        board[x][y] = 0;
        return true;
    }
    // Checks if a tile exist to the left of the current tile we are looking at and if that tile is empty
    else if (y + 1 < d && board[x][y + 1] == 0)
    {
        //swaps the tiles
        board[x][y + 1] = board[x][y];
        board[x][y] = 0;
        return true;
    }
    // means the tile does not have a valid move
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // keeps track of the tile number
    int tileCounter = 1;
    for (int i = 0; i < d; i++) {
      if ( i != d-1 ) {
        for (int j = 0; j < d; j++) {
            // if the tile currently looked at does not equal the tile counter return false
            if (board[i][j] != tileCounter) {
                return false;
            }
            tileCounter++;
        }
      } else {
	for(int j = 0; j < 2; j++){
	  if (board[i][j] != tileCounter){
	    return false;
	  }
	  tileCounter++;
	}
      }
    }
    // return false if the last tile does not have a value > 0
    if (board[d - 1][d - 1] > 0) {
        return false;
    }
    return true;
}
