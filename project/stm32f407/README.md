### 1. Chip

#### 1.1 Chip Info

Chip Name: STM32F407ZGT6.

Extern Oscillator: 8MHz.

UART Pin: TX/RX PA9/PA10.

IIC Pin: SCL/SDA PB8/PB9.

### 2. Development and Debugging

#### 2.1 Integrated Development Environment

LibDriver provides both Keil and IAR integrated development environment projects.

MDK is the Keil ARM project and your Keil version must be 5 or higher.Keil ARM project needs STMicroelectronics STM32F4 Series Device Family Pack and you can download from https://www.keil.com/dd2/stmicroelectronics/stm32f407zgtx.

EW is the IAR ARM project and your IAR version must be 9 or higher.

#### 2.2 Serial Port Parameter

Baud Rate: 115200.

Data Bits : 8.

Stop Bits: 1.

Parity: None.

Flow Control: None.

#### 2.3 Serial Port Assistant

We use '\n' to wrap lines.If your serial port assistant displays exceptions (e.g. the displayed content does not divide lines), please modify the configuration of your serial port assistant or replace one that supports '\n' parsing.

### 3. TM1929

#### 3.1 Command Instruction

1. Show tm1929 chip and driver information.

   ```shell
   tm1929 (-i | --information)
   ```

2. Show tm1929 help.

   ```shell
   tm1929 (-h | --help)
   ```

3. Show tm1929 pin connections of the current board.

   ```shell
   tm1929 (-p | --port)
   ```

4. Run tm1929  write test.

   ```shell
   tm1929 (-t write | --test=write) [--addr=<0 | 1 | 2 | 3>]
   ```

5. Run tm1929 write function, num means the brightness in hex formart.  

   ```shell
   tm1929 (-e write | --example=write) [--addr=<0 | 1 | 2 | 3>] [--hex=<num>]
   ```

#### 3.2 Command Example

```shell
tm1929 -i

tm1929: chip is Titan Micro Electronics TM1929.
tm1929: manufacturer is Titan Micro Electronics.
tm1929: interface is IIC.
tm1929: driver version is 1.0.
tm1929: min supply voltage is 2.4V.
tm1929: max supply voltage is 5.5V.
tm1929: max current is 40.00mA.
tm1929: max temperature is 85.0C.
tm1929: min temperature is -40.0C.
```

```shell
tm1929 -p

tm1929: SCL connected to GPIOB PIN8.
tm1929: SDA connected to GPIOB PIN9.
```

```shell
tm1929 -t write --addr=0

tm1929: chip is Titan Micro Electronics TM1929.
tm1929: manufacturer is Titan Micro Electronics.
tm1929: interface is IIC.
tm1929: driver version is 1.0.
tm1929: min supply voltage is 2.4V.
tm1929: max supply voltage is 5.5V.
tm1929: max current is 40.00mA.
tm1929: max temperature is 85.0C.
tm1929: min temperature is -40.0C.
tm1929: start write test.
tm1929: tm1929_set_all_on test.
tm1929: tm1929_set_all_off test.
tm1929: tm1929_set_brightness test.
tm1929: finish write test.
```

```shell
tm1929 -e write --addr=0 --hex=0x7F

tm1929: set brightness 0x7F.
```

```shell
tm1929 -h

Usage:
  tm1929 (-i | --information)
  tm1929 (-h | --help)
  tm1929 (-p | --port)
  tm1929 (-t write | --test=write) [--addr=<0 | 1 | 2 | 3>]
  tm1929 (-e write | --example=write) [--addr=<0 | 1 | 2 | 3>] [--hex=<num>]

Options:
      --addr=<0 | 1 | 2 | 3>           Set the chip iic address.([default: 0])
  -e <write>, --example=<write>        Run the driver example.
  -h, --help                           Show the help.
      --hex=<num>                      Set the brightness.([default: 0x7F])
  -i, --information                    Show the chip information.
  -p, --port                           Display the pin connections of the current board.
  -t <write>, --test=<write>           Run the driver test.
```

