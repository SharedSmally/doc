See 23.032, Chapter 5. Shapes
posEstimate: 30 | 23 8e 39 | ce 38 e3 | 24 77 9b 43
Shape Type: Ellipsoid point with uncertainty ellipse( 0x30: 0011 - 0000 )
Latitude: 3 octets; [Section 6.2]
             Sign=NORTH; value=25.000001 => [0,90)
             sign-31bits-value: sign=0-NORTH; sign=1=SOUTH
             value: 0x238e39=2330169; Scaler=90.0/(2**23-1) (with or without(correct) -1; )
             real value: 2330169/(2**23-1)*90.0=25.000004
                         2330169*90.0/2**23=25.0000012
Longitude:3 octets; [Section 6.1]
             value: -70.000011 
             sign-31bits-value: sign=1; 0xce = 1100 1110 =>[0,180)
             value: 0x4E38E3=5126371, Scaler: 180/(2**23-1) (with or without(correct)-1)
             real value: 0x4E38E3 = 0xFF4E38E3
                         => signed int(-3262237 from signed 2's complement)
                         => -3262237*180.0/(2**23-1) = -70.000020
                         => -3262237*180.0/2**23 = -70.000011
Semi-major:1 octet; 36(0x24)->299 = 10*((1+0.1)**36-1)      [Section 6.2]
Semi-minor:1 octet; 119(0x77)=>842800  = 10*((1+0.1)**36-1) [Section 6.2]
Angle major: 1 octet; => 155 (0x9B)
Confidence:  1 octet; 67 (0x43)
