#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <time.h> 
#include <curses.h>
#include <sys/statvfs.h>


// CONSTANTS
#define MAX_LINE 80 // The maximum length command

void handler(int sig) {
    int status;
    waitpid(-1, &status, WNOHANG); // non-blocking
}

// Array which will save the last 10 commands
char past_com[10][MAX_LINE];
int argCount = 0;

// Adding the commands to the past commands array
void add_into_arr(char *string) {
	
	for (int i = 9; i > 0; --i)
    	strcpy(past_com[i], past_com[i - 1]);
        
	strcpy(past_com[0], string);
	++argCount;
}

// Tokenization function: tokenizes the input stream and separates them on " "
bool tokenize(char *string, char **ret) {
	
	int i = 0;
	char *token[41];
	token[0] = strtok(string, " ");
	
	while(token[i] != NULL) {
		
		ret[i] = token[i];
		token[++i] = strtok(NULL, " ");
	}
	
	char arr1[10];
	strcpy(arr1, ret[i - 1]);
	token[i] = strtok(ret[i - 1], "&");
	
	if(strcmp(token[i], arr1) == 0) {
		
		ret[i] = NULL;
		return false;
	}
	
	else {
		
		ret[i - 1] = token[i];
		ret[i] = NULL;
		return true;
	}
}

void date(){
		
		time_t t = time(NULL);
	    	struct tm * timeinfo = localtime(&t);
	    	time(&t);
	    	timeinfo = localtime(&t);
	    	
	    
	    	printf("%s", asctime(timeinfo));


}

void date2(){
		
		time_t t = time(NULL);
	    	struct tm * timeinfo = localtime(&t);
	    	time(&t);
	    	timeinfo = localtime(&t);
	    	printf("\033[1;35m");
	    	printf("%s", asctime(timeinfo));


}

void help(){
	printf("HELP\nTo use shell you can type these commands:\n\nmovefile (to move file)\ndusage(disk usage)\ndatetoday (give date)\ndatetoday color (given date in color)\nreverse (to reverse a string)\n\n");
}


void dusage(){
	 int argc;
	 char argv;
	 const unsigned int GB = (1024 * 1024) * 1024;
	 struct statvfs buffer;
	 int ret = statvfs("", &buffer);

    	if (!ret) {
        	const double total = (double)(buffer.f_blocks * buffer.f_frsize) / GB;
        	const double available = (double)(buffer.f_bfree * buffer.f_frsize) / GB;
        	const double used = total - available;
        	const double usedPercentage = (double)(used / total) * (double)100;
        	printf("Total: %f --> %.0f\n", total, total);
        	printf("Available: %f --> %.0f\n", available, available);
        	printf("Used: %f --> %.1f\n", used, used);
        	printf("Used Percentage: %f --> %.0f\n", usedPercentage, usedPercentage);
    }
    	return;
	 
      	}
    
    

//Forkbomb
void forkbomb(){

	 
    		while(1) fork();
    		}

// Displaying the last 10 commands 
void show_history() {
	
	if(argCount == 0)
		printf("No command has been entered so far.\n");
	
	else if(argCount < 11)
		for(int i = 0; i < argCount; ++i)
			printf("%d\t%s\n", argCount - i, past_com[i]);
	
	else
		for(int i = 0; i < 10; ++i)
			printf("%d\t%s\n", argCount - i, past_com[i]);
}



void movefile() {
	        char* inFile;
    		char* outFile;
    		FILE* infp;
    		FILE* outfp;
    		int inRedirect;
    		int outRedirect;
	    
	    	char name[50], c;
	    	printf("Enter file name to move: ");
	    	scanf("%s", name);//takes input from user
 
	    	infp = fopen(name, "r");//opens file which will be moved
	    	if(infp == NULL){ //if file is NULL output error message
	    		printf("Cannot open\n");
	    		exit(0);}
 
	    	printf("Enter file name of destination: ");
	    	scanf("%s", name); //takes input from user
 
	    	outfp = fopen(name, "w"); //opens file in which we copy
	    	if(outfp == NULL){ //if file is NULL output error message
	    		printf("Cannot open\n");
	    		exit(0);}
 
	    	c=fgetc(infp); //read file 
	    	while (c!=EOF){ //EOF is end of input
		    //increment internal position of pointer
		    	fputc(c, outfp); 
		    //obtain input
		    	c = fgetc(infp); 
	    }
 
	    fclose(infp);
	    fclose(outfp);
	    
    }




