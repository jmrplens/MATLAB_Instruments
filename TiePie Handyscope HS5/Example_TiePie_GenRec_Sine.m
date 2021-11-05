% Test TiePie
clc, close all;

%% Parameters

% Signal parameters
fs = 1e6;  % Sample rate (Hz)
f = 80e3;  % Hz
% Amplitude
Amp = 8; % Volts pp
% Repetitions
Pulses = 50;

% Acquisition parameters
RecordLength    = ceil((1/f*Pulses+0.1e-3)*fs); % Samples
VRange          = [Amp,0.1*Amp]; % Volts
ProbeGain       = [1,3];
Channels        = [1,2];

%% Import Assets
addpath('TiePieLib')
% Get library
import LibTiePie.*
LIB = get_TiePie_Library();

%% Generation and reception
[signal,t,real_fs] = TiePie_GENandREC_Sine(LIB,f,fs,Channels,Amp,Pulses,RecordLength,VRange,ProbeGain);

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
