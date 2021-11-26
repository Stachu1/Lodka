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
            task = input("task: ")
            if task == "sm" or task == "set motors":
                task = "set_motors"
                arg = input("Lm;Rm;t: ")
                arg = {"left": float(arg.split(";")[0]), "right": float(arg.split(";")[1]), "time": float(arg.split(";")[2])}

            if task == "mt" or task == "move to":
                task = "move_to"
                arg = input("North;East: ")
                arg = {"north": float(arg.split(";")[0]), "east": float(arg.split(";")[1])}

            if task == "gd" or task == "get data":
                task = "get_data"
                arg = {}

            msg = self.create_msg(task, arg)
            self.send_msg(msg)

    def create_msg(self, task, arg):
        msg = {
            "key": self.key,
            "task": task,
            "arg": arg,
        }
        return msg

    def send_msg(self, msg):
        try:
            self.s.send(str.encode(str(msg)))
            reply = self.s.recv(2048).decode()
            return reply
        except socket.error as e:
            return str(e)


if __name__ == '__main__':
    network = Network()