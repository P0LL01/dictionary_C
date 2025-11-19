#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Struct to hold letter and its frequency
struct LetterFrequency {
    char letter;
    int count;
};

void printLejiko(char **, int, int);
int tsek(char **, int, int);
void Letters(char**, int, int);
void letterCount(char **, int, struct LetterFrequency*);
void bubbleSort(struct LetterFrequency*, int);
void swap(struct LetterFrequency*, struct LetterFrequency*);

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
	int check=tsek(lejiko,pl,columns);
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
    //makes a counter for each letter of the alphabet and puts them in an array so that latter we can sort them and pick the top 5 most used letters
    struct LetterFrequency frequencies[26];
    letterCount(lejiko, pl, frequencies);
    
    // Print the results
    printf("Letter frequencies:\n");
    for (i = 0; i < 26; i++) {
        printf("%c %07d\n", frequencies[i].letter, frequencies[i].count);
    }
    //sorts the array for the frequency of the letters
    bubbleSort(frequencies, 26);
    //printd the 5 most used letters of the file
    printf("The five most used letters are: \n");
    for(i=0;i<5;i++){
	printf("%c %d\n", frequencies[i].letter, frequencies[i].count);
	}

    for(i=0;i<pl;i++){	
    	free(lejiko[i]);
	}
	free(lejiko);
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

int tsek(char **lejiko, int pl, int columns){
	int i,j;
	for(i=0;i<pl;i++){
		for(j=0;j<strlen(lejiko[i]);j++){
			if(lejiko[i][j]==' '){
				return 2;
			}
			if(!isalpha(lejiko[i][j])){
				return 1;
			}
			if(!isupper(lejiko[i][j])){
				return 3;
			}
		}
	}
	return 0;
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

void letterCount(char** lejiko, int pl, struct LetterFrequency* frequencies){
    int i, j;
    for(i = 0; i < 26; i++){
        frequencies[i].letter = 'A' + i;
        frequencies[i].count = 0;
    }

    for (i = 0; i < pl; i++) {
        for (j = 0; j < strlen(lejiko[i]); j++) {
            char ch = toupper(lejiko[i][j]);
            if (ch >= 'A' && ch <= 'Z') {
                frequencies[ch - 'A'].count++;
            }
        }
    }
}


//a function that swaps the values of two variables, mostly used in the bubbleSort function
void swap(struct LetterFrequency *xp, struct LetterFrequency *yp) {
    struct LetterFrequency temp = *xp;
    *xp = *yp;
    *yp = temp;
}

//sorts the table that has the letters by frequency in descending order
void bubbleSort(struct LetterFrequency *array, int n) {
    int i,j;
    for (i = 0; i < n-1; i++)
        for (j = 0; j < n-i-1; j++)
            if (array[j].count < array[j+1].count)
                swap(&array[j], &array[j+1]);
}
