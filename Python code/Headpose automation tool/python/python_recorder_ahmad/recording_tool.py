import csv
import json
import sys
from GuardianPythonCommon.PythonClient import PythonClient
import GuardianPythonCommon
import guardianCExt
import os
import cv2
import datetime
import gc
import time
import config_file
import numpy as np
import csv
import socket
import time
from pathlib import Path
import Freddy
import Logger
import pandas as pd
import Report

VERSION_NUMBER = "1.2.1"
EXPOSURE_LIMIT_TIME = 28000 #28 millisecond
SYNC_BEGINING_FRAME=5
DELAY_FRAME_NUMBER = 2+SYNC_BEGINING_FRAME
MAX_FRAME_RATE = 20
#help to print the error color
CRED = '\033[91m'
CEND = '\033[0m'

def save_data_to_json(frame_number_to_record,web_cam_height,web_cam_width,system_fps,modulation,exposure_ratio,long_exposure,path_to_file):
        to_save = {
            "recorder_version": VERSION_NUMBER,
            "frame_number_to_record": frame_number_to_record,
            "fps": system_fps,
            "web camera":{
                "web_cam_height": web_cam_height,
                "web_cam_width": web_cam_width
            },
            "gsm":{
                "modulation": modulation,
                "exposure_ratio": exposure_ratio,
                "long_exposure": long_exposure
            }
        }
        # write the selected roi to json
        with open(path_to_file + '/data.json', 'w') as f:
            json.dump(to_save, f,indent=2)#indent 2 is new line between variables

    #data_file.close()



def check_modulation(modulation):
    valid=True
    # only torches
    if (modulation == "torches"):
        laserFramesOn = 0
        ledsFramesOn = 1
        lightsFramesOff = 0
    # only lasers
    elif (modulation == "lasers"):
        laserFramesOn = 1
        ledsFramesOn = 0
        lightsFramesOff = 0
    # only lasers
    elif (modulation == "interleaved"):
        laserFramesOn = 1
        ledsFramesOn = 1
        lightsFramesOff = 1
    else:
        print("There is problem with modulation value, the options are:\n\t torches \n\t lasers \n\t interleaved")
        valid=False
    return laserFramesOn,ledsFramesOn,lightsFramesOff,valid


def check_frame_number(frame_number_to_record):
    valid=True
    try:
        frame_number_to_record = (int)(frame_number_to_record)
        if(frame_number_to_record<0):
            print("There is problem with frame number, insert a positive number")
            valid=False
    except:
        print("There is problem with frame number, insert a positive number")
        valid = False
    return frame_number_to_record,valid


def check_web_cam_height(web_cam_height):
    valid = True
    try:
        web_cam_height = (int)(web_cam_height)
        if (web_cam_height < 0):
            print("There is problem with cam height , insert a positive number")
            valid = False
    except:
        print("There is problem with web cam height, insert a positive number")
        valid = False
    return web_cam_height, valid


def check_web_cam_width(web_cam_width):
    valid = True
    try:
        web_cam_width = (int)(web_cam_width)
        if (web_cam_width < 0):
            print("There is problem with cam width, insert a positive number")
            valid = False
    except:
        print("There is problem with web cam width, insert a positive number")
        valid = False
    return web_cam_width, valid


def check_fps(fps):
    valid = True
    try:
        fps = (int)(fps)
        if (fps < 1 or fps > MAX_FRAME_RATE):
            print("There is problem with fps, insert a positive number between 1-",MAX_FRAME_RATE)
            valid = False
    except:
        print("There is problem with fps, insert a positive number")
        valid = False
    return fps, valid


def check_video_capture(video_capture):
    valid=True
    if (video_capture == "both" or video_capture == "web" or video_capture == "gsm" ):
        return video_capture,valid
    else:
        print("There is problem with video capture value, the options are:\n\t both \n\t web \n\t gsm ")
        valid=False
        return video_capture,valid


