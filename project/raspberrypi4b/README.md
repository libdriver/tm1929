### 1. Board

#### 1.1 Board Info

Board Name: Raspberry Pi 4B.

IIC Pin: SCL/SDA GPIO3/GPIO2.

### 2. Install

#### 2.1 Dependencies

Install the necessary dependencies.

```shell
sudo apt-get install libgpiod-dev pkg-config cmake -y
```

#### 2.2 Makefile

Build the project.

```shell
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

#### 2.3 CMake

Build the project.

```shell
mkdir build && cd build 
cmake .. 
make
```

Install the project and this is optional.

```shell
sudo make install
```

Uninstall the project and this is optional.

```shell
sudo make uninstall
```

Test the project and this is optional.

```shell
make test
```

Find the compiled library in CMake. 

```cmake
find_package(tm1929 REQUIRED)
```
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
./tm1929 -i

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
./tm1929 -p

tm1929: SCL connected to GPIO3(BCM).
tm1929: SDA connected to GPIO2(BCM).
```

```shell
./tm1929 -t write --addr=0

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
./tm1929 -e write --addr=0 --hex=0x7F

tm1929: set brightness 0x7F.
```

```shell
./tm1929 -h

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
