/*
 * PDC8544.cpp
 *
 *  Created on: Jan 20, 2013
 *      Author: Rafa Couto http://bitbucket.org/rafacouto
 *     License: See LICENSE.txt
 */

#include "PDC8544.h"
#include "fonts/font5x8.h"


// internal defines
#define MATRIX_SIZE 6*84 // matrix size in bytes

// commands
#define CMD_SET_X 0x80 // sets X-address of RAM
#define CMD_SET_Y 0x40 // sets Y-address of RAM
#define CMD_FUNCTION_SET 0x20 // PD, V, H
#define CMD_DISPLAY_CONTROL 0x08 // D, E
#define CMD_EXT_TEMPERATURE 0x04  // TC1-TC2
#define CMD_EXT_BIAS 0x10  // BS2-BS0
#define CMD_EXT_SET_VOP 0x80  // VOP6-VOP0

// function set
#define FUNCTION_POWER_DOWN 0X00
#define FUNCTION_POWER_ACTIVE 0X04
#define FUNCTION_ADDRESSING_HORIZONTAL 0X01
#define FUNCTION_ADDRESSING_VERTICAL 0X02
#define FUNCTION_INSTRUCTIONS_BASIC 0X00
#define FUNCTION_INSTRUCTIONS_EXTENDED 0X01

// display control
#define DISPLAY_CONTROL_BLANK 0x00
#define DISPLAY_CONTROL_ALL_SEGMENTS_ON 0x01
#define DISPLAY_CONTROL_NORMAL 0x04
#define DISPLAY_CONTROL_INVERSE_VIDEO 0x05


PDC8544::PDC8544(
        int pinSCE, int pinRST, int pinDC, int pinSDIN, int pinSCLK)
{
    // arduino connected digital IO's
    this->pinSCE  = pinSCE;
    this->pinRST  = pinRST;
    this->pinDC   = pinDC;
    this->pinSDIN = pinSDIN;
    this->pinSCLK = pinSCLK;
}


void PDC8544::init() 
{
    // set pins for output
    pinMode(pinSCE,  OUTPUT);
    pinMode(pinRST,  OUTPUT);
    pinMode(pinDC,   OUTPUT);
    pinMode(pinSDIN, OUTPUT);
    pinMode(pinSCLK, OUTPUT);

    // reset lcd
    digitalWrite(pinRST, LOW);
    delay(20);
    digitalWrite(pinRST, HIGH);

    // initial commands
    cmdFunctionSet(FUNCTION_INSTRUCTIONS_EXTENDED);
    cmdExtSetOperationVoltage(0x3F);
    cmdExtSetBiasSystem(2); //  LCD bias mode 1:65
    cmdFunctionSet(FUNCTION_INSTRUCTIONS_BASIC);
    cmdDisplayControl(DISPLAY_CONTROL_NORMAL);
}


/***** interface management *****/

void PDC8544::sendCommand(byte command) 
{
    digitalWrite(this->pinDC, LOW);
    digitalWrite(this->pinSCE, LOW);
    shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, command);
    digitalWrite(this->pinSCE, HIGH);
}


void PDC8544::sendData(byte data) 
{
    digitalWrite(this->pinDC, HIGH);
    digitalWrite(this->pinSCE, LOW);
    shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, data);
    digitalWrite(this->pinSCE, HIGH);
}


void PDC8544::sendData(const byte* data, int count) 
{
    digitalWrite(this->pinDC, HIGH);
    digitalWrite(this->pinSCE, LOW);
    while (count-- > 0) {
        shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, *data++);
    }
    digitalWrite(this->pinSCE, HIGH);
}


/***** commands *****/

void PDC8544::cmdFunctionSet(byte function) 
{
    sendCommand(CMD_FUNCTION_SET | function);
}


void PDC8544::cmdDisplayControl(byte mode) 
{
    sendCommand(CMD_DISPLAY_CONTROL | mode);
}


void PDC8544::cmdSetX(int x) 
{
    sendCommand(CMD_SET_X | x);
}


void PDC8544::cmdSetY(int y) 
{
    sendCommand(CMD_SET_Y | y);
}


void PDC8544::cmdExtSetTemperature(byte temperature) 
{
    if (temperature > 3) return;
    sendCommand(CMD_EXT_TEMPERATURE | temperature);
}


void PDC8544::cmdExtSetBiasSystem(byte system) 
{
    if (system > 7) return;
    sendCommand(CMD_EXT_BIAS | system);
}


void PDC8544::cmdExtSetOperationVoltage(byte opv) 
{
    if (opv > 128) return;
    sendCommand(CMD_EXT_SET_VOP | opv);
}


/***** draw functions *****/

void PDC8544::clear()
{
    digitalWrite(this->pinDC, HIGH);
    digitalWrite(this->pinSCE, LOW);

    for (int b = MATRIX_SIZE; b > 0; b--)
    {
        shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, 0x00);
    }

    digitalWrite(this->pinSCE, HIGH);
    gotoXY(0,0);
}


void PDC8544::gotoXY(byte x, byte y) 
{
    if (x > PDC8544_MAX_X || y > PDC8544_MAX_Y) return;
    digitalWrite(this->pinDC, LOW);
    digitalWrite(this->pinSCE, LOW);
    shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, CMD_SET_X | x);
    shiftOut(this->pinSDIN, this->pinSCLK, MSBFIRST, CMD_SET_Y | y);
    digitalWrite(this->pinSCE, HIGH);
}


void PDC8544::drawByte(byte data)
{
    sendData(data);
}


void PDC8544::drawChar(char c)
{
    const byte* data = FONT5X8[c - 32];
    for (int b = 0; b < 5; b++)
    {
        drawByte(*data++);
    }
    drawByte(0x00);
}


void PDC8544::drawString(const char* s)
{
    while (*s)
    {
        drawChar(*s++);
    }
}


void PDC8544::drawMap(int x, int y, int width, int height, const byte* pixels) 
{
    // TODO
}


