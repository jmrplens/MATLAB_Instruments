% Test TiePie
clc, close all;

%% Parameters

% Signal parameters
fs = 1e6;   % Sample rate (Hz)
f1 = 30e3;  % Hz
f2 = 50e3;  % Hz
T  = 0.1;  % s
phase0 = false;
% Amplitude
Amp = 8; % Volts pp
% Repetitions
Pulses = 1;

% Acquisition parameters
RecordLength    = ceil((T*Pulses+20e-3)*fs); % Samples
VRange          = [Amp,0.1*Amp]; % Volts
ProbeGain       = [1,3];
Channels        = [1,2];

%% Import Assets
addpath('TiePieLib')
% Get library
import LibTiePie.*
LIB = get_TiePie_Library();

%% Signal generation
import Others.*
[data,~] = Sync_SweptSine(f1,f2,fs,T,phase0);

%% Generation and reception
[signal,t,real_fs] = TiePie_GENandREC_Arbitrary(LIB,data,fs,Channels,Amp,Pulses,RecordLength,VRange,ProbeGain);

% Data
dataCH1 = signal(:,1);
dataCH2 = signal(:,2);

% Plot
figure('Color',[1,1,1])
yyaxis left
plot(t,dataCH1);
ylim([-VRange(1),VRange(1)])
xlabel('Time [s]');
ylabel('Amplitude channel 1 [V]');
yyaxis right
plot(t,dataCH2);
ylim([-VRange(2),VRange(2)])
legend('Channel 1','Channel 2')
xlabel('Time [s]');
ylabel('Amplitude channel 2 [V]');

%% Deconv
Sync_SweptSine_Deconv(dataCH1,f1,f2,fs,T,phase0,3,1);

Sync_SweptSine_Deconv(dataCH2,f1,f2,fs,T,phase0,3,1);