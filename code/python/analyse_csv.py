import pandas as pd 
import numpy as np 
import scipy as sc 
import matplotlib.pyplot as plt
import os 
from tkinter import *
from tkinter.filedialog import askdirectory,askopenfilename


sampling_freq_value=0
def ms_pdf(filename,path):
    exg_df=pandas_framemaker(filename,path)
    muscle_state_exdf(filename,path,exg_df)
    
def pandas_framemaker(filename,path):
    exg_Df=pd.read_csv(path+"/"+filename, header=None,on_bad_lines='skip')
    try:
        exg_Df.columns=['e1','e2','e3','T7','C3','C4','T8']
    except ValueError:
        exg_Df.columns=['T7','C3','C4','T8']
    else:
        exg_Df.columns=['e1','e2','e3','T7','C3','C4','T8']
    return exg_Df

def get_sampling_freq(filename,path):
    global sampling_freq_value
    df=pd.read_csv(path+"/"+filename,sep='delimiter', header=None)
    length=len(df)
    sampling_freq_value=float(length/120)
    return float(length/120)

def muscle_state_exdf(filename,path,exg_Df):
    
    sampling_frequency=float(len(exg_Df)/120)
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
    print(f"file  is created with  sampling frequency {sampling_frequency}")
    file.close()
    return musclestate


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
    print(f"file  is created with  sampling frequency {sampling_frequency}")
    file.close()

def get_fft(filename,path):
    
    nameofc=['e1','e2','e3','T7','C3','C4','T8']
    
    eeg_df=pd.read_csv(path+"/"+filename,header=None,on_bad_lines='skip')
    
    try:
        eeg_df.columns=['e1','e2','e3','T7','C3','C4','T8']
    except ValueError:
        eeg_df.columns=['T7','C3','C4','T8']
    else:
        eeg_df.columns=['e1','e2','e3','T7','C3','C4','T8']
    
    eeg1=eeg_df.loc[:,["T7"]]
    eeg2=eeg_df.loc[:,["C3"]]
    eeg3=eeg_df.loc[:,["C4"]]
    eeg4=eeg_df.loc[:,["T8"]]
    
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plotter_eeg(filename,path,eeg1,eeg2,eeg3,eeg4,T)
    
    E1=np.fft.fft(eeg1)
    E2=np.fft.fft(eeg2)
    E3=np.fft.fft(eeg3)
    E4=np.fft.fft(eeg4)
    
    N=np.arange(len(E1))
    T_f=len(E1)/s_f
    freq=N/T_f
    plotter_fft(filename,path,E1,E2,E3,E4,T_f,freq=freq,T=T,eeg1=eeg1,eeg2=eeg2,eeg3=eeg3,eeg4=eeg4)
    plotter_psd(filename,path,eeg1,eeg2,eeg3,eeg4,s_f,T)

