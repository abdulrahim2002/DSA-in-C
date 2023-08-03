#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

enum { OUT, IN ,MAIN ,WORDF , MAX_CHARS_PER_WORD= 200};

#define MAXLEN SHRT_MAX                                          //max number of characters in the text data= max short int(data type) can handle i.e. (approx)32000

int search(char*,char*,int);
void conver_to_words(char*);
void wordF(char*);
void count(char*);

//helper functions
void printUI(void);
char *getstring(char*);


int main()
{
    printf("\nEnter the textual data.\nNote: When you are done writing your Essay, type ctrl + D + ENTER.\n\n");
    
    int c,i;
	char essay[MAXLEN];

    //getting input
    for (i = 0; i < MAXLEN && (c=getchar())!= 4 ; i++)
        essay[i]= c;
    
    if (i== MAXLEN)
    {
        printf("Overflow. Max characters allowed = %d.\n",MAXLEN);
        return 10;
    }
    else if (i== 0)
    {
        printf("Error: Empty text.\n");
        return 11;
    }
    else
        essay[i]= '\0';

    
    //perform operations on text
    while (1)
    {
        printUI();

        int ans= atoi(getstring("Enter your choice: "));

        switch (ans)
        {
            case 1:
            {
                /*Search a pattern/word*/

                //asking the user to enter the patter to search. lets call it target
                char *word= getstring("Enter the target/pattern: ");
                search(word,essay,MAIN);                                      
                break;
            }

            case 2:
            {
                /*Covert into its components/words*/
                conver_to_words(essay);
                break;
            }

            case 3:
            {
                /*Find the frequency of each word*/
                wordF(essay);
                break;
            }

            case 4:
            {
                /*Count the number of characters, words, sentences and paragraphs in a given text data*/
                count(essay);
                break;
            }
            
            case 5:
            {
                /*EXIT*/
                goto EXIT;
                break;
            }
        
            default:
                break;
        }

    }
    
    EXIT:
        return 0;
}



int search(char *target,char *text,int caller)
{
    /*
    in this algorithm we look at input text in chunk of given word(to search) sized blocks, if the block matches its starting index is recorded
    */
    
    int len_input= strlen(text);
    int len_target= strlen(target);
    
    if (len_target > len_input)
    {
        printf("Error: pattern is larger than input text.\n");
        return 20;
    }
    
    

    //current pattern being read from actual text.
    char current_pattern[len_target];

    //to store result
    int locations_of_match[1000], x= 0;                                                     // x is used for indexing in locations_of_match array 


    
    for (int i = 0; i < (len_input - len_target) ; i++)
    {
        int j,k= 0;
        for (j = i ; j < (i + len_target) ; j++ , ++k)
            current_pattern[k]= text[j];

        current_pattern[k]= '\0';


        if (!strcmp(current_pattern,target))                                            //strcmp returns 0 on match so a '!' executes this block 
            locations_of_match[x++]= i;
    }

    //result
    if (x== 0)
    {
        if (caller== WORDF)                                                                                                  //caller is wordf function 
            return 0;
            
        else                                                                                                                 //caller is main
        {
            printf("\nNo match found.\n");
            return 21;
        }
    }
    else
    {
        //on successfull search this algorithm returns number of occurences of that word.
            
        if (caller == WORDF)                                                                                                    //caller is wordf function 
            return x;
        
        else                                                                                                                    //caller is main
        {
            printf("\nIndices with matching pattern: ");

            for (int i = 0; i < x-1; i++)
                printf("%d, ",locations_of_match[i]);

            printf("%d\n\n",locations_of_match[x-1]);

            return 0;
        }

    }
}


