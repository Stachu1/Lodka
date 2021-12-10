import RPi.GPIO as io

io.setmode(io.BCM)

motorLF = 18
motorLB = 17

motorRF = 27
motorRB = 22

io.setup(motorLF, io.OUT)
io.setup(motorLB, io.OUT)
io.setup(motorRF, io.OUT)
io.setup(motorRB, io.OUT)

def setMotors(lf, lb, rf, rb):
    io.output(lf, False)
    io.output(lb, False)
    io.output(rf, False)
    io.output(rb, False)

def stop():
    setMotors(False, False, False, False)

def forward():
    setMotors(True, False, True, False)

def backward():
    setMotors(False, True, False, True)

def left():
    setMotors(False, True, True, False)

def right():
    setMotors(True, False, False, True)