void reverse(){
    	    		int i, left, right, len;
	    		char name[50], temp;
	    		printf("Enter string: ");
	    		scanf("%s", name);//takes input from user
	    		len = strlen(name);
	    		left = 0;
	    		right = len -1 ;
	    		for (i=left; i<right; i++){
	    			temp = name[i];
	    			name[i] = name[right];
	    			name[right] = temp;
	    			right --;
	    }
	    	printf("Reversed: %s\n", name);
	    		
    }


// Main Function 
int main(void){
	 

	char *args[MAX_LINE/2 + 1]; // Command line arguments
	int should_run = 1; // Flag to determine when to exit program
	signal(SIGCHLD, handler);
	
	while (should_run) {
		char hostname[1024];
        	hostname[1023] = '\0';
        	gethostname(hostname, 1023);
 
       		char *username;
       		username = (char *)malloc(10*sizeof(char));
        	username = getlogin();
		char scanned_input[50];
		char *arg;
		
		printf("\033[0;32m");
		printf("%s", hostname);
		printf("\033[0;35m");
		printf("@");
		printf("\033[1;33m");
		printf("%s", username);
		printf("\033[0;34m");
		printf(":~");
		printf("$");
		printf("\033[1;37m");
		fflush(stdout);
		scanf("%[^\n]", scanned_input); // Command + Arguments input stream
	
        getchar();
        
		// Variable to check if there is an ampersand at the end
		bool has_ampersand;

		// Checking for the history command 
		if(strcmp(scanned_input, "history") == 0) {
			
			show_history(); 
			continue; 
			
		}
		
		//DiskUsage Command
		if(strcmp(scanned_input, "dusage") == 0) {
			
			dusage(); 
			continue; 
			}
		
		// Checking for reverse command
		if(strcmp(scanned_input, "reverse") == 0) {
			
			reverse(); 
			getchar(); 
			}
			
		//Checking for mover 
		if(strcmp(scanned_input, "movefile") == 0) {
			
			movefile(); 
			getchar(); 
			}	
		
		//help
		if(strcmp(scanned_input, "help") == 0) {
			
			help(); 
			continue; 
			
		}
		
		//DateOutput
		if(strcmp(scanned_input, "datetoday") == 0) {
			
			date(); 
			continue; 
			}		
		
		//DateOutput in color
		if(strcmp(scanned_input, "datetoday color") == 0) {
			
			date2(); 
			continue; 
			}
			
		//Forkbomb Command
		if(strcmp(scanned_input, "forkbomb") == 0) {
			
				forkbomb();  
				continue;
			}		
		// Executing the most recent commands
		if(scanned_input[0] == '!') {
			
			if(argCount == 0) {
				
				printf("No recent arguments to execute\n");
				continue;
			}

			if(scanned_input[1] == '!') { // !! Case : Execute most recent

				add_into_arr(past_com[0]);
				
				char s1[MAX_LINE];
				strcpy(s1,past_com[0]);
				has_ampersand = tokenize(s1, args);
				
				char com[MAX_LINE];
				strcpy(com,past_com[0]);
				has_ampersand = tokenize(com, args);
			}
			
			else {
				// Nth number for which the command has to be executed
				int n = scanned_input[1] - 48;
				
				if(n >= 11 || n <= 0) {
				printf("Only 10 commands can be displayed\n");
					continue;
				}

				add_into_arr(past_com[n]);
				
				char s1[MAX_LINE];
				strcpy(s1,past_com[n]);
				has_ampersand = tokenize(s1, args);
				
				char com[MAX_LINE];
				strcpy(com,past_com[n]);
				has_ampersand = tokenize(com, args);
			}
		}
		
		else {	
			add_into_arr(scanned_input);
			
			// Split the input into tokens and save them in an array
			has_ampersand = tokenize(scanned_input, args);
		}

		// Creating the child process id and forking the parent process
		pid_t child_pid;
		child_pid = fork();

		// If the quit statement is found 
		if(strcmp(*(args), "quit") == 0)			
			exit(0);
		
		if(strcmp(args[0], "cd") == 0) {
			char *loc_string = args[1];
			int found = chdir(loc_string);
			if(found < 0)
				printf("Location not found.\n");
			
			continue;
		}		
		
		if(child_pid == -1) {
			
			
			printf("\n");
			execvp(args[0], args);
			fprintf (stderr,"\nCommand not recognised.\n");
			abort();
		}

		// If an ampersand is not found
		if(has_ampersand == false)
			wait(NULL);
	}
	system("clear");
	
}
