#!/usr/bin/env python3

import sys
import os
import datetime
import zmq


def main():
    context = zmq.Context()
    socket = context.socket(zmq.SUB)
    socket.connect(sys.argv[1])
    socket.setsockopt_string(zmq.SUBSCRIBE, '')

    while True:
        string = socket.recv_string()
        print(string)


if __name__ == "__main__":
    main()
