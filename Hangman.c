#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX 20

bool Checks_Letter(char currentLetter, char* guessLog, int attempts);
bool Guessed(char secretWord[MAX], char guessLog[26], int attempts);
bool Hanged(char secretWord[MAX], char guessLog[26], int attempts);
void Showcases_Letters(char secretWord[MAX], char guessLog[26], int attempts);
void Chooses_Word(char secretWord[MAX]);
void User_Input(char guessLog[], int* attempts);
void Screen_Art(int mistakes);
void Hanged_Art(void);
void Guessed_Art(void);

int main(){
	char secretWord[MAX], guessLog[26];
	int attempts = 0;
	Chooses_Word(secretWord);
	Screen_Art(0);
	do{
		Showcases_Letters(secretWord, guessLog, attempts);
		User_Input(guessLog, &attempts);
	}while(!Guessed(secretWord, guessLog, attempts) && !Hanged(secretWord, guessLog, attempts)); 
	return 0;
	// TODO: accept upper and lowercase, allow the player to repeat the game, create a menu, insert new words at the end 
}

// Inserts a random word to the "Secret Word" array:
void Chooses_Word(char secretWord[MAX]){
	FILE* words = fopen("words.txt", "r");
	if(!words){
		printf("\nUnable to find words.txt\n");
		exit(1);
	}
	// The text file must include a number informing the ammount of words
	int wordNumber; 
	fscanf(words, "%d", &wordNumber);
	// Random selection of the word:
	srand(time(0));
	wordNumber = rand()%wordNumber;
	// Insertion of the selected word into the array:
	for(int i = 0; i <= wordNumber; i++) fscanf(words, "%s", secretWord);
	fclose(words);
	printf("\n");
}

// Recieves a new guess from the user:
void User_Input(char guessLog[], int* attempts){
	char userGuess;
	printf("\tInsert new letter: ");
	scanf(" %c", &userGuess); // A space before %c will make it ignore the buffer
	printf("\n");
	// Registers a new attempt at the log:
	guessLog[*attempts] = userGuess;
	(*attempts)++;
}

// Prints the letter when it's found in the "Secret Word" or just an underscore otherwise:
void Showcases_Letters(char secretWord[MAX], char guessLog[26], int attempts){
	printf("\t");
	for(int i = 0; i < strlen(secretWord); i++){	
		if(Checks_Letter(secretWord[i], guessLog, attempts)) printf("%c ", secretWord[i]);
		else printf("_ ");
	}
	printf("\n");
}

// Goes through each letter stored in the "Guess Log" and raises a "Letter Found" flag when it exists in the "Secret word":
bool Checks_Letter(char currentLetter, char* guessLog, int attempts){ 
	bool letterFound = 0;
	for(int i = 0; i < attempts && letterFound == 0; i++){
		if(guessLog[i] == currentLetter) letterFound++;
	}
	return letterFound;
}

// Counts the player's mistakes by comparing each letter on the "Guess Log" to each letter on the "Secret Word": 
bool Hanged(char secretWord[MAX], char guessLog[26], int attempts){
	int mistakes = 0;
	bool correct = 0;
	for(int i = 0; i < attempts; i++){
		correct = 0;
		for(int j = 0; j < strlen(secretWord) && correct == 0; j++)
			if(guessLog[i] == secretWord[j]) correct = 1;
	if(!correct) mistakes++;
	}
	Screen_Art(mistakes);
	// Returns 1 if the player is hanged or 0 otherwise:
	if(mistakes >= 4){
		Hanged_Art();
		printf("\n\tHanged!\n");
		return 1;	
	}
	else return 0;
}

// If every letter in the word is found, this function returns 1:
bool Guessed(char secretWord[MAX], char guessLog[26], int attempts){
	for(int i = 0; i < strlen(secretWord); i++){
		if(!Checks_Letter(secretWord[i], guessLog, attempts)) return 0;
	}
	Guessed_Art();
	printf("\t");
	for(int i = 0; i < strlen(secretWord); i++) printf("%c ", secretWord[i]);
	printf("\n\tYou found the secret word!\n");
	return 1;
}

void Screen_Art(int mistakes){

printf("  _______       \n");
printf(" |/      |      \n");
printf(" |      %c%c%c  \n", (mistakes>=1?'(':' '), 
    (mistakes>=1?'_':' '), (mistakes>=1?')':' '));
printf(" |      %c%c%c  \n", (mistakes>=3?'\\':' '), 
    (mistakes>=2?'|':' '), (mistakes>=3?'/': ' '));
printf(" |       %c     \n", (mistakes>=2?'|':' '));
printf(" |      %c %c   \n", (mistakes>=4?'/':' '), 
    (mistakes>=4?'\\':' '));
printf(" |              \n");
printf("_|___           \n");

}

void Guessed_Art(void){

	printf("       ___________      \n");
    printf("      '._==_==_=_.'     \n");
    printf("      .-\\:      /-.    \n");
    printf("     | (|:.     |) |    \n");
    printf("      '-|:.     |-'     \n");
    printf("        \\::.    /      \n");
    printf("         '::. .'        \n");
    printf("           ) (          \n");
    printf("         _.' '._        \n");
    printf("        '-------'       \n\n");

}
void Hanged_Art(void){

	printf("    _______________         \n");
    printf("   /               \\       \n"); 
    printf("  /                 \\      \n");
    printf("//                   \\/\\  \n");
    printf("\\|   XXXX     XXXX   | /   \n");
    printf(" |   XXXX     XXXX   |/     \n");
    printf(" |   XXX       XXX   |      \n");
    printf(" |                   |      \n");
    printf(" \\__      XXX      __/     \n");
    printf("   |\\     XXX     /|       \n");
    printf("   | |           | |        \n");
    printf("   | I I I I I I I |        \n");
    printf("   |  I I I I I I  |        \n");
    printf("   \\_             _/       \n");
    printf("     \\_         _/         \n");
    printf("       \\_______/           \n");

}