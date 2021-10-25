# Author : Ahmad Bakri
# This code moves the servos to the positions by sending command to arduino
# HPV7
import datetime

import serial
import time
import numpy as np
import Logger

# Communication parameters
Port_name = '/dev/ttyUSB0'
Baud_rate = 115200

# ServoID dictionary
servo_dict = {
    "Yaw": 1,
    "Pitch": 2,
    "Roll": 3
}

# Servo ID
Yaw_servo_id = servo_dict["Yaw"]
Pitch_servo_id = servo_dict["Pitch"]
Roll_servo_id = servo_dict["Roll"]
Get_Real_Angle_id = 9

# Default parametes
Default_Yaw_angle = 0
Default_Pitch_angle = 0
Default_Roll_angle = 0
Default_time = 1

# Speed of movement
trans_time = 0.01
steps = 10
checks = 1


# This function converts the given angle to the aprropriate servo value
def convertAngle(Angle):
    Position = int(512 + (int(Angle) * (1 / 0.29)))
    return Position


# This function converts the given servo value to the aprropriate angle
def convertPosition(Position):
    angle = int((int(Position - 512) * 0.29))
    return angle


# Boundaries parameters
# Upper/Lower limits for the Yaw servo - by defualt they are the normal 0-1023 (0-300) positions for the servo
Yaw_MAX = convertPosition(999)
Yaw_MIN = convertPosition(100)
# the F2 'C' bracket attached to the Pitch servo creates a physical limitation to how far
# we can move the Pitch servo. This software limit will ensure that we don't jam the bracket into the servo.
Pitch_MAX = convertPosition(860)
Pitch_MIN = convertPosition(200)
# the F2 'C' bracket attached to the Pitch servo creates a physical limitation to how far
# we can move the Pitch servo. This software limit will ensure that we don't jam the bracket into the servo.
Roll_MAX = convertPosition(860)
Roll_MIN = convertPosition(200)

# initiating the communication to Arduino
arduino = serial.Serial(Port_name, Baud_rate)


# This function sends the commands to Arduino
def sendCommand(Servo, Position):
    msg = '$' + str(Servo) + str(Position) + '!'
    arduino.write(msg.encode('utf-8'))


# This function sends the commands to Arduino
def sendPosition(Servo, Angle):
    Position = convertAngle(Angle)
    msg = '$' + str(Servo) + str(Position) + '!'
    arduino.write(msg.encode('utf-8'))


# This function checks that the requested position is in the boundaries
def checkBoundries(Servo, Requested_Angle):
    if (Servo == Yaw_servo_id):
        if (Requested_Angle > Yaw_MAX):
            print("Yaw angle is out of Boundries. Yaw angle set to ", Yaw_MAX)
            return Yaw_MAX, 0x0002
        elif (Requested_Angle < Yaw_MIN):
            print("Yaw angle is out of Boundries. Yaw angle set to ", Yaw_MIN)
            return Yaw_MIN, 0x0002
        else:
            return Requested_Angle, 0x0000
    elif (Servo == Pitch_servo_id):
        if (Requested_Angle > Pitch_MAX):
            print("Pitch angle is out of Boundries. Pitch angle set to ", Pitch_MAX)
            return Pitch_MAX, 0x0002
        elif (Requested_Angle < Pitch_MIN):
            print("Pitch angle is out of Boundries. Pitch angle set to ", Pitch_MIN)
            return Pitch_MIN, 0x0002
        else:
            return Requested_Angle, 0x0000
    elif (Servo == Roll_servo_id):
        if (Requested_Angle > Roll_MAX):
            print("Roll angle is out of Boundries. Roll angle set to ", Roll_MAX)
            return Roll_MAX, 0x0002
        elif (Requested_Angle < Roll_MIN):
            print("Roll angle is out of Boundries. Roll angle set to ", Roll_MIN)
            return Roll_MIN, 0x0002
        else:
            return Requested_Angle, 0x0000
    else:
        return Requested_Angle, 0x0004


# This function checks the real position of hte requested servo
def checkRealAngle(Servo_id):
    # Translate servo ID (use dictionary)
    time.sleep(0.001)  # This delay is so the position register updates
    sendCommand(Get_Real_Angle_id, Servo_id * 100)
    try:
        upper_byte = arduino.read()
        lower_byte = arduino.read()
        real_position = int.from_bytes(upper_byte, "big") * 256 + int.from_bytes(lower_byte, "big")
        real_Angle = convertPosition(real_position)
        return real_Angle, 0x0000
    except:
        print("Communication ERROR with servo", Servo_id)
        return -1, 0x0001


# This function check the position of the three head servos
def getHeadPosition():
    yaw_Angle, yaw_Angle_status = checkRealAngle(Yaw_servo_id)
    pitch_Angle, pitch_Angle_status = checkRealAngle(Pitch_servo_id)
    roll_Angle, roll_Angle_status = checkRealAngle(Roll_servo_id)
    if (yaw_Angle_status == 0x0001 or pitch_Angle_status == 0x0001 or roll_Angle_status == 0x0001):
        return yaw_Angle, pitch_Angle, roll_Angle, 0x0001
    else:
        return yaw_Angle, pitch_Angle, roll_Angle, 0x0000


