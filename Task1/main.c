#include <stdio.h>

#include <stdbool.h>

#include <stdlib.h>

#include <string.h>

// function that turns user input into int so it's easier to work with, it has one input(user input)
int string_to_floor(char * translate) {
  // variable where we save our floor
  int translation;
  if (strcmp(translate, "1") == 0 || strcmp(translate, "2") == 0 || strcmp(translate, "3") == 0 || strcmp(translate, "4") == 0 || strcmp(translate, "5") == 0) {
    translation = atoi(translate);
  } else if (strcmp(translate, "G") == 0) {
    translation = 0;
  } else if (strcmp(translate, "B1") == 0) {
    translation = -1;
  } else if (strcmp(translate, "B2") == 0) {
    translation = -2;
  } else if (strcmp(translate, "B3") == 0) {
    translation = -3;
  } else if (strcmp(translate, "N") == 0) {
    translation = -5;
  }
  //we have this -100 if user entered a wrong input
  else {
    translation = -100;
  }
  return translation;
}
// we want to check if the elevator needs to go up or down(2 inputs selected floor and curret floor)
bool greater_or_lower(int selected_floor, int current_floor) {
  //we just need to check which one is bigger(if selected is bigger we go up if current is bigger we go down)
  if (selected_floor > current_floor) {
    return true;
  } else {
    return false;
  }
}

