
// common_macro.h

#pragma once

#include <stdint.h>

#define SET_REG8(address, value) (*(volatile uint8_t*)(address) = (uint8_t)(value))
#define GET_REG8(address) (uint8_t)(*(volatile uint8_t*)(address))

#define SET_REG16(address, value) (*(volatile uint16_t*)(address) = (uint16_t)(value))
#define GET_REG16(address) (uint16_t)(*(volatile uint16_t*)(address))

#define SET_REG32(address, value) (*(volatile uint32_t*)(address) = (uint32_t)(value))
#define GET_REG32(address) (uint32_t)(*(volatile uint32_t*)(address))


