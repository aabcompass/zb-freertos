#include "ff_headers.h"
#include "ff_stdio.h"
#include <string.h>

/* The number of bytes read/written to the example files at a time. */
#define tf_fsRAM_BUFFER_SIZE 				200

void write_to_file(char* pcRAMBuffer,FF_FILE* pxFile, char* text){
	size_t l = strlen(text);
	memset( pcRAMBuffer, 0x00, tf_fsRAM_BUFFER_SIZE);
	snprintf( pcRAMBuffer, tf_fsRAM_BUFFER_SIZE, text);
	int32_t lItemsWritten = ff_fwrite( pcRAMBuffer, 1, l, pxFile );
	configASSERT( lItemsWritten==l);
}

void write_lorem(char* pcRAMBuffer,FF_FILE* pxFile){
	write_to_file( pcRAMBuffer, pxFile, "Lorem ipsum dolor sit amet, \n");
	write_to_file( pcRAMBuffer, pxFile, "consectetur adipiscing elit, \n");
	write_to_file( pcRAMBuffer, pxFile, "sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. \n");
	write_to_file( pcRAMBuffer, pxFile, "Ut enim ad minim veniam, \n");
	write_to_file( pcRAMBuffer, pxFile, "quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. \n");
	write_to_file( pcRAMBuffer, pxFile, "Duis aute irure dolor in reprehenderit in voluptate velit \n");
	write_to_file( pcRAMBuffer, pxFile, "esse cillum dolore eu fugiat nulla pariatur. \n");
	write_to_file( pcRAMBuffer, pxFile, "Excepteur sint occaecat cupidatat non proident, \n");
	write_to_file( pcRAMBuffer, pxFile, "sunt in culpa qui officia deserunt mollit anim id est laborum.\n");

}

void create_lorem(int times, char* pcRAMBuffer, char* pcFileName){
	FF_FILE *pxFile;
	snprintf( pcFileName, ffconfigMAX_FILENAME, "lorem_x%d.txt",times);

	/* Obtain the current working directory and print out the file name and
	the	directory into which the file is being written. */
	ff_getcwd( pcRAMBuffer, tf_fsRAM_BUFFER_SIZE );
	FF_PRINTF( "Creating file %s in %s\n", pcFileName, pcRAMBuffer );

	pxFile = ff_fopen( pcFileName, "w" );
	configASSERT( pxFile );

	for(int i=0;i<times;i++)write_lorem( pcRAMBuffer, pxFile);

	FF_Close(pxFile);
}

void createTestFile( const char *pcMountPath )
{
	char *pcRAMBuffer, *pcFileName;

	/* Allocate buffers used to hold date written to/from the disk, and the
	file names. */
	pcRAMBuffer = ( char * ) pvPortMalloc( tf_fsRAM_BUFFER_SIZE );
	pcFileName = ( char * ) pvPortMalloc( ffconfigMAX_FILENAME );
	configASSERT( pcRAMBuffer );
	configASSERT( pcFileName );

	//cd WORKDIR
	int32_t lResult = ff_chdir( pcMountPath );
	configASSERT( lResult >= 0 );


	create_lorem(100,pcRAMBuffer, pcFileName);
	create_lorem(200,pcRAMBuffer, pcFileName);
	create_lorem(500,pcRAMBuffer, pcFileName);
	create_lorem(1000,pcRAMBuffer, pcFileName);
	create_lorem(2000,pcRAMBuffer, pcFileName);
	create_lorem(5000,pcRAMBuffer, pcFileName);
	create_lorem(10000,pcRAMBuffer, pcFileName);
	create_lorem(20000,pcRAMBuffer, pcFileName);
	//create_lorem(50000,pcRAMBuffer, pcFileName);
	//create_lorem(100000,pcRAMBuffer, pcFileName);
	//create_lorem(200000,pcRAMBuffer, pcFileName);
	//create_lorem(500000,pcRAMBuffer, pcFileName);
	//create_lorem(1000000,pcRAMBuffer, pcFileName);
	//create_lorem(2000000,pcRAMBuffer, pcFileName);
	//create_lorem(5000000,pcRAMBuffer, pcFileName);


	vPortFree( pcRAMBuffer );
	vPortFree( pcFileName );
}
