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

/* Standard Buffer Size */
#define BUFFER_SIZE 2000

/* General Functions */

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
