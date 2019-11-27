#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>

#define MAX_WORDS  20000 //estimated maximum distinct words 20000
#define MAX_LETTERS 100 //estimated maximum letters for a word 100

char **words;                       //words will be the array of distinct words
char *word;                         //word will be used to the current word
int  count[MAX_WORDS];              //for keeping a track of the frequency
static int wordCount = 0;           //number of distinct words
int file;                           //file pointer to read from the text file
int inputType = 0;                  //inputType defines the form of reading
                                    //1 => command line args, 0 => std_input
void word_freak(char * filePath){
    int i,found;
    
    if(inputType == 1){
        file = open(filePath,O_RDONLY);  //try to open file
    }
    if (file == -1){                //when there is an errorin inputfile
        char *errorStr = (char*)malloc(sizeof(char)*200);
        sprintf(errorStr,"Unable to open file.\nerror : %s\n",strerror(0));
        write(1,errorStr,strlen(errorStr));
        free(errorStr);
        return;
    }
    else{
    	int itr = 0,scanning = 0;   //itr is used for iterating through the current word
				    //scanning variable is used to skip multiple spaces or other symbols among words
        char *c = (char*)malloc(sizeof(char));
        int type = (inputType==1)?file:0; //type is set to verify if the paths are given from
                                          //command line or standard input
    	while(read(type,c,1) != 0){ //scanning each word in character c
            if(*c >= 'A' && *c <= 'Z'){
                scanning = 1;
                word[itr++] = (*c+32);
            }
            else if(*c >= 'a' && *c <= 'z'){
                scanning = 1;
                word[itr++] = *c;
            }
            else{
                if(scanning){
                    found = 0;
            	    for (i=0; i < wordCount; i++){  //checking if the scanned word exits in the list of distinct words
                        if (strcmp(*(words+i), word) == 0){
                            found = 1;
                            break;
                        }
            	    }
            	    if (!found){
                        strcpy(*(words+wordCount), word); //the word is a new one,that's why, adding this to the list
	                    count[wordCount++]++;             //incrementing the count of that word
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
    if(inputType == 1){
        close(file);   //closing the current text file
    }
                                          
}


int main(int argc, char * argv[], char** envp)
{

    int i;
    char *str = (char *)malloc(sizeof(char)*100);  //this string is used for printing
                                                  //using standard output
    word = (char *)malloc(sizeof(char)*MAX_LETTERS);
    words = (char **)malloc(sizeof(char*)*MAX_WORDS);
    for(i = 0 ; i < MAX_WORDS ; i++){             //for allocating spaces for 8000 words
        *(words+i) = (char*)malloc(sizeof(char)*MAX_LETTERS);
    }
    for (i=0; i<MAX_WORDS; i++)     //initializing all counts to zero
        count[i] = 0;
    
    if(argc <= 1){
        if(getenv("WORD_FREAK") != NULL){     //if environment variable is used
            inputType = 1;
            //printf("path => %s\n",path);
            word_freak(getenv("WORD_FREAK"));
            //free(path);
        }
        else{                                     //if standard input is used
            char d = 'a';
            word_freak(&d);
        }
    }
    else{
        inputType = 1;
        for(i = 1 ; i < argc ; i++){    //the input-file names are taken from terminal
            //printf("%s\n",argv[i]);
            word_freak(argv[i]);
        }   
    }
    for (i = 0; i < wordCount; i++)
    {
        sprintf(str,"%-20s  : %d\n", words[i], count[i]);
        write(1,str,strlen(str));
    }
    free(str);
    free(word);
    for(i = 0 ; i < MAX_WORDS ; i++){
        char * temp = words[i];
        free(temp);
    }
    return 0;
}
