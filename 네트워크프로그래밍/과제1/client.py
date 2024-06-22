# 4_Simple Client
# 서버에게 연결 요청 후 서버가 보낸 문자열 받고 연결 종료

from socket import *
import sys

BUFSIZE = 1024
HOST = '127.0.0.1'
PORT = 5000
ADDR = (HOST, PORT)

serverSocket = socket(AF_INET, SOCK_STREAM)

try: 
    serverSocket.connect(ADDR)
except Exception as e:  
    print('fail %s:%s'%ADDR)
    sys.exit()

print('연결 성공')

while True:
    sendData = input("입력데이터: ")
    serverSocket.send(sendData.encode())
    if sendData == 'exit':
        break
    data = serverSocket.recv(BUFSIZE)
    print("받은 데이터: ", data.decode())
    
serverSocket.close()
print("종료")