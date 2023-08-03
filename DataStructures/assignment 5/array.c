#include <stdio.h>
#include <stdlib.h>

void add(int size,int array[],int element);
void insertAt(int size,int array[],int element,int index);
void delete(int size,int array[],int element);
void update(int size,int array[],int new,int index);
void MaxMin(int size,int array[]);


int main()
{
    int A[]= {10,20,30,40};
    printf("\nOriginal array: 10 , 20 , 30 , 40\n");


    //making the user interface

    printf("\n__________________________________________________________________________\n\n");

    printf("Enter 1 to  Add an element to the array.\n");
    printf("Enter 2 to  Insert an element at the desired location in an array.\n");
    printf("Enter 3 to  Delete an element from an array.\n");
    printf("Enter 4 to  Update an element/information at an index of the array.\n");
    printf("Enter 5 to  Find max and min in array.\n\n");

    printf("___________________________________________________________________________\n");

    int ans1= ( getchar() - '0' );
    printf("\n\nYou pressed %d.\n\n",ans1);
    fflush(stdin);

   
   switch (ans1)
   {
        case 1:
        
            //taking the element
            printf("Enter the element to insert in the array.\n");
            int element_to_add;
            scanf("%d",&element_to_add);
            fflush(stdin);
            printf("\nYou entered %d.\n\n",element_to_add);

            add(4,A,element_to_add); 
            break;

      
        case 2:
        
            //taking the element
            printf("Enter the element to insert in the array.\n");
            int element_to_insert;
            scanf("%d",&element_to_insert);
            fflush(stdin);
            printf("\nYou entered %d.\n\n",element_to_insert);      
            
            //taking the index
            printf("Enter the index( >=0 && < 4) in the array.\n");
            int index_to_insert= (getchar() - '0');
            printf("\nYou entered %d.\n\n",index_to_insert);
            
            insertAt(4,A,element_to_insert,index_to_insert);
            break;
      
      
        case 3:

            //taking the element
            printf("Enter the element to delete in the array.\n");
            int element_to_delete;
            scanf("%d",&element_to_delete);
            fflush(stdin);
            printf("\nYou entered %d.\n\n",element_to_delete);

            delete(4,A,element_to_delete);
            break;


        case 4:
        
            //taking the index
            printf("Enter the index( >=0 && < 4) in the array to update.\n");
            int index_to_update= (getchar() - '0');
            fflush(stdin);
            printf("\nYou entered %d.\n\n",index_to_update);

            //taking the element
            printf("Enter the element.\n");
            int element_to_update;
            scanf("%d",&element_to_update);
            printf("\nYou entered %d.\n\n",element_to_update);
            fflush(stdin);

            update(4,A,element_to_update,index_to_update);
            break;

        case 5:
            MaxMin(4,A);
            break;
        
        default:
        printf("Invalid choice.\n");

   }

   return 0;
    
}



void add(int size,int array[],int element)
{
    //to calculate space and time complexity
    int space= 0,statements= 0;

    //declaring an array temp which has sizeof= size of ariginal array + 1 integer
    int temp[ size+ 1 ];
    space= (size+1);

    //copy the elements of original array in temp array
    ++space; ++statements;         //for i and an assignment(i=0) respectively

    for (int i = 0/*++space,++statement done above*/; i < size ; i++)
    {
        temp[i]= array[i];

        ++statements;//condition checked
        ++statements;//assignment
        ++statements;//increment
    }

    temp[size]= element;
    ++statements;

    //printing the array, this wont count in the space and time complexity
    printf("Added successfully\n\nNew Array: ");
    for (int i = 0; i < size ; i++)
    {
        printf("%d ",temp[i]);
    }
    printf("%d\n\n",temp[size]);
    
    printf("Space used= %d units,      i.e. size of input array + 2         NOTE: 1 unit= sizeof(int) bytes         // it is machine dependent \n"
            "Statements executed= %d,  i.e. (3 * size of input array) + 2\n\n",space ,statements );       

    exit(0);
    
}


