from time import sleep
from pygame import event, QUIT
from client import Client

def main():
    client = Client()
    while True:
        for e in event.get():
            if e.type == QUIT:
                return
        client.update()
        sleep(0.1)

if __name__ == '__main__':
    main()
