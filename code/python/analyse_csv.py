import pandas as pd 
import numpy as np 
import scipy as sc 
import matplotlib.pyplot as plt
import os 

sampling_freq_value=0
def get_sampling_freq(filename,path):
    global sampling_freq_value
    df=pd.read_csv(path+"/"+filename)
    length=len(df)
    sampling_freq_value=float(length/120)
    return float(length/120)

def muscle_state(filename,path):
   global sampling_freq_value
   sampling_frequency=sampling_freq_value
   time10=int(sampling_frequency*10)
   time20=int(sampling_frequency*20)
   time30=time20+time10
   time50=time30+time20
   time110=time50+time20
   time130=time110+time20
   time150=time130+time20
   time200=time150+time10
#    musclestate=[]
   
#    for i in range (0,time10):#for reststate of 10s
#       musclestate[i]=0
      
#    for i in range (time10,time30):#righthand_slow_motion for 20s
#       musclestate[i]=1
    
#    for i in range (time30,time50):#right_hand_fast_motion for 20s
#       musclestate[i]=2
   
#    for i in range (time50,time110):#for reststate of 20s
#       musclestate[i]=0
      
#    for i in range (time110,time130):#left_hand_slow_motion  for 20s
#       musclestate[i]=3    

#    for i in range (time130,time150):#left_hand_fast_motion  for 20s
#       musclestate[i]=4   

#    for i in range (time150,time200):#left_hand_fast_motion  for 20s
#       musclestate[i]=5   

   musclestate = [0] * time200

# Define segments with their corresponding muscle states
   segments = [
    (0, time10, 0),        # rest state of 10s
    (time10, time30, 1),   # right hand slow motion for 20s
    (time30, time50, 2),   # right hand fast motion for 20s
    (time50, time110, 0),  # rest state of 20s
    (time110, time130, 3), # left hand slow motion for 20s
    (time130, time150, 4), # left hand fast motion for 20s
    (time150, time200, 5)  # left hand fast motion for 20s
]

# Set muscle states based on defined segments
   for start, end, state in segments:
       musclestate[start:end] = [state] * (end - start)

   file_to_open=path+"/musclestate_"+filename 
   file=open(file_to_open,"w")
   
   file.write(str(musclestate))
   print("file named {%s} is created with {%d} sampling frequency ",file_to_open,sampling_frequency)
   file.close()

   