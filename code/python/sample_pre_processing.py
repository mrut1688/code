# %%


# %%
import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import scipy as sc 





# %%
eeg_df=pd.read_csv(r"D:\matlab\ymaps_code\data\20240209\data_20240209164956.csv")


# %%
emg_df=pd.read_csv(r"D:\matlab\ymaps_code\data\muscle_state.csv")

# %%
emg_df.head()

# %%


# %%
eeg_df.columns=['e1','e2','e3','t7','c3','c4','t8']

# %%
eeg1=eeg_df.loc[:,["t7"]]
eeg2=eeg_df.loc[:,["c3"]]
eeg3=eeg_df.loc[:,["c4"]]
eeg4=eeg_df.loc[:,["t8"]]


# %%
s_f=len(eeg1)/120
t_f=1/s_f
T=np.arange(0,120,t_f)

# %%
len(T)

plt.style.use('dark_background')

# %%
fig1=plt.Figure(figsize= (10,8))
plt.plot(T,eeg1,'r',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG T7')
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()

# %%
fig2=plt.Figure(figsize= (10,8))
plt.plot(T,eeg2,'b',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG C3')
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()

# %%

fig3=plt.Figure(figsize= (10,8))
plt.plot(T,eeg3,'g',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG C4')
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()

# %%
fig4=plt.Figure(figsize= (10,8))
plt.plot(T,eeg4,'m',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG T8')
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()

# %%
E1=np.fft.fft(eeg1)
E2=np.fft.fft(eeg2)
E3=np.fft.fft(eeg3)
E4=np.fft.fft(eeg4)



# %%
N=np.arange(len(E1))
T_f=len(E1)/s_f
freq=N/T_f

# %%

fig5=plt.Figure(facecolor='#94F008')
plt.subplot(211)

plt.plot(T,eeg1,'r',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG T7')
plt.grid(linestyle = ':', linewidth = 0.5)

plt.subplot(212)

plt.plot(freq, np.abs(E1), '',linewidth=0.5)
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



# %%
plt.Figure(facecolor='#94F008')
plt.subplot(211)

plt.plot(T,eeg2,'g',linewidth=0.5)
plt.ylabel('V')

plt.xlabel('Time-s')
plt.title('EEG C3')
plt.grid(linestyle = ':', linewidth = 0.5)

plt.subplot(212)

plt.plot(freq, np.abs(E2), '',linewidth=0.5)
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT Amplitude |C3(freq)|')
plt.xlim(0, 20)
#plt.tight_layout()
plt.grid(linestyle = ':', linewidth = 0.5)
#plt.show()


plt.subplot(313)

plt.plot(freq, 20*np.log10(np.abs(E2)), 'b',linewidth=0.5)
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT '+r'$20log_{10}$'+'|C3(freq)| '+r'$db$')
plt.xlim(0, 20)
plt.tight_layout()
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()


# %%
plt.Figure(facecolor='#94F008')
plt.subplot(211)

plt.plot(T,eeg3,'r',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG C4')
plt.grid(linestyle = ':', linewidth = 0.5)

plt.subplot(212)

plt.plot(freq, np.abs(E3), '',linewidth=0.5)
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT Amplitude |C4(freq)|')
plt.xlim(0, 20)
#plt.tight_layout()
plt.grid(linestyle = ':', linewidth = 0.5)
#plt.show()


plt.subplot(313)

plt.plot(freq,20*np.log10(np.abs(E3)), 'b',linewidth=0.5)
plt.xlabel('Freq (Hz)')
plt.ylabel('FFT '+r'$20log_{10}$'+'|C4(freq)| '+r'$db$')
plt.xlim(0, 20)
plt.tight_layout()
plt.grid(linestyle = ':', linewidth = 0.5)
plt.show()


# %%
plt.Figure(facecolor='#94F008')
plt.subplot(211)

plt.plot(T,eeg4,'m',linewidth=0.5)
plt.ylabel('V')
plt.xlabel('Time-s')
plt.title('EEG T8')
plt.grid(linestyle = ':', linewidth = 0.5)

plt.subplot(212)

plt.plot(freq, np.abs(E3), 'y',linewidth=0.5)
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