void wordF(char* text)
{
    /*in this algorithm we first store each word. then we search these words unsing search function*/
    
    //storing words in linked list, defining the list

    typedef struct word
    {
        //the word itself.
        char word[MAX_CHARS_PER_WORD];

        //position of the word
        int position;

        //pointer to the next node
        struct word* next;

    }node;

    //start pointer, points to first node
    node *start= NULL;

    //word counter keeps track of number of words, buffer index is used to index within buffer.
    int word_counter= 0, buffer_index= 0;
    
    char buffer[MAX_CHARS_PER_WORD];                                                                            //bnuffer stores the word temporarily.
    int state= OUT;


    //storing words from text
    for (int i = 0 ; text[i] != '\0'  ; i++)
    {
        if (text[i] ==' ' || text[i] =='\n' || text[i] =='\t'|| text[i] =='/' || text[i] =='\\' || text[i]== '.')
		{
			if (state== OUT)                                                                                       //continous blank characters.
				continue;
			else                                                                          //state was in and now we are out of the word. Count the word.
            {
                state = OUT;
			    //end of word, terminate the word, increment the word counter, reset the buffer_index, insert the word in list
                buffer[buffer_index]= '\0';
                ++word_counter;
                buffer_index= 0;

                //inserting buffer in the list.
                {
                    //elimination repeated words, donot store words which are already present
                    for (node *i = start; i!= NULL; i= i->next)
                    {
                        for (node *j = start; j != NULL ; j= j->next)
                        {
                            if (j->position==i->position)
                            {
                                j= j->next;
                                if (j== NULL)
                                    break;
                            }
                        
                            if (!strcmp(buffer,j->word))
                                goto SKIP;
                        }
                    }
                    
                    
                    if (start== NULL)
                    {
                        //list is empty
                        node *new= malloc(sizeof(node));
                        new->next= NULL;

                        strcpy(new->word,buffer);
                        new->position= word_counter;

                        start= new;
                    }
                    else
                    {
                        //inserting in non empty list.
                        node *new= malloc(sizeof(node));
                        new->next= NULL;
                        
                        strcpy(new->word,buffer);
                        new->position= word_counter;

                        for (node *i = start; i!= NULL; i= i->next)
                        {
                            if (i->next== NULL)
                            {
                                i->next= new;
                                break;
                            }
                            
                        }
                    }
                }
            }
		}	
        
        else if(state == OUT)
        {
            state=IN;
            buffer[buffer_index++]= text[i];
        }                                                          //state is out and we read a non-blsnk chsrscter, update state=in

        else                                   //Third case: state is in and reading a nonblank character, character in curr. word, print chracter(if normal)
        {
            if ( isalpha(text[i]) || isdigit(text[i]) )                                 //to eliminate writing ',' ':' which are not part of normal words.
                buffer[buffer_index++]= text[i];
        }

        SKIP:
            ;
    }
    

    //printing result
    printf("\n\nFollowing is the list of words with their frequencies.\n");
    printf("\n\nWord_______________|_______frequency\n\n");


    //printing non-repeated words.
    for (node *i = start; i!= NULL; i= i->next)
        {
            printf("%s",i->word);
                
            //to print adequate number of blank spaces.
            int n= strlen(i->word);
            for (int i = 0; i < 20-n; i++)
                if(i>0)
                    printf(" ");
            
                
            printf("|       %d\n",search(i->word,text,WORDF));
        }

    //freeing the memory
    while(start!= NULL)
    {
        node *temp= start->next;
        free(start);
        start= temp;
    }
    
}


void conver_to_words(char* text)
{
    //state tells weatherwe are inside or outside a word.
    int state= OUT;

    printf("\nEach line contain a component word in cronological order.\n\n");
    
    for (int i = 0; text[i] != '\0'  ; i++)
    {
        if (text[i] ==' ' || text[i] =='\n' || text[i] =='\t'|| text[i] =='/' || text[i] =='\\' || text[i]== '.')
		{
			if (state== OUT)                                                                                       //continous blank characters.
				continue;
			else                                                                          //state was in and now we are out of the word. Count the word.
            {
                state = OUT;
			    putchar('\n');
            }
		}	
        
        else if(state == OUT)
        {
            state=IN;
            putchar(text[i]);
        }                                                          //state is out and we read a non-blsnk chsrscter, update state=in

        else                                   //Third case: state is in and reading a nonblank character, character in curr. word, print chracter(if normal)
        {
            if ( isalpha(text[i]) || isdigit(text[i]) )                                 //to eliminate writing ',' ':' which are not part of notmal words.
                putchar(text[i]);
        }
    }
    
    printf("\n\n");
}


