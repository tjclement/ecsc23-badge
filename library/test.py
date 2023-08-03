from gpio import GPIOController
from scope import Scope
import serial

scope = Scope()
controller = GPIOController(scope._dev)
for i in range(0, 4):
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
    controller.adds(i, 1, (i+1)*0.05)
    controller.adds(i, 0, (i+1)*0.05)
controller.upload()

scope.glitch.repeat = 38
while True:
    scope.trigger()
