% Test TiePie
clc, close all;

%% Parameters

% Signal parameters
fs = 1e6;   % Sample rate (Hz)
f1 = 37e3;  % Hz
f2 = 43e3;  % Hz
T  = 0.02;  % s
% Amplitude
Amp = 2; % Volts pp
% Repetitions
Pulses = 1;

% Acquisition parameters
RecordLength    = ceil((T+5e-3)*fs); % Samples
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
[data,~] = SweptSine(f1,f2,fs,T);

%% Generation and reception
[signal,t,real_fs] = TiePie_GENandREC_Arbitrary(LIB,data,fs,Channels,Amp,Pulses,RecordLength,VRange,ProbeGain);

% Data
dataCH1 = signal(:,1);
dataCH2 = signal(:,2);

% Plot
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