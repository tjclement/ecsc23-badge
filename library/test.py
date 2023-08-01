from gpio import GPIOController
import serial

dev = serial.Serial("/dev/ttyACM1", baudrate=115200)
controller = GPIOController(dev)
for i in range(0, 4):
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
controller.upload()
dev.write(":TRIGGER:NOW\n".encode("ascii"))
