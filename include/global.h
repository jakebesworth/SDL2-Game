/*  
 * global.h
 *
 * Global functions and preprocessor constant definitions
 *
 */

#ifndef GLOBAL_
#define GLOBAL_

#ifdef __cplusplus
extern "C"
{
#endif

/* File Paths */
#define IMG_DIR "assets/img/"
#define FONT_DIR "assets/fonts/"
#define ERROR_FILE "logs/error_log"
#define CONFIG_FILE ".config"

/* Standard Buffer Size */
#define BUFFER_SIZE 2000

/*  
 * Get contents of a file, put into a string and return allocated memory
 *
 * @param file  filename to read
 *
 * @return allocated string with entire file contents
 *
 */
char * fileGetContents(char * filename);

/*  
 * Opens a stream at the given filename with the given mode
 *
 * @param filename  file to open
 * @param mode      mode for which to open the stream
 *
 * @return FILE pointer to new stream
 *
 */
FILE * openFile(char * filename, char * mode);

/*  
 * Get the system date
 *
 * @return string of the current date
 *
 */
char * getDate();

#ifdef __cplusplus
}
#endif

#endif
