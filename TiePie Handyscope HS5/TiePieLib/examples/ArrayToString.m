function [Result] = ArrayToString(ar, seperator)
    % Converts an array to a string, values are seperated by `seperator`, default `seperator` is ', '.
    if nargin < 2 || isempty(seperator)
        seperator = ', ';
    end
    Result = '';
    for k = 1 : length(ar)
        if k > 1
            Result = [Result, seperator];
        end
        Result = [Result, char(ar(k))];
    end
end
