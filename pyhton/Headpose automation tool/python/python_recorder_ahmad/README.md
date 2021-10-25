python recorder program 

*** Version 1.2.1


What's new in the release : 
	Works with tx2bridge version 1.3.3

Known bugs and limitations : 
	1)Maximum fps 20


Additional Packages :
Tested with:
Numpy 1.17.2    
Opencv 3.4.2
Opencv-python 4.1.1.26
GuardianPythonCommon (commit ID 3002122c164a82ef86849eaba9a4efe8eefa94a7)

Dependencies:
tx2bridge version: 1.3.3
python client version: 1.4.2
cuda version : 7.5

How to run:
python3 recording_tool.py -pcm live -rfp /home/sw-linux-1/Desktop/Tools/python_recorder/data_folder 

-pcm is the python client mode-according to version 1.4.2

-rfp is the root folder path-according to version 1.4.2 without this flag the frame will not save

--help will show help screen

Sample test application which shows how to use the package: There are a default parameters, if you want to understand the valid parameters (flags that can be changed by command line) just type in the command line: python3 recording_tool.py --help

Controlable options:
	1) Number of frames to record - "--frame_number_to_record" option. Defualt value is 300 
	2) Modulation scheme - "--modulation" option. Defualt value is torches
	3) Webcam image height - "--web_cam_height" option. Default value is 480 
	4) Webcam image width - "--web_cam_width" option. Default value is 640 
	5) Frame rate - "--fps" option. Defualt value is 20
	6) Video captures sources - "--video_capture" option. Default value is gsm 
	7) GSM long exposure - "--long_exposure" option. Default value is 8000
	8) GSM exposure ratio - "--exposure_ratio" option. Defualt value is 8 
	9) Video device number of web cam - "--web_cam_number". Default value is 1 which is /dev/video1 . if the screen is black, please check the dev/video<number> number that the WEB camera is connected to.

Examples:

Live without recording:
	python3 recording_tool.py -pcm live 

Live with recording :
	python3 recording_tool.py -pcm live -rfp <path_to_directory> 
	such as: /home/sw-linux-1/Desktop/Tools/python_recorder/data_folder

##################################################################

python recorder program 

*** Version 1.2.0


What's new in the release : 
	1)New recording tool supporting gsm and/or web cam 
	2)New flags: -pcm,-rfp

Known bugs and limitations : 
	1)Maximum fps 20


Additional Packages :
Tested with:
Numpy 1.17.2    
Opencv 3.4.2
Opencv-python 4.1.1.26
GuardianPythonCommon (commit ID 3002122c164a82ef86849eaba9a4efe8eefa94a7)

Dependencies:
tx2bridge version: 1.2.0
python client version: 1.4.2
cuda version : 7.5

How to run:
python3 recording_tool.py -pcm live -rfp /home/sw-linux-1/Desktop/Tools/python_recorder/data_folder 

-pcm is the python client mode-according to version 1.4.2

-rfp is the root folder path-according to version 1.4.2 without this flag the frame will not save

--help will show help screen

Sample test application which shows how to use the package: There are a default parameters, if you want to understand the valid parameters (flags that can be changed by command line) just type in the command line: python3 recording_tool.py --help

Controlable options:
	1) Number of frames to record - "--frame_number_to_record" option. Defualt value is 300 
	2) Modulation scheme - "--modulation" option. Defualt value is torches
	3) Webcam image height - "--web_cam_height" option. Default value is 480 
	4) Webcam image width - "--web_cam_width" option. Default value is 640 
	5) Frame rate - "--fps" option. Defualt value is 20
	6) Video captures sources - "--video_capture" option. Default value is gsm 
	7) GSM long exposure - "--long_exposure" option. Default value is 8000
	8) GSM exposure ratio - "--exposure_ratio" option. Defualt value is 8 
	9) Video device number of web cam - "--web_cam_number". Default value is 1 which is /dev/video1 . if the screen is black, please check the dev/video<number> number that the WEB camera is connected to.

Examples:

Live without recording:
	python3 recording_tool.py -pcm live 

Live with recording :
	python3 recording_tool.py -pcm live -rfp <path_to_directory> 
	such as: /home/sw-linux-1/Desktop/Tools/python_recorder/data_folder

##################################################################
python recorder program 

*** Version 1.1.0


What's new in the release : 
	1)New recording tool supporting gsm and/or web cam

Known bugs and limitations : 
	1)Maximum fps 20


Additional Packages :
Tested with:
Numpy 1.17.2    
Opencv 3.4.2
Opencv-python 4.1.1.26

Dependencies:
tx2bridge version: 1.1.0
python client version: 1.4.1
cuda version : 7.5

How to run:
python3 recording_tool.py 

--help will show help screen

Sample test application which shows how to use the package: There are a default parameters, if you want to understand the valid parameters (flags that can be changed by command line) just type in the command line: python3 recording_tool.py --help

Controlable options:
	1) Number of frames to record - "--frame_number_to_record" option. Defualt value is 300 
	2) MOdulation scheme - "--modulation" option. Defualt value is torches
	3) Webcam image height - "--web_cam_height" option. Default value is 480 
	4) Webcam image width - "--web_cam_width" option. Default value is 640 
	5) Frame rate - "--fps" option. Defualt value is 20 
	6) Video captures sources - "--video_capture" option. Default value is both 
	7) GSM long exposure - "--long_exposure" option. Default value is 8000
	8) GSM exposure ratio - "--exposure_ratio" option. Defualt value is 8 
	9) Video device number of web cam - "--web_cam_number". Default value is 1 

	sample usage: python3 recording_tool.py --frame_number_to_record 50 --modulation interleaved --web_cam_height 480 --web_cam_width 640 --fps 20 --video_capture both --long_exposure 20000 --exposure_ratio 8 --web_cam_number 1
