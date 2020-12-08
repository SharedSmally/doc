# ASN1 data
## BITSTRING
```
<wlan-ecid-MeasSupported>apSSID apSN apDevType apPhyType apRSSI apChanFreq apRTD ueTP ueAG
      apRepLoc non-serving historic apTP apAG ueSN ueRSSI</wlan-ecid-MeasSupported>
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
```
using [bitstrhelpers functions](https://www.obj-sys.com/docs/acv61/CCppRunTime/com/group__bitstrhelpers.shtml) to access size-varied bitstring: 
bitIndex starts from 0.
```
int 	rtxSetBit (OSOCTET *pBits, OSUINT32 numbits, OSUINT32 bitIndex)
OSUINT32 	rtxSetBitFlags (OSUINT32 flags, OSUINT32 mask, OSBOOL action)
int 	rtxClearBit (OSOCTET *pBits, OSUINT32 numbits, OSUINT32 bitIndex)
OSBOOL 	rtxTestBit (const OSOCTET *pBits, OSUINT32 numbits, OSUINT32 bitIndex)
```

For encode/decode of fixed-length bitstring:
```
nrci is a 36bits string:
uint64_t nrci;

encode:
uint8_t ptr[5];
*ptr++ = nrci >> 28;
*ptr++ = (nrci >> 20) & 0xFF;
*ptr++ = (nrci >> 12) & 0xFF;
*ptr++ = (nrci >> 4) & 0xFF;
*ptr++ = (nrci << 4) & 0xF0;

decode:
uint8_t buffer[5];
nrci = 0;
nrci |= static_cast<uint64_t> (*buffer++) >> 28;
nrci |= static_cast<uint32_t> (*buffer++) >> 20;
nrci |= static_cast<uint32_t> (*buffer++) >> 12;
nrci |= static_cast<uint32_t> (*buffer++) >> 4;
nrci |= static_cast<uint32_t> (*buffer++) << 4;
```

## Iterator
```
ASN1T_EPDU_Sequence & epduSeq = r9->epdu_ProvideLocationInformation;
ASN1C_EPDU_Sequence epduCSeq(epduSeq);
ASN1CSeqOfListIterator * iter = epduCSeq.iterator();

while( iter->hasNext()) {
    ASN1T_EPDU * epdu = static_cast<lppv14_3::ASN1T_EPDU*>(iter->next());
    // using EPDU
    ASN1T_EPDU_Identifier & epduId = epdu->ePDU_Identifier;
    ASN1T_EPDU_Body & epduBody = epdu->ePDU_Body;
}
    
EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU
maxEPDU INTEGER ::= 16
EPDU ::= SEQUENCE {
        ePDU-Identifier                 EPDU-Identifier,
        ePDU-Body                       EPDU-Body
}

ProvideLocationInformation-r9-IEs ::= SEQUENCE {
        commonIEsProvideLocationInformation    CommonIEsProvideLocationInformation     OPTIONAL,
        a-gnss-ProvideLocationInformation       A-GNSS-ProvideLocationInformation       OPTIONAL,
        otdoa-ProvideLocationInformation        OTDOA-ProvideLocationInformation        OPTIONAL,
        ecid-ProvideLocationInformation         ECID-ProvideLocationInformation         OPTIONAL,
        epdu-ProvideLocationInformation         EPDU-Sequence                           OPTIONAL,
        ...,
        [[
        sensor-ProvideLocationInformation-r13   Sensor-ProvideLocationInformation-r13   OPTIONAL,
        tbs-ProvideLocationInformation-r13      TBS-ProvideLocationInformation-r13      OPTIONAL,
        wlan-ProvideLocationInformation-r13     WLAN-ProvideLocationInformation-r13     OPTIONAL,
        bt-ProvideLocationInformation-r13       BT-ProvideLocationInformation-r13       OPTIONAL
        ]]
}
```


## Debug
- using debug version of asn1 runtime libraries
```
unsigned char buf[ups::MAX_BUFFER_SIZE];
ASN1PEREncodeBuffer encodeBuffer(buf, ups::MAX_BUFFER_SIZE, FALSE);
ASN1C_ULP_PDU pduc(encodeBuffer, pdu);

int16_t status(pduc.EncodeTo(encodeBuffer));

if(status != RT_OK)
{
    ASN1Utils::printASNErrorInfo(encodeBuffer);
}
    
    template< typename T >
    inline void printASNErrorInfo(T &msg)
    {
        char buffer[ASN1_ERROR_SIZE];
        size_t len(sizeof(buffer));
        memset(buffer, 0, len);

        msg.getErrorInfo(buffer, len);
        std::cout << "ASN1 Error Info: " << std::endl << buffer << std::endl;
    }
    
    printErrorInfo();   setDiag(true);
    
    lsof to check code libs
```
