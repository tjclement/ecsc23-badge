import serial
from serial.tools.list_ports import comports
import logging


class ADCSettings():
    def __init__(self, dev) -> None:
        self._dev = dev
        self._clk_freq = 25000000
        self._delay = 0

    def _set_clk_freq(self, freq):
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

    def _get_clk_freq(self):
        return self._clk_freq
    
    clk_freq = property(
        fget = _get_clk_freq,
        fset = _set_clk_freq,
        doc="Set ADC Clk frequency must be between 500Hz and 31.25MHz"
    )

    def _set_delay(self, delay):
        self._delay = delay
        self._dev.write(f":ADC:DELAY {delay}\n".encode("ascii"))
    
    def _get_delay(self):
        return self._delay

    delay = property(
        fget = _get_delay,
        fset = _set_delay,
        doc = "Set delay between start of ADC and trigger"
    )

class GlitchSettings():
    def __init__(self, dev) -> None:
        self._dev = dev
        self._offset = 10
        self._repeat = 10

    @property
    def ext_offset(self):
        return self._offset
    
    @ext_offset.setter
    def ext_offset(self, offset):
        self._dev.write(f":GLITCH:DELAY {offset}\n".encode("ascii"))
        self._offset = offset
    
    @property
    def repeat(self):
        """Width of glitch in cycles (approx = 8.3 ns * width)"""
        return self._repeat

    @repeat.setter
    def repeat(self, width):
        self._dev.write(f":GLITCH:LEN {width}\n".encode("ascii"))
        self._repeat = width

class GPIOSettings():
    pass

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
        return [int(x) for x in data]

    