def check_long_exposure_and_exposure_ratio(long_exposure, exposure_ratio):
    valid = True
    try:
        long_exposure = (int)(long_exposure)
        exposure_ratio = (int)(exposure_ratio)
        if (long_exposure < 0 or exposure_ratio < 0):
            print("There is problem with long exposure or exposure ratio , insert a positive number")
            valid = False
        elif(long_exposure+(long_exposure/exposure_ratio)>EXPOSURE_LIMIT_TIME):
            print("There is problem with ratio between long exposure and exposure ratio , insert a valid values")
            valid = False
    except:
        print("There is problem with long exposure or exposure ratio, insert a positive number")
        valid = False
    return long_exposure,exposure_ratio, valid


def check_web_cam_number(web_cam_number):
    valid = True
    try:
        web_cam_number = (int)(web_cam_number)
        if (web_cam_number < 0 ):
            print("There is problem with web_cam_number , insert a positive number")
            valid = False
    except:
        print("There is problem with web cam number, insert a positive number")
        valid = False
    return web_cam_number, valid


def parse_config_file_and_check_valid_values(config):
    frame_number_to_record,valid_frame_number=check_frame_number(config.frame_number_to_record)
    laserFramesOn,ledsFramesOn,lightsFramesOff,valid_modulation=check_modulation(config.modulation)
    web_cam_height, valid_web_cam_height=check_web_cam_height(config.web_cam_height)
    web_cam_width, valid_web_cam_width=check_web_cam_width(config.web_cam_width)
    system_fps, valid_fps=check_fps(config.fps)
    video_capture, valid_video_capture=check_video_capture(config.video_capture)
    long_exposure,exposure_ratio, valid_long_exposure_and_exposure_ratio=check_long_exposure_and_exposure_ratio(config.long_exposure,config.exposure_ratio)
    web_cam_number,valid_web_cam_number = check_web_cam_number(config.web_cam_number)
    valid= valid_frame_number and valid_modulation and valid_web_cam_height and valid_web_cam_width and valid_fps and valid_video_capture and valid_long_exposure_and_exposure_ratio and valid_web_cam_number
    return frame_number_to_record,laserFramesOn,ledsFramesOn,lightsFramesOff,web_cam_height,web_cam_width,system_fps,video_capture,long_exposure,exposure_ratio,web_cam_number,valid


def init_web_cam(web_cam_width,web_cam_height,fps,web_cam_number,path_to_file):
    ####Init Web Camera#####
    # Capture video from webcam
    web_cam_vid_capture = cv2.VideoCapture((int)(web_cam_number))
    web_cam_vid_cod = cv2.VideoWriter_fourcc(*'XVID')  # 640x480
    # web_cam_vid_cod = cv2.VideoWriter_fourcc(*'24BG') #raw
    web_cam_vid_capture.set(cv2.CAP_PROP_FRAME_WIDTH, web_cam_width)
    web_cam_vid_capture.set(cv2.CAP_PROP_FRAME_HEIGHT, web_cam_height)
    web_cam_vid_capture.set(cv2.CAP_PVAPI_PIXELFORMAT_RGB24, 30)
    web_cam_vid_capture.set(cv2.CAP_PROP_BUFFERSIZE, 1)
    if(path_to_file==""):
        return None,web_cam_vid_capture
    web_cam_output = cv2.VideoWriter(path_to_file + "/wc_video.avi", web_cam_vid_cod, fps,
                                     (web_cam_width, web_cam_height))  # 640, 480))
    return web_cam_output,web_cam_vid_capture


#First do grab and after we got the sensor frame we do  retrieve to improve the sync mechanism
def grab_frame_from_web_cam(web_cam_vid_capture):
    # Capture each frame of webcam video
    web_cam_vid_capture.grab()
    #web_cam_frame = web_cam_vid_capture.read()
    return web_cam_vid_capture

def config_parse_application(config):
    UDP_IP = config.computer_ip
    UDP_PORT = config.port
    Phone_type = "Phone Type: "+config.phone_type
    return UDP_IP,UDP_PORT,Phone_type

def connect_to_application(UDP_IP, UDP_PORT):
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind((UDP_IP, UDP_PORT))
    return sock


def get_information_from_app(sock,frame_num,csv_app):
    try:
        data, addr = sock.recvfrom(1024)  # buffer size is 1024 bytes
    except:
        print(CRED + "There is a problem with the connection to the application, please check: \n\t 1)IP and Port are correct \n\t 2)There is a network for your phone \n\t" + CRED)
        return
    print("received message:", data)
    #Parse the data from application
    x = str(data).split(",")
    time_stamp_from_phone=x[0][2:]
    computer_time_stamp=time.time()
    accX = x[2]
    accY = x[3]
    accZ = x[4]
    try:
        gyroscopeX = x[6]
        gyroscopeY = x[7]
        gyroscopeZ = x[8]
    except:
        csv_app.append([frame_num, accX, accY, accZ[:-1],"-","-","-","-","-","-",computer_time_stamp])
        return
    try:
        magneticX = x[10]
        magneticY = x[11]
        magneticZ = x[12]
    except:
        csv_app.append([frame_num, accX, accY, accZ, gyroscopeX, gyroscopeY, gyroscopeZ[:-1],"-","-","-",computer_time_stamp])
        return
    return csv_app.append([frame_num, accX, accY, accZ, gyroscopeX, gyroscopeY, gyroscopeZ, magneticX, magneticY, magneticZ[:-1],computer_time_stamp])


def write_web_cam_frame_to_file(web_cam_output, web_cam_frame,binary_file):
    web_cam_output.write(web_cam_frame[1]) #web_cam_frame[1] is the frame, web_cam_frame[0] is indicate if the frame arrived
    # insert raw frame to binary file
    binary_file.write(web_cam_frame[1].astype('uint8'))

def main():
    record_from_web_cam=False
    record_from_gsm=False
    csv_sensor=[["Frame Number","Time stamp"]]
    csv_web_cam=[["Frame Number","Time stamp"]]
    path_to_file=""
    lasersToSet = 0xf
    ledsToSet = 0xf

    try:
        print("Recorder version: ",VERSION_NUMBER)
        #Takes as default or getresults new values from command line
        args_parser=config_file.parse_args()
        config = PythonClient.parse_cmd_args(args_parser)

        #Version without accelerometer
        config.accelerometer =False

        if(config.accelerometer==True):
            #Connect to application
            UDP_IP, UDP_PORT, Phone_type = config_parse_application(config)
            sock = connect_to_application(UDP_IP, UDP_PORT)
            #sock.settimeout(5)  # Set time out time to stop try to connect to application
            csv_app = [['Frame Number', 'accX', 'accY', 'accZ', 'gyroscopeX', 'gyroscopeY', 'gyroscopeZ', 'magneticX', 'magneticY','magneticZ',"Computer Time Stamp", Phone_type]]
        frame_number_to_record,laserFramesOn,ledsFramesOn,lightsFramesOff,web_cam_height,web_cam_width,system_fps,video_capture,long_exposure,exposure_ratio,web_cam_number,valid=parse_config_file_and_check_valid_values(config)
        if(valid == False):
            return

        if not os.path.exists('data_folder'):
            os.makedirs('data_folder')

        path_to_file=config.results_folder_path

        #if PythonClient._is_live_mode:
        #    config.file_raw = file_path+"/video_" + time_video+".raw"

        if (video_capture == "both" or video_capture == "gsm"):
            record_from_gsm = True
        else:
            record_from_gsm = False

        print("Initializing the library (work mode:PYTHONC_ALGO_DEV_LIVE_WORK_MODE) ...")

        config.rec_delay_frames = DELAY_FRAME_NUMBER
        PythonClient.init(
            # disable_save=False,
            play_cyclic=True,
            disable_display=True,
            display_debug_verbose=True
            # parameters fpr avi saving will be used only of -oa command line parameter is used !
            # avi_fps=15,
            # avi_width=CV2_WINDOW_WIDTH,
            # avi_height=CV2_WINDOW_HEIGHT,
            # avi_rotate=True
        )
        PythonClient.start()

        if(record_from_gsm):
            if PythonClient._is_live_mode:
                # settings that we want to apply only in live mode !
                hdr_mode = GuardianPythonCommon.SENSOR_HDR_LINEARIZE
                long_exposure = 8000
                exposure_ratio = 8
                pwl_table = 1
                print("Setting HDR (Long Exposure:{0} [usec], Exposure Ratio:{1}, Mode:{2}, PWL Table:{3}) ...".format(
                    long_exposure, exposure_ratio, hdr_mode, pwl_table))
                guardianCExt.py_guarc_set_hdr(hdr_mode, long_exposure, exposure_ratio, pwl_table)


                print(
                    "Setting light modulation (lasersToSet:{0}, laserFramesOn:{1}, ledsToSet:{2}, ledsFramesOn:{3}, lightsFramesOff:{4}) ...".format(
                        lasersToSet, laserFramesOn, ledsToSet, ledsFramesOn, lightsFramesOff))
                guardianCExt.py_guarc_set_light_mod(lasersToSet, laserFramesOn, ledsToSet, ledsFramesOn,
                                                    lightsFramesOff)


            #display window
            cv2.namedWindow('frame', cv2.WINDOW_KEEPRATIO | cv2.WINDOW_NORMAL)
            cv2.resizeWindow('frame', 640, 480)
            cv2.moveWindow('frame', 1200, 200)

        time_begin = time.time()
        tick = 0
        frames_counter = 0
        fps = 0
        h,w = 1200, 640
        text_scale_thick = 5

        if (video_capture == "both" or video_capture=="web"):
            record_from_web_cam=True
            web_cam_output,web_cam_vid_capture=init_web_cam(web_cam_width,web_cam_height,system_fps,web_cam_number,path_to_file)
            if(path_to_file!=""):
                binary_file = open(path_to_file + "/web_cam_raw.bgr", "wb")
        else:
            record_from_web_cam=False

        (frame, dict_meta, lib_token) = guardianCExt.py_guarc_trigger_frame() #Takes one frame for the unsync frame mode

        frame_num=0
        if(record_from_web_cam):
            cv2.namedWindow('My cam video', cv2.WINDOW_KEEPRATIO | cv2.WINDOW_NORMAL)
            cv2.resizeWindow('My cam video', 640, 480)
            cv2.moveWindow('My cam video', 200, 200)

        if (path_to_file != ""):
            for j in range(SYNC_BEGINING_FRAME):
                if (record_from_gsm):
                     # to synchronize the beginning of the video
                    (frame, dict_meta, lib_token) = guardianCExt.py_guarc_trigger_frame()
                    guardianCExt.py_guarc_release_frame(lib_token)
        #start of Ahmad adjustments
        home = str(Path.home())
        test_plan_path = config.path_to_tesplan#home + '/Test_plan/test_plan.csv'
        results_folder_path = path_to_file  #home + '/Results'

        count = 0
        test_plan = pd.read_csv(test_plan_path)
        test_name = test_plan.Test_name[0]
        test = Logger.log_utils(results_folder_path, test_name)
        test.append_log(['Test_NO', 'Frame', 'GT_roll', 'GT_pitch', 'GT_yaw'])

        while True:
            try:
                i = frame_number_to_record
                test_no = test_plan.Test_NO
                roll = test_plan.roll[count]
                pitch = test_plan.pitch[count]
                yaw = test_plan.yaw[count]
                Freddy.setPosition("Roll", roll)
                Freddy.setPosition("Pitch", pitch)
                Freddy.setPosition("Yaw", yaw)
                yaw, pitch, roll, staus = Freddy.getHeadPosition()
                count += 1

                while(i>0 and PythonClient.continue_running()):
                    start_while_time=time.time()
                    #ahmad adj start
                    log = [test_no, frame_num, str(roll), str(pitch), str(yaw)]
                    test.append_log(log)
                    # ahmad adj end

                    if (record_from_web_cam):
                        web_cam_vid_capture= grab_frame_from_web_cam(web_cam_vid_capture)
                        csv_web_cam.append([frame_num, time.time()])
                    if (config.accelerometer == True):
                        get_information_from_app(sock,frame_num,csv_app)
                    if(record_from_gsm):
                        lib_token_next = guardianCExt.py_guarc_async_trigger_frame()
                    if (record_from_web_cam):
                        web_cam_frame = web_cam_vid_capture.retrieve()
                        cv2.imshow("My cam video", web_cam_frame[1])
                        cv2.waitKey(1)
                    if (record_from_gsm):
                        csv_sensor.append([frame_num, time.time()])
                        #(frame, dict_meta, lib_token) = guardianCExt.py_guarc_trigger_frame()

                        #lib_token = guardianCExt.py_guarc_async_trigger_frame()
                        #(frame, dict_meta, lib_token) = guardianCExt.py_guarc_complete_async_trigger_frame(lib_token)


                        """
                        print("frame index:{0}, frame seq:{1}, frame index in seq:{2}, seq length:{3}".format(
                            dict_meta[META_PROP_FRAME_INDEX],
                            dict_meta[META_PROP_SEQ_INDEX],
                            dict_meta[META_PROP_FRAME_INDEX_IN_SEQ],
                            dict_meta[META_PROP_SEQ_LEN]))
                        """
                        frame = cv2.rotate(frame, 0)

                        cv2.putText(frame, "Frame: {0} FPS: {1}".format(frame_num, fps),
                            (0, 1550),
                            cv2.FONT_HERSHEY_PLAIN,
                            text_scale_thick,
                            (128, 128, 128),
                            text_scale_thick)

                        #cv2.rotate(frame,frame,0)

                        cv2.imshow('frame',frame)
                        if (cv2.waitKey(1) & 0xFF) == ord('q'):
                            break

                        #input("Press Enter for the next frame...\n")
                        guardianCExt.py_guarc_release_frame(lib_token)

                        (frame, dict_meta, lib_token) = guardianCExt.py_guarc_complete_async_trigger_frame(lib_token_next)

                        frames_counter = frames_counter + 1
                        time_now = time.time() - time_begin
                        if (time_now - tick) >= 1:
                            tick = tick + 1
                            fps = frames_counter
                            frames_counter = 0
                    if(path_to_file!="" and record_from_web_cam):
                        write_web_cam_frame_to_file(web_cam_output,web_cam_frame,binary_file)
                    frame_num=frame_num+1
                    i=i-1
                    #Make sure the fps is correct
                    end_while_time=time.time()
                    total_loop_time=end_while_time-start_while_time
                    sleep_time=((1.0/system_fps)-total_loop_time)
                    #sleep_time = -1
                    if(sleep_time>0):
                        time.sleep(sleep_time)

            except:
                break
            test.writetofile()

    #input("Press Enter to exit...\n")
    except (guardianCExt.ClientCmdTimeoutException, guardianCExt.ClientConnectRefusedException,
            guardianCExt.ClientAPIVersionMismatchException, guardianCExt.ServerSensorException, guardianCExt.ClientInvalidParameterException,
            KeyboardInterrupt,
            Exception) as e:
        print(e)
    finally:
        if(path_to_file!=""):
            if(record_from_gsm):
                for i in range(DELAY_FRAME_NUMBER-1-SYNC_BEGINING_FRAME):#to synchronize the beginning of the video
                    (frame, dict_meta, lib_token) = guardianCExt.py_guarc_trigger_frame()
                    guardianCExt.py_guarc_release_frame(lib_token)
                    frame = cv2.rotate(frame, 0)
                    cv2.imshow('frame',frame)
                    if (cv2.waitKey(1) & 0xFF) == ord('q'):
                        break
                with open(path_to_file + '/sensor_status.csv', 'w') as sensor_csv:
                    writer = csv.writer(sensor_csv)
                    writer.writerows(csv_sensor)
                sensor_csv.close()
            save_data_to_json(frame_number_to_record,web_cam_height,web_cam_width,system_fps,config.modulation,exposure_ratio,long_exposure,path_to_file)
            if (record_from_web_cam and path_to_file!=""):
                # close the already opened camera
                web_cam_vid_capture.release()
                # close the already opened file
                web_cam_output.release()
                #binary_file.write(web_cam_frame.astype('uint8'))
                if(path_to_file!=""):
                    binary_file.close()
                    with open(path_to_file + '/web_cam_status.csv', 'w') as web_csv:
                        writer = csv.writer(web_csv)
                        writer.writerows(csv_web_cam)
                    web_csv.close()
            if (config.accelerometer == True):
                with open(path_to_file + '/app_status.csv', 'w') as csvFile:
                    writer = csv.writer(csvFile)
                    writer.writerows(csv_app)
                csvFile.close()
        # close the window and de-allocate any associated memory usage
        cv2.destroyAllWindows()

main()

