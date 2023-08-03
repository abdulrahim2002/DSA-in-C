#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define PATH "C:\\Users\\Abdul\\Desktop\\programs\\assignment 3\\db.csv"

//function prototypes
int add(void);
int delete(void);
int search(void);
int update(void);

//helper functions
char *getstring(char *string_to_print);


typedef struct person
{
    char adhar[20];
    char name[200];
    char gender[30];
    char father[200];
    char mother[100];
    char dob[30];

    //pointer to left and right nodes in the doubly linked list
    struct person* left;
    struct person* right;
}node;


//declaring left and right pointers and assigning null
node *leftend= NULL;
node *rightend= NULL;

//no of people in database.
int no_of_people= 0;

int main()
{
    //storing the data locally

    //opening the file
    FILE *fp= fopen(PATH,"r");
    if (fp==NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    //counting the number of people in source file.
    
    //current input character
    int c;
    while (( c=getc(fp) )!=EOF)
    {
        if (c=='\n')
        {
            ++no_of_people;
        }
        
    }
    //to reset the cursor(pointer) to start of file.
    rewind(fp);

    for (int i = 0; i < no_of_people ; i++)
    {
        //declaring a node, big N stands for node
        node *Nnew= malloc(sizeof(node));

        //initialise left and right pointer to NULL.
        Nnew->left= NULL;
        Nnew->right= NULL;
        
        //used to index array within nodes
        int j;  

        //fetching adhar number
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
        {
            Nnew->adhar[j]= c;
        }
        Nnew->adhar[j]= '\0';

        
        //name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            Nnew->name[j]= c;
        }
        Nnew->name[j]= '\0';

        
        //gender
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            Nnew->gender[j]= c;
        }
        Nnew->gender[j]= '\0';

        
        //fathers name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            Nnew->father[j]= c;
        }
        Nnew->father[j]= '\0';

        
        //mothers name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            Nnew->mother[j]= c;
        }
        Nnew->mother[j]= '\0';

        
        //dob
        for( j= 0 ; ( c= getc(fp) )!= EOF && c!='\n' ; ++j) 
        {
            Nnew->dob[j]= c;
        }
        Nnew->dob[j]= '\0';
        
        if( c != '\n' )
        {
            printf("Failed to fetch data.\n");
            return 2;
        }

        //inserting this node in the list, at desired place.
        if (leftend== NULL && rightend== NULL)
        {
            leftend= Nnew;
            rightend= Nnew;
        }
        else
        {
            //is 0 if node is not inserted 1 if it has
            int done= 0;
            
            for (node *current_node = leftend ; current_node != NULL ; current_node= current_node->right )
            {
                //if name in new node being checked is smaller than name in current node, it is target node.
                int r= strcmp( Nnew->name , current_node->name );

                //target node is found
                //subcase 1: the target node maybe first node.(insertion at left end)
	            //subcase 2: the target node maybe any node.(insertion at left of tsrget node)
	            //subcase 3: target node is not found.(insertion at last(from right) that will be right end ).
                if (r < 0)
                {
                    //assuming subcase 2
                    node *temp= current_node->left;
                    //this was actually subcase 1
                    if (temp== NULL)
                    {
                        //subcaes 1: insertion at left end
                        leftend->left= Nnew;
                        Nnew->right= leftend;
                        leftend= Nnew;

                        //insertion is complete hence break loop i.e. no need to look further nodes
                        ++done;
                        break;
                    }
                    //it is subcase 2
                    else
                    {
                        //connect whith temp and currentnode respectively
                        temp->right= Nnew;
                        Nnew->left= temp;

                        current_node->left= Nnew;
                        Nnew->right= current_node;

                        ++done;
                        break;

                    }
                    

                }
                


            }

            if (done== 0 )
            {
                //by now all the list has been teansversed and no target was found hence. new node is largest
                //subcase 3: insert at right end
                rightend->right= Nnew;
                Nnew->left= rightend;
                rightend= Nnew;
            }

        }
        


    }
    
    


    //making UI

    //making the user interface

    printf("__________________________________________________________________________\n\n");

    printf("Enter 1 to  Add a record.\n");
    printf("Enter 2 to  Delete a record.\n");
    printf("Enter 3 to  Search a Record.\n");
    printf("Enter 4 to  Update a record.\n\n");

    printf("___________________________________________________________________________\n");

    int ans1= ( (int)getchar() - 48 ) ;
    printf("\n\nYou pressed %d.\n\n",ans1);

    int r1,r2,r3,r4,r5; //return values of functions
    
    switch (ans1)
    {
        case 1:
        r1= add();
        if (r1)
        {
            printf("Failed to add, add manually to database at location :%s .\n",PATH);
        }    
        break;

        
        
        case 2:
        r2= delete();
        if (r2 && r2!=6 )
        {
            printf("Failed to delete, delete manually to database at location:%s .\n",PATH);
        }
        break;

        
        
        case 3:
        r3= search();
        if (r3 && r3!=5)
        {
            printf("Failed to search.\n");
        }
        break;


        case 4:
        r5= update();
        if (r5)
        {
            printf("Failed to Update. You can update database manually at location: %s ",PATH);
        }
        
        break;
        
        default:
        printf("Invalid choice.\n");

    }




    //free memory
    while (leftend!= NULL)
    {
        node* temp= leftend->right;
        free(leftend);
        leftend= temp;
    }

    //close file
    fclose(fp);
    
    return 0;

}

