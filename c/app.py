import socket
import json as JSON
from flask import Flask
from flask_cors import CORS

SERVERIP   = "127.0.0.1"
SERVERPORT = 20001
BUFFERSIZE = 1024

app = Flask(__name__)
CORS(app)

@app.route("/ip/<ip>")
def hello_world(ip):
    SERVERIP = ip
    obj = { 
            "request": "user/create",  
            "data":{
                  "username":"Aaron"
                }
          }
    return sendServerRequest(obj) + " " + SERVERIP

@app.route("/call")
def hello_world2():
    SERVERIP = "http://server-svc"
    obj = { 
            "request": "user/create",  
            "data":{
                  "username":"Aaron"
                }
          }
    return sendServerRequest(obj) + " " + SERVERIP

@app.route("/<message>")
def hello_world3(message):
    obj = { 
            "request": "user/create",  
            "data":{
                  "username": message
                }
          }
    return JSON.dumps(obj)



@app.route("/")
def hello():
    return "Hello"


def receiveMessageFrom(connection):
    
    response = ''
    while True:
        msg = connection.recv(BUFFERSIZE).decode('utf-8')
        if msg == "/0":
            break
        print(msg)
        response += msg

    return response

def sendServerRequest(json):
    request = JSON.dumps(json)
    request_bytes = str.encode(request)
    address_port = (SERVERIP, SERVERPORT)

    connection = socket.socket(family=socket.AF_INET, type=socket.SOCK_DGRAM)

    connection.sendto(request_bytes, address_port)
    
    response = receiveMessageFrom(connection)

    # json = JSON.loads(response)

    return response 


