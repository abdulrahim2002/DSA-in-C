#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

#define path "C:\\Users\\Abdul\\Desktop\\programs\\dsa assignments done by me\\assignment 2\\db.csv"    //path of the source file


//node declaration
typedef struct address
{
    char houseno[10];
    char streetname[50];
    char city[50];
    char state[50];
    char country[50];
    char pin[20];

}address_type;

typedef struct citizen
{
    char adhar_number[15];
    char citizen_name[50];
    char fathers_name[50];
    char mothers_name[50];
    char job_rank[50];
    char department[50];
    char date_of_joining[20]; //in format dd/mm/yyyy
    
    address_type address;

    //pointer to the next citizen
    struct citizen *next;

}node;

node *list= NULL;   //pointer to first node in the list
int no_of_people=0; //no of people in the database

//functions used
int add(void);
int delete(void);
int search(void);
int display(void);
int update(void);


//helper functions
char *getstring(char *string_to_print);




int main()
{
    //storing the data locally

    //opening the file
    FILE *fp= fopen(path,"r");
    if (fp==NULL)
    {
        printf("Failed to open file");
        return 1;
    }

    //counting the number of citizens in source file. this much nodes will be read
    int c;
    while (( c=getc(fp) )!=EOF)
    {
        if (c=='\n')
        {
            ++no_of_people;
        }
        
    }
    rewind(fp); //to reset the cursor to start of file.

    

    for(int i=0; i< no_of_people; ++i)
    {
        //initialize a pointer to node and allocating memory.Now the pointer has garbage node.
        node *p= malloc( sizeof(node) );

        p->next= NULL; // ** VVP

        int j;  //used to index array within nodes//current input character

        //fetching adhar number
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
        {
            p->adhar_number[j]= c;
        }
        p->adhar_number[j]= '\0';

        
        //citizen name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->citizen_name[j]= c;
        }
        p->citizen_name[j]= '\0';

        
        //fathers name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->fathers_name[j]= c;
        }
        p->fathers_name[j]= '\0';

        
        //mothers name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->mothers_name[j]= c;
        }
        p->mothers_name[j]= '\0';


        //job rank
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->job_rank[j]= c;
        }
        p->job_rank[j]= '\0';

        
        //department
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->department[j]= c;
        }
        p->department[j]= '\0';


        //date of joining
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->date_of_joining[j]= c;
        }
        p->date_of_joining[j]= '\0';


        //house no
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->address.houseno[j]= c;
        }
        p->address.houseno[j]= '\0';


        //steet name
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->address.streetname[j]= c;
        }
        p->address.streetname[j]= '\0';


        //city
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->address.city[j]= c;
        }
        p->address.city[j]= '\0';


        //state
        for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++) 
        {
            p->address.state[j]= c;
        }
        p->address.state[j]= '\0';


        //countary
        for( j= 0 ; ( c= getc(fp) ) != ',' && c!= EOF  ; ++j) 
        {
            p->address.country[j]= c;
        }
        p->address.country[j]= '\0';
        
        //pin
        for( j= 0 ; ( c= getc(fp) ) != ',' && c!= EOF && c!='\n' ; ++j) 
        {
            p->address.pin[j]= c;
        }
        p->address.pin[j]= '\0';
        
        if( c != '\n' )
        {
            printf("Failed to fetch data.\n");
            return 3;
        }


        
        //integrating this node onto the list, Adding at the beggining
        
        /*
        p->next= list;  //p and list are pointing the first node in existing list.

        list= p;        //list now has the address of first node i.e. p. and p has address of the second node.
        
        */
        
        
        //adding at the end
        if (list== NULL)
        {
            list= p;
        }
        else
        {
            for (node *i = list ; i!= NULL ;   )
            {
                if (i->next == NULL)
                {
                    //we found the last node it is in i(i points to it). no we dereference it it assign it our node p
                    i->next= p;
                    break;
                }
                else
                {
                    i= i->next;
                }
            }
        }
        
    
        
        
    }
    
    

    
    //making UI

    //making the user interface

   printf("__________________________________________________________________________\n\n");

   printf("Enter 1 to  Add a record.\n");
   printf("Enter 2 to  Delete a record.\n");
   printf("Enter 3 to  Search a Record.\n");
   printf("Enter 4 for Displaying people belonging to particular city/State/Country.\n");
   printf("Enter 5 to  Update a record.\n\n");

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
         printf("Failed to add, add manually to database at location :%s .\n",path);
      }    
      break;

      
      
      case 2:
      r2= delete();
      if (r2 && r2!=6 )
      {
         printf("Failed to delete, delete manually to database at location:%s .\n",path);
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
      r4= display();
      if (r4)
      {
         printf("Failed to display.\n");
      }
      break;

      case 5:
      r5= update();
      if (r5)
      {
          printf("Failed to Update. You can update database manually at location: %s ",path);
      }
      
      break;
      
      default:
      printf("Invalid choice.\n");

   }


    

    
    // Free list
    while (list != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
    
    //closing the file
    fclose(fp);
    
    return 0;

}




