import argparse


def parse_args():
    parser = argparse.ArgumentParser(description='Recorder main code')
    # data and files
    parser.add_argument('--frame_number_to_record', default=300, help='Frame number to record, insert a positive number')
    parser.add_argument('--modulation',default="torches", help='modulation mode: interleaved,torches or lasers')
    parser.add_argument('--web_cam_height', default=480, help='height of web cam resolution,insert a positive number')
    parser.add_argument('--web_cam_width', default=640, help='width of web cam resolution,insert a positive number')
    parser.add_argument('--fps', default=20, help='fps,insert a positive number between 1 to 20')
    parser.add_argument('--video_capture', default="gsm", help='Video capture mode: web,gsm or both')
    parser.add_argument('--long_exposure',default=8000,help='Long exposure,insert a positive number between 1 to 20000')
    parser.add_argument('--exposure_ratio',default=8,help='Exposure ratio,insert a positive number')
    parser.add_argument('--web_cam_number',default=1,help='Select the USB camera number 0,1 or 2')
    parser.add_argument('--path_to_tesplan', default="", help='Path of the test plan')

    #acl version
    # parser.add_argument('--computer_ip', default="192.168.2.28", help='IP of the computer')
    # parser.add_argument('--port', default=5695, help='Port to send the messages')
    # parser.add_argument('--phone_type', default="Galaxy S8", help='Phone type')
    # parser.add_argument('-acl', '--accelerometer', action='store_true', help='Decide whether to connect to application')

    return parser

