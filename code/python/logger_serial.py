import serial
import time
import threading
import datetime
import os
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
 
def logger_data_img():
    global closefile_flag
    global thread
    global ser
    
    datestamp = datetime.datetime.now().strftime("%Y%m%d")
    timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    file_name = f"data_{timestamp}.csv"
    par_dir="D:/matlab/ymaps_code/data/"
    path= os.path.join(par_dir+datestamp)
    
    if not os.path.exists(path): 
        os.mkdir(path)
        
    file= open(path+"/"+"img_"+file_name, "w") 
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
             break
            
        if(closefile_flag==1):
            file.close()
            print(f"file{file_name} cloced after 120s \n")
            break 
        print(thread)

 
def logger_data():
    global closefile_flag
    global thread
    global ser
    
    datestamp = datetime.datetime.now().strftime("%Y%m%d")
    timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
    file_name = f"data_{timestamp}.csv"
    par_dir="D:/matlab/ymaps_code/data/"
    path= os.path.join(par_dir+datestamp)
    
    if not os.path.exists(path): 
        os.mkdir(path)
        
    file= open(path+"/"+file_name, "w") 
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
             break
            
        if(closefile_flag==1):
            file.close()
            print(f"file{file_name} cloced after 120s \n")
            break 
        print(thread)

def main(i):
    while True:
        s=str(input("press s for actual data or press i  for imaginaty data "))
        if(s=='s'):
            logger_data()
            s=''
        if(s=='i'):
            logger_data_img()
            s=''
        
        
if __name__=="__main__":
    main(0)
    

