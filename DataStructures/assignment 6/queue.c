//for our analogy consider a queue of people in front of a cinema hall to buy tickets
#include <stdio.h>
#include <stdlib.h>

enum { false , true , MAX= 5 /*maximum nodes in queue*/};

//keeps track of the number of persons in the queue
int counter= 0;

//defining the node
typedef struct person
{
    //amount of money this person has
    int money;

    //points to previous person in the queue towards first
    struct person *previous;
    //points to next person in the queue towards last
    struct person *next;
}node;


//points to first person in this queue
node *first= NULL;
//points to last person in this  queue
node *last= NULL;

//function prototypes
int isEmpty(void);
int isFull(void);
int Insert_in_Queue(int data_to_insert);
int Delete_in_Queue(node *first);
int Search_in_Queue(int data_to_look_for);
int Update_in_Queue(node *first,int position,int updated_data);
int Display_queue(node *first);
void printUI(void);

//helper functions
char *getstring(char *);

int main()
{
    //to make changes in queue in the run time we need an infinite loop
    while (true)
    {
        printUI();  //prints UIs
        
        int ans1= atoi(getstring("Enter your choice: "));
        
        printf("\nYou entered: %d\n\n",ans1);

        switch (ans1)
        {
            case 1:
            {
                if (!Insert_in_Queue(1))
                {
                    printf("Error: Queue is full\n");
                }
                break;
            }
                

            case 2:
            {
                if (Delete_in_Queue(first))
                {
                    printf("Error: Queue is Empty\n");
                }
                break;
            }


            case 3:
            {
                printf("Note: All the persons in the queue with equavalent money(data) will be shown.\n");
                
                if (  Search_in_Queue(atoi(getstring("Enter the data you want to search in queue: ")))  )
                {
                    printf("Error: Queue is empty\n");
                }
                break;
            }
                


            case 4:
            {
                printf("Note: You cannot access positions below 1 or more than end Of Queue which is %d\n",counter);

                if ( Update_in_Queue                                                            /*update function called*/
                        (first,                                                                 /*update function argument, nested function calls*/
                        atoi(getstring("Enter the position you want to update: ")),             /*update function argument, nested function calls*/
                        atoi(getstring("Enter the data(money this person has): "))              /*update function argument, nested function calls*/
                        ) 
                    )
                {
                    printf("Error: Queue is Empty.\n");
                }
                break;
            }


            
            case 5:
            {
                if ( Display_queue(first) )
                {
                    printf("Error: Queue is Empty\n");
                }
                break;
            }
                

            
            case 6:
                if (isFull())
                {
                    printf("Queue is full.\n");
                }
                else
                {
                    printf("Queue is not full.\n");
                }
                break;


            case 7:
            {
                if (isEmpty())
                {
                    printf("Queue is empty.\n");
                }
                else
                {
                    printf("Queue is not empty.\n");
                }
                break;
            }
                
            

            case 8:
                goto EXIT_PROGRAM;
            
            default:
                break;
        }

        
    }
    
    EXIT_PROGRAM:
    
    while (first!= NULL)
    {
        node *temp= first->next;
        free(first);
        first= temp;
    }
    return 0;
    
}



int Insert_in_Queue(int data_to_insert)
{
    if (isFull())
    {
        return true;
    }
    //case 1 dll is empty
    if (first== NULL && last== NULL)
    {
        node *new= malloc(sizeof(node));
                    
        new->money= atoi(getstring("Enter the money this person has: "));
        new->next= NULL;
        new->previous= NULL;

        first= new;
        last= new;

        ++counter;
        printf("Person inserted in queue. Total no. of people in quque now: %d\n",counter);
    }
    else
    {
        //case 2  one or more nodes
        node *new= malloc(sizeof(node));
                    
        new->money= atoi(getstring("Enter the money this person has: "));
        new->next= NULL;
        new->previous= NULL;

        last->next= new;
        new->previous= last;
        last= new;

        ++counter;
        printf("Person inserted in queue. Total no. of people in quque now: %d\n",counter);
    }
    
    /*
    else if (isEmpty())
    {
        //queue is empty. insert the first node
        node *new= malloc(sizeof(node));
        new->money= data_to_insert;

        new->next= NULL;
        new->previous= NULL;

        first= new;
        last= new;

        ++counter;
        printf("\nPerson inserted successfully in queue(code: c1)\nNo. of people in queue:%d\n\n",counter);

        return false;
    }
    else
    {
        //inserting in non empty queue
        node *new= malloc(sizeof(node));
        printf("Done 1\n");
        
        new->money= data_to_insert;
        printf("Done 2\n");
        new->next= NULL;
        printf("Done 3\n");
        new->previous= NULL;
        printf("Done 4\n");

        printf("%d\n",last->money);
        new->previous= last;                                         //prev of new has last node(previously)
        printf("Done 5\n");  
                                                
        last->next= new;                                             //next of last node is new
        printf("Done 6\n");
        last= new;
    
        ++counter;
        printf("Person inserted successfully in queue(code: c2)\nNo. of people in queue:%d\n",counter);

        return false;
    }
    */
    

}


