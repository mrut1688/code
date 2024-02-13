import logger_serial as lg 
import analyse_csv as acsv
import mapy_gui as m
import serial as ser
def live_log():
    global ser
    return (str(ser.readline().decode('utf-8').strip().split(','))
            .replace("[","").replace("]","").replace("'","")
            .replace(" ","") + '\n')

def mapy_model(*Earg,**Karg):
    for earg in Earg :
        return earg


def logging_data_csv():
    filename,path=lg.main()
    return filename,path

def mne_analyse(*Earg,**Karg):
    for earg in Earg :
        return earg
def load_model(file_path,path):
    return file_path,path

def main(i):
    return 0


if __name__=="__main__":
    main(0)