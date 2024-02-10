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

    musclestate = [0] * time200

    segments =[
    (0, time10, 0),        # rest state of 10s
    (time10, time30, 1),   # right hand slow motion for 20s
    (time30, time50, 2),   # right hand fast motion for 20s
    (time50, time110, 0),  # rest state of 20s
    (time110, time130, 3), # left hand slow motion for 20s
    (time130, time150, 4), # left hand fast motion for 20s
    (time150, time200, 5)  # left hand fast motion for 20s
    ]

    for start, end, state in segments:
       musclestate[start:end] = [state] * (end - start)

    file_to_open=path+"/musclestate_"+filename 
    file=open(file_to_open,"w")
   
    file.write(str(musclestate))
    print("file named {%s} is created with {%d} sampling frequency ",file_to_open,sampling_frequency)
    file.close()


def get_fft(filename,path):
    
    df_x=pd.read_csv(path+"/"+filename)
    
    s_F=get_sampling_freq(filename,path)
    
    
    