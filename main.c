#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "svg.h"

typedef struct key_value
{
    char sno[50];
    char col1[50];
    char col2[50];
} dict;

void drawallshapes(void);
void drawchart(dict values[], int row_count);
void readfile(void);
void writeTohtml(void);
int findMax(dict values[], int row);
int findMin(dict values[], int row);
//--------------------------------------------------------
// FUNCTION main
//--------------------------------------------------------
int main()
{
    puts("-----------------");
    puts("| SVG Library   |");
    puts("-----------------\n");
    
    readfile();
    writeTohtml();


    return EXIT_SUCCESS;
}

void drawchart(dict values[], int row_count){
     svg* psvg;
    psvg = svg_create(720, 512);
    if(psvg == NULL)
    {
        puts("psvg is NULL");
    }
    else
    {
        svg_fill(psvg, "none");
        svg_line(psvg, "#000000", 1, 150, 30, 150, 380);
        
        svg_text(psvg, -250, 80, "sans-serif", 14, "#000000", "#000000", "Laps", "rotate");
        
        int space = 560/(row_count+2);
        int x = 130;
        int arr[100];
       
        int max = findMax(values, row_count);
        int min = findMin(values, row_count);
        int y;
        int spaceY;
        
        for(int i=0; i< row_count ; i++){
        sscanf(values[i].col2 , "%d", &y);
     
        x= x+space;
        svg_text(psvg, -450, x, "sans-serif", 10, "#000000", "#000000", values[i].col1, "rotate");
        svg_line(psvg, "#000000", 1, x, 375, x, 385);

        spaceY = (max-y)*4;
        printf("spaceY = %d \n", spaceY);
        svg_circle(psvg, "#000080", 0, "#0000FF", 4,  x ,  30+spaceY);
        spaceY = 0;
        }
      
        int y1 = 30;
        int num2;
        if(max%2 ==0){
          num2= (max-min)/4;
        }else{
          num2 = ((max-min)+1)/4;
        }
      
          char  buf[BUFSIZ];
            if(min%2 !=0){
                  min=min-1;
            }
            
        for(int i=0;i< 5; i++){
           
            svg_line(psvg, "#000000", 1, 155, y1, 145, y1);
          sprintf(buf, "%d", max);
            svg_text(psvg, 120, y1, "sans-serif", 12, "#000000", "#000000", buf ,"");
               max=max-num2;
                y1 = y1 + 70;
        }
        
        svg_line(psvg, "#000000", 1, 150, 380, 600, 380);
        svg_text(psvg, 605, 380, "sans-serif", 14, "#000000", "#000000", "Team","");
        svg_finalize(psvg);
        svg_save(psvg, "charts.svg");
        svg_free(psvg);
    }
    
}


void writeTohtml(void){
    FILE *ptrFile = fopen( "index.html", "w");
    int i; 
    fprintf( ptrFile, "<HTML>\n ");
    fprintf( ptrFile, "<HEAD> <TITLE> Scatter graph </TITLE> </HEAD>\n" );
    fprintf( ptrFile, "<BODY BGCOLOR=\"#FFFFFF\" TEXT=\"#FFBBAA\"> \n"); 
    fprintf( ptrFile, "<p>Example 1: This file was created from a C program</p>\n");
   fprintf(ptrFile, "<img src = 'charts.svg'/>\n");
    fprintf( ptrFile, "</BODY>\n"); 
    fprintf( ptrFile, "</HTML>"); 
    fclose( ptrFile );
}

int findMax(dict values[],int row){
    int max;
    int num;
    sscanf(values[0].col2 , "%d", &max);
       for(int i=0; i< row ; i++){
         sscanf(values[i].col2 , "%d", &num);
     /* If current element is greater than max */
        if(num > max)
        {
            max = num;
        }
       }
       
    printf("\n Max value = : %d",max);
    return max;
}

int findMin(dict values[],int row){
     int min;
     int num;
     sscanf(values[0].col2 , "%d", &min);
     for(int i=0; i< row ; i++){
         sscanf(values[i].col2 , "%d", &num);
     /* If current element is smaller than min */
        if(num < min)
        {
            min = num;
        }
       }
      printf("\n Min value = : %d\n",min);
       return min;
}


void readfile(void) {
    
    char fname[1024];
    printf("Enter the file name: ");
    scanf("%s", fname);
    
    FILE * file = fopen(fname, "r");
    
    if(!file){
    	printf("Could not open the file\n");
	}
	
	char content[1024];
	int row_count = 0;
	int field_count = 0;
	
	dict values[0];
	
	int i=0;
	while(fgets(content, 1024, file)){
	        field_count =0;
	        
	        char *field = strtok(content, ",");
	        row_count++;
	        while(field){
	           if(field_count ==0)
	               strcpy(values[i].col1, field);  
	           if(field_count ==1)
	               strcpy(values[i].col2, field); 
	               
	           field = strtok(NULL, ",");
	           field_count++;
	        }
	        
	        i++;
	}
	fclose(file);
	printf("row_count = %d \n",row_count);
 for(int i=0; i< row_count ; i++){
        printf("%s , %s \n",values[i].col1, values[i].col2);
    }
    drawchart(values,row_count);
}
