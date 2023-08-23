import matplotlib.pyplot as plt
from scope import Scope
from time import sleep

scope = Scope()
controller = scope.io
for i in range(0, 250, 2):
    controller.add(0, 1, seconds=0.001*i)
    controller.add(0, 0, seconds=0.001*i+0.001)
controller.upload()

scope.glitch.repeat = 38
while True:
    scope.trigger()
    sleep(1)
    data = scope.get_last_trace()
    #plt.plot(data)
    #plt.show()
