% BitMask2Array extracts from an integer the values of the separate bits.
% Example:
%   BitMaskToArray( 3 ) is [ 1 , 2 ]
%   BitMaskToArray( 5 ) is [ 1 , 4 ]
%
% Copyright (c) 2012-2021 TiePie engineering

function arBitValues = BitMask2Array( nMask )
    arBitValues = [];
    %arOnes = dec2binvec( nMask ); % Copied the next two lines from dec2binvec because it is not always available:
    out = dec2bin( nMask );
    arOnes = logical( str2num( [ fliplr( out ) ; blanks( length( out ) ) ]' )' );

    for k = 1 : length( arOnes )
        if arOnes( k )
            arBitValues = [ arBitValues , 2^( k - 1 ) ];
        end
    end;
end
