/**
 * main.c
 * 
 * The natural habitat of the main() function.
 * You may refer to this file to gain an understanding
 * of the program's flow.
 * 
 * Do NOT modify this file.
 */

#include "user.h"
#include "emulator.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


uint64_t iter = 0;
bool ready = false;

void wait_for_ack(void)
{
    char input_buffer[64];
    if (!fgets(input_buffer, 64, stdin)) return;
    int len = strlen(input_buffer);
    if (len == 0) return;
    input_buffer[3] = 0;
    ready = (strcmp(input_buffer, "ACK") == 0);
}


int main(void)
{
    while (!ready)
        wait_for_ack();

    setup();
    emwrite(100);
    emsend();
    eminit();

    while (1)
    {
        loop();
        emsend();

        iter++;
        emdelay_until(50);  //  Space out each loop iteration by ~50ms.
    }
}
