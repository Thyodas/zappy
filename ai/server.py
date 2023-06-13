import socket


class ZappyClient:
    def __init__(self, port, name, machine='localhost'):
        self.port = port
        self.name = name
        self.machine = machine
        self.client_socket = None

    def connect(self):
        print("Machine {} connected on port {}".format(self.machine, self.port))
        self.client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.client_socket.connect((self.machine, self.port))
        self.send('TEAM - NAME')

    def send(self, message):
        self.client_socket.sendall(message.encode('utf-8'))

    def receive(self):
        return self.client_socket.recv(1024).decode('utf-8')

    def close(self):
        self.client_socket.close()

    def move_forward(self):
        self.send('Forward')
        return self.receive()  # "ok" or "ko"

    def turn_right(self):
        self.send('Right')
        return self.receive()  # "ok" or "ko"

    def turn_left(self):
        self.send('Left')
        return self.receive()  # "ok" or "ko"

    def look_around(self):
        self.send('Look')
        return self.receive()  # [tile1, tile2,. . . ]

    def broadcast(self, text):
        self.send('Broadcast {}'.format(text))
        return self.receive()  # "ok" or "ko"

    def move_forward(self):
        self.send('Forward')
        return self.receive()  # "ok" or "ko"

    def turn_right(self):
        self.send('Right')
        return self.receive()  # "ok" or "ko"

    def turn_left(self):
        self.send('Left')
        return self.receive()  # "ok" or "ko"

    def look_around(self):
        self.send('Look')
        return self.receive()  # [tile1, tile2,. . . ]

    def broadcast(self, text):
        self.send('Broadcast {}'.format(text))
        return self.receive()  # "ok" or "ko"


client = ZappyClient(port=8005, name='JEAN')
client.connect()

response = client.move_forward()
print("1", response)  # "ok" or "ko"

response = client.turn_right()
print("2", response)  # "ok" or "ko"

response = client.look_around()
print("3", response)  # [tile1, tile2,. . . ]

client.close()
