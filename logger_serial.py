import serial
import time
import threading
import datetime

while  True:
    try:
        ser = serial.Serial('COM7', 115200)
        break
    except  serial.serialutil.SerialException:
    
        print("connect to comport7")

print(str(ser.readline().decode('utf-8').strip().split(',')).replace("[","").replace("]","").replace("'","").replace(" ","") + '\n')

closefile_flag=0
def timer_callback():
    global closefile_flag
    closefile_flag=1
 
    
def logger_data():
    global closefile_flag
    global thread
    global ser
    
    timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    file_name = f"data_{timestamp}.txt"
    file= open("D:/matlab/ymaps_code/data"+file_name, "w") 
    print("File created:", file_name)
    
    closefile_flag=0
    
    thread=threading.Timer(120,timer_callback)
    thread.start()
    
    o=1
    
    while o==1:
#         print(".")
#         print(str(ser.readline().decode('utf-8').strip().split(',')) + '\n')
#         file.write(str(ser.readline().decode('utf-8').strip().split(',')) + '\n')
#         print(".")
        try:
             
             file.write(str(ser.readline().decode('utf-8').strip().split(',')).replace("[","").replace("]","").replace("'","").replace(" ","") + '\n')
             print(".")
        except KeyboardInterrupt:
             file.close()
             print(f"file{file_name} cloced \n")
        
            
        if(closefile_flag==1):
            file.close()
            print(f"file{file_name} cloced after 120s \n")
            
        print(".")

def main(i):
    while True:
        s=str(input("press s to start"))
        if(s=='s'):
            logger_data()
            s=' '
        
        
if __name__=="__main__":
    main(0)
    

