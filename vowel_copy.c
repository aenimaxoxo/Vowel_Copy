# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <ctype.h>

# define MAXCHAR 1000

void writeToFile(char c[MAXCHAR], char filename[MAXCHAR]);
void read_words (FILE *f);

int main(void){
  FILE *fp;
  char str[MAXCHAR], c;
  char *filename;
 
  // file entry
  printf("Please enter the location of a text file without quotes.\n");
  scanf("%s", filename);
  fp = fopen(filename, "r");
  
  // catch null file
  if (fp == NULL){
    printf("\nCan not open file: %s. Check file path and permissions.", filename);
    return 1;
  }

  // read words in txt file 
  read_words(fp);

  // close file stream
  fclose(fp);
  return 0;
}

void writeToFile(char c[MAXCHAR], char filename[MAXCHAR]){
  FILE * fo;
  int i;
  
   // open new text file in append mode
   fo = fopen(filename, "a+");

   fprintf(fo, "%s ", c);
  
   fclose(fo);
}

void read_words (FILE *f) {
    char x[MAXCHAR];
    
    /* assumes no word exceeds length of 1000 */
    while (fscanf(f, " %1000s", x) == 1) {
      
       // get x length for end of word
       int x_length = strlen(x);
       
       // check if word starts with a vowel. If so, write to new file. Assumes we want vowels unformatted
       if (x[0] == 65 || x[0] == 69 || x[0] == 73 || x[0] == 79 || x[0] == 85 || x[0] == 97 || x[0] == 101 || x[0] == 105 || x[0] == 111 || x[0] == 117){
	writeToFile(x, "vowel_starters.txt");
       }

       // begin transcription to new file with changes 
       if (x_length > 1){
	 
	 // check if first letter is uppercase. If yes, lowercase first . elif first letter is lowercase, make it uppercase.
	 if (x[0] > 64 && x[0] < 91){
	   x[0] = x[0] + 32;
	 } else if (x[0] > 96 && x[0] < 123){
	   x[0] = x[0] - 32;
	 }
	 
	 // check if last character is non alphabet
	 if (!isalpha(x[x_length-1])){
	   // shorten string so we change the last letter and not some punctuation
	   x_length = x_length - 1;
	 }
	 
	 // check if last letter is uppercase. If yes, lowercase last. If last lowercase, make it uppercase. 
	 if (x[x_length-1] > 64 && x[x_length-1] < 91){
	   x[x_length-1] = x[x_length-1] + 32;
	 } else if (x[x_length-1] > 96 && x[x_length-1] < 123){
   	   x[x_length-1] = x[x_length-1] - 32;
	 }
	 
	 writeToFile(x, "new_output.txt");
	}
       // print to terminal
       puts(x);
    }
}
