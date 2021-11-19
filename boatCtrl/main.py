from pynput import keyboard
import socket

foreward = 'w'
backward = 's'
left = 'a'
right = 'd'

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(("192.168.101.206", 80))

def sendMsg(msg):
    s.sendall(msg.encode("utf-8"))

def on_pressed(key):
    if key == keyboard.Key.esc:
        return False
    try:
        k = key.char
    except:
        k = key.name

    msg = ""
    if(k=="w"):
        msg += "W"
    else:
        msg += "w"
    if(k=="s"):
        msg += "S"
    else:
        msg += "s"
    if(k=="a"):
        msg += "A"
    else:
        msg += "a"
    if(k=="d"):
        msg += "D"
    else:
        msg += "d"

    print("Pressed", k)
    sendMsg(msg+"e")

def on_released(key):
    pass
    # if key == keyboard.Key.esc:
    #     return False
    # try:
    #     k = key.char
    # except:
    #     k = key.name

    # if(k=="w"):
    #     foreward = "w"
    # if(k=="s"):
    #     backward = "s"
    # if(k=="a"):
    #     left = "a"
    # if(k=="d"):
    #     right = "d"

    # print("Released", k)
    # sendMsg()



listener = keyboard.Listener(on_press=on_pressed, on_release=on_released)
listener.start()
listener.join()