/**
 * Emulator.c
 * 
 * Do NOT modify this file.
 * You may copy the stuff here to a new file to modify, 
 * but don't modify this file directly.
 */

#include "emulator.h"
#include "qdbmp.h"
#include <stdarg.h>
#include <stdio.h>
#include <time.h>


#define PRINT_BUFFER_LENGTH 64
#define INPUT_BUFFER_LENGTH 256


//  Local variables.
static clock_t last_ticks;
static char buffer[64][PRINT_BUFFER_LENGTH];
static uint8_t buffsz = 0;

static char input_buffer[INPUT_BUFFER_LENGTH];

/**
 * Macros for reading a line and parsing by a format.
 * A typical way of using these is:
        bool read_something() {
            //  Read an entire line. Return false if the line couldn't be read.
            if (!rdln()) return false;

            //  Parse the line. Return false if EOF or if params couldn't be parsed.
            int val = 0;
            if (!parse("STUFF %d", 1, &val)) return false;

            return true;
        }
 */
#define rdln()                          fgets(input_buffer, INPUT_BUFFER_LENGTH, stdin)
#define parse(fmt, num_params, ...)     (sscanf(input_buffer, fmt, __VA_ARGS__) >= num_params)
#define parse0(fmt)                     (sscanf(input_buffer, fmt) >= 0)


bool emread_int(int* value)
{
    if (!rdln()) return false;
    if (!parse("%d", 1, value)) return false;
    return true;
}

bool emread_grab_code(int array[3])
{
    if (!rdln()) return false;
    if (!parse("%d %d %d", 3, &array[0], &array[1], &array[2])) return false;
    return true;
}

bool emread_camera(BMP** bmp)
{
    if (!rdln()) return false;
    if (!parse0("CAMERA")) return false;
    
    *bmp = BMP_ReadFile("./camera.bmp");
    BMP_CHECK_ERROR(stderr, false); // If an error has occurred, notify and return false.
    return true;
}

bool emread_line_sensor(int* id, bool* value)
{
    int tmp;
    if (!rdln()) return false;
    if (!parse("LINE %d %d", 2, id, &tmp)) return false;
    *value = tmp;
    return true;
}

bool emread_ir_sensor(int* id, bool* value)
{
    int tmp;
    if (!rdln()) return false;
    if (!parse("IR %d %d", 2, id, &tmp)) return false;
    *value = tmp;
    return true;
}

bool emread_magnetic_sensor(int* id, int* value)
{
    if (!rdln()) return false;
    if (!parse("MAGNETIC %d %d", 2, id, value)) return false;
    return true;
}

#define printcase(num, fmt) case num: vsnprintf(buffer[buffsz++], PRINT_BUFFER_LENGTH, fmt, args); break;
void emwrite(int code, ...)
{
    //  Buffers the data to write. It gets sent later on when emsend() is called.
    va_list args;
    va_start(args, code);
    switch (code)
    {
    printcase(0, "WAIT")
    printcase(1, "INIT %d")
    printcase(2, "CONFIG %d %d %d %.6f")
    printcase(3, "SET %d %d %.6f")
    printcase(4, "REQUEST %d")
    printcase(5, "REQUESTVAR %d")
    printcase(10, "GRAB %d")
    printcase(11, "PLACE %d")
    printcase(13, "CONFIGCAM %d %f")
    printcase(20, "TMLOAD %.6f")
    printcase(21, "TMTHROW")
    printcase(100, "STOPINIT")
    default: break;
    }
    va_end(args);
}

void emdebug(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fflush(stderr);
    va_end(args);
}

/* ===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-=== */
/* ===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-=== */
/* ===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-===-=== */

void eminit(void)
{
    last_ticks = clock();
}

void emsend(void)
{
    for (uint8_t i = 0; i < buffsz; i++)
        printf("%s\n", buffer[i]);
    printf("ENDTURN\n");
    fflush(stdout);

    buffsz = 0;
}

/**
 * @brief   Delays until not more than ms has passed since the last delay.
 */
void emdelay_until(uint64_t ms)
{
    uint64_t pause = ms * (CLOCKS_PER_SEC/1000);
    clock_t now = clock();
    while (now - last_ticks < pause)
        now = clock();
    last_ticks = now;
}