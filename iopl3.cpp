/*
 *	iopl3.cpp	 (Enables user programs to perform direct I/O)
 *
 *	This utility for Linux systems allows a user to launch a
 *	new command shell which possesses system privileges that
 *	each subsequenty executed application will then inherit,
 *	and thereafter be able execute the 'iopl()' system-call.
 *
 *	  compile using:  root# make iopl3
 *	     		  root# chmod a+s iopl3  
 *	  install using:  root# mv iopl3 /usr/local/bin/.
 *
 *	  execute using:  user$ iopl3
 *
 */

#include <stdio.h>	// for printf()
#include <unistd.h>	// for getuid(), setuid()
#include <sys/io.h>	// for iopl()
#include <stdlib.h>	// for system()

int main(int argc, char *argv[])
{
	/* preserve this task's user-identity */
        int 	uid = getuid();
        printf( "my uid: %d\n", getuid() );

	/* change this task's effective user-identity to 'root' */
        setuid( 0 );
        printf( "new uid: %d\n", getuid() );

	/* now 'root' can change this task's I/O Privilege-Level: IOPL=3 */
        iopl( 3 );

	/* restore this task's former user-identity */
        setuid( uid );
        printf( "uid afer iopl: %d\n", getuid()) ;

	/* launch a new command-shell which will inherit IOPL=3 
	 * note the new shell is not in a new window and may not
	 * inherit properties of parent shell.  $ exit, to return
	 * to original shell
	 */
        system( "bash --login" );
        return 0;
}