int main() {
  //int value of the level we are on
  int elevator_lvl = 0;
  // input from user that he enters to the elevator
  char input_from_user[10];
  // boolean to help us with if else statements for going up or down(we save the value from the function here)
  bool greater = false;

  int num_of_people = 0;
  // we ask for maximum number of passangers so we know when to end the program
  printf("Enter the number of passangers allowed: ");
  while (num_of_people < 1) {
    scanf("%d", & num_of_people);
    // we don't want invalid input and i capped it at 9 because everything after 9 in ascii table is a sign
    if (num_of_people < 1 || num_of_people > 9) {
      printf("You entered invalid number of people please try again.");
    }

  }
  // int value we get from our function
  int translated;
  // when the user is already in the elevator we use this variable for input
  char leave[10];
  // current number of people is always 1 in the beggining 
  int current_num_of_people = 1;
  // we increase this value by 1 on the start(We use it to check if we went trough all the passangers)
  int current_passanger = 0;
  // we use first for the output later(to check if this is the first interaction with the program)
  int first = 1;
  //infinite loop
  while (true) {
    // we branch off in 2 similar programs depending if there is 1 max person or multiple(the program could have been designed differently but I went through each of the requirtements one by one)
    if (num_of_people == 1) {
      printf("\nEnter your desired floor(B1 for basement, B2 for basement 2, B3 for basement 3, G for ground, 1 for the first floor, 2 for the second, 3 for the third, 4 for forth, 5 for fifth and a for alighting.\n");
      // the input for the floor
      scanf("%s", input_from_user);
      // char to int function which gives us floor in int
      translated = string_to_floor(input_from_user);
      // invalid input case
      if (translated == -100) {
        printf("You entered wrong input please try again");
        break;
      }
      // boolean for checking do we need to go up or down
      greater = greater_or_lower(translated, elevator_lvl);
      // while loop while user is getting to his floor
      while (translated != elevator_lvl) {
        // two brances again going up and down
        if (greater) {
          // the level the elevator is one changes
          elevator_lvl++;
          printf("You are on floor %d. Do you wish to leave?(press y for yes, n for no)\n", elevator_lvl);
          scanf("%s", leave);
          if (strcmp(leave, "y") == 0) {
            // we break because our only user left
            break;
          } else if (strcmp(leave, "n") == 0) {

            // we already increased the floor but this is needed so we can check wether the user has inputed something wrong
          } else {
            printf("Wrong input try again\n");
            //we don't want to floor to change because of wrong input
            elevator_lvl--;
          }
        }
        // same thing as for going up, here we only go down so we use --
        else {
          elevator_lvl--;
          printf("You are on floor %d. Do you wish to leave?(press y for yes, n for no)\n", elevator_lvl);
          scanf("%s", leave);
          if (strcmp(leave, "y") == 0) {
            break;
          } else if (strcmp(leave, "n") == 0) {

            // we already increased the floor but this is needed so we can check wether the user has inputed something wrong
          } else {
            printf("Wrong input try again\n");
            //we don't want to floor to change because of wrong input
            elevator_lvl--;
          }
        }
      }
      if (strcmp(leave, "y") == 0) {
        // if the user decided to end the ride this(his last input is y) we end here in other case the while loop restarts and we ask him for input again
        printf("Thank you for riding with us. The program is ending.");
        break;
      }
    } else {

      printf("\nEnter your desired floor(B1 for basement, B2 for basement 2, B3 for basement 3, G for ground, 1 for the first floor, 2 for the second, 3 for the third, 4 for forth, 5 for fifth and a for alighting) Enter N if new passanger arrived. People who came before will go to their floors first. \n");

      // input for the floor
      scanf("%s", input_from_user);

      // floor to int
      translated = string_to_floor(input_from_user);
      //wrong input 
      if (translated == -100) {
        printf("You entered wrong input please try again");
        break;
      }
      // if input is N
      if (translated == -5) {
        //
        if (current_num_of_people > num_of_people) {
          printf("There are too many people, please try again");
        }
        // if this is the first person because we initilized our number of people with 1 we don't have to increase it and by saving the variable like this we know for later that this is not the first loop in the program. The first user can but doesn't have to input N.
        else if (first == 0) {
          first++;

        } else {
          current_num_of_people++;
        }

        continue;
      }
      first++;
      greater = greater_or_lower(translated, elevator_lvl);
      // same logic as before with the while statement
      while (translated != elevator_lvl) {
        if (greater) {
          elevator_lvl++;
          printf("You are on floor %d. Do you wish to leave?(press y for yes, n for no) Press N if new passanger arrived.\n", elevator_lvl);
          scanf("%s", leave);
          if (strcmp(leave, "y") == 0) {

            current_passanger++;
            current_num_of_people--;

            break;
          } // same logich as before we have to have this condintion because of wrong input
          else if (strcmp(leave, "n") == 0) {}
          // new person
          else if (strcmp(leave, "N") == 0) {
            // checking if there is room
            if (current_num_of_people >= num_of_people) {
              printf("There are too many people, you can't enter.\n");
            } else {
              current_num_of_people++;

            }
            // we have to decrease level so it stays in the same place in the next loop
            elevator_lvl--;
          } else {
            // we have to decrease level so it stays in the same place in the next loop
            printf("Wrong input try again\n");
            elevator_lvl--;
          }
        } else {
          elevator_lvl--;
          printf("You are on floor %d. Do you wish to leave?(press y for yes, n for no) Press N if new passanger arrived.\n", elevator_lvl);
          scanf("%s", leave);
          // wwants to leave
          if (strcmp(leave, "y") == 0) {
            //decreasing total num of people
            current_num_of_people--;
            // going to the next passanger
            current_passanger++;
            break;
          } //for bad input
          else if (strcmp(leave, "n") == 0) {} //same logic as in the loop above just ++ here to stay on the same floor
          else if (strcmp(leave, "N") == 0) {
            if (current_num_of_people >= num_of_people) {
              printf("There are too many people, you can't enter.\n");
            } else {
              //increase in num of people 
              current_num_of_people++;
            }
            // staying on the same level
            elevator_lvl++;
          } else {
            // bad input and staying on the same level
            printf("Wrong input try again\n");
            elevator_lvl++;
          }
        }
      }
      // if user wants to leave and there are no more people the program ends, otherwise we go back to the beggining
      if (strcmp(leave, "y") == 0 && current_num_of_people == 0) {
        printf("Thank you for riding with us.");
        break;
      }
    }

  }

  return 0;

}
