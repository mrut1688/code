function [pdata,fdata,tdata] = data_pspm(dat,fs)
        [pdata,fdata,tdata]=pspectrum(dat,fs,'spectrogram','MinThreshold',-10,'TimeResolution',1,'overlapPercent',99,FrequencyLimits=[0,30]);
end