def plotter_eeg(file_name,filepath,eeg1,eeg2,eeg3,eeg4,T):
    
    plt.style.use('dark_background')
    
    plt.Figure(edgecolor='red')
    plt.subplot(2,2,1)
    
   
    plt.plot(T,eeg1,'r',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG T7')
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.subplot(2,2,2)
    
    plt.plot(T,eeg2,'b',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG C3')
    plt.grid(linestyle = ':', linewidth = 0.5)
    
    plt.subplot(2,2,3)
    
    plt.plot(T,eeg3,'g',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG C4')
    plt.grid(linestyle = ':', linewidth = 0.5)
    
    plt.subplot(2,2,4)
    
    plt.plot(T,eeg4,'m',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG T8')
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.tight_layout()
    plt.savefig(filepath+'/'+'VvsT_'+file_name.replace('.csv','')+'.svg')    
    plt.show()
    
    
def plotter_fft(file_name,filepath,E1,E2,E3,E4,N,T,freq,eeg1,eeg2,eeg3,eeg4):
    plt.style.use('dark_background')
    plt.Figure(figsize= (10,8))

    plt.subplot(311)

    plt.plot(T,eeg1,'r',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG T7')
    plt.grid(linestyle = ':', linewidth = 0.5)

    plt.subplot(312)

    plt.plot(freq, np.abs(E1), 'g',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude |T7(freq)|')
    plt.xlim(0, 20)
    plt.grid(linestyle = ':', linewidth = 0.5)


    plt.subplot(313)

    plt.plot(freq,20*np.log10(np.abs(E1)), 'b',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT '+r'$20log_{10}$'+'|T7(freq)| '+r'$db$')
    plt.xlim(0, 20)
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.tight_layout()
    plt.savefig(filepath+'/'+'fftT7freq_'+file_name.replace('.csv','')+'.svg')
    
    plt.show()
    
    plt.subplot(311)

    plt.plot(T,eeg2,'r',linewidth=0.5)
    plt.ylabel('V')

    plt.xlabel('Time-s')
    plt.title('EEG C3')
    plt.grid(linestyle = ':', linewidth = 0.5)

    plt.subplot(312)

    plt.plot(freq, np.abs(E2), 'g',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude |C3(freq)|')
    plt.xlim(0, 20)
    
    plt.grid(linestyle = ':', linewidth = 0.5)
   


    plt.subplot(313)

    plt.plot(freq, 20*np.log10(np.abs(E2)), 'b',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT '+r'$20log_{10}$'+'|C3(freq)| '+r'$db$')
    plt.xlim(0, 20)
    plt.tight_layout()
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.savefig(filepath+'/'+'fftC3freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    

    plt.subplot(311)

    plt.plot(T,eeg3,'r',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG C4')
    plt.grid(linestyle = ':', linewidth = 0.5)

    plt.subplot(312)

    plt.plot(freq, np.abs(E3), 'g',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude |C4(freq)|')
    plt.xlim(0, 20)
    
    plt.grid(linestyle = ':', linewidth = 0.5)
    


    plt.subplot(313)

    plt.plot(freq,20*np.log10(np.abs(E3)), 'b',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT '+r'$20log_{10}$'+'|C4(freq)| '+r'$db$')
    plt.xlim(0, 20)
    plt.tight_layout()
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.savefig(filepath+'/'+'fftC4freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()

    
    plt.subplot(311)

    plt.plot(T,eeg4,'r',linewidth=0.5)
    plt.ylabel('V')
    plt.xlabel('Time-s')
    plt.title('EEG T8')
    plt.grid(linestyle = ':', linewidth = 0.5)

    plt.subplot(312)

    plt.plot(freq, np.abs(E4), 'g',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT Amplitude |T8(freq)|')
    plt.xlim(0, 20)
    plt.grid(linestyle = ':', linewidth = 0.5)


    plt.subplot(313)

    plt.plot(freq,20*np.log10(np.abs(E4)), 'b',linewidth=0.5)
    plt.xlabel('Freq (Hz)')
    plt.ylabel('FFT '+r'$20log_{10}$'+'|T8(freq)| '+r'$db$')
    plt.xlim(0, 20)
    plt.grid(linestyle = ':', linewidth = 0.5)
    plt.tight_layout()
    plt.savefig(filepath+'/'+'fftT8freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    


def plotter_psd(file_name,filepath,eeg1,eeg2,eeg3,eeg4,s_f,T):
    eeg1_=eeg1.to_numpy()
    eeg1_=eeg1_.reshape(len(eeg1),)
    eeg2_=eeg2.to_numpy().reshape(len(eeg1),)
    eeg3_=eeg3.to_numpy().reshape(len(eeg1),)
    eeg4_=eeg4.to_numpy().reshape(len(eeg1),)



    plt.style.use('dark_background')
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg1,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG T7')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg1_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T7')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdT7freq_'+file_name.replace('.csv','')+'.svg')

    plt.show()
  
    plt.style.use('dark_background')
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg2_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG C3')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg2_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C3')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdC3freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    
    plt.style.use('dark_background')
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg3_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG C4')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg3_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C4')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdC4freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    
    plt.style.use('dark_background')
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg4_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG T8')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg4_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T8')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdT8freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()

def figure_option_eeg(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg1=eeg_df.loc[:,["T7"]]
    eeg2=eeg_df.loc[:,["C3"]]
    eeg3=eeg_df.loc[:,["C4"]]
    eeg4=eeg_df.loc[:,["T8"]]
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plt.style.use('dark_background')
    fig,(ax1,ax2,ax3,ax4) =plt.subplots(nrows=2,ncols=2,sharex='col',sharey='row',layout='constrained')
    ax1.plot(T,eeg1,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    ax1.set_title('EEG T7')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    ax2.plot(T,eeg2,'green','--',linewidth=0.2)

    ax2.set_ylabel('signal in V')
    ax2.set_xlabel('Time in s')
    ax2.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax2.set_title('EEG C3')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    ax3.plot(T,eeg3,'blue','--',linewidth=0.2)

    ax3.set_ylabel('signal in V')
    ax3.set_xlabel('Time in s')
    ax3.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax3.set_title('EEG C3')
    ax3.grid(linewidth=0.5,linestyle=':',color='green')
    
    ax4.plot(T,eeg4,'white','--',linewidth=0.2)

    ax4.set_ylabel('signal in V')
    ax4.set_xlabel('Time in s')
    ax4.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax4.set_title('EEG C4')
    ax4.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'VvsT_'+file_name.replace('.csv','')+'.svg')    
    plt.show()
    
def figure_option_fft(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg1=eeg_df.loc[:,["T7"]]
    eeg2=eeg_df.loc[:,["C3"]]
    eeg3=eeg_df.loc[:,["C4"]]
    eeg4=eeg_df.loc[:,["T8"]]
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    N=np.arange(len(E1))
    T_f=len(E1)/s_f
    freq=N/T_f
    E1=np.fft.fft(eeg1)
    E2=np.fft.fft(eeg2)
    E3=np.fft.fft(eeg3)
    E4=np.fft.fft(eeg4)
    
    fig,(ax)=plt.subplots(nrows=3,ncols=4,layout='constrained')
    ax[0,0].plot(T,eeg1,'red','--',linewidth=0.2)
    ax[0,0].set_ylabel('signal in V')
    ax[0,0].set_xlabel('Time in s')
    ax[0,0].set_xlim(-0.1,120)
    ax[0.0].set_title('EEG T7')
    ax[0,0].grid(linewidth=0.5,linestyle=':',color='green')
    ax[0,1].plot(T,eeg2,'green','--',linewidth=0.2)

    ax[0,1].set_ylabel('signal in V')
    ax[0,1].set_xlabel('Time in s')
    ax[0,1].set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax[0,1].set_title('EEG C3')
    ax[0,1].grid(linewidth=0.5,linestyle=':',color='green')
    ax[0,2].plot(T,eeg3,'blue','--',linewidth=0.2)

    ax[0,2].set_ylabel('signal in V')
    ax[0,2].set_xlabel('Time in s')
    ax[0,2].set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax[0,2].set_title('EEG C3')
    ax[0,2].grid(linewidth=0.5,linestyle=':',color='green')
    
    ax[0,3].plot(T,eeg4,'white','--',linewidth=0.2)

    ax[0,3].set_ylabel('signal in V')
    ax[0,3].set_xlabel('Time in s')
    ax[0,3].set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax[0,3].set_title('EEG C4')
    ax[0,3].grid(linewidth=0.5,linestyle=':',color='green')
    
    
    ax[1,0].plot(freq, np.abs(E1), 'g',linewidth=0.5)
    ax[1,0].set_xlabel('Freq (Hz)')
    ax[1,0].set_ylabel('FFT Amplitude |T7(freq)|')
    ax[1,0].xlim(0, 20)
    ax[1,0].grid(linestyle = ':', linewidth = 0.5)
    
    ax[2,0].plot(freq,20*np.log10(np.abs(E1)), 'b',linewidth=0.5)
    ax[2,0].set_xlabel('Freq (Hz)')
    ax[2,0].set_ylabel('FFT '+r'$20log_{10}$'+'|T7(freq)| '+r'$db$')
    ax[2,0].xlim(0, 20)
    ax[2,0].grid(linestyle = ':', linewidth = 0.5)
    
    
    ax[1,1].plot(freq, np.abs(E2), 'g',linewidth=0.5)
    ax[1,1].set_xlabel('Freq (Hz)')
    ax[1,1].set_ylabel('FFT Amplitude |C3(freq)|')
    ax[1,1].xlim(0, 20)
    ax[1,1].grid(linestyle = ':', linewidth = 0.5)
    
    #ax[2,1].plot(freq,20*np.log10(np.abs(E2)), 'b',linewidth=0.5)
    ax[2,1].plot(freq,20*np.log10(np.abs(E1)), 'b',linewidth=0.5)
    ax[2,1].set_xlabel('Freq (Hz)')
    ax[2,1].set_ylabel('FFT '+r'$20log_{10}$'+'|C3(freq)| '+r'$db$')
    ax[2,1].xlim(0, 20)
    ax[2,1].grid(linestyle = ':', linewidth = 0.5)
    
   
   
    ax[1,2].plot(freq, np.abs(E3), 'g',linewidth=0.5)
    ax[1,2].set_xlabel('Freq (Hz)')
    ax[1,2].set_ylabel('FFT Amplitude |C4(freq)|')
    ax[1,2].xlim(0, 20)
    ax[1,2].grid(linestyle = ':', linewidth = 0.5)
    
    #x[2,2].plot(freq,20*np.log10(np.abs(E1)), 'b',linewidth=0.5)
    ax[2,2].plot(freq,20*np.log10(np.abs(E3)), 'b',linewidth=0.5)
    ax[2,2].set_xlabel('Freq (Hz)')
    ax[2,2].set_ylabel('FFT '+r'$20log_{10}$'+'|C4(freq)| '+r'$db$')
    ax[2,2].xlim(0, 20)
    ax[2,2].grid(linestyle = ':', linewidth = 0.5)
    
   
    ax[1,3].plot(freq, np.abs(E4), 'g',linewidth=0.5)
    ax[1,3].set_xlabel('Freq (Hz)')
    ax[1,3].set_ylabel('FFT Amplitude |T7(freq)|')
    ax[1,3].xlim(0, 20)
    ax[1,3].grid(linestyle = ':', linewidth = 0.5)
    
    ax[2,3].plot(freq,20*np.log10(np.abs(E4)), 'b',linewidth=0.5)
    #ax[2,3].plot(freq,20*np.log10(np.abs(E1)), 'b',linewidth=0.5)
    ax[2,3].set_xlabel('Freq (Hz)')
    ax[2,3].set_ylabel('FFT '+r'$20log_{10}$'+'|T8(freq)| '+r'$db$')
    ax[2,3].xlim(0, 20)
    ax[2,3].grid(linestyle = ':', linewidth = 0.5)
    plt.savefig(filepath+'/'+'fftfreq_'+file_name.replace('.csv','')+'.svg')
    plt.show()

def figure_option_psdT7(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg1=eeg_df.loc[:,["T7"]]
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plt.style.use('dark_background')
    eeg1_=eeg1.to_numpy().reshape(len(eeg1),)
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg1_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG T7')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg1_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T7')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdT7freq_'+file_name.replace('.csv','')+'.svg')

    plt.show()
      
def figure_option_psdC3(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg2=eeg_df.loc[:,["C3"]]
    s_f=len(eeg2)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plt.style.use('dark_background')
    eeg2_=eeg2.to_numpy().reshape(len(eeg2))
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg2_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG C3')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg2_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C3')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdC3freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    
    
def figure_option_psdC4(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg3=eeg_df.loc[:,["C4"]]
    s_f=len(eeg3)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plt.style.use('dark_background')
    eeg3_=eeg3.to_numpy().reshape(len(eeg3))
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg3_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG C4')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg3_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C4')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdC4freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()
    

def figure_option_psdT8(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    eeg4=eeg_df.loc[:,["T8"]]
    s_f=len(eeg4)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plt.style.use('dark_background')
    eeg4_=eeg4.to_numpy().reshape(len(eeg4))
    fig,(ax1,ax2) =plt.subplots(nrows=2,layout='constrained')


    ax1.plot(T,eeg4_,'red','--',linewidth=0.2)

    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax1.set_title('EEG T8')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    Pxx,fxx,t,im=ax2.specgram(eeg4_,NFFT=170,Fs=s_f,mode='psd',scale='dB',
                            noverlap=158,cmap='tab20b'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T8')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'psdT8freq_'+file_name.replace('.csv','')+'.svg')
    plt.show()

def eeg_muscle_plot(filename,path):
    eeg_df=pandas_framemaker(filename,path)
    ms=muscle_state_exdf(filename,path,eeg_df)
    eeg1=eeg_df.loc[:,["T7"]]
    eeg2=eeg_df.loc[:,["C3"]]
    eeg3=eeg_df.loc[:,["C4"]]
    eeg4=eeg_df.loc[:,["T8"]]
    
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    time10=int(s_f*10)
    time20=int(s_f*20)
    time30=time20+time10
    time50=time30+time20
    time110=time50+time20
    time130=time110+time20
    time150=time130+time20
    time200=time150+time10
    
    time=[0,10,20,30,50,70,90,110,120]
    time__=[time30,time50,time110,time130,time150,time200]
    colo=['cyan','#0957ff','red','#ff9b0a','#e2ff08','#ffffff']
    
   
    plt.style.use('dark_background')
    fig,(ax1,ax2,ax3,ax4) =plt.subplots(nrows=2,ncols=2,sharex='col',sharey='row',layout='constrained')
    #fig,(ax1)=plt.subplots(1,sharey=True,sharex=True,layout='constrained')
    ax1.plot(T,eeg1,'white','--',linewidth=0.3)
    ti_0=0
    ax1.axvspan(T[ti_0],T[time10] ,facecolor='red', alpha=0.3)
    ti_0=time10+1
    for ti,co in zip(time__,colo):
        ax1.axvspan(T[ti_0],T[ti-1] ,facecolor=co, alpha=0.3)
        ti_0=ti
    ax1.set_ylabel('signal in V')
    ax1.set_xlabel('Time in s')
    ax1.set_xlim(-0.1,120)
    ax1.set_title('EEG T7')
    ax1.grid(linewidth=0.5,linestyle=':',color='green')
    ax2.plot(T,eeg2,'White','--',linewidth=0.3)
    ti_0=0
    ax2.axvspan(T[ti_0],T[time10] ,facecolor='red', alpha=0.3)
    ti_0=time10+1
    for ti,co in zip(time__,colo):
        ax2.axvspan(T[ti_0],T[ti-1] ,facecolor=co, alpha=0.3)
        ti_0=ti
    ax2.set_ylabel('signal in V')
    ax2.set_xlabel('Time in s')
    ax2.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax2.set_title('EEG C3')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    ax3.plot(T,eeg3,'blue','--',linewidth=0.2)
    ti_0=0
    ax1.axvspan(T[ti_0],T[time10] ,facecolor='red', alpha=0.3)
    ti_0=time10+1
    for ti,co in zip(time__,colo):
        ax1.axvspan(T[ti_0],T[ti-1] ,facecolor=co, alpha=0.3)
        ti_0=ti
    ax3.set_ylabel('signal in V')
    ax3.set_xlabel('Time in s')
    ax3.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax3.set_title('EEG C3')
    ax3.grid(linewidth=0.5,linestyle=':',color='green')
    
    ax4.plot(T,eeg4,'white','--',linewidth=0.2)

    ax4.set_ylabel('signal in V')
    ax4.set_xlabel('Time in s')
    ax4.set_xlim(-0.1,120)
    #plt.xlabel('Time-s')

    ax4.set_title('EEG C4')
    ax4.grid(linewidth=0.5,linestyle=':',color='green')
    plt.savefig(filepath+'/'+'VvsT_ms'+file_name.replace('.csv','')+'.svg')    
    plt.show()



def main(i):
    
    path_=askdirectory()
    filen=askopenfilename().split('/').pop()
    get_sampling_freq(filen,path_)
    get_fft(filen,path_)
    return filen,path_
    
if __name__=="__main__":
    main(0)        
