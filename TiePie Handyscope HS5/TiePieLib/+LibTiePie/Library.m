% MatlabLibTiePie - Matlab bindings for LibTiePie library
%
% Copyright (c) 2012-2021 TiePie engineering
%
% Website: http://www.tiepie.com/LibTiePie

classdef Library < handle
    properties (SetAccess = private)
        Name = 'libtiepie';
        DeviceList;
        Network;
    end
    properties (SetAccess = private)
        IsInitialized;
        Version;
        VersionString;
        VersionExtra;
        Config;
        LastStatus;
        LastStatusStr;
    end
    methods
        function obj = Library(name)
            if nargin > 0
                obj.Name = name;
            end
            mfile_name          = mfilename('fullpath');
            [pathstr,name,ext]  = fileparts(mfile_name);
            addpath([pathstr,filesep,'LibTiePieHeaders'])
            % Load library if that is not already done:
            if ~libisloaded(obj.Name)
                if isunix()
                    addpath('/usr/include'); % On Unix systems the LibTiePie headers are here.
                end
                [notfound, warnings] = loadlibrary(obj.Name, 'libtiepiematlab.h', 'addheader', 'libtiepie');
                pause(0.2);
                if libisloaded(obj.Name)
                    versionMin = hex2dec(['0000' '0009' '0000' '0000']);
                    versionMax = hex2dec(['0000' 'FFFF' 'FFFF' 'FFFF']);
                    % Version check:
                    if obj.Version < versionMin
                        warning(sprintf('To fully function, this version of MatlabLibTiePie needs LibTiePie %s or higher, but version %s was detected.', LibTiePie.VersionNumber2String(versionMin), LibTiePie.VersionNumber2String(obj.Version)));
                    elseif obj.Version > versionMax
                        warning(sprintf('This version of MatlabLibTiePie is designed to work with LibTiePie up to version %s, but version %s was detected. Not everything may work correctly.', LibTiePie.VersionNumber2String(versionMax), LibTiePie.VersionNumber2String(obj.Version)));
                    end
                  else
                    error(['Could not load library ', obj.Name])
                end
            end

            calllib(obj.Name, 'LibInit');

            obj.DeviceList = LibTiePie.DeviceList(obj);
            obj.Network = LibTiePie.Network(obj);
        end

        function delete(self)
            calllib(self.Name, 'LibExit');
            if ~self.IsInitialized
                unloadlibrary(self.Name);
            end
        end

        function checkLastStatus(self)
            status = self.LastStatus;
            if status < 0
                error(self.LastStatusStr);
            elseif status > 0
                %warning(self.LastStatusStr);
            end
        end
    end
    methods
        function value = get.IsInitialized(self)
            value = calllib(self.Name, 'LibIsInitialized');
        end

        function value = get.Version(self)
            value = calllib(self.Name, 'LibGetVersion');
        end

        function value = get.VersionString(self)
            value = LibTiePie.VersionNumber2String(self.Version);
        end

        function value = get.VersionExtra(self)
            value = calllib(self.Name, 'LibGetVersionExtra');
        end

        function value = get.Config(self)
            length = calllib(self.Name, 'LibGetConfig', [], 0);
            [~, value] = calllib(self.Name, 'LibGetConfig', zeros(length, 1), length);
        end

        function value = get.LastStatus(self)
            value = calllib(self.Name, 'LibGetLastStatus');
        end

        function value = get.LastStatusStr(self)
            value = calllib(self.Name, 'LibGetLastStatusStr');
        end
    end
end
