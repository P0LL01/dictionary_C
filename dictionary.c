#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


void printLejiko(char **, int , int);
int tsek(char **, int, int, FILE*);
void Letters(char**, int, int);

int *letterCount(char **,int,FILE*a);
void bubbleSort(int*,int);
void swap(int*,int*);

int main(int argc, char *argv[]){
//	system("chcp 1253");
	int pl, columns,j,i;
	FILE *fp;
	//opens and reads input file 
	if ( argc!= 2){
		printf("Usage: %s <input_file> \n", argv[0]);
		return 1;
	}
	
	fp = fopen(argv[1], "r");

	//checks if the file was empty 
	if (fp == NULL) {
		printf("Cannot read input file.\n");
		return 1; //exits the program
	}
	//Reads the amount of words=pl and the amount o columns of the txt file, both of which are in the row of the file 
	if(fscanf(fp,"%d,%d\n",&pl,&columns)!=2){
		printf("Error reading the integers from the file\n");
		return 1;
	} 
	
	//dynamically allocates a 2D matrix for the words of the dictionary
	char **lejiko =(char**)calloc(pl,sizeof(char*));
	for(i=0;i<pl;i++){
		lejiko[i] =(char*)calloc(columns+1,sizeof(char));
	    fscanf(fp,"%s\n",lejiko[i]);
	
	//Checks the case of the memory being empty
	if (lejiko==NULL){
		printf("Memory Problem.\n");
		fclose(fp);
		return 1;
	 }	
	 	
	}
	//Checks the possible errors of the text file 
	int check=tsek(lejiko,pl,columns,fp);
	if(check==1){
		printf("Wrong input! The file has to contain only latin characters and not numbers.\n");
		return 1;
	}else if(check==2){
		printf("There appears to be a space between the words. Wrong input\n");
		return 1;
	}else if(check==3){
		printf("Not all characters are capital letters. Wrong input.\n");
		return 1;
	}
	
	
	printf("%c", lejiko[0][3]);
	//Prints the lejiko
	printLejiko(lejiko,pl,columns);
	//Prints all the capital legtters of the dictionary
	Letters(lejiko, pl, columns);
	for (i = 0; i < pl; i++) {
        free(lejiko[i]);
    }
    //makes a counter for each letter of the alphabet and puts them in an array so that latter we can sort them and pick the top 5 most used letters
    int *array=letterCount(lejiko,pl,fp);
//    countLetters(fp,array,lejiko,pl);
    
    // Print the results
    printf("Letter frequencies:\n");
    for (i = 0; i < 26; i++) {
        printf("%c %07d\n", 'A' + i, array[i]);
    }
    //sorts the array for the frequency of the letters
    bubbleSort(array,pl);
    //printd the 5 most used letters of the file
    printf("The five most used letters are: \n");
    for(i=0;i<5;i++){
    	printf("%c %d\n", 'A'+i, array[i]);
	}
	for(i=0;i<5;i++){
		for(j=1;j<4;j++){
			printf("%c%c\n",'A'+i, 'A'+j);	
		}
	}
    free(array);
    for(i=0;i<pl;i++){	
    	free(lejiko[i]);
	}
	fclose(fp);
	
	return 0;
}

void printLejiko(char **lejiko, int pl, int columns){
	int i,j;
	for(i=0;i<pl;i++){
		for(j=0;j<columns;j++){   
			printf("%c", lejiko[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int tsek(char **lejiko, int pl, int columns, FILE *fp){
	int i,j; 
	for(i=0;i<pl;i++){
		lejiko[i]=(char*)calloc(sizeof(char),columns+1);
		if (lejiko[i] == NULL) {
            printf("Memory Problem.\n");
            return -1;  // Indicate memory allocation failure
        }
        	getchar();

		fgets(lejiko[i],columns+1,fp);
		for(j=0;j<strlen(lejiko[i]);j++){
			if(lejiko[i][j]=='\n'){
				lejiko[i][j]='\0';
			}
			if(lejiko[i][j]==' '){
				return 2;	
			}
			if(isalnum(lejiko[i][j])!=0){
				return 1;
			}
			if(lejiko[i][j]!='\0'){
				if(!((lejiko[i][j]>='A') && (lejiko[i][j]<='Z'))){
				return 3;
			}
		}
	}
	return 0;
	}
}

void Letters(char **lejiko, int pl, int columns){
	int i,j;
	printf("All the letters are: ");
	for(i=0;i<pl;i++){
		for(j=0;j<columns;j++){
			printf("%c", lejiko[i][j]);
		}
	}
	printf("\n");
}

int *letterCount(char** lejiko,int pl,FILE *fp){
	int i;
	int *array1=(int*)calloc(26,sizeof(int));
	if(array1==NULL){
		printf("Memory Problem.\n");
		exit;
	}
	//initializes array to 0
	printf("The following are letter counters for each of the 26 letters of the alphabet.\n");
	for(i=0;i<26;i++){
		array1[i]=0;
	}
	int j;
	for (i = 0; i < pl; i++) {
         for (j = 0; j < strlen(lejiko[i]); j++) {
             char ch = (lejiko[i][j]);

             if ('A' <= ch && ch <= 'Z') {
                 array1[ch - 'A']++;
             }
         }
     }
//	array=&letterCount;
	return array1;
}


//a function that swaps the values of two variables, mostly used in the bubbleSort function 
void swap(int *xp, int *yp) {
    int temp;
	temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//sorts the table that has the letters
void bubbleSort(int *array, int pl) {
    int i,j;
	for (i = 0; i < pl-1; i++)
        for (j = 0; j < pl-i-1; j++)
            if (array[j] > array[j+1])
                swap(&array[j], &array[j+1]);
}
