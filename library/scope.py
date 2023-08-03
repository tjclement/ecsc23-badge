import serial
from serial.tools.list_ports import comports
import logging


class ADCSettings():
    def __init__(self, dev:serial) -> None:
        self._dev = dev
        self._clk_freq = 25000000
        self._delay = 0

    @property
    def clk_freq(self):
        return self._clk_freq
    
    @clk_freq.setter
    def _set_clk_freq(self, freq:int):
        BASE_CLK = 125000000
        pio_freq = freq*4
        divider = BASE_CLK/pio_freq
        integer = int(divider)
        frac = int((divider-integer)*256)
        if frac == 256:
            frac = 0
            integer += 1
        self._dev.write(f":ADC:PLL {integer},{frac}\n".encode("ascii"))
        self._clk_freq = BASE_CLK/(integer+frac/256)/4
    
    @property
    def delay(self):
        return self._delay
    
    @delay.setter
    def _set_delay(self, delay):
        self._delay = delay
        self._dev.write(f":ADC:DELAY {delay}\n".encode("ascii"))

class GlitchSettings():
    def __init__(self, dev:serial) -> None:
        self._dev = dev
        self._offset = 10
        self._repeat = 10

    @property
    def ext_offset(self):
        return self._offset
    
    @ext_offset.setter
    def ext_offset(self, offset:int):
        self._dev.write(f":GLITCH:DELAY {offset}\n".encode("ascii"))
        self._offset = offset
    
    @property
    def repeat(self):
        """Width of glitch in cycles (approx = 10 ns * width)"""
        return self._repeat

    @repeat.setter
    def repeat(self, width:int):
        self._dev.write(f":GLITCH:LEN {width}\n".encode("ascii"))
        self._repeat = width

class GPIOSettings():
    def __init__(self, dev:serial) -> None:
        self.gpio = []
        for i in range(0, 4):
            self.gpio.append(list())
        self.dev = dev
        self.MAX_CHANGES = 255
        self.MAX_DELAY = 2147483647
        
    def add(self, pin:int, state:bool, delay:int=None, seconds:float=None):
        """
        Add state change to gpio

        Arguments
        ---------
        pin : int
            Which pin to add state change to, [0,3]
        state : bool
            What the state of the pin should be
        delay : int
            Number of cycles delay after state change, each cycle is ~10ns
        seconds : float
            Seconds of delay after state change if delay is not provided

        Returns
        -------
        None        
        """
        if pin < 0 or pin > 3:
            raise ValueError("Pin must be between 0 and 3")
        
        if len(self.gpio[pin]) >= self.MAX_CHANGES:
            raise ValueError("Pin reached max state changes")

        if delay is None:
            if seconds is None:
                raise ValueError("delay or seconds must be provided")
            delay = int(seconds*100000000)

        if delay > self.MAX_DELAY:
            raise ValueError("delay exceeds maximum")
        
        self.gpio[pin].append((delay << 1) | state)
    
    def reset(self):
        """
        Reset all GPIO state changes

        Arguments
        ---------
        None

        Returns
        -------
        None
        """
        for i in range(0, 4):
            self.gpio[i].clear()

    def upload(self):
        """
        Upload GPIO changes to device

        Arguments
        ---------
        None

        Returns
        -------
        None
        """
        self.dev.write(b":GPIO:RESET\n")
        for i in range(0, 4):
            for item in self.gpio[i]:
                print(f":GPIO:ADD {i},{item}")
                self.dev.write(f":GPIO:ADD {i},{item}\n".encode("ascii"))
    

class Scope():
    RISING_EDGE = 0
    FALLING_EDGE = 1

    def __init__(self, port=None) -> None:
        if port is None:
            ports = comports()
            matches = [p.device for p in ports if p.interface == "Sparkle API"]
            if len(matches) != 1:
                matches = [p.device for p in ports if p.product == "Sparkle"]
                matches.reverse()
            if len(matches) != 2:
                raise IOError('Sparkle device not found. Please check if it\'s connected, and pass its port explicitly if it is.')
            port = matches[0]

        self._port = port
        self._dev = serial.Serial(port, 115200, timeout=1.0)
        self.adc = ADCSettings(self._dev)
        self.glitch = GlitchSettings(self._dev)

    def arm(self, pin=0, edge=RISING_EDGE):
        self._dev.write(f":TRIGGER:PIN {pin},{edge}\n".encode("ascii"))

    def trigger(self):
        self._dev.write(b":TRIGGER:NOW\n")
    
    def default_setup(self):
        pass

    def con(self):
        if not self._dev.is_open:
            self._dev.open()

    def dis(self):
        self._dev.close()

    def get_last_trace(self, as_int=False):
        self._dev.reset_input_buffer() #Clear any data
        self._dev.write(b":ADC:DATA?\n")
        data = self._dev.readline()
        if data is None:
            return []
        data = data.decode("ascii").strip()
        if "ERR" in data:
            logging.warning(f"Received: {data}")
            return []
        data = data.split(",")
        data = data[0:50000]
        if as_int:
            return [int(x) for x in data]
        return [float(x)/1024-0.5 for x in data]

    
