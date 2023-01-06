#include <stdio.h>

#include <stdlib.h>

#include <time.h>

#include <string.h>

#include<stdbool.h>
 //  getting random index to select a word
int random_index_picker();
// return the current state of guess after each round
char * location(char opcija[], char guess, char do_sad[]);

int main() {
  // words that can be picked
  char options[4][15] = {
    {
      'a',
      'p',
      'p',
      'l',
      'e'
    },
    {
      'b',
      'a',
      'n',
      'n',
      'a',
      'n',
      'a'
    },
    {
      'p',
      'e',
      'a',
      'c',
      'h'
    },
    {
      'g',
      'r',
      'a',
      'p',
      'e',
      'f',
      'r',
      'u',
      'i',
      't'
    }
  };
  // number of times user made a mistake
  int error = 0;
  // getting a random index
  int random_index = random_index_picker();
  // empty string the length of the correct word
  char lines[strlen(options[random_index])];
  // just variable to fill the word with _
  char down = '_';
  // input from the user
  char selected_char;
  // getting a _ length of selected word
  for (int x = 0; x < strlen(options[random_index]); x++) {

    strcpy( & lines[x], & down);
  }
  // the guess until now
  char * value;
  // declaring the variable for loop in advance
  int counter = 0;

  printf("-----|\n");
  printf("     |\n");
  printf("     |\n");
  printf("     |\n");
  printf("     |\n");
  printf("_____|\n\n\n\n");
  // getting the string for_____
  char * privremeni = lines;
  // selected character
  char check[10];
  printf("\nhelp for testing %s\n", options[random_index]);
  // repeating until 4 errors
  for (counter = 0; error < 4; counter++) {

    printf("Enter your guess: ");
    scanf("%s", check);
    // checking if input is valid
    if (strlen(check) > 1 || !isalpha(check[0])) {
      printf("Wrong input");
      break;
    }
    // turning the input into a char
    selected_char = check[0];
    // getting the current word and declaring our temporary word with the value before the change
    if (counter == 0) {
      value = location(options[random_index], selected_char, lines);
    } else {
      strcpy(privremeni, value);
      value = location(options[random_index], selected_char, value);
    }
    // if the current word has _ then the game is not done
    if (strchr(value, '_') != NULL) {

      printf("\nYour current status: %s\n ", value);

    } else {
      // if theres no _ that means the game is over
      printf("The word is %s, you won", value);
      break;
    }
    //if the temporary string and the return from the function are the same that means user didn't guess correctly
    if (strcmp(privremeni, value) == 0) {
      printf("\n");
      // increasing num of errors
      error++;
      // based on error we draw parts of stickman
      if (error == 1) {
        printf("-----|\n");
        printf("  0  |\n");
        printf("     |\n");
        printf("     |\n");
        printf("     |\n");
        printf("_____|\n\n\n");
      } else if (error == 2) {
        printf("-----|\n");
        printf("  0  |\n");
        printf("  |  |\n");
        printf("     |\n");
        printf("     |\n");
        printf("_____|\n\n\n");
      } else if (error == 3) {
        printf("-----|\n");
        printf("  0  |\n");
        printf(" /|\\ |\n");
        printf("     |\n");
        printf("     |\n");
        printf("_____|\n\n\n");
      } else if (error == 4) {
        printf("-----|\n");
        printf("  0  |\n");
        printf(" /|\\ |\n");
        printf(" / \\ |\n");
        printf("     |\n");
        printf("_____|\n\n\n");
        printf("game over");
      }
    }

  }

  return 0;
}
int random_index_picker() {
  // generating a new seed so we can a new random number each time
  srand(time(NULL));
  // mod with for because of the length of our string for choice of words
  int random_number = rand() % 4;
  return random_number;
}
// returning the current status word after the guess(the function takes the selected word, the guess, and do word untl now)
char * location(char options[], char guess, char do_sad[]) {
  // value we return
  char vracam[strlen(options)];
  // going through the word that was selected
  for (int x = 0; x < strlen(options); x++) {
    // if there is a match we input it inside of our ____
    if (options[x] == guess) {

      strcpy( & vracam[x], & guess);
    } else {
      // if not we just put _ in it's place
      strcpy( & vracam[x], & do_sad[x]);
    }
  }
  // we have to use malloc because of the return type, we can't return a pointer of a variable that exists locally and dissapears after function is finicshed
  char * ovo = malloc(sizeof(char) * 100);

  strcat(ovo, vracam);
  return ovo;
}
