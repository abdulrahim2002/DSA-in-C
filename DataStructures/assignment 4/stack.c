#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 10 //max no of elements in stack
#define true 1
#define false 0

//defining a stack called cards
int cards[CAPACITY];

//defining top of stack 
//which keeps track of number of elements
static int tos= 0;

//methods
int push(int stack[],int element);
int pop(int stack[]);
int peek(int stack[],int pos);
int update(int stack[],int pos,int val);
int display(int stack[]);
int isFull(int stack[]);
int isEmpty(int stack[]);

//helper function
char *getstring(char *string_to_print);

int main()
{
    while (true)
    {
        START:
        //UI
        printf("\n\nEnter 1 to push onto stack.\n");
        printf("\nEnter 2 to pop from stack.\n");
        printf("\nEnter 3 to peek in stack.\n");
        printf("\nEnter 4 to update onto stack.\n");
        printf("\nEnter 5 to Display stack.\n");
        printf("\nEnter 6 to check if stack is full.\n");
        printf("\nEnter 7 to if stack is empty.\n");
        printf("\nEnter 8 to EXIT PROGRAM.\n\n");
        
        int ans1= atoi(getstring("Enter your choice: "));

        switch (ans1)
        {
            case 1:
                if (push(cards, atoi(getstring("Enter the value to push: ")) ))
                {
                    printf("Error: Stack is full\n");
                }
                break;


            case 2:
                if (pop(cards))
                {
                    printf("Error: Stack is Empty\n");
                }
                break;


            case 3:
                printf("Note: You cannot peek positions below 1 or more than Top Of Stack which is: %d\n",tos);
                int pos= atoi(getstring("Enter the position you want to sneak: "));
                
                if (peek(cards,pos))
                {
                    printf("Error: Stack is empty\n");
                }
                break;


            case 4:
                printf("Note: You cannot access positions below 1 or more than Top Of Stack which is: %d\n",tos);
                int position= atoi(getstring("Enter the position you want to update: "));
                int val= atoi(getstring("Enter the value: "));
                
                if (update(cards,position,val))
                {
                    printf("Error: Stack is Empty.\n");
                }
                break;

            
            case 5:
                if (display(cards))
                {
                    printf("Error: Stack is Empty\n");
                }
                break;

            
            case 6:
                if (isFull(cards))
                {
                    printf("Stack is full.\n");
                }
                else
                {
                    printf("Stack is not full.\n");
                }
                break;


            case 7:
                if (isEmpty(cards))
                {
                    printf("Stack is empty.\n");
                }
                else
                {
                    printf("Stack is not empty.\n");
                }
                break;
            

            case 8:
                goto EXIT_PROGRAM;
            
            default:
                break;
        }

        
    }
    
    EXIT_PROGRAM:
        return 0;
}

int push(int stack[],int element)
{
	if (isFull(stack))
		return  true;
	
    stack[tos++] = element;
	printf("%d pushed to stack\n", element);
    return false;
}

int pop(int stack[])
{
	if (isEmpty(stack))
		return true;
	--tos;
    return false;
}

int peek(int stack[],int pos)
{
	if (isEmpty(stack))
		return true;
	printf("Stack pointer: %d, Element: %d\n", 1+pos , stack[--pos] );
    return false;
}

int update(int stack[],int pos,int val)
{
    if (isEmpty(stack))
    {
        return true;
    }
    
    stack[pos-1]= val;
    printf("Stack updated.\n");

    return false;
}

int display(int stack[])
{
    if (isEmpty(stack))
    {
        return true;
    }
    
    for (int i = 0; i < tos ; i++)
    {
        printf("\nStack pointer %d, Stack Element: %d\n", i+1 , cards[i] );
    }
    return false;
}

// Stack is full when top is equal to the last index
int isFull(int stack[])
{
	return (tos == CAPACITY);
}

// Stack is empty when top is equal to 0
int isEmpty(int stack[])
{
	return (tos == 0);
}


/*

//Case Study of Array using Stack: 
//Write an ADT program for Stack using an array. Use a method for every case to be checked. 
//In general define the following methods. 
//Also write a method for stack to evaluate any kind of mixed expression. 

//  1.isEmpty()
//  2.isFull()
//  *.create() // This method may be omitted/avoided in array based ADT implementation of Stack.
//  4.push()
//  5.pop()
//  6.peek()
//  7.update()

//Use the following algorithms for push, pop, peep/peek and update methods. 
//It is also possible to write your own algorithm.
// For Underflow and Overflow conditions call an appropriate method in the Push/Pop/Peep/Update methods. 

//You are also required to write algorithms for Underflow and Overflow conditions. 
//Also analyse the algorithm mentioned in this problem/written by you.  Show all the steps used in the analysis.

/*
Push(S, TOS)
S: Name of stack
TOS: Top of stack
1.[Check for Full of Stack or space in the stack to receive an element]
If (TOS=Size) // where Size is total space allocated for stack  Output “Overflow” and exit
2.[Increment the value of TOS by 1]TOS=TOS+1
3.[Get the element to be added]Read Element
4.[Add/Insert/Push the element into the stack] S[TOS]=Element   // is name of stack
5.End
*/

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