int add(void)
{
    int ans2; //to ask if continue

   //opening file in a mode
   FILE *file= fopen(path,"a");
   if (file==NULL)
   {
      return 1;
   }


   //adding value
   do
   {
        printf("\nPlease do not exit until current persons data is not entered completly.\n");
        printf("\nNote use Camel case only. i.e. first letter capital and  rest small. eg. = 'Hi' 'These' 'Are' 'Camel' 'Case'  \n");

        START:
        //taking roll no.      
        fflush(stdin);
        char *adhar= getstring("\nEnter the Adhar number/Social security number of the person: ");

        //checking if the person is currently in the record. 
        for (node *i= list; i!= NULL ; i= i->next )
        {
            if (  atoll( adhar ) == atoll( i->adhar_number ) )
            {
                printf("\nThis Adhar number/Social security number is already in the record.\n\n");
                goto START;
            }
              
        }
        fprintf(file,"%s,",adhar);
    
      
      
      //student name.
      fflush(stdin);
      char *name= getstring("\nEnter the name of person. : ");
      fprintf(file,"%s,",name);
      


      //student f. name.
      fflush(stdin);
      char *fname= getstring("\nEnter the fathers name.  : ");  
      fprintf(file,"%s,",fname);
     


      //student m. name.
      fflush(stdin);
      char *mname= getstring("\nEnter the mothers name. : ");
      fprintf(file,"%s,",mname);
      

      //rank 
      fflush(stdin);
      char *rank_position= getstring("\nEnter the Rank/position/occupation.  : ");
      fprintf(file,"%s,",rank_position);
      

      //company
      fflush(stdin);
      char *department= getstring("\nEnter the department of work palce/Company.  : ");
      fprintf(file,"%s,",department);
      
      

      //date of joining
      fflush(stdin);
      char *doj= getstring("\nEnter the date of joining.  : ");
      fprintf(file,"%s,",doj);
      

      //gouse
      fflush(stdin);
      char *house_no= getstring("\nEnter the house no. of the person  : ");
      fprintf(file,"%s,",house_no);
      
      
      //street
      fflush(stdin);
      char *streetname= getstring("\nEnter the streetname of the person.  : ");
      fprintf(file,"%s,",streetname);
      

      //city
      fflush(stdin);
      char *city= getstring("\nEnter the city of the person.  : ");
      fprintf(file,"%s,",city);
      
 
 
      //state
      fflush(stdin);
      char *state= getstring("\nEnter the state of the person.  : ");
      fprintf(file,"%s,",state);


      //countary
      fflush(stdin);
      char *countaryname= getstring("\nEnter the country of residense.  : ");
      fprintf(file,"%s,",countaryname);


      //pin
      fflush(stdin);
      char *pin= getstring("\nEnter the pin code of the area.  : ");
      fprintf(file,"%s\n",pin);


      printf("\n\nThank you the data base has been updated.\n");
      printf("Open the databse at %s\n",path);


      printf("\nPress 0 to exit, any other key to continue,\n");
      fflush(stdin);
      ans2= ( getchar() - 48 );
      printf("\nYou entered %d.\n",ans2);

   } while (ans2);
   
   

   fclose(file);
   
   return 0;
    
}



