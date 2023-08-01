class GPIOController():
    def __init__(self, dev) -> None:
        self.gpio = []
        for i in range(0, 4):
            self.gpio.append(list())
        self.dev = dev
        
    def add(self, pin, state, delay):
        self.gpio[pin].append((delay << 1) | state)
    
    def adds(self, pin, state, seconds):
        delay = int(seconds*100000000)
        self.add(pin, state, delay)

    def upload(self):
        self.dev.write(b":GPIO:RESET\n")
        for i in range(0, 4):
            for item in self.gpio[i]:
                print(f":GPIO:ADD {i},{item}")
                self.dev.write(f":GPIO:ADD {i},{item}\n".encode("ascii"))
    