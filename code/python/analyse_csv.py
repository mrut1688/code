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
    
    eeg_df=pd.read_csv(path+"/"+filename)
    
    eeg_df.columns=['e1','e2','e3','t7','c3','c4','t8']
    eeg1=eeg_df.loc[:,["t7"]]
    eeg2=eeg_df.loc[:,["c3"]]
    eeg3=eeg_df.loc[:,["c4"]]
    eeg4=eeg_df.loc[:,["t8"]]
    
    s_f=len(eeg1)/120
    t_f=1/s_f
    T=np.arange(0,120,t_f)
    plotter_eeg(eeg1,eeg2,eeg3,eeg4,T)
    
    E1=np.fft.fft(eeg1)
    E2=np.fft.fft(eeg2)
    E3=np.fft.fft(eeg3)
    E4=np.fft.fft(eeg4)

    N=np.arange(len(E1))
    T_f=len(E1)/s_f
    freq=N/T_f
    plotter_fft(E1,E2,E3,E4,T_f,freq)
    

def plotter_eeg(eeg1,eeg2,eeg3,eeg4,T):
    
    plt.style.use('dark_background')
    
    plt.Figure(figsize= (10,8))
    plt.subplot(2,2,1)
    
    plt.Figure(filename='EEG T7')
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
    plt.show()
    
def plotter_fft(E1,E2,E3,E4,N,T_f,freq):
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
    plt.show()



def plotter_psd(eeg1,eeg2,eeg3,eeg4,s_f):
    eeg1_=eeg1.to_numpy()
    eeg1_=eeg1_.reshape(21345,)
    eeg2_=eeg2.to_numpy().reshape(21345,)
    eeg3_=eeg3.to_numpy().reshape(21345,)
    eeg4_=eeg4.to_numpy().reshape(21345,)



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
                            noverlap=158,cmap='jet'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T7')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
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
                            noverlap=158,cmap='jet'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C3')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
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
                            noverlap=158,cmap='jet'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of C4')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
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
                            noverlap=158,cmap='jet'
                            ,vmin=-50)
    ax2.set_ylim(4,20)
    ax2.set_xlim(-0.10,120)
    fig.colorbar(im,shrink=0.6).set_label('power in '+r'$dB$')
    ax2.set_ylabel('Frequency')
    ax2.set_xlabel('Time in s')
    ax2.set_title('PSD of T8')
    ax2.grid(linewidth=0.5,linestyle=':',color='green')
    plt.show()