void insertAt(int size,int array[],int element,int index)
{
    //to calculate space and time complexity
    int space= 0,statements= 0;
    
    if (!(index>= 0 && index< size))
    {
        printf("Invalid index.\n");
        exit(1);
    }
    ++statements;//condition check


    //declaring an array temp which has sizeof= size of original array + 1 integer
    int temp[ size+ 1 ];
    space= (size+1);

    //copy the elements of original array in temp array, before index
    ++space; ++statements;         //for i and an assignment(i=0) respectively

    for (int i = 0/*++space,++statement done above*/; i < index ; i++)
    {
        temp[i]= array[i];

        ++statements;//condition checked
        ++statements;//assignment
        ++statements;//increment
    }

    temp[index]= element;
    ++statements;

    ++space; ++statements;     //for i and an assignment(i=index+1) respectively
    for (int i = index + 1 ; i < size+1; i++)
    {
        temp[i]= array[i-1];
        ++statements;//condition checked
        ++statements;//assignment
        ++statements;//increment
    }
    
    
    //printing the array, this wont count in the space and time complexity
    printf("Inserted successfully\n\nNew Array: ");
    for (int i = 0; i < size ; i++)
    {
        printf("%d ",temp[i]);
    }
    printf("%d\n\n",temp[size]);
    
    printf("Space used= %d units,      i.e. size of input array + 3         NOTE: 1 unit= sizeof(int) bytes            // it is machine dependent \n"
            "Statements executed= %d,  i.e. (3 * size of input array) + 4\n\n",space ,statements );
    
    exit(0);
}


void delete(int size,int array[],int element)
{
    //to calculate space and time complexity
    int space= 0,statements= 0;
    
    //for indexing in for loop
    int i;

    //declaring an array temp which has size= size of original array
    int temp[size-1];
    space= size-1;

    //copy the elements of original array in temp array, until target element is not found
    ++space; ++statements;         //for i and an assignment(i=0) respectively

    for ( i = 0/*++space,++statement done above*/; i< size && array[i]!=element ; i++)
    {
        temp[i]= array[i];

        ++statements;//condition1 checked
        ++statements;//condition2 checked
        ++statements;//assignment
        ++statements;//increment
    }

    if ( i== size )
    {
        //whole array has been transversed without finding element
        printf("Element not found.\n");
        exit(1);
    }
    ++statements;
    
    
    //we are skipping this element(to be deleted)
    ++i;

    for ( ; i < size; i++)
    {
        temp[i-1]= array[i];
        ++statements;//condition checked
        ++statements;//assignment
        ++statements;//increment
    }
    
    
    //printing the array, this wont count in the space and time complexity
    printf("Deleted successfully\n\nNew Array: ");
    for (int i = 0; i < size-2 ; i++)
    {
        printf("%d ",temp[i]);
    }
    printf("%d\n\n",temp[size-2]);
    
    printf("Space used= %d units,      i.e. size of input array        NOTE: 1 unit= sizeof(int) bytes            // it is machine dependent \n"
            "Statements executed= %d,  i.e. 3 * size of input array\n\n",space ,statements );
    
    exit(0);
}


void update(int size,int array[],int new,int index)
{
    //to calculate space and time complexity
    int space= 0,statements= 0;
    
    if (!(index>= 0 && index< size))
    {
        printf("Invalid index.\n");
        exit(1);
    }
    ++statements;//condition check
    
    array[index]= new;
    ++statements;



    //printing the array, this wont count in the space and time complexity
    printf("Updated successfully\n\nNew Array: ");
    for (int i = 0; i < size-1 ; i++)
    {
        printf("%d ",array[i]);
    }
    printf("%d\n\n",array[size-1]);
    
    printf("Space used= %d units,         NOTE: 1 unit= sizeof(int) bytes           // it is machine dependent \n"
            "Statements executed= %d\n\n",space ,statements );


    exit(0);
}


void MaxMin(int size,int array[])
{
    //to calculate space and time complexity
    int space= 0,statements= 0;

    //max element seen so far and minium element seen so far, initilize the min value with such a number which is greater than all elements
    int max=0,min=1000;
    space=2;

    for (int i = 0; i < size; i++)
    {
        if (array[i]>=max)
        {
            max= array[i];
            ++statements;//assignment
            ++statements;//condition
        }
        else
        {
            ++statements;//condition checked
        }
        

        if (array[i]<= min)
        {
            min= array[i];
            ++statements;//assignment
            ++statements;//condition
        }
        else
        {
            ++statements;//condition checked
        }
        
    }
    


    printf("Maxium element: %d\nMinium element: %d\n\n",max,min);
    
    printf("Space used= %d units        Note: 1 unit=sizeof(int)        //machine dependent\n"
            "Statements executed= %d,  // may vary, dependent on input array\n\n",space ,statements );       


    exit(0);
}



/*
Requirments:
Write a modular program which demonstrates the following operation on an array. 
Write algorithm for each operation/method defined by you. 
You are also required find/compute Time and Spacecomplexity of defined algorithm.

1.Add an element to the array
2.Insert/add an element at the desired location in an array 
3.Delete an element from an array
4.Update an element/information associated with a pocket of an array
5.Find max and min in array

array= 10,20,30,40

*/