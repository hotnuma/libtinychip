<link href="style.css" rel="stylesheet"></link>

#### LibTinyChip

* Reference
    
    https://pinout.xyz/  
    https://libgpiod.readthedocs.io/en/latest/gpio_tools.html  
    https://abyz.me.uk/lg/lgpio.html  

* Tools
    
    There are currently six command-line tools available:
    
    **gpiodetect**: list all gpiochips present on the system, their names, labels and number of GPIO lines
    
    **gpioinfo**: list lines, their gpiochip, offset, name, and direction, and if in use then the consumer name and any other configured attributes, such as active state, bias, drive, edge detection and debounce period
    
    **gpioget**: read values of specified GPIO lines
    
    **gpioset**: set values of specified GPIO lines, holding the lines until the process is killed or otherwise exits
    
    **gpiomon**: wait for edge events on GPIO lines, specify which edges to watch for, how many events to process before exiting, or if the events should be reported to the console
    
    **gpionotify**: wait for changed to the info for GPIO lines, specify which changes to watch for, how many events to process before exiting, or if the events should be reported to the console