//implementing functions
int add()
{
    int ans2; //to ask if continue

    //opening file
    FILE *fp= fopen(PATH,"w");
    if (fp== NULL)
    {
        printf("couldnt open file.");
        return 4;
    }


    //adding value
    do
    {
            //data is stored in this node. this node inserted in the list. list is written to the file
            node *Nnew= malloc(sizeof(node));
            Nnew->left= NULL;
            Nnew->right= NULL;
            
            printf("\nPlease do not exit until current persons data is not entered completly.\n");

            START:
            //taking roll no.      
            fflush(stdin);
            char *getadhar= getstring("\nEnter the Adhar number/Social security number of the person: ");

            //checking if the person is currently in the record. 
            for (node *i= leftend ; i!= NULL ; i= i->right )
            {
                if (  strcmp(getadhar , i->adhar)== 0 )
                {
                    printf("\nThis Adhar number/Social security number is already in the record.Please enter another number.\n\n");
                    goto START;
                }
                
            }
            //this data goes into new node
            strcpy( Nnew->adhar , getadhar );
        
        
        
            //student name.
            fflush(stdin);
            char *name= getstring("\nEnter the name of person(First letter capital) : ");
            strcpy( Nnew->name , name );
            


            //gender 
            fflush(stdin);
            char *gen= getstring("\nEnter the gender  : ");
            strcpy( Nnew->gender , gen );
            
            
            
            //student f. name.
            fflush(stdin);
            char *fname= getstring("\nEnter the fathers name.  : ");  
            strcpy( Nnew->father , fname );
            


            //student m. name.
            fflush(stdin);
            char *mname= getstring("\nEnter the mothers name. : ");
            strcpy( Nnew->mother , mname );
            

            //dob
            fflush(stdin);
            char *gdob= getstring("\nEnter the date of birth. : ");
            strcpy( Nnew->dob , gdob );



            //inserting this node in the list, at desired place.
            if (leftend== NULL && rightend== NULL)
            {
                leftend= Nnew;
                rightend= Nnew;
            }
            else
            {
                //is 0 if node is not inserted 1 if it has
                int done= 0;
                
                for (node *current_node = leftend ; current_node != NULL ; current_node= current_node->right )
                {
                    //if name in new node being checked is smaller than name in current node, it is target node.
                    int r= strcmp( Nnew->name , current_node->name );

                    //target node is found
                    //subcase 1: the target node maybe first node.(insertion at left end)
                    //subcase 2: the target node maybe any node.(insertion at left of tsrget node)
                    //subcase 3: target node is not found.(insertion at last(from right) that will be right end ).
                    if (r < 0)
                    {
                        //assuming subcase 2
                        node *temp= current_node->left;
                        //this was actually subcase 1
                        if (temp== NULL)
                        {
                            //subcaes 1: insertion at left end
                            leftend->left= Nnew;
                            Nnew->right= leftend;
                            leftend= Nnew;

                            //insertion is complete hence break loop i.e. no need to look further nodes
                            ++done;
                            break;
                        }
                        //it is subcase 2
                        else
                        {
                            //connect whith temp and currentnode respectively
                            temp->right= Nnew;
                            Nnew->left= temp;

                            current_node->left= Nnew;
                            Nnew->right= current_node;

                            ++done;
                            break;

                        }
                        

                    }
                    


                }

                if (done== 0 )
                {
                    //by now all the list has been teansversed and no target was found hence. new node is largest
                    //subcase 3: insert at right end
                    rightend->right= Nnew;
                    Nnew->left= rightend;
                    rightend= Nnew;
                }

            }

    

            printf("\n\nThank you the data base has been updated.\n");
            printf("Open the databse at %s\n",PATH);


            printf("\nPress 0 to exit, any other key to continue,\n");
            fflush(stdin);
            ans2= ( getchar() - 48 );
            printf("\nYou entered %d.\n",ans2);

        } while (ans2);

    //now the list is ready to be inserted
    for (node *i = leftend ; i != NULL ; i= i->right )
    {
        fprintf( fp , "%s," , i->adhar  );
        fprintf( fp , "%s," , i->name   );
        fprintf( fp , "%s," , i->gender );
        fprintf( fp , "%s," , i->father );
        fprintf( fp , "%s," , i->mother );
        fprintf( fp , "%s\n" , i->dob   );
    }
    
    //closing file
    fclose(fp);
    
    return 0;
    
}


