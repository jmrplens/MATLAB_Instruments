function [x,t] = Sync_SweptSine(f1,f2,fs,T,phase0,fadeInT,fadeOutT)
% Generation of Synchronized Swept Sine.
%
% [x,t] = SweptSine(f1,f2,fs,T,phase0,fadeInT,fadeOutT)
%
% Examples:  
%   Swept sine signal form 30Khz to 50Khz with 1 second duration and 1MHz 
%   sample and initial phase to be zero:
%               [x,t] = SweptSine(30e3,50e3,1e6)
%
%   Same signal but with a duration of 0.5 seconds:
%               [x,t] = SweptSine(30e3,50e3,1e6,0.5)
%
%   Swept sine signal form 30Khz to 50Khz with 1 second duration and 1MHz
%   sample without phase restriction:
%               [x,t] = SweptSine(30e3,50e3,1e6,0.5,false)
%
%   Swept sine signal form 30Khz to 50Khz with 1 second duration and 1MHz
%   sample without phase restriction and with 0.1 seconds fade in:
%               [x,t] = SweptSine(30e3,50e3,1e6,0.5,false,0.1)
%
%   Swept sine signal form 30Khz to 50Khz with 1 second duration and 1MHz
%   sample without phase restriction and with 0.1 seconds fade in and fade out:
%               [x,t] = SweptSine(30e3,50e3,1e6,0.5,false,0.1,0.1)
%
%   [1] Antonin Novak, Laurent Simon, Pierrick Lotton. Synchronized
%       Swept-Sine: Theory, Application, and Implementation. Journal of the
%       Audio Engineering Society, Audio Engineering Society, 2015, 63
%       (10), pp.786-798. 10.17743/jaes.2015.0071. hal-02504321
%
% Input:
%   f1          Initial frequency (Hz)
%   f2          Final frequency (Hz)
%   fs          Sample rate (Hz)
%   T           (optional) Signal duration (s). Default: 1 second
%   phase0      (optional) Boolean to enable phase restriction (initial phase 
%               equal to 0 when true). Default: true 
%   fadeInT     (optional) Fade in time in seconds. Default: Empty
%   fadeOutT    (optional) Fade in time in seconds. Default: Empty
%
% Output:
%   x   Signal array
%   t   Time array (s)
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]

% Check inputs
arguments
    f1          (1,1) double {mustBePositive}
    f2          (1,1) double {mustBePositive}
    fs          (1,1) double {mustBePositive}
    T           (1,1) double {mustBePositive} = 1
    phase0      {mustBeScalarOrEmpty,mustBeMember(phase0,[0,1])} = true
    fadeInT     double {mustBePositive,mustBeScalarOrEmpty} = []
    fadeOutT    double {mustBePositive,mustBeScalarOrEmpty} = []
end

% Rate frequency increase
if phase0 == true
    L = (1/f1)*round((f1/log(f2/f1))*T); % Initial phase at 0
else
    L = T/log(f2/f1);
end

% Time array
t = (0:1/fs:T-1/fs);

% Swept Sine signal
x = sin(2*pi*f1*L*(exp(t/L))).';

% Fade−in the input signal
if ~isempty(fadeInT)
    fadeInSam = round(fs * fadeInT); % number of samlpes
    fade_in = (1-cos((0:fadeInSam-1)/fadeInSam*pi))/2;
    index = 1:fadeInSam;
    x(index) = x(index).*fade_in.';
end

% Fade−out the input signal
if ~isempty(fadeOutT)
    fadeOutSam = round(fs * fadeOutT); % number of samlpes
    fade_out = (1-cos((0:fadeOutSam-1)/fadeOutSam*pi))/2;
    index = (1:fadeOutSam)-1;
    x(end-index) = x(end-index).*fade_out.';
end

% To column
t = t(:);