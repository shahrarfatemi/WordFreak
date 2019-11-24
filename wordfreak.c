#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS  8000 //estimated maximum distinct words 8000
#define MAX_LETTERS 100 //estimated maximum letters for a word 100

char words[MAX_WORDS][MAX_LETTERS]; //words will be the array of distinct words
char word[MAX_LETTERS];             //word will be used to the current word
int  count[MAX_WORDS];              //for keeping a track of the frequency
static int wordCount = 0;           //number of distinct words
FILE *file;                         //file pointer to read from the text file

void word_freak(char * filePath){
    int i,found;
    file = fopen(filePath, "r");    //try to open file
    
    if (file == NULL){
        printf("Unable to open file.\n");
    }
    else{
    	int itr = 0,scanning = 0;   //itr is used for iterating through the current word
				    //scanning variable is used to skip multiple spaces or other symbols among words
    	char c;
    	while((c = fgetc(file)) != EOF){ //scanning each word in character c
            if(c >= 'A' && c <= 'Z'){
                scanning = 1;
                word[itr++] = (c+32);
            }
            else if(c >= 'a' && c <= 'z'){
                scanning = 1;
                word[itr++] = c;
            }
            else{
                if(scanning){
                    found = 0;
            	    for (i=0; i < wordCount; i++){  //checking if the scanned word exits in the list of distinct words
                        if (strcmp(words[i], word) == 0){
                            found = 1;
                            break;
                        }
            	    }
            	    if (!found){
                        strcpy(words[wordCount], word); //the word is a new one,that's why, adding this to the list
	                count[wordCount++]++;           //incrementing the count of that word
                    }
       	            else{
            	        count[i]++;                     //incrementing the count of the matched word
            	    }
            	    for(i = 0 ; i < itr ; i++){
               	        word[i] = '\0';                 //freeing the word array for re-using
            	    }
            	    scanning = 0;
            	    itr = 0;  
                 }
            }
        } 

    }
    fclose(file);   //closing the current text file                                      
}


int main(int argc, char * argv[])
{


    int i;
    for (i=0; i<MAX_WORDS; i++)     //initializing all counts to zero
        count[i] = 0;

    for(i = 1 ; i < argc ; i++){    //the input-file names are taken from terminal
        printf("%s\n",argv[i]);
        word_freak(argv[i]);
    }

    for (i = 0; i < wordCount; i++)
    {
        printf("%-10s  => %d\n", words[i], count[i]);
    }
    return 0;
}
