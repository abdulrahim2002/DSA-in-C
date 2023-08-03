#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NO_OF_STUDENTS 7 //no. of students in data
char *path= "C:\\Users\\Abdul\\Desktop\\programs\\assignment 1\\db.csv"; //path of source data

//functions used
int add(void);
int delete(void);
int search(void);
int display(void);

//helper functions
char *getstring(char *string_to_print);

typedef struct adress_type
{
   char house_no[50];
   char streetname[50];
   char city[50];
   char state[50];
}adress_type;

typedef struct student
{
   //Roll No ( As a primary key)
   char roll_no[3];
   // Students Name
   char studentsname[50];
   // Father’s Name
   char fathersname[50];
   // Mother’s Name
   char mothersname[50];
   // Semester
   char semester[10];
   // Branch
   char branch[10];

   adress_type adress;
   
}student;

//declaring an array of students which  will have attributes mensioned in class
student students[NO_OF_STUDENTS];


int main(void)
{ 
   //fetching the data from csv file

   //opening file
   FILE *fp= fopen(path,"r");
   if (fp==NULL)
   {
      printf("Failed to open file.");
      return 1;
   }


   //storing the data locally

   int c; //current character being read

   for (int i = 0; i < NO_OF_STUDENTS; i++)
   {
      //declaring j which will be used to index,
      int j;
      
      //fetching roll no.
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].roll_no[j]= (char)c;
      }
      students[i].roll_no[j]= '\0';

      //fething name
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].studentsname[j]= (char)c;
      }
      students[i].studentsname[j]= '\0';


      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].fathersname[j]= (char)c;
      }
      students[i].fathersname[j]= '\0';


      //fething m. name
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].mothersname[j]= (char)c;
      }
      students[i].mothersname[j]= '\0';

      

      //fetcihng semester
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].semester[j]= (char)c;
      }
      students[i].semester[j]= '\0';


      //fething branch
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].branch[j]= (char)c;
      }
      students[i].branch[j]= '\0';


      //fething house no
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].adress.house_no[j]= (char)c;
      }
      students[i].adress.house_no[j]= '\0';


      //fething street
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].adress.streetname[j]= (char)c;
      }
      students[i].adress.streetname[j]= '\0';


      //fething city
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' ; j++)
      {
         students[i].adress.city[j]= (char)c;
      }
      students[i].adress.city[j]= '\0';


      //fething state ,faulty
      for (j = 0; ( c= getc(fp) )!= EOF  && c!= ',' && c!='\n' ; j++)
      {
         students[i].adress.state[j]= (char)c;
      }
      students[i].adress.state[j]= '\0';


      
      //checking if data was read correctly
      if (c!= '\n' || c== EOF)
      {
         printf("Failed to fetch data.\n\n");
         return 3;
         
      }

   }
   
   
   
   //making the user interface

   printf("__________________________________________________________________________\n\n");

   printf("Enter 1 to Add a record.\n");
   printf("Enter 2 to Delete a record.\n");
   printf("Enter 3 to Search a Record.\n");
   printf("Enter 4 for Displaying students belonging to particular city/State/Country.\n\n");

   printf("___________________________________________________________________________\n");

   int ans1= ( (int)getchar() - 48 ) ;
   printf("\nYou pressed %d.\n\n",ans1);

   int r1,r2,r3,r4; //return values of functions
   
   switch (ans1)
   {
      case 1:
      r1= add();
      if (r1)
      {
         printf("Failed to add, add manually to avoid malfunctioning.\n");
      }    
      break;

      
      
      case 2:
      r2= delete();
      if (r2 && r2!=6 )
      {
         printf("Failed to delete, delete manually to avoid malfunctioning.\n");
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

      default:
      printf("Invalid choice.\n");

   }



   //closing the files
   fclose(fp);

   return 0;

}







//implementing functions

int add(void)
{
   int ans2; //to ask if continue
   int n; //to take the no. read

   //opening file in a mode
   FILE *file= fopen(path,"a");
   if (file==NULL)
   {
      return 1;
   }


   //adding value
   do
   {
      START:
      //taking roll no.      
      fflush(stdin);
      printf("\nEnter the roll number of student. (Note: roll no. should be less than %d )",NO_OF_STUDENTS);
      char *rollno= getstring(" : ");

      if (atoi(rollno) <= NO_OF_STUDENTS )
      {
         goto START;
      }
      fprintf(file,"%s,",rollno);
      
      
      //student name.
      fflush(stdin);
      char *name= getstring("\nEnter the name of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",name);
      


      //student f. name.
      fflush(stdin);
      char *fname= getstring("\nEnter the fathers name (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",fname);
     


      //student m. name.
      fflush(stdin);
      char *mname= getstring("\nEnter the mothers name (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",mname);
      

      //semester 
      fflush(stdin);
      char *semester= getstring("\nEnter the semester (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",semester);
      

      //brench
      fflush(stdin);
      char *branch= getstring("\nEnter the branch of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",branch);
      
      

      //house no.
      fflush(stdin);
      char *houseno= getstring("\nEnter the houseno of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",houseno);
      

      //street
      fflush(stdin);
      char *streetname= getstring("\nEnter the streetname of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",streetname);
      

      //city
      fflush(stdin);
      char *city= getstring("\nEnter the city of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s,",city);
      
 
 
      //state
      fflush(stdin);
      char *state= getstring("\nEnter the state of student (warning, dont exit until current data is not entered.) : ");
      fprintf(file,"%s",state);
      
      
      //printing next line
      fprintf(file,"\n");

      printf("\n\nNote: Go to the source code of this program and increment NO_OF_STUDENT by 1, otherwize fetching data may fail.\n");
      printf("Since array lenght cannot be modified(constant) we cannot do it auto matically.\n");


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
   printf("\nEnter the roll no. of student to be deleted.\n");
   
   fflush(stdin);
   int ans3= ( getchar() - 48 );
   int exist= 0; //checking if this roll no. exists
   
   //opening the file
   FILE *fp= fopen(path,"w");
   if (fp==NULL)
   {
      exit(1);
   }
   
   for (int i = 0; i < NO_OF_STUDENTS ; i++)
   {
      if( ans3== atoi(students[i].roll_no) )
      {
         exist= 1;
         break;
      }
      
   }

   if (exist== 0)
   {
      printf("Roll no. was not found.");
      return 6;
   }
   
   //writing to file all but not the mensioned roll no.
   for (int i = 0; i < NO_OF_STUDENTS; i++)
   {
      //checking if the roll no. is target (automatically skips if target)
      if ( ans3!= atoi(students[i].roll_no) )
      {
         //copying the student data
         fprintf(fp, "%s,%s,%s,%s,%s,", students[i].roll_no ,students[i].studentsname , students[i].fathersname , students[i].mothersname , students[i].semester  );

         fprintf(fp, "%s,%s,%s,%s,%s\n", students[i].branch , students[i].adress.house_no , students[i].adress.streetname , students[i].adress.city , students[i].adress.state  );

      }   
      
   }
   
     
   //closing file
   fclose(fp);

   printf("\nStudent deleted successfully.\n");
   return 0;
}


//working fine
int search(void)
{
   fflush(stdin);
   char *roll_as_string= getstring("Enter the roll of student: ");
   int roll= atoi(roll_as_string); //taking roll no os student and converting it into string.

   for (int i = 0; i < NO_OF_STUDENTS; i++)
   {
      int current= atoi(students[i].roll_no);
      if (current==roll)
      {
         printf("\n\nRoll no. : %s\nName: %s\n", students[i].roll_no ,students[i].studentsname );
            
         printf("Fathers name: %s\nMothers name: %s\n", students[i].fathersname , students[i].mothersname );

         printf("Semester: %s\nBranch: %s\n", students[i].semester , students[i].branch );

         printf("House no. : %s\nStreet name: %s\n", students[i].adress.house_no , students[i].adress.streetname );

         printf("City: %s\nState: %s\n\n", students[i].adress.city , students[i].adress.state);

         return 0;

      }
   }
   
   printf("Not found.\n");
   return 5;

}


int display(void)
{
   printf("Press c to search by city, Press s to search by state: ");
   
   fflush(stdin);
   int ans2= getchar();
   printf("You entered %c\n\n",ans2);

   if (ans2!= 'c' && ans2!= 's' )
   {
      printf("\ninvalid choice.\n"); 
      return 3;
   }
   

   //useful variables.
   int students_with_given_city_state= 0;
   int loopran= 0;


   if (ans2== 'c')
   {
      //searching by city
      fflush(stdin);
      char *city= getstring("Enter the city(students of that city will be displayed)\nNote: use lower case letters only\n-> ");
   
   
      for (int i = 0; i < NO_OF_STUDENTS; i++)
      {
         if ( strcmp( city,students[i].adress.city ) == 0 )
         {        
            printf("\n\nRoll no. : %s\nName: %s\n", students[i].roll_no ,students[i].studentsname );
               
            printf("Fathers name: %s\nMothers name: %s\n", students[i].fathersname , students[i].mothersname );

            printf("Semester: %s\nBranch: %s\n", students[i].semester , students[i].branch );

            printf("House no. : %s\nStreet name: %s\n", students[i].adress.house_no , students[i].adress.streetname );

            printf("City: %s\nState: %s\n\n\n", students[i].adress.city , students[i].adress.state);

            ++students_with_given_city_state;

         }

         ++loopran;

      }
   
   }
   
   
   //searching by state
   else
   {
      //searching by city
      fflush(stdin);
      char *state= getstring("Enter the state(students of that state will be displayed)\nNpte: use lower case letters only\n-> ");
   
   
      for (int i = 0; i < NO_OF_STUDENTS; i++)
      {
         if ( strcmp( state,students[i].adress.state ) == 0 )
         {        
            printf("\n\nRoll no. : %s\nName: %s\n", students[i].roll_no ,students[i].studentsname );
               
            printf("Fathers name: %s\nMothers name: %s\n", students[i].fathersname , students[i].mothersname );

            printf("Semester: %s\nBranch: %s\n", students[i].semester , students[i].branch );

            printf("House no. : %s\nStreet name: %s\n", students[i].adress.house_no , students[i].adress.streetname );

            printf("City: %s\nState: %s\n\n\n", students[i].adress.city , students[i].adress.state);

            ++students_with_given_city_state;

         }

         ++loopran;

      }
   
   }

  

  
  //results
  if ( students_with_given_city_state == 0 )
  {
     printf("No student has matching city or state.\n");
  }

  if (loopran!= NO_OF_STUDENTS )
  {
     return 1;
  }
  
  return 0;
  
}




//helper functions
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

REQUIRMENTS

Write a program which should manage record of your class.
1. Roll No ( As a primary key)
2. Students Name
3. Father’s Name
4. Mother’s Name
6. Semester
7. Branch
8. Address
 a. Home/House No
 b. Street Name
 c. City
 d. State
 

 The program must contain the following methods/functions

(i) Input/ add a record in the data list/database/Data
Array/Record Array
(ii) Delete a record from the data list/database/Data
Array/Record Array
(iii) Search a Record from the data list/database/Data
Array/Record Array.
(iv) Display the records of all the students belong to
particular city/State/Country
(v) Generate report as per requirements


(i) City Name
(ii) State Name
(iii) Country Name

5. Generate Report as per the requirements

*/