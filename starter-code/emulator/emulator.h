/**
 * Emulator.h
 * 
 * Contains useful I/O functions for communicating with the emulator.
 * 
 * Do NOT modify this file.
 * You may copy the stuff here to a new file to modify, 
 * but don't modify this file directly.
 */

#include <stdbool.h>
#include <stdint.h>


typedef struct _BMP BMP;    //  Forward declaration of the BMP struct.


/**
 * Input Functions
 * 
 * Use these functions to read input from the emulator.
 * Make sure you request for the input first though!
 * 
 * These functions return true/false depending on whether 
 * the value was successfully read.
 */
bool emread_int(int* value);
bool emread_grab_code(int array[3]);
bool emread_camera(BMP** bmp);  //  Allocates memory into bmp! Make sure you call BMP_Free when you finish using the bitmap!
bool emread_line_sensor(int* id, bool* value);
bool emread_ir_sensor(int* id, bool* value);
bool emread_magnetic_sensor(int* id, int* value);


/**
 * Output Functions
 * 
 * Use these functions to print output to the emulator.
 *  - emwrite(int, ...)             // Writes commands. Pass in params as necessary.
 *  - emdebug(const char*, ...)     // Print debug messages onto the emulator.
 *                                  // Works just like printf().
 * 
 * Make sure the values you pass are of an appropriate type.
 */
void emwrite(int code, ...);
void emdebug(const char* fmt, ...);

/**
 * The following functions are used in main.c.
 * You shouldn't need to call these directly yourself.
 */
void eminit(void);
void emsend(void);
void emdelay_until(uint64_t ms);