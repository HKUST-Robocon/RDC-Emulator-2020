/**
 * user.c
 * 
 * This is where you'll write your code.
 * 
 * You may create files and include them here 
 * and whatnot.
 */

#include "user.h"
#include "emulator.h"
#include "qdbmp.h"


extern uint64_t iter;   //  This variable keeps track of how many times loop() was run.
                        //  Feel free to use it.

void setup(void)
{
    //  Initialise your program here.
    //  This function will be called once before loop().

    //  You will probably want to start out by initialising some components.
    emwrite(1, 100);    //  Initialises the left wheel motor.

    //  N.B. You can only initialise and configure components within this function.
    //       (Of course, you can still call another function which does the init.)
}

void loop(void)
{
    //  This function will be called continuously, and spaced out by approximately the same amount of time.

    //  Write your code in here.
    //  N.B. Your program will timeout if no emwrite() output is provided within ~500ms.

    emwrite(0); //  This will output a WAIT command -- which basically does nothing.
}