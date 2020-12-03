# BITSTRING
<wlan-ecid-MeasSupported>apSSID apSN apDevType apPhyType apRSSI apChanFreq apRTD ueTP ueAG apRepLoc non-serving historic apTP apAG ueSN ueRSSI</wlan-ecid-MeasSupported>
16:  16 0xFF; 0xFF

<wlan-ecid-MeasSupported>apSSID apRSSI</wlan-ecid-MeasSupported>
 numbits=5; data=88,6f;  data[0], data[1]  
    1000 1000      88      0110 1111
	appSID
	     apRSSI
<wlan-ecid-MeasSupported>apSSID apRSSI apRepLoc ueSN</wlan-ecid-MeasSupported>
numbits=15; data=88,42     
    1000 1000 0100 0010
	0    4     9     14
	
wlan-ecid-MeasSupported    BIT    STRING    {
    apSSID    (0),
    apSN    (1),
    apDevType    (2),
    apPhyType    (3),
    apRSSI    (4),
    apChanFreq    (5),
    apRTD    (6),
    ueTP    (7),
    ueAG    (8),
    apRepLoc    (9),
    non-serving    (10),
    historic    (11),
    apTP    (12),
    apAG    (13),
    ueSN    (14),
    ueRSSI    (15)}    (SIZE(1..16)),
    