int Delete_in_Queue(node *first)
{
    if (isEmpty())
        return true;
    
    else
    {
        node *temp= first->next;
        free(first);
        first= temp;

        first->previous= NULL;

        --counter;
        printf("First person was removed from the queue.\nNo. of people in queue now: %d.\n",counter);

        return false;
        /*
        while (first!= NULL)
    {
        node *temp= first->next;
        free(first);
        first= temp;
    }
        */
    }
}


int Search_in_Queue(int data_to_look_for)
{
    if (isEmpty())
        return true;

    else
    {
       int position=1;
       for (node *i = first; i != NULL ; position++,i= i->next)
        {
            if (i->money== data_to_look_for)
            {
                printf("\nQueue position %d, Money: %d\n",position,i->money);
                break;
            }
        }
        
        return false;
    }
}


int Update_in_Queue(node *first,int position,int updated_data)
{
    if (isEmpty())
        return true;
    
    else if (position < 1 || position > counter )
    {
        printf("Invalid position.\n");
        return false;
    }
    
    else
    {
        int pos= 1;
        for (node *i = first; i!= NULL ; pos++,i= i->next)
        {
            if (pos== position)
            {
                i->money= updated_data;
                pos= 99;
                break;
            }
        }
        
        if (pos!= 99)
        {
            printf("Failed.\n");
            return false;
        }
        else
        {
            printf("Updated successfully.\n");
            return false;
        }
        
    }
    
}


int Display_queue(node *first)
{
    if (isEmpty())
        return true;
    else
    {
        int pos=1;
        for (node *i = first ; i!= NULL ; ++pos, i= i->next )
        {
            printf("Queue position: %d, Money :%d\n",pos,i->money);
        }
        
        return false;
    }
}




int isEmpty(void)
{
    //the contidion is evaluated to 1 if furst=last=null i.e. the queue is empty else 0
    if (first==NULL && last== NULL)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int isFull(void)
{
    //the contidion is evaluated to 1 if counter= max i.e. the queue is full else 0
    if (counter== MAX)
    {
        return true;
    }
    else
    {
        return false;
    }
}


char *getstring(char *string_to_print)
{
    int temp;//to store current character
    char *name=malloc(sizeof(char)); //allocating string(pointer to first index) to 1 byte    
    // Check if the memory has been successfully
    // allocated by malloc or not
    if (name == NULL) {
        printf("Memory not allocated.\n");
        exit(1);
    }
    
    fflush(stdin);
    //getting the string character by character
    printf("%s",string_to_print);    
    int i=0;
    for ( ; (temp=getchar())!='\n'; ++i)
    {
        name[i]=temp;
        name=realloc(name,i+1+sizeof(char));    //makes space for the next(i+1) character
    }
    temp=0;
    name[i]='\0';

    fflush(stdin);
    return (name);
}

void printUI(void)
{
    //UI
    printf("\nThis hypothetical Queue describes a queue of people in front of a movie threater.\n"
            "The money each person has is described by the data.\n");
        
    printf("\n\nEnter 1 to insert in queue.\n");
    printf("\nEnter 2 to delete from queue.\n");
    printf("\nEnter 3 to search in queue.\n");
    printf("\nEnter 4 to update into queue.\n");
    printf("\nEnter 5 to display queue.\n");
    printf("\nEnter 6 to check if queue is full.\n");
    printf("\nEnter 7 to check if queue is empty.\n");
    printf("\nEnter 8 to EXIT PROGRAM.\n\n");
}

/*
Problem  7:  Case  Study  of  Doubly  Linked  List:
Write  a  modular  program  using  doubly  linked  list  to demonstrate  the  basic  concept  of  Simple  Queue.  
For  verifying  all  boundary  conditions  of  simple queue  consider  the  size  of  queue,  i.e.,  n  =  5.  

The  main  focus  of  implementation  should  on  the following methods: 

1. isEmpty() 
2. isFull() 
3. Create_Queue()
4. Insert_in_Queue() 
5. Delete_in_Queue() 
6. Search_in_Queue() 
7. Update_in_Queue() 

8. User Interface method

You are required to bind all above methods with the help of User Interface method. 
You are also requested write algorithm for each method defined in the program.

Note:  Consider  the  left  most  pointer  as  Rear  Pointer  and  right  most  pointer  as  Front  pointer. 
Counter=0  means  there  is  element  in  the  queue.  If  Counter=1  means  1  record/item/value  in  the 
queue.  Counter  increased  and  it  becomes 5. Queue  will  be  treated  as  full.  If  queue  is  empty 
Rear=Front=NULL.  If  Rear  =Front=1  (address)  both  the  pointers  having  same  address.  If  full  means 
Rear will hold 5th location and Front will 1 location, iff no deletion is performed.  
*/