arduino-PDC8544
===============

This is an Arduino library to manage a LCD shield controlled by a PDC8544
chipset.

The library provides helper methods to:

* Initialize the LCD shield 
* Send data and commands to the PDC8544
* Draw characters and character strings

Install the library
===================

[Here][1] is a list of tagged versions of the library where the column on the 
right contains several archive formats (zip, gz):

[1]: https://github.com/rafacouto/pdc8544/releases

Download it and extract the archive in the sketchbook/libraries of your 
Arduino IDE. Rename the extracted folder to 'PDC8544' so that it will be 
easier to identify from the IDE.

Remember to restart the Arduino IDE in order to make the library available
from the menus.


Use the library
===============

From Arduino IDE, select 'PDC8544' under the menu Sketch > Import Library.

Declaring PDC8544
-----------------

Create an instance of PDC8544 indicating the pins where the controller is
connected. For example:

// LCD connected to digital IO's 45,47,49,51,53
PDC8544 lcd(45,47,49,51,53);

These 5 numbers represent the Arduino pins connected to the corresponding
pins in the PDC8544: SCE, RST, DC, SDIN and SCLK

Set up
------

Within the setup() function of your Arduino sketch, call the init() and
clear() funtions to initialize the LCD:

    void setup()
    {
      lcd.init();
      lcd.clear();
    }

Writing text
------------

Use gotoXY(x,y) to set the position where you want to write a text. The
PDC8544 is comformed with a virtual set of 6 rows (Y-coordinate from 0 to 5)
and 84 pixels by row (X-coordinate from 0 to 83).

The functions drawChar(char) and drawString(string) are useful to write
text (chars or strings). Examine 'HelloWord' example provided with the
library to see a working sketch that writes text in the LCD.


Issues
======

Please, send issues with this library to the [issue tracker][2].

[2]: https://github.com/rafacouto/pdc8544/issues

Support is not guaranteed, but your voice is welcome.

Are you developer? If you have any improvement to this code or a bug
review, please, send [pull requests][3].

[3]: https://github.com/rafacouto/pdc8544/pulls


License
=======

This library is free software: you can redistribute it and/or modify
it under the terms of the [GNU General Public License as published by
the Free Software Foundation, either version 3 of the License][4], or
(at your option) any later version.

[4]: https://raw.githubusercontent.com/rafacouto/pdc8544/master/LICENSE.txt

This library is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

Copyright 2012-2013 Rafa Couto




