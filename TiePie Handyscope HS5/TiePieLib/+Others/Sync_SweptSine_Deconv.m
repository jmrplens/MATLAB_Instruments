function [FR,f,IR,t,HHFR,fHH,HHIR,tHH] = Sync_SweptSine_Deconv(signal_rec,f1,f2,fs,T,phase0,N,show)
%
%
%   [1] Antonin Novak, Laurent Simon, Pierrick Lotton. Synchronized
%       Swept-Sine: Theory, Application, and Implementation. Journal of the
%       Audio Engineering Society, Audio Engineering Society, 2015, 63
%       (10), pp.786-798. 10.17743/jaes.2015.0071. hal-02504321
%
% Input:
%   signal_rec  Signal received
%   f1          Initial frequency (Hz)
%   f2          Final frequency (Hz)
%   fs          Sample rate (Hz)
%   T           (optional) Signal duration (s). Default: 1 second
%   phase0      (optional) Boolean to enable phase restriction (initial phase
%               equal to 0 when true). Default: true
%   N           Number of Harmonics to study. Default: 3
%   show        Boolean to plot results. Default: false
%
% Output:
%   FR          Frequency Response of deconvolution.
%   f           Frequency array for FR.
%   IR          Impulse response of deconvolution.
%   t           Time array for IR.
%   HHFR        Higher Harmonic frequency responses (one colum for each harmonic)
%   fHH         Frequency array for HHFR.
%   HHIR        Higher Harmonic impulse responses (one colum for each harmonic)
%   tHH         Time array for HHIR
%
% Jose Manuel Requena Plens (2021) [joreple@upv.es]


% Check inputs
arguments
    signal_rec  (1,:) double
    f1          (1,1) double {mustBePositive}
    f2          (1,1) double {mustBePositive}
    fs          (1,1) double {mustBePositive}
    T           (1,1) double {mustBePositive} = 1
    phase0      {mustBeScalarOrEmpty,mustBeMember(phase0,[0,1])} = true
    N           (1,1) {mustBeScalarOrEmpty,mustBeInteger,mustBePositive} = 3
    show        {mustBeScalarOrEmpty,mustBeMember(show,[0,1])} = false
end
close all
% Rate frequency increase
if phase0 == true
    L = (1/f1)*round((f1/log(f2/f1))*T); % Initial phase at 0
else
    L = T/log(f2/f1);
end

% Signal to column
y = signal_rec(:);

%% Nonlinear (de)convolution
% Nonlinear convolution in frequency domain:
Y = fft(y)./fs;   % FFT of the output signal
len = length(y);
% frequency axis
f_ax = linspace(0,fs,len+1).'; f_ax(end) = [];

% analytical expression of the spectra of the synchronized swept-sine
% [Novak et al. (2015)] "Synchronized swept-sine: Theory, application,
% and implementation. JAES 63(10), pp.786-798., Eq. (42)
X = 1/2*sqrt(L./f_ax).*exp(1i*2*pi*f_ax*L.*(1 - log(f_ax/f1)) - 1i*pi/4);

% Deconvolution
FR = Y./X; FR(1) = 0;  % avoid Inf at DC
n = length(FR);
if rem(n,2) == 0
    f = (-n/2:n/2-1)*(fs/n);
else
    f = (-(n-1)/2:(n-1)/2)*(fs/n);
end

IR = ifft(FR,'symmetric');     % impulse response
t = (0:length(IR)-1)/fs;

FR = fftshift(FR);

%% Separation of Higher Harmonic Impulse Responses (HHIRs)
% positions of higher harmonic IRs
dt = L.*log(1:N).*fs;

% rounded positions [samples]
dt_ = round(dt);
% non-integer difference
dt_rem = dt - dt_;

% circular periodisation of IR
len_IR = 2^14;
pre_IR = round(len_IR / 2);
h_pos = [IR; IR(1:len_IR)];

% frequency axis definition
axe_w = linspace(0,2*pi,len_IR+1).'; axe_w(end) = [];

% space localisation for IRs
HHIR = zeros(len_IR,N);

st0 = length(h_pos);
for n = 1:N
    % start position of n-th IR
    st = length(IR) - dt_(n) - pre_IR;
    % end position of n-th IR
    ed = min(st + len_IR, st0);

    % separation of IRs
    HHIR(1:ed-st,n) = h_pos(st+1:ed);

    % Non-integer sample delay correction
    Hx = fft(HHIR(:,n)) .* exp(-1i*dt_rem(n)*axe_w);
    HHIR(:,n) = ifft(Hx,'symmetric');

    % last sample poition for the next IR
    st0 = st - 1;
end
HHIR = HHIR(pre_IR:end,:);
tHH = (0:length(HHIR)-1)/fs;

%% Higher Harmonic Frequency Responses (HHFRs)
HHFR = fftshift(fft(HHIR));
n = length(HHFR);
if rem(n,2) == 0
    fHH = (-n/2:n/2-1)*(fs/n);
else
    fHH = (-(n-1)/2:(n-1)/2)*(fs/n);
end

%% Graphics
if show
    figure('Color',[1,1,1],'Name','Deconvolution',...
        'NumberTitle','off');

    tiledlayout(3,2,'TileSpacing','loose','Padding','compact')
    % Signal time domain
    ta = nexttile;
    plot(t,y)
    title('Signal [time domain]')
    xlim([0 max(t)])

    % Signal frequency domain
    fa = nexttile;
    plot(f,abs(fftshift(Y)))
    title('Signal [frequency domain]')

    % Impulse response time domain
    tb = nexttile;
    plot(t,IR)
    title('IR [time domain]')
    xlim([0 max(tHH)])

    % Impulse response frequency domain
    fb = nexttile;
    plot(f,abs((FR)))
    title('IR [frequency domain]')


    % Higher Harmonic time domain
    tc = nexttile;
    plot(tHH,HHIR)
    colororder(lines(N))
    xlabel('Time (s)')
    title('Higher Harmonic [time domain]')
    xlim([0 max(tHH)])

    % Higher Harmonic frequency domain
    fc = nexttile;
    plot(fHH,abs(HHFR))
    colororder(lines(N))
    xlabel('Frequency [Hz]')
    title('Higher Harmonic [frequency domain]')
    for i=1:N
        str(i) = string(sprintf('Harmonic N=%d',i));
    end
    legend(str,'Location','westoutside')
    linkaxes([fa fb fc],'x')
    linkaxes([tb tc],'x')
end