int delete(void)
{
    int done= 0;
    //opening file
    FILE *fp= fopen(PATH,"w");
    if (fp== NULL)
    {
        printf("Couldnt open file");
        return 4;
    }

    char *target= getstring("Enter the name of the adhar/social security no. of the person you want to delete: ");

    for (node *i = leftend ; i != NULL ; i= i->right )
    {
        if ( strcmp( i->adhar , target )!= 0 )
        {
            fprintf( fp , "%s," , i->adhar  );
            fprintf( fp , "%s," , i->name   );
            fprintf( fp , "%s," , i->gender );
            fprintf( fp , "%s," , i->father );
            fprintf( fp , "%s," , i->mother );
            fprintf( fp , "%s\n" , i->dob   );
        }
        else
            ++done;     
    }
    
    if (done== 0)
    {
        printf("Not found.");
        fclose(fp);
        return 1;
    }
    else
    {
        printf("Deleted successfully. Check here: %s\n",PATH);
        fclose(fp);
        return 0;
    }
}


int search(void)
{
   fflush(stdin);
   char *adhar_as_string= getstring("Enter the adhar no./Social security no.  of person: ");

   for (node *i = leftend ; i != NULL ; i= i->right )
   {    
        if ( strcmp(adhar_as_string,i->adhar)== 0 )
        {
            
            printf("\n\nAdhar no./Social Security no. : %s\nName: %s\n", i->adhar ,i->name );

            printf("Gender: %s\n" , i->gender );

            printf("Fathers name: %s\nMothers name: %s\n", i->father , i->mother );

            printf("Date of Birth : %s\n\n" , i->dob );

            return 0;

        }

   }

   
   printf("Not found.\n");
   return 5;

}


