% VersionNumber2String converts a 64 bit version number to a string.
%
% Copyright (c) 2012-2021 TiePie engineering

function VersionString = VersionNumber2String( nVersion )
    VersionString = [ sprintf( '%d' , bitand( nVersion , 65535 ) ) ];
    for k = 1:3
        VersionString = [ sprintf( '%d' , bitand( bitshift( nVersion , -k * 16 ) , 65535 ) ) , '.' , VersionString ];
    end
end
