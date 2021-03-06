/*
 *	mmake.cpp	    (An LKM developer's tool for Linux 2.6) 
 *
 *	This utility compiles the kernel-modules whose source-files
 *	reside in the current directory (then cleans up afterward).
 *	
 *	Adapted from: "Building and Running Modules" (Chapter Two), 
 *	in: "Linux Device Drivers (3rd Ed)," by Rubini and Corbett. 
 *
 *	for kernel 2.6.17
 *	TODO: update for kernel 3.10+
 *-------------------------------------------------------------------
 */

#include <stdio.h>	// for fopen(), fprintf(), fclose(), perror() 
#include <dirent.h>	// for opendir(), readdir()
#include <string.h>	// for strchr(), strncmp(), strncpy()
#include <stdlib.h>	// for exit() 

int main( int argc, char **argv )
{
	/* open the current directory */
	DIR	*dp = opendir( "." );	 
	if ( dp == NULL ) { perror( "opendir" ); exit(1); }

	/* create 'Makefile' */
	FILE	*fp = fopen( "Makefile", "w" );	
	if ( fp == NULL ) { perror( "Makefile" ); exit(1); }

	/* write boilerplate statements to compile Linux 2.6 modules */
	fprintf( fp, "\nifneq\t($(KERNELRELEASE),)" );
	fprintf( fp, "\nobj-m\t:= " ); 

	/* form the list of ".o" files from command-line arguments */
	char	filename[ NAME_MAX ];
	for (int i = 1; i < argc; i++)
		{
		strncpy( filename, argv[i], NAME_MAX );
		char	*suffixp = strchr( filename, '.' );
		if (( suffixp == NULL )&&( strlen(filename) < NAME_MAX-3 ))
			strncat( filename, ".o", 3 );  
		suffixp = strchr( filename, '.' );
		if ( strncmp( suffixp, ".o", 3 ) != 0 ) 
			strncpy( suffixp, ".o", 3 );
		fprintf( fp, "%s ", filename );
		}

	/* or form the list of ".o" files from current ".c" files */
	struct dirent		*entry;
	if ( argc == 1 ) while ( entry = readdir( dp ) )
		{
		strncpy( filename, entry->d_name, NAME_MAX );
		char	*suffixp = strchr( filename, '.' );
		if ( suffixp == NULL ) continue;
		if ( strncmp( suffixp, ".c", 3 ) != 0 ) continue; 
		strncpy( suffixp, ".o", 3 );
		fprintf( fp, "%s ", filename );
		}

	/* generate the remainder of the 'Makefile' boilerplate */
	fprintf( fp, "\n" );
	fprintf( fp, "\nelse" );
	fprintf( fp, "\nKDIR\t:= /lib/modules/$(shell uname -r)/build" );
	fprintf( fp, "\nPWD\t:= $(shell pwd)" );
	fprintf( fp, "\n" );
	fprintf( fp, "default:\t" );
	fprintf( fp, "\n\t$(MAKE) -C $(KDIR) SUBDIRS=$(PWD) modules ");
	fprintf( fp, "\n\trm -r -f .tmp_versions *.mod.c .*.cmd *.o " );
	fprintf( fp, "Modules.symvers " );  
	fprintf( fp, "\n" );
	fprintf( fp, "\nendif" );
	fprintf( fp, "\n\n" );
	fclose( fp );

	/* execute the 'make' utility using the created 'Makefile' */
	system(" make ");
}
