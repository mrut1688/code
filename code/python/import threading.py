import threading
import time
import RPi.GPIO as GPIO
import serial
from datetime import datetime


button_pin = 18  
GPIO.setmode(GPIO.BCM)
GPIO.setup(button_pin, GPIO.IN, pull_up_down=GPIO.PUD_UP)

closefile_flag=0
check_start_flag=0

 

ser = serial.Serial('/dev/ttyUSB0', 9600) 
def handle_file_operations():
    global check_start_flag
    check_start_flag=1

def timer_callback():
    global closefile_flag
    closefile_flag=1




GPIO.add_event_detect(button_pin, GPIO.FALLING, callback=handle_file_operations, bouncetime=300)

def main(i):
    
    while True:
        print("press the button to start the data aquisition")
        while True:
            if check_start_flag!=0:
                 print("pressed the button to start the data aquisition")
                 break
        
        timer_interval = 120.0 
        timer = threading.Timer(timer_interval, timer_callback)
       
       
        timestamp = datetime.now().strftime("%Y-%m-%d_%H-%M-%S")
        file_name = f"data_{timestamp}.txt"
        file= open(file_name, "w") 
        print("File created:", file_name)
        
        
        timer.start()
        
        
        try:
            while True:
                        # ser.readline().decode('utf-8').strip()
          
                      
                file.write(ser.readline().decode('utf-8').strip().split(',') + '\n')
                if closefile_flag!=0:
                    print('120 seconds of data recorded')
                    file.close()
        
        
        except KeyboardInterrupt:
            print("Keyboard interrupt. Closing the file.")
            
            
            if file_name:
                file.close()
                check_start_flag=0
                closefile_flag=0



if __name__ == "__main__":
    main(0)  
        