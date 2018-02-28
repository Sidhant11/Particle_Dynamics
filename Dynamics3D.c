# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <time.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
# define g 900   //Number of particles

int main() {
    
    float xm = 16.4705;  //maximum x dimension
    float zm = 41.1762;  //maximum z dimension
    float ym = 16.4705;  //maximum y dimension
    int start_cy = 0;
    float vol = xm*ym*zm;
    int i, j, k, traj_lines = 0, con_lines=0, ch =0;
    int cyc,ind1,ind2,ind3,ind4;
    double **T2;

    float elapsed;
    char G[50];
    clock_t start, end;
    FILE *infile_ptr;
    char str[1024];
    FILE *outfile_ptr;
    int t = -24, t1 = -22;   //commented part in the traj.txt and cont.txt

    start = clock();

    //Reading traj.txt and removing filler lines while counting.
    
    infile_ptr = fopen("traj.txt","r");
    if (infile_ptr == NULL)
    {  printf("\n can not open traj.dat");
        exit(1);                             }
    
    outfile_ptr = fopen("T2.txt","w");          //temporary file
    while(fgets(str, sizeof(str), infile_ptr))
    {
        if (str[0]!='#' && str[0]!=' ' && str[0]!='\n')
        {
            fprintf(outfile_ptr, "%s", str) ;
            traj_lines++;
        }
        if (str[0]=='#')
        {
            t1++;   //getting current print cycle number
        }
        
    }
    printf("%d \n", t1);
    int cy_n = (t1-start_cy -1);  //problem in code error in last two cycles hence ingore
    int s1 = (traj_lines);
    fclose(outfile_ptr);
    fclose(infile_ptr);

    infile_ptr = fopen("traj.txt","r");

    //Dynamic memory allocation for reading T2.txt
    
    T2 = (double **) calloc(s1, sizeof(double *));
    for (i = 0; i < s1; i++)
        T2[i] = (double *)calloc(14, sizeof(double));

    infile_ptr = fopen("T2.txt","r");       //reading from temporary file
    
    for (i = 0; i < s1; i++)
        fscanf(infile_ptr, "%le %le %le %le %le %le %le %le %le %le %le %le %le %le \n", &T2[i][0], &T2[i][1], &T2[i][2], &T2[i][3], &T2[i][4], &T2[i][5], &T2[i][6], &T2[i][7], &T2[i][8], &T2[i][9], &T2[i][10], &T2[i][11], &T2[i][12], &T2[i][13]);
    
    fclose(infile_ptr);
   
     outfile_ptr = fopen("T.txt","w");
     if (outfile_ptr == NULL) {
        printf("\n Cannot open file T.txt");
        exit(1);}

    for (i = 0; i < s1; i++)                //converting y = 0 line from mid-point to bottom of computation box
    {
        T2[i][2] = T2[i][2] + xm/2.0;
        T2[i][3] = T2[i][3] + ym/2.0;
        T2[i][4] = T2[i][4] + zm/2.0;
    }

    for (i = 0; i < s1; i++)
    {
        fprintf(outfile_ptr, "%.0f %.2f %le %le %le %le %le %le %le %le %le \n", T2[i][0], T2[i][1], T2[i][2], T2[i][3], T2[i][4], T2[i][5], T2[i][6], T2[i][7], T2[i][11], T2[i][12], T2[i][13]) ;  //output into main file (T.txt)   in format counter, radius, x,y,z
    }
    fclose(outfile_ptr);

    //reading interaction file, remove gibberish and count real lines
    
    end = clock();
    elapsed = ((double) (end - start))/ CLOCKS_PER_SEC;
    printf("\n the elapsed time is: %-1.12f", elapsed);
}



