int delete(void)
{
   printf("\nEnter the Adhar number/Social security number of person to be deleted.\n");
   
   fflush(stdin);
   char ans3[20];

   int c,i;   //current input character
   for (i = 0; i < 20 && ( c=getchar() ) != '\n' ; i++)
   {
       ans3[i]= c;
   }
   ans3[i]= '\0';
   
   
   int exist= 0; //checking if this  no. exists
   
   //opening the file
   FILE *fp= fopen(path,"w");
   if (fp==NULL)
   {
      exit(1);
   }
   
   for (node *i=list; i!=NULL ; i= i->next )
   {
      if( atoll(ans3) == atoll(i->adhar_number) )
      {
         exist= 1;
         break;
      }
      
   }

   if (exist== 0)
   {
      printf("\nAdhar no./Social Security no.  was Not Found.\n");
      return 6;
   }
   
   
   //writing to file all but not the mensioned roll no.
   for (node *i = list; i!= NULL ; i= i->next )
   {
       //checking if the roll no. is target (automatically skips if target)
        if ( atoll(ans3) != atoll(i->adhar_number) )
       {
            //copying the student data
            fprintf(fp, "%s,%s,%s,%s,%s,", i->adhar_number , i->citizen_name , i->fathers_name , i->mothers_name , i->job_rank  );

            fprintf(fp, "%s,%s,%s,%s,%s,", i->department , i->date_of_joining , i->address.houseno , i->address.streetname , i->address.city  );

            fprintf(fp, "%s,%s,%s\n", i->address.state , i->address.country , i->address.pin  );

       }
   }
   
     
   //closing file
   fclose(fp);

   printf("\nRecord deleted successfully. Check on database location: %s \n",path );
   return 0;
}



int search(void)
{
   fflush(stdin);
   char *adhar_as_string= getstring("Enter the adhar no./Social security no.  of person: ");

   long long int adhar= atoll(adhar_as_string); //taking roll no os student and converting it into string.

   for (node *i = list; i != NULL ; i= i->next )
   {
        long long int current= atoll(i->adhar_number);
        
        if ( current== adhar )
        {
            
            printf("\n\nAdhar no./Social Security no. : %s\nName: %s\n", i->adhar_number ,i->citizen_name );
                
            printf("Fathers name: %s\nMothers name: %s\n", i->fathers_name , i->mothers_name );

            printf("Rank/Position/Occupation: %s\nDepartment/Company: %s\n", i->job_rank , i->department );

            printf("Date of joining : %s\nHouse no. : %s\n", i->date_of_joining , i->address.houseno );

            printf("Street name: %s\nCity: %s\n", i->address.streetname , i->address.city );

            printf("State: %s\nCountary: %s\n", i->address.state , i->address.country );

            printf("Pin : %s\n\n", i->address.pin );

            return 0;

        }

   }

   
   printf("Not found.\n");
   return 5;

}



int display(void)
{
   printf("Press 'c' to search by city, 's' to search by state, 'x' to search by country: ");
   
   fflush(stdin);
   int ans2= getchar();
   printf("You entered %c\n\n",ans2);

   if (ans2!= 'c' && ans2!= 's' && ans2!= 'x' )
   {
      printf("\ninvalid choice.\n"); 
      return 3;
   }
   

   //useful variables.
   int people_with_given_city_state_countary= 0;
   int loopran= 0;


    //searching by city
   if (ans2== 'c')
   {
      //searching by city
      fflush(stdin);
      char *city= getstring("Enter the city(people of that city will be displayed)\nNote: use Camel case letters only \ni.e. first letter capital, rest small. eg.=Yokohama\n\n-> ");



      for (node *i = list; i != NULL ; i= i->next )
      {
        if ( strcmp( city,  i->address.city ) == 0 )
        {        
            printf("\n\nAdhar no./Social Security no. : %s\nName: %s\n", i->adhar_number ,i->citizen_name );
                
            printf("Fathers name: %s\nMothers name: %s\n", i->fathers_name , i->mothers_name );

            printf("Rank/Position/Occupation: %s\nDepartment/Company: %s\n", i->job_rank , i->department );

            printf("Date of joining : %s\nHouse no. : %s\n", i->date_of_joining , i->address.houseno );

            printf("Street name: %s\nCity: %s\n", i->address.streetname , i->address.city );

            printf("State: %s\nCountary: %s\n", i->address.state , i->address.country );

            printf("Pin : %s\n\n", i->address.pin );

            ++people_with_given_city_state_countary;

        }

        ++loopran;

      }

   
   } 
   
   //searching by state
   else if(ans2 == 's')
   {
      //searching by state
      fflush(stdin);
      char *state= getstring("Enter the State (People of that state will be displayed)\nNote: use Camel case letters only \ni.e. first letter capital, rest small. eg.= Kanagawa\n\n-> ");



      for (node *i = list; i != NULL ; i= i->next )
      {
        if ( strcmp( state,  i->address.state ) == 0 )
        {        
            printf("\n\nAdhar no./Social Security no. : %s\nName: %s\n", i->adhar_number ,i->citizen_name );
                
            printf("Fathers name: %s\nMothers name: %s\n", i->fathers_name , i->mothers_name );

            printf("Rank/Position/Occupation: %s\nDepartment/Company: %s\n", i->job_rank , i->department );

            printf("Date of joining : %s\nHouse no. : %s\n", i->date_of_joining , i->address.houseno );

            printf("Street name: %s\nCity: %s\n", i->address.streetname , i->address.city );

            printf("State: %s\nCountary: %s\n", i->address.state , i->address.country );

            printf("Pin : %s\n\n", i->address.pin );

            ++people_with_given_city_state_countary;

        }

        ++loopran;

      }
   
    }

   //searching by country
   else
   {
      //searching by country
      fflush(stdin);
      char *country= getstring("Enter the Country (People of that country will be displayed)\nNote: use Camel case letters only \ni.e. first letter capital, rest small. eg.= India\n\n-> ");



      for (node *i = list; i != NULL ; i= i->next )
      {
        if ( strcmp( country,  i->address.country ) == 0 )
        {        
            printf("\n\nAdhar no./Social Security no. : %s\nName: %s\n", i->adhar_number ,i->citizen_name );
                
            printf("Fathers name: %s\nMothers name: %s\n", i->fathers_name , i->mothers_name );

            printf("Rank/Position/Occupation: %s\nDepartment/Company: %s\n", i->job_rank , i->department );

            printf("Date of joining : %s\nHouse no. : %s\n", i->date_of_joining , i->address.houseno );

            printf("Street name: %s\nCity: %s\n", i->address.streetname , i->address.city );

            printf("State: %s\nCountary: %s\n", i->address.state , i->address.country );

            printf("Pin : %s\n\n", i->address.pin );

            ++people_with_given_city_state_countary;

        }

        ++loopran;

      }
 
    }

  

  
  //results
  if ( people_with_given_city_state_countary == 0 )
  {
     printf("No person has matching city/state/country .\n");
  }

  if (loopran!= no_of_people )
  {
     return 1;
  }
  
  return 0;
}


