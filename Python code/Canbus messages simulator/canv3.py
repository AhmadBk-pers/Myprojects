#This code runs on RPI3 and sends canbus messages that emulates the car messages

import RPi.GPIO as GPIO
import time

# Doors
LEFT_FRONT_DOOR_GPIO            = 7
RIGHT_FRONT_DOOR_GPIO           = 11
LEFT_BACK_DOOR__GPIO            = 13
RIGHT_BACK_DOOR_GPIO            = 15

# seatbelt
DRIVER_SEATBELT_GPIO                    = 12
PASSENGER_SEATBELT_GPIO                 = 16
RL_SEATBELT_GPIO                        = 18
M_SEATBELT_GPIO                         = 22
RR_SEATBELT_GPIO                        = 32

# MORE GUARDIAN CLIENT MESSAGES ARE DEFINED IN /CANMessagesClient/TestApplications/C/CANMessagesClient.h
GUAR_CLIENT_DOORS_STATE_MSG_ID          = 0x0010
GUAR_CLIENT_DOORS_STATE_NOT_AVAIL       = 0x00  # discard the message
GUAR_CLIENT_DOORS_STATE_ERR             = 0x01
GUAR_CLIENT_DOORS_STATE_OPEN            = 0x03  # door is open
GUAR_CLIENT_DOORS_STATE_CLOSED          = 0x02  # door is closed




def setup():
    GPIO.setmode(GPIO.BOARD)
    GPIO.setup(LEFT_FRONT_DOOR_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(RIGHT_FRONT_DOOR_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(LEFT_BACK_DOOR__GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(RIGHT_BACK_DOOR_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(DRIVER_SEATBELT_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(PASSENGER_SEATBELT_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(RL_SEATBELT_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(M_SEATBELT_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)
    GPIO.setup(RR_SEATBELT_GPIO, GPIO.IN, pull_up_down=GPIO.PUD_UP)


def loop():
    while True:
        LEFT_FRONT_DOOR_STATE = GPIO.input(LEFT_FRONT_DOOR_GPIO)
        RIGHT_FRONT_DOOR_STATE = GPIO.input(RIGHT_FRONT_DOOR_GPIO)
        LEFT_BACK_DOOR_STATE = GPIO.input(LEFT_BACK_DOOR__GPIO)
        RIGHT_BACK_DOOR_STATE = GPIO.input(RIGHT_BACK_DOOR_GPIO)
        DRIVER_SEATBELT_STATE = GPIO.input(DRIVER_SEATBELT_GPIO)
        PASSENGER_SEATBELT_STATE = GPIO.input(PASSENGER_SEATBELT_GPIO)
        RL_SEATBELT_STATE = GPIO.input(RL_SEATBELT_GPIO)
        M_SEATBELT_STATE = GPIO.input(M_SEATBELT_GPIO)
        RR_SEATBELT_STATE = GPIO.input(RR_SEATBELT_GPIO)

        if LEFT_FRONT_DOOR_STATE == False:
            print("Left front Door is opened")
            LEFT_FRONT_DOOR_MES = GUAR_CLIENT_DOORS_STATE_OPENED
        else:
            print("Left Door is closed")
            LEFT_FRONT_DOOR_MES = GUAR_CLIENT_DOORS_STATE_CLOSED

        if RIGHT_FRONT_DOOR_STATE == False:
            print("Right front Door is opened")
            RIGHT_FRONT_DOOR_MES = GUAR_CLIENT_DOORS_STATE_OPENED
        else:
            print("Right front Door is closed")
            RIGHT_FRONT_DOOR_MES = GUAR_CLIENT_DOORS_STATE_CLOSED

        if LEFT_BACK_DOOR_STATE == False:
            print("Left back Door is opened")
            LEFT_BACK_DOOR_MES = GUAR_CLIENT_DOORS_STATE_OPENED
        else:
            print("Left back Door is closed")
            LEFT_BACK_DOOR_MES = GUAR_CLIENT_DOORS_STATE_CLOSED

        if RIGHT_BACK_DOOR_STATE == False:
            print("Right back Door is opened")
            RIGHT_BACK_DOOR_MES = GUAR_CLIENT_DOORS_STATE_OPENED
        else:
            print("Right back Door is closed")
            RIGHT_BACK_DOOR_MES = GUAR_CLIENT_DOORS_STATE_CLOSED

        guar_doors_msg_0x10 = pack('>IIIIIHBBBBBB',

        # HEADER - is always 20 bytes
        0x47554152,  # GUAR 32 bit UINT6yj
        1,   # version 32 bit UINT
        0,  # bus ID 32 bit UINT
        666,  # timestamp 32 bit UINT
        6,  # payload size in bytes as 32 bit UINT
        # END HEADER

        # START OF PAYLOAD - THE PAYLOAD MUST BE ALIGNED
        0x10,  # Guardian Client Message ID as 16 bit UINT
        LEFT_FRONT_DOOR_MES,  # Driver 1 BYTE
        RIGHT_FRONT_DOOR_MES,  # Passenger 1 BYTE
        LEFT_BACK_DOOR_MES,  # Rear Driver 1 BYTE
        RIGHT_BACK_DOOR_MES,  # Rear Passenger 1 BYTE

        # ---> 26 byes SO FAR
        0,  # PADDING
        0)  # PADDING

        sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

        # change this to the address of the machine on which the Translator is running
        server_address = ('192.168.1.100', 10000)
        sock.connect(server_address)
        sock.send(guar_doors_msg_0x10)

        print("***********************************")
        time.sleep(0.1)



if __name__ == '__main__':

    setup()

    try:
        loop()

    except KeyboardInterrupt:
        print
        'keyboard interrupt detected'