int update(void)
{
    fflush(stdin);
    char *getadhar= getstring("Enter the Adhar number/Social security number of person to update: ");
    
    //checking if this no. exists
    int exist= 0;
    //points to this node(adhar to be deleted)
    node *this;
    
    for (node *i= leftend ; i!=NULL ; i= i->right )
    {
        if(strcmp( getadhar , i->adhar )== 0 )
        {
            exist= 1;
            this= i;
            break;
        }
        
    }

    if (exist== 0)
    {
        printf("\nAdhar no./Social Security no.  was Not Found.\n");
        return 6;
    }
        
    //opening the file
    FILE *fp= fopen(PATH,"w");
    if (fp==NULL)
    {
        return 6;
    }

    
    //getting rest data
    printf("\nPlease do not exit until current persons data is not entered completly.\n");

    //student name.
    fflush(stdin);
    char *name= getstring("\nEnter the name of person. : ");     


    //gender 
    fflush(stdin);
    char *gen= getstring("\nEnter the gender  : ");
         
            
    //student f. name.
    fflush(stdin);
    char *fname= getstring("\nEnter the fathers name.  : ");  
    

    //student m. name.
    fflush(stdin);
    char *mname= getstring("\nEnter the mothers name. : ");
    

    //dob
    fflush(stdin);
    char *gdob= getstring("\nEnter the date of birth. : ");
    
    
    //deleting this node
    if (this->right== NULL || this->left == NULL)
    {
        //this is a corner node
        if (this->left== NULL)
        {
            //this is a left corner node
            leftend= this->right;
            leftend->left= NULL;
            free(this);
        }
        else
        {
            //this is a right corner node
            rightend= this->left;
            rightend->right= NULL;
            free(this); 
        }
        
    }
    else
    {
        //middle node
        node *front= this->right;
        node *behind= this->left;
    
        //connect behind and front
        behind->right= front;
        front->left= behind;
        
        free(this);

    }
    

    //creating a new node
    node *Nnew= malloc(sizeof(node));
    Nnew->right= NULL;
    Nnew->left= NULL;

    strcpy( Nnew->adhar , getadhar );
    strcpy( Nnew->name , name );
    strcpy( Nnew->gender , gen );
    strcpy( Nnew->father , fname );
    strcpy( Nnew->mother , mname );
    strcpy( Nnew->dob , gdob );

    //inserting this node in the list, at desired place.
    if (leftend== NULL && rightend== NULL)
    {
        leftend= Nnew;
        rightend= Nnew;
    }
     else
    {
        //is 0 if node is not inserted 1 if it has
        int done= 0;
                
        for (node *current_node = leftend ; current_node != NULL ; current_node= current_node->right )
        {
            //if name in new node being checked is smaller than name in current node, it is target node.
            int r= strcmp( Nnew->name , current_node->name );

            //target node is found
            //subcase 1: the target node maybe first node.(insertion at left end)
            //subcase 2: the target node maybe any node.(insertion at left of tsrget node)
            //subcase 3: target node is not found.(insertion at last(from right) that will be right end ).
            if (r < 0)
            {
                //assuming subcase 2
                node *temp= current_node->left;
                //this was actually subcase 1
                if (temp== NULL)
                {
                    //subcaes 1: insertion at left end
                    leftend->left= Nnew;
                    Nnew->right= leftend;
                    leftend= Nnew;

                    //insertion is complete hence break loop i.e. no need to look further nodes
                    ++done;
                    break;
                }
                //it is subcase 2
                else
                {
                    //connect whith temp and currentnode respectively
                    temp->right= Nnew;
                    Nnew->left= temp;

                    current_node->left= Nnew;
                    Nnew->right= current_node;

                    ++done;
                    break;

                }
                        

            }
                    


        }

        if (done== 0 )
        {
            //by now all the list has been teansversed and no target was found hence. new node is largest
            //subcase 3: insert at right end
            rightend->right= Nnew;
            Nnew->left= rightend;
            rightend= Nnew;
        }

    }
    
    

    //now the list is ready to be inserted
    for (node *i = leftend ; i != NULL ; i= i->right )
    {
        fprintf( fp , "%s," , i->adhar  );
        fprintf( fp , "%s," , i->name   );
        fprintf( fp , "%s," , i->gender );
        fprintf( fp , "%s," , i->father );
        fprintf( fp , "%s," , i->mother );
        fprintf( fp , "%s\n" , i->dob   );
    }
    
        
    //closing file
    fclose(fp);

    printf("\n\nThank you the data base has been updated.\n");
    printf("Open the databse at %s\n\n",PATH);
    
    return 0;
}

//helper function
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