int update(void)
{
    printf("\nEnter the Adhar number/Social security number of person to update.\n");
   
    fflush(stdin);
    char ans3[20];

    int c,i;   //current input character
    for (i = 0; i < 20 && ( c=getchar() ) != '\n' ; i++)
    {
        ans3[i]= c;
    }
    ans3[i]= '\0';
    
    
    int exist= 0; //checking if this  no. exists
    
    //opening the file
    FILE *fp= fopen(path,"w");
    if (fp==NULL)
    {
        exit(1);
    }
    
    for (node *i=list; i!=NULL ; i= i->next )
    {
        if( atoll(ans3) == atoll(i->adhar_number) )
        {
            exist= 1;
            break;
        }
        
    }

    if (exist== 0)
    {
        printf("\nAdhar no./Social Security no.  was Not Found.\n");
        return 6;
    }
   
   


   //getting data and printing it in file on first

        //adhar number
        fprintf(fp,"%s,",ans3);
        
        
        
        printf("\nPlease do not exit until current persons data is not entered completly.\n");
        printf("\nNote use Camel case only. i.e. first letter capital and  rest small. eg. = 'Hi' 'These' 'Are' 'Camel' 'Case'  \n");

        //student name.
        fflush(stdin);
        char *name= getstring("\nEnter the name of person. : ");
        fprintf(fp,"%s,",name);
        


        //student f. name.
        fflush(stdin);
        char *fname= getstring("\nEnter the fathers name.  : ");  
        fprintf(fp,"%s,",fname);
        


        //student m. name.
        fflush(stdin);
        char *mname= getstring("\nEnter the mothers name. : ");
        fprintf(fp,"%s,",mname);
        

        //rank 
        fflush(stdin);
        char *rank_position= getstring("\nEnter the Rank/position/occupation.  : ");
        fprintf(fp,"%s,",rank_position);
        

        //company
        fflush(stdin);
        char *department= getstring("\nEnter the department of work palce/Company.  : ");
        fprintf(fp,"%s,",department);
        
        

        //date of joining
        fflush(stdin);
        char *doj= getstring("\nEnter the date of joining.  : ");
        fprintf(fp,"%s,",doj);
        

        //gouse
        fflush(stdin);
        char *house_no= getstring("\nEnter the house no. of the person  : ");
        fprintf(fp,"%s,",house_no);
        
        
        //street
        fflush(stdin);
        char *streetname= getstring("\nEnter the streetname of the person.  : ");
        fprintf(fp,"%s,",streetname);
        

        //city
        fflush(stdin);
        char *city= getstring("\nEnter the city of the person.  : ");
        fprintf(fp,"%s,",city);
        
    
    
        //state
        fflush(stdin);
        char *state= getstring("\nEnter the state of the person.  : ");
        fprintf(fp,"%s,",state);


        //countary
        fflush(stdin);
        char *countaryname= getstring("\nEnter the country of residense.  : ");
        fprintf(fp,"%s,",countaryname);


        //pin
        fflush(stdin);
        char *pin= getstring("\nEnter the pin code of the area.  : ");
        fprintf(fp,"%s\n",pin);
 
      





   
    //writing to file all but not the mensioned roll no.
    for (node *i = list; i!= NULL ; i= i->next )
    {
        //checking if the roll no. is target (automatically skips if target)
            if ( atoll(ans3) != atoll(i->adhar_number) )
        {
                //copying the student data
                fprintf(fp, "%s,%s,%s,%s,%s,", i->adhar_number , i->citizen_name , i->fathers_name , i->mothers_name , i->job_rank  );

                fprintf(fp, "%s,%s,%s,%s,%s,", i->department , i->date_of_joining , i->address.houseno , i->address.streetname , i->address.city  );

                fprintf(fp, "%s,%s,%s\n", i->address.state , i->address.country , i->address.pin  );

        }
    }
    
        
    //closing file
    fclose(fp);

        printf("\n\nThank you the data base has been updated.\n");
        printf("Open the databse at %s\n\n",path);
    
    return 0;
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



/*
requirments:

Write a modular program using Simple Linked List for managing record of Citizen of a Country 
(e.g. India may be considered). The attributes of a record are as follows-

    •Aadhar Card/Social Security Number (As a primary key)
    • Citizen Name {Alphabets a-z(only) and .}
    • Citizen Father’s Name {Alphabets a-z(only) and .}
    • Citizen Mother’s Name {Alphabets a-z(only) and .}
    • Rank/Position {Alphabets a-z(only) and .}
    • Department of Work Place {Alphabets a-z(only) and .}
    • Date of Joining the Department {Only Numeric Value dates and months should not be more than 2 digits and year should not be less or more than 4 digits.
    • Citizen Address
        • Home/House No
        • Street Name
        • City
        • State
        • Country
        • Pin

The program must contain the following modules.
 
    • Insert a record into the database.
    • Delete a record from the database
    • Find a Record into the database
    • Update a Record {Aadhar Card cannot be changed}
    • Display the records of all the Persons belong to particular city/State/Country/Pin.
    

 Generate report as per requirements {e.g., List the Persons City/State wise}

Note: Database should not maintain duplication records.

*/