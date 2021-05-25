# RoboticGuideDogSpeech

## Prerequisites:
- ROS Kinetic
- Latest version of DeepSpeech

To run this program, put mic_vad_streaming into the home directory, and src into a folder named catkin_ws. 

`catkin_make` catkin_ws, and run an instance of roscore before running the following commands in two different terminals:

Terminal 1:  
`source ./devel/setup.bash`  
`python3.7 ~/mic_vad_streaming/mic_vad_streaming.py -m ~/deepspeech-0.9.3-models.pbmm --nospinner -s ~/deepspeech-0.9.3-models.scorer | rosrun beginner_tutorials talker.py`

Terminal 2:  
`source ./devel/setup.bash`  
`rosrun beginner_tutorials listener`
