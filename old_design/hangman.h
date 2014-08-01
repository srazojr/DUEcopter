#ifndef __HANGMAN_H
#define __HANGMAN_H


#define MAX_MISSES 7
#define MAX_SCORES 5

#define TRUE 1
#define FALSE 0

struct dict_node{
  char word[64];
  struct dict_node* next;
};

struct score_node{
  char name[64];
  int score;
  struct score_node* next;
};


//========== game.c functions ==========

int play_game(char* word);  
// plays a round of hangman with the given word

void print_gallows(int n_miss);
// prints the gallows with a different state depending on the number of misses

char get_guess(char* tried,int n_tried); 
// gets a guess from the user, checks if it is in the tried list
// prompts for a new input if the letter has already been tried



//========== dictionary.c functions ==========

struct dict_node* load_dict();
// loads the dictionary from a file, returns a pointer to the head of the list

int get_length(struct dict_node* head);
// get the length of the dictionary list

char* get_word(struct dict_node* head, int index);
// returns the word in the dictionary at the given index

void print_dictionary(struct dict_node* head);
// prints the entire dictionary to the screen




//========== score.c functions ==========

struct score_node* load_scores();
// loads the high scores from a file, returns a pointer to the head of the list

void save_scores(struct score_node* head);
// saves the high scores to a file given the head of the list

struct score_node* check_score(struct score_node* head, int score); 
// checks if a score would be on the high score list, if so:
//  prompts for a name, then creates a new node and inserts it into the list
// returns the new head of the high scores list

void trim_list(struct score_node* head, int maxlen);
// a utility function to ensure that the high scores list has no more than maxlen elements


#endif
