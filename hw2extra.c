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

    int dir, infile, outfile;

    // argc counter
	if( argc < 3 ) {
		fprintf(stderr, "USAGE: %s inputFiles (spaces in between) outputDir.\n", argv[0]);
		exit(-1);
	}

    // if the file at the end of the cmd line isn't a dir ... error
    if((dir = open(argv[argc - 1], O_DIRECTORY)) == 0)
    {
        fprintf(stderr, "USAGE: %s inputFiles (spaces in between) outputDir.\n", argv[0]);
		exit(-1);
    }

    for(int i = 1; i < argc - 1; i++)
    {
        // reasonably large buffer, snprintf will not overstep here.
        char outName[100];
        snprintf(outName, 100, "%s/%s", argv[argc - 1], argv[i]);

        /* OPEN INPUT FILE */
        if((infile = open(argv[i], O_RDONLY)) == -1)
        {
            fprintf(stderr, "Input file: %s \nCould not be opened! Exiting.\n", argv[i]);
            return -1;
        }
        
        /* OPEN OUTPUT FILE */
        if((outfile = open(outName, O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
        {

            fprintf(stderr, "Output file: %s \nCould not be opened! Exiting.\n", outName);
            return -1;
        }

        /* 
        * 	1) START A LOOP
        *	2) Read from input file into the buffer
        *         Don't read one byte at a time!  Try to read 257 bytes at a time. (this is a major requirement for this assignment).
        * 	3) Write, whatever you read into the buffer, into the output file
        */
        int rr = 257, rwr = 257;

        while( rr == 257 && rwr == 257 ) 
        {
            rr = read(infile, buffer, 257);
            rwr = write(outfile, buffer, rr);
        }   

        /* CLOSE THE FILES */
        close(infile);
        close(outfile);
    }
    close(dir);

    return(0);
}
