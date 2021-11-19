from pynput import keyboard
import socket




class Network:
    def __init__(self):
        self.s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.addr = ("192.168.4.1", 80)

        self.connect()
        self.run()

    def connect(self):
        self.s.connect(self.addr)
        self.key = self.s.recv(2048).decode()
        print(f"Key: {self.key}")

    def run(self):
        self.running = True
        while self.running:
            ms = ""
            m = ""
            task = input("task: ")
            if task == "sm" or task == "set motors":
                ms = input("Lm;Rm;t: ")
            if task == "m" or task == "move":
                m = input("North;East")

            msg = self.create_msg(ms)
            self.send_msg(msg)

    def create_msg(self, ms, m):
        msg = {
            "key": self.key,
            "set_motors": ms,
            "move": m,
        }
        return msg

    def send_msg(self, msg):
        try:
            self.s.send(str.encode(str(msg)))
            reply = self.s.recv(2048).decode()
            return reply
        except socket.error as e:
            return str(e)

# class Control:
#     def __init__(self):
#         self.foreward = 'w'
#         self.backward = 's'
#         self.left = 'a'
#         self.right = 'd'
#
#         listener = keyboard.Listener(on_press=self.on_pressed)
#         listener.start()
#         listener.join()
#
#     def on_pressed(self, key):
#         if key == keyboard.Key.esc:
#             return False
#         try:
#             k = key.char
#         except:
#             k = key.name
#
#         msg = ""
#         if(k=="w"):
#             msg += "W"
#         else:
#             msg += "w"
#         if(k=="s"):
#             msg += "S"
#         else:
#             msg += "s"
#         if(k=="a"):
#             msg += "A"
#         else:
#             msg += "a"
#         if(k=="d"):
#             msg += "D"
#         else:
#             msg += "d"
#
#         print("Pressed", k)


if __name__ == '__main__':
    network = Network()