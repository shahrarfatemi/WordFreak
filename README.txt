In this assignment,the two dimensional character array 'words' is used to store all the
distinct words of the input files.
I have made an estimation of at most twenty thousand(20000) distinct words so that we can
test it with at most this number of words.
Also, it was estimated that no word is longer than 100 characters.

I used an integer array 'count' to store the occurences of a word.The i-th entry of that 
'count' array is the frequency of the i-th entry of
the 'words' array.This array was initialized with all '0' entries.

At first I read the input file character by character and for any other symbol apart 
from the alphabet,I considered the previous scanned part to be a word and after that, 
I went through the 'words' array to check if a similar word existed.If a similar word
was found,this current word was not added in the 'words' array,only the corresponding
entry of the 'count' array was incremented.Otherwise,the word was enlisted in the array
and it's count was incremented.

For all the input files,the files were read one by one in a loop.And the above task 
was done using the 'word_freak' function for each of them.So,at last I got the frequencies
for each of the distinct words of those input files combined.

A variable 'inputType' was used for the two methods of reading the inputs. 
inputType = 1 => for taking file names as command line arguments
inputType = 0 => for taking file names as standard inputs
Also,environment variables were checked if an environment variable named 'WORD_FREAK'
had been initialized so that the value of that could be used as a filename.
So, thus all the three conditions for commands were fulfilled.