void count(char* text)
{
    //Count  the  number  of  characters,  words,  sentences  and  paragraphs  in  a given text data
    int i,state= OUT;
    int characters= 0, words= 0, sentenses= 0, paragraph= 1;                                             /*all non-empty text has atleast 1 paragraph*/


    //loop to count sentenses and paragraphs.
    for (i = 0; text[i] != '\0'  ; i++)
    {                                                                           
        if (text[i]== '.' || text[i]== '?' || text[i]== '!' )
            ++sentenses;
        
        
        if (text[i]== '\n' )                                                                             //counts paragraphs
        {
            if ( text[++i]== '\n')
            {
                //at this point we know that this is a new paragraph. but there may be
                //more than 2 new lines, so we are eliminations them.
                
                ++paragraph;

                while (text[++i]!= '\n')
                    if (text[i]== '\0')                                                      //important to check terminating condition on each iteration
                        break;
            }
            
            if(text[i]== '\0')                                                              //important to check terminating condition on each iteration
                break;
        }

    }

    for (i = 0; text[i] != '\0'  ; i++)
    {
        if (text[i] ==' ' || text[i] =='\n' || text[i] =='\t' || text[i] =='/' || text[i] =='\\' || text[i]== '.' )      //this if-else block counts words
		{
			if (state== OUT)                                                                                       //continous blank characters.
				continue;
			else                                                                          //state was in and now we are out of the word. Count the word.
            {
                state = OUT;
			    ++words;
            }
		}	
        else if(state == OUT)                                                          //state is out and we read a non-blsnk chsrscter, update state=in
            state=IN;
        
        /*Third case: state is in and reading a nonblank character, character in curr. word*/     //no action needed
    }
    
    
    characters= i;                                                                                    //from the last iteration i has (no. of characters)

    //prints result
    printf("\n\nNumber of characters: %d\n"
            "Number of words: %d\n"
            "Number of sentences: %d\n"
            "Number of paragraphs: %d\n\n", characters , words , sentenses , paragraph );

}


void printUI(void)
{
    printf("\n\n|  Enter 1 to Search a pattern/word.                                                                   |\n"
            "|  Enter 2 to Covert into its components/words.                                                        |\n" 
            "|  Enter 3 to Find the frequency of each word.                                                         |\n"
            "|  Enter 4 to Count the number of characters, words, sentences and paragraphs in a given text data.    |\n"
            "|  Enter 5 to EXIT.                                                                                    |\n\n" );
}


char *getstring(char* string_to_print)
{
    /*
    this program is an improvent over previous get_string function i wrote.
    since it doest allocate memory from heap for which freeing the memory becomes 
    a problem.
    It instead returns static storage class variable whose life remains till the end of the 
    program and which can be accessed outside the block.

    the compromise you are making is that you are wasting space and text beyond 100000 cannot be inputted
    */

    printf("%s",string_to_print);

    int c,i;
    static char text[10000]; 
    
    fflush(stdin);

    for (i = 0; i < 10000 && (c=getchar())!= '\n' ; i++)
    {
        text[i]= c;
    }

    if (i>10000)
    {
        printf("Source: getstring()..Overflow, cannot insert more than 10,000 characters.\n");
        exit(1);
    }
    else
    {
        text[i]= '\0';
    }
    
    fflush(stdin);
    
    return text;
}


/*
Problem  7:  Case  Study  of  Pattern  Matching:  Write  a  program  to  implement 
the following methods for textual data set. 
The said data set may be organized as paragraphs, tables, or any readable pattern. 
Each method is required to be tested for a given paragraph. 

1.  Search a pattern/word
2.  Covert into its components/words 
3.  Find the frequency of each word
4.  Count  the  number  of  characters,  words,  sentences  and  paragraphs  in  a given text data 
 
You are also required to draw block of your program.    
*/