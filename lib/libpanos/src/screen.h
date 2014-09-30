#ifndef PANOS_SCREEN_H
#define PANOS_SCREEN_H

/**
 * @author      Benno Zeeman
 * @brief       Functions to control the screen
 * @copyright   The MIT License (MIT)
 * @date        2014
 * @version     1.0
 */

#include <stdint.h>

int panos_screen_initialize(uint16_t width, uint16_t height, uint8_t depth);

#endif
