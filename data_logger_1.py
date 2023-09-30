<<<<<<< HEAD
from machine import Pin, ADC,Timer
import os
from time import sleep
import utime
# from datetime import datetime
#-----------------------------------
eeg1 = ADC(Pin(34))
eeg2 = ADC(Pin(35))
eeg3 = ADC(Pin(32))
eeg4 = ADC(Pin(33))
eeg5 = ADC(Pin(25))
eeg6 = ADC(Pin(26))
emg7 = ADC(Pin(27))
#-----------------------------------
eeg1.atten(ADC.ATTN_11DB)       
eeg2.atten(ADC.ATTN_11DB)
eeg3.atten(ADC.ATTN_11DB)
eeg4.atten(ADC.ATTN_11DB)
eeg5.atten(ADC.ATTN_11DB)
eeg6.atten(ADC.ATTN_11DB)
emg7.atten(ADC.ATTN_11DB)
#-----------------------------------
def button_isr(button):
    global check_flag
    check_flag=1
    
#     button.irq.disable()
file_close_flag = 0
check_flag=0
button=Pin(13,Pin.IN,pull=Pin.PULL_UP)
button.irq(trigger=Pin.IRQ_FALLING,handler=button_isr)


#------------------------------------
def tim_isr(tim):
    print("\nData successfully collected from the subject.file would close\n \b")
    global file_close_flag
    file_close_flag=1
#     file.close()
    
tim = Timer(-1)
tim.init(period=120000, mode=Timer.ONE_SHOT, callback=tim_isr) 

#------------------------------------------------
# 
# def logger():
#     file.write("{0},{1},{2},{3},{4},{5},{6},{7}\n".format(eeg1.read(),eeg2.read(),eeg3.read(),eeg4.read(),eeg5.read(),eeg6.read(),emg7.read()))
#------------------------------------------------------------------------------------------- 
 
  

def main(i):
    while True:
        if check_flag!=0:
            print("press the button to start the data aquisition")
            break

        
#     cu_dt = datetime.now().strftime("%Y-%m-%d %H-%M-%S")
#     print("experiment started on : ", cu_dt)
#     str_cu_dt= str(cu_dt)
    current_time = utime.localtime()
    year, month, day, hour, minute, second, *_ = current_time
    file_name = "{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}.txt".format(year, month, day, hour, minute, second)
# 
#     filename=str_cu_dt+".txt"
    file= open(file_name,"w")
    while True:
        file.write("{0},{1},{2},{3},{4},{5},{6}\n".format(eeg1.read(),eeg2.read(),eeg3.read(),eeg4.read(),eeg5.read(),eeg6.read(),emg7.read()))
        sleep(0.004)
        if file_close_flag==1:
            file.close()
            

if __name__ == "__main__":
=======
from machine import Pin, ADC,Timer
import os
from time import sleep
import utime
# from datetime import datetime
#-----------------------------------
eeg1 = ADC(Pin(34))
eeg2 = ADC(Pin(35))
eeg3 = ADC(Pin(32))
eeg4 = ADC(Pin(33))
eeg5 = ADC(Pin(25))
eeg6 = ADC(Pin(26))
emg7 = ADC(Pin(27))
#-----------------------------------
eeg1.atten(ADC.ATTN_11DB)       
eeg2.atten(ADC.ATTN_11DB)
eeg3.atten(ADC.ATTN_11DB)
eeg4.atten(ADC.ATTN_11DB)
eeg5.atten(ADC.ATTN_11DB)
eeg6.atten(ADC.ATTN_11DB)
emg7.atten(ADC.ATTN_11DB)
#-----------------------------------
def button_isr(button):
    global check_flag
    check_flag=1
    
#     button.irq.disable()
file_close_flag = 0
check_flag=0
button=Pin(13,Pin.IN,pull=Pin.PULL_UP)
button.irq(trigger=Pin.IRQ_FALLING,handler=button_isr)


#------------------------------------
def tim_isr(tim):
    print("\nData successfully collected from the subject.file would close\n \b")
    global file_close_flag
    file_close_flag=1
#     file.close()
    
tim = Timer(-1)
tim.init(period=120000, mode=Timer.ONE_SHOT, callback=tim_isr) 

#------------------------------------------------
# 
# def logger():
#     file.write("{0},{1},{2},{3},{4},{5},{6},{7}\n".format(eeg1.read(),eeg2.read(),eeg3.read(),eeg4.read(),eeg5.read(),eeg6.read(),emg7.read()))
#------------------------------------------------------------------------------------------- 
 
  

def main(i):
    while True:
        if check_flag!=0:
            print("press the button to start the data aquisition")
            break

        
#     cu_dt = datetime.now().strftime("%Y-%m-%d %H-%M-%S")
#     print("experiment started on : ", cu_dt)
#     str_cu_dt= str(cu_dt)
    current_time = utime.localtime()
    year, month, day, hour, minute, second, *_ = current_time
    file_name = "{:04d}-{:02d}-{:02d}_{:02d}-{:02d}-{:02d}.txt".format(year, month, day, hour, minute, second)
# 
#     filename=str_cu_dt+".txt"
    file= open(file_name,"w")
    while True:
        file.write("{0},{1},{2},{3},{4},{5},{6}\n".format(eeg1.read(),eeg2.read(),eeg3.read(),eeg4.read(),eeg5.read(),eeg6.read(),emg7.read()))
        sleep(0.004)
        if file_close_flag==1:
            file.close()
            

if __name__ == "__main__":
>>>>>>> a73a13b226717f7103f548730cc403470029c9fc
    main(0)  