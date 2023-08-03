// Q. To find the longest common subsequence of two strings.
#include <stdio.h>
#include <string.h>

int max(int a, int b);

int main()
{
    //given: a = "AGGTAB", b = "GXTXAYB"
    char *a = "abdul rahim khan is a good person and he is a good engennier and he is a good programmer";
    char *b = "abdul is a good person, engennier and programmer";

    //getting the no of characters in A and B, n=6 and m=7
    const int n = strlen(a);
    const int m = strlen(b);

        //now create strings with length 1 more than the length of A and B
        //since the starting index of the strings according to our algo. is 1
        //to do this we concatenate a and b to blank strings A and B
        char A[n + 2];
        A[0] = ' ';
        A[1] = '\0';
        char B[m + 2];
        B[0] = ' ';
        B[1] = '\0';

        strcat(A, a);
        strcat(B, b);


    //creating LCS matrix of size n+1 and m+1
    int LCS[n + 1][m + 1];
    
    //filling the matrix according to the algo.
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            if (i == 0 || j == 0)
            {
                LCS[i][j] = 0;
            }
            else if (A[i] == B[j])
            {
                LCS[i][j] = LCS[i - 1][j - 1] + 1;
            }
            else
            {
                LCS[i][j] = max(LCS[i - 1][j], LCS[i][j - 1]);
            }
        }
        
    }
    
    //printing the LCS
    printf("\nThe LCS matrix is: \n");
    for (int i = 0; i < n + 1; i++)
    {
        for (int j = 0; j < m + 1; j++)
        {
            printf("%2d ", LCS[i][j]);
        }
        printf("\n");
    }
    
    //printing lengrh of LCS
    printf("\nThe length of longest common subsequence is: %d\n\n", LCS[n][m]);

    //printing the longest common subsequence
    //for storing the sequence, the max length of lcs can be max of n and m
    char lcs[max(n, m)];
    int current_index = 0;

    int i = n, j = m;

    while (i>0 && j>0)
    {
        if (A[i] == B[j])
        {
            lcs[current_index] = A[i];
            current_index++;
            i--;
            j--;
        }
        else if (LCS[i - 1][j] > LCS[i][j - 1])
        {
            i--;
        }
        else
        {
            j--;
        }
    }

    printf("The longest common subsequence is: ");
    for (int i = current_index-1; i >=0; i--)
    {
        printf("%c", lcs[i]);
    }
    printf("\n\n");
    
    

    return 0;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}