[English](/README.md) | [ 简体中文](/README_zh-Hans.md) | [繁體中文](/README_zh-Hant.md) | [日本語](/README_ja.md) | [Deutsch](/README_de.md) | [한국어](/README_ko.md)

<div align=center>
<img src="/doc/image/logo.svg" width="400" height="150"/>
</div>

## LibDriver TM1929

[![MISRA](https://img.shields.io/badge/misra-compliant-brightgreen.svg)](/misra/README.md) [![API](https://img.shields.io/badge/api-reference-blue.svg)](https://www.libdriver.com/docs/tm1929/index.html) [![License](https://img.shields.io/badge/license-MIT-brightgreen.svg)](/LICENSE)

TM1929 is a constant current LED driver circuit with 128 order linear current regulation function, built-in with 18 independent low impedance color LED driver channels, which can provide a constant current of 3-40mA at each output stage. TM1929 adopts the I2C bus structure, and through code settings, the current size of any channel can be adjusted. There are a total of 128 levels of current adjustment, ranging from 0% to 190%. Every three LEDs share an enable switch, and by controlling this switch signal, it is possible to achieve the brightness change of any color of RGB lights.

LibDriver TM1929 is a full-featured driver for TM1929, launched by LibDriver. It provides LED display and additional features. LibDriver is MISRA compliant.

### Table of Contents

  - [Instruction](#Instruction)
  - [Install](#Install)
  - [Usage](#Usage)
    - [example basic](#example-basic)
  - [Document](#Document)
  - [Contributing](#Contributing)
  - [License](#License)
  - [Contact Us](#Contact-Us)

### Instruction

/src includes LibDriver TM1929 source files.

/interface includes LibDriver TM1929 IIC platform independent template.

/test includes LibDriver TM1929 driver test code and this code can test the chip necessary function simply.

/example includes LibDriver TM1929 sample code.

/doc includes LibDriver TM1929 offline document.

/datasheet includes TM1929 datasheet.

/project includes the common Linux and MCU development board sample code. All projects use the shell script to debug the driver and the detail instruction can be found in each project's README.md.

/misra includes the LibDriver MISRA code scanning results.

### Install

Reference /interface IIC platform independent template and finish your platform IIC driver.

Add the /src directory, the interface driver for your platform, and your own drivers to your project, if you want to use the default example drivers, add the /example directory to your project.

### Usage

You can refer to the examples in the /example directory to complete your own driver. If you want to use the default programming examples, here's how to use them.

#### example basic

```C
#include "driver_tm1929_basic.h"

uint8_t res;
uint8_t j;
uint8_t buffer[18];
uint8_t hex_code = 127;

/* basic init */
res = tm1929_basic_init(TM1929_ADDRESS_0);
if (res != 0)
{
    return 1;
}

...
    
/* make brightness */
for (j = 0; j < 18; j++)
{
    buffer[j] = hex_code;
}
res = tm1929_basic_set_brightness(0, buffer, 18);
if (res != 0)
{
    tm1929_interface_debug_print("tm1929: set brightness failed.\n");
    (void)tm1929_basic_deinit();

    return 1;
}

/* output */
tm1929_interface_debug_print("tm1929: set brightness 0x%02X.\n", hex_code);

...
    
/* deinit */
(void)tm1929_basic_deinit();

return 0;
```

### Document

Online documents: [https://www.libdriver.com/docs/tm1929/index.html](https://www.libdriver.com/docs/tm1929/index.html).

Offline documents: /doc/html/index.html.

### Contributing

Please refer to CONTRIBUTING.md.

### License

Copyright (c) 2015 - present LibDriver All rights reserved



The MIT License (MIT) 



Permission is hereby granted, free of charge, to any person obtaining a copy

of this software and associated documentation files (the "Software"), to deal

in the Software without restriction, including without limitation the rights

to use, copy, modify, merge, publish, distribute, sublicense, and/or sell

copies of the Software, and to permit persons to whom the Software is

furnished to do so, subject to the following conditions: 



The above copyright notice and this permission notice shall be included in all

copies or substantial portions of the Software. 



THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR

IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,

FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE

AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER

LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,

OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE

SOFTWARE. 

### Contact Us

Please send an e-mail to lishifenging@outlook.com.