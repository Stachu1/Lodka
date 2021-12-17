import RPi.GPIO as io

io.setmode(io.BCM)

motorLF = 23
motorLB = 17

motorRF = 27
motorRB = 22

motorEN = 18

io.setup(motorLF, io.OUT)
io.setup(motorLB, io.OUT)
io.setup(motorRF, io.OUT)
io.setup(motorRB, io.OUT)

io.setup(motorEN, io.OUT)

power = io.PWM(18, 60)
power.start(60)

def setMotors(lf, lb, rf, rb):
    io.output(motorLF, lf)
    io.output(motorLB, lb)
    io.output(motorRF, rf)
    io.output(motorRB, rb)

def stop():
    setMotors(False, False, False, False)

def foreward():
    setMotors(True, False, True, False)

def backward():
    setMotors(False, True, False, True)

def left():
    setMotors(False, True, True, False)

def right():
    setMotors(True, False, False, True)