# Move the requested servo smoothly
def setPosition(axis, Angle):
    Servo_id = servo_dict[axis]
    Angle, Boundries_status = checkBoundries(Servo_id, Angle)
    if (Boundries_status == 0x0004):
        print("Invalid Servo ID")
        return 0x0004
    current_angle, Real_Angle_status = checkRealAngle(Servo_id)
    if (Real_Angle_status == 0x0001):
        print("couldn't read the current position! Default angle was applied (0)")
        current_angle = 0
    if (current_angle > Angle):
        while (current_angle > Angle):
            sendPosition(Servo_id, current_angle)
            current_angle -= steps
            time.sleep(trans_time)
    elif (current_angle < Angle):
        while (current_angle < Angle):
            sendPosition(Servo_id, current_angle)
            current_angle += steps
            time.sleep(trans_time)
    if ((Angle - steps) <= current_angle <= (Angle + steps)):
        sendPosition(Servo_id, Angle)
    # Reading the current position to check the results
    time.sleep(0.001)  # This delay is so the position register updates
    real_angle, status = checkRealAngle(Servo_id)
    while (status == 0x0001):
        real_angle, status = checkRealAngle(Servo_id)
    if ((Angle - 1) <= real_angle <= (Angle + 1)):
        return 0x0000
    else:
        return 0x0003


# This function resets the head position to the default position 0 , 0 , 0
def resetHeadPosition():
    yaw_status = setPosition("Yaw", 0)
    pitch_status = setPosition("Pitch", 0)
    roll_status = setPosition("Roll", 0)
    if (yaw_status == 0x0000 and pitch_status == 0x0000 and roll_status == 0x0000):
        return 0x0000
    else:
        return 0x0003


def setHeadPosition(reqyawAngle=Default_Yaw_angle, reqpitchAngle=Default_Pitch_angle, reqrollAngle=Default_Roll_angle,
                    duration=Default_time, QA=False):
    duration = duration * (1 - (0.05 * checks))
    # Boundries check
    yawAngle, yaw_Boundries_status = checkBoundries(Yaw_servo_id, reqyawAngle)
    pitchAngle, pitch_Boundries_status = checkBoundries(Pitch_servo_id, reqpitchAngle)
    rollAngle, roll_Boundries_status = checkBoundries(Roll_servo_id, reqrollAngle)
    # current position check
    yaw_current_Angle, yaw_Angle_status = checkRealAngle(Yaw_servo_id)
    pitch_current_Angle, pitch_Angle_status = checkRealAngle(Pitch_servo_id)
    roll_current_Angle, roll_Angle_status = 0, 0  # checkRealAngle(Roll_servo_id)
    # calculating the distances
    yaw_distance = yawAngle - yaw_current_Angle
    pitch_distance = pitchAngle - pitch_current_Angle
    roll_distance = 1  # rollAngle - roll_current_Angle
    # checking communication errors
    if (yaw_Angle_status == 0x0001):
        print("Communication ERROR with yaw servo!!")
        yaw_distance = 1
    elif (pitch_Angle_status == 0x0001):
        print("Communication ERROR with pitch servo!!")
        pitch_distance = 1
    elif (roll_Angle_status == 0x0001):
        print("Communication ERROR with roll servo!!")
        roll_distance = 1
    Distances = np.array([yaw_distance, pitch_distance, roll_distance])
    # tempsteps = abs(min(yaw_distance, pitch_distance, roll_distance))
    tempsteps = abs(np.max(abs(Distances[np.nonzero(Distances)])))
    delay = duration / tempsteps
    yaw_steps = yaw_distance / tempsteps
    pitch_steps = pitch_distance / tempsteps
    roll_steps = 0
    # roll_steps = roll_distance / tempsteps
    if (abs(yaw_distance) <= 1 and abs(pitch_distance) <= 1 and abs(roll_distance) <= 1):
        print("already in place")
    else:
        count = 1
        test_name = 'HP_GT'
        test = Logger.log_utils(Logger.results_folder_path, test_name)
        test.append_log(['Time', 'GT_roll', 'GT_pitch', 'GT_yaw'])
        old_time = time.time()
        while (count <= tempsteps):
            sendPosition(Yaw_servo_id, yaw_current_Angle + (yaw_steps * count))
            sendPosition(Pitch_servo_id, pitch_current_Angle + (pitch_steps * count))
            # sendPosition(Roll_servo_id, roll_current_Angle + (roll_steps * count))
            time.sleep(delay)
            count += 1
            new_time = time.time()
            if (QA and (new_time - old_time) >= (1 / checks)):
                old_time = new_time
                yaw, pitch, roll, staus = getHeadPosition()
                log = [datetime.datetime.now().strftime("%Y%m%d_%H%M%S"), str(roll), str(pitch), str(yaw)]
                test.append_log(log)
        if (QA):
            test.writetofile()

    Yaw_real_angle, Yaw_status = checkRealAngle(Yaw_servo_id)

    while (Yaw_status == 0x0001):
        Yaw_real_angle, Yaw_status = checkRealAngle(Yaw_servo_id)

    if ((yawAngle - 1) <= Yaw_real_angle <= (yawAngle + 1)):
        pass
    else:
        return 0x0003
    Pitch_real_angle, Pitch_status = checkRealAngle(Pitch_servo_id)
    while (Pitch_status == 0x0001):
        Pitch_real_angle, Pitch_status = checkRealAngle(Pitch_servo_id)

    if ((pitchAngle - 1) <= Pitch_real_angle <= (pitchAngle + 1)):
        pass
    else:
        return 0x0003
    Roll_real_angle, Roll_status = checkRealAngle(Roll_servo_id)
    while (Roll_status == 0x0001):
        Roll_real_angle, Roll_status = checkRealAngle(Roll_servo_id)

    if ((rollAngle - 1) <= Roll_real_angle <= (rollAngle + 1)):
        return 0x0000
    else:
        return 0x0003
