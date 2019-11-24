/**
 * C program to count occurrences of all words in a file.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS  8000
#define MAX_LETTERS 100

char words[MAX_WORDS][MAX_LETTERS];
char word[MAX_LETTERS];
int  count[MAX_WORDS];
static int wordCount = 0;
FILE *file;

void word_freak(char * filePath){
    int i,found;
    /* Try to open file */
    file = fopen(filePath, "r");

    /* Exit if file not opened successfully */
    if (file == NULL){
        printf("Unable to open file.\n");
    }
    else{
    	int itr = 0,scanning = 0;
    	char c;
    	while((c = fgetc(file)) != EOF){
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
                    // Check if word exits in list of all distinct words
            	    found = 0;
            	    for (i=0; i < wordCount; i++){
                        if (strcmp(words[i], word) == 0){
                            found = 1;
                            break;
                        }
            	    }

            	    // If word is unique then add it to distinct words list
            	    // and increment index. Otherwise increment occurrence
            	    // count of current word.
            	    if (!found){
                        strcpy(words[wordCount], word);
	                count[wordCount++]++;
                    }
       	            else{
            	        count[i]++;
            	    }
            	    for(i = 0 ; i < itr ; i++){
               	        word[i] = '\0';
            	    }
            	    scanning = 0;
            	    itr = 0;  
                 }
            }
        } 

    }
    // Close file
    fclose(file);
}


int main(int argc, char * argv[])
{


    int i;
    // Initialize words count to 0
    for (i=0; i<MAX_WORDS; i++)
        count[i] = 0;



    /* Input file path */

    for(i = 1 ; i < argc ; i++){
        printf("%s\n",argv[i]);
        word_freak(argv[i]);
    }
    //word_freak("output.txt");


    /*
     * Print occurrences of all words in file.
     */
    printf("\nOccurrences of all distinct words in file: \n");
    for (i = 0; i < wordCount; i++)
    {
        printf("%-10s => %d\n", words[i], count[i]);
    }


    return 0;
}
