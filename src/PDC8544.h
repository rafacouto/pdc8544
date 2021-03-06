/*
 * PDC8544.h
 *
 *  Created on: Jan 20, 2013
 *      Author: Rafa Couto http://bitbucket.org/rafacouto
 *     License: See LICENSE.txt
 */

#ifndef PDC8544_H_
#define PDC8544_H_

#include <Arduino.h>

#define PDC8544_MAX_X 83
#define PDC8544_MAX_Y 5

/**
 * Manager for a LCD PDC8544 controller. It is a LcdDisplay so that it is
 * possible to use its methods to draw complex forms on it.
 */
class PDC8544 {

public:

    /**
     * @parameter int pinSCE Arduino digital IO where SCE pin is connected.
     * @parameter int pinRST Arduino digital IO where RST pin is connected.
     * @parameter int pinDC Arduino digital IO where DC pin is connected.
     * @parameter int pinSDIN Arduino digital IO where SDIN pin is connected.
     * @parameter int pinSCLK Arduino digital IO where SCLK pin is connected.
     */
    PDC8544(int pinSCE, int pinRST, int pinDC, int pinSDIN, int pinSCLK);

    /***** initialize *****/
    void init();
    
    /***** low level functions *****/
    void sendCommand(byte command);
    void sendData(byte data);
    void sendData(const byte* data, int count);

    /***** draw functions *****/
    void clear();
    void gotoXY(byte x, byte y);
    void drawByte(byte data);
    void drawChar(char c);
    void drawString(const char* s);

private:

    int _pinSCE, _pinRST, _pinDC, _pinSDIN, _pinSCLK;

    // select functions
    void cmdFunctionSet(byte function);

    // normal commands
    void cmdDisplayControl(byte mode);
    void cmdSetX(int x);
    void cmdSetY(int y);

    // extended commands
    void cmdExtSetTemperature(byte temperature);
    void cmdExtSetBiasSystem(byte system);
    void cmdExtSetOperationVoltage(byte opv);

};

#endif /* PDC8544_H_ */
