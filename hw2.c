/*******************************************************************
 * Henry Walker
 * Assignment number 2
 * Date: June 23, 2022
 *******************************************************************
 * Material by Leonidas Deligiannidis (deligiannidisl@wit.edu) 
 * is licensed under a Creative Commons Attribution-NonCommercial 
 * 3.0 Unported License 
 * (http://creativecommons.org/licenses/by-nc/3.0/). 
 *******************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#include <stdlib.h>


int main ( int argc, char *argv[]) {
	char buffer[257];

	if( argc != 3 ) {
		fprintf(stderr, "USAGE: %s inputFile outputFile.\n", argv[0]);
		exit(-1);
	}

    int infile, outfile, rwr = 257, rr = 257;

    char* outName;

    /* OPEN INPUT FILE */
    if((infile = open(argv[1], O_RDONLY)) == -1)
    {
        fprintf(stderr, "Input file: %s \nCould not be opened! Exiting.\n", argv[1]);
        return -1;
    }
    
    /* OPEN OUTPUT FILE */
    if((outfile = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
    {
        fprintf(stderr, "Output file: %s \nCould not be opened! Exiting.\n", argv[2]);
        return -1;
    }

    /* 
    * 	1) START A LOOP
    *	2) Read from input file into the buffer
    *         Don't read one byte at a time!  Try to read 257 bytes at a time. (this is a major requirement for this assignment).
    * 	3) Write, whatever you read into the buffer, into the output file
    */
    while( rr == 257 && rwr == 257 ) 
    {
        rr = read(infile, buffer, 257);
        rwr = write(outfile, buffer, rr);
    }   

    /* CLOSE THE FILES */
    close(infile);
    close(outfile);

    return(0);
}
