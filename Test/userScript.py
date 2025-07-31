import socket
import json
import bson
DOMAIN = "127.0.0.1"
SERVER_PORT = 8000
LOG_IN = 10  # message codes
SIGN_UP = 12
SUCCESS = 1
ERROR = 99
INC = 1
BYTE_SIZE = 8   # byte size in bits
INT_SIZE = 4    # int size in bytes
CODE_SIZE = 1   # code size
DATA_LEN_BEGIN = 1  # protocol constants
DATA_LEN_END = 4
DATA_BEGIN = 5
CODE_BEGIN = 0
BUFFER_SIZE = 1024


def main():
    with socket.socket() as sock:
        try:
            server_address = (DOMAIN, SERVER_PORT)  # connecting to port
            sock.connect(server_address)  # connecting to port
        except Exception as e:
            print("Error: ", e)

        print("Choose the request option:")
        print("Log In: 10")
        print("Sign Up: 12")
        print("Error: 99")
        user_choice = int(input())     # get user input
        if user_choice == LOG_IN:
            username = input("Enter username: ")  # get login fields input
            password = input("Enter password: ")
            login_json = {"username": username, "password": password}   # create json and convert it to binary
            login_bson = bson.dumps(login_json)
            msg_to_send = LOG_IN.to_bytes(CODE_SIZE, "big") + len(login_bson).to_bytes(INT_SIZE, "big") + login_bson  # construct message to send
            sock.sendall(msg_to_send)  # send message
        elif user_choice == SIGN_UP:
            username = input("Enter username: ")  # get signup fields input
            password = input("Enter password: ")
            email = input("Enter email: ")
            address = input("Enter address: ")
            phone_number = input("Enter phone number: ")
            birth_date = input("Enter birth date: ")
            signup_json = {"username": username, "password": password, "email": email, "address": address, "phoneNumber": phone_number, "birthDate": birth_date}  # create json and convert it to binary
            signup_bson = bson.dumps(signup_json)
            msg_to_send = SIGN_UP.to_bytes(CODE_SIZE, "big") + len(signup_bson).to_bytes(INT_SIZE, "big") + signup_bson  # construct message to send
            sock.sendall(msg_to_send)  # send message
        elif user_choice == ERROR:
            error_json = {}  # create empty json and convert it to binary
            error_bson = bson.dumps(error_json)
            msg_to_send = ERROR.to_bytes(CODE_SIZE, "big") + len(error_bson).to_bytes(INT_SIZE, "big") + error_bson  # construct message to send
            sock.sendall(msg_to_send)  # send message
        else:
            exit()
        ans = sock.recv(BUFFER_SIZE)  # print the server's answer
        print("Received:")
        print("Message Code - " + str(ans[CODE_BEGIN]))  # print message code

        data_length = int.from_bytes(ans[DATA_LEN_BEGIN:DATA_LEN_END + INC], "big")   # print data length (read to DATA_LEN_END + 1 because it is an index value)
        print("Data Length - " + str(data_length))
        json_data = bson.loads(ans[DATA_BEGIN:DATA_BEGIN + data_length])  # get data json (decode json from buffer)
        print("JSON data:")
        if user_choice == LOG_IN or user_choice == SIGN_UP:
            print("Status - " + str(json_data["status"]))   # print signup or login response
            if json_data["status"] == SUCCESS:  # login was successful
                print("Success")
            else:
                print("Error")
        else:
            print("Message - " + json_data["message"])  # print error response


if __name__ == "__main__":
    main()
