# [SIGTRAN protocols](https://en.wikipedia.org/wiki/SIGTRAN)
## [TCAP](https://www.itu.int/ITU-T/recommendations/index.aspx?ser=Q): 771-775
- Q.771: Functional description of transaction capabilities
-	Q.772: Transaction capabilities information element definitions
-	Q.773: Transaction capabilities formats and encoding: ASN1
-	Q.774: Transaction capabilities procedures
-	Q.775: Guidelines for using transaction capabilities

## [Signalling connection control part (SCCP)](https://en.wikipedia.org/wiki/Signalling_Connection_Control_Part):
ITU SCCP defined in 711-715:
-	Q.711: Functional description of the signalling connection control part
-	Q.712: Definition and function of Signalling connection control part messages
-	Q.713: Signalling connection control part formats and codes: ASN1
-	Q.714: Signalling connection control part procedures
-	Q.715: Signalling connection control part user guide
-	Q.716: Signalling System No. 7 – Signalling connection control part (SCCP) performance

## Other SCCP
- ETSI EN 300 009-1
- ANSI T1.112/2002
- OpenSource Impl:[OpenSS7](http://www.openss7.org/)

## M3UA
- [RFC 4666](https://tools.ietf.org/rfc/rfc4666.txt) Signaling System 7 (SS7) Message Transfer Part 3 (MTP3) - User Adaptation Layer (M3UA)
- [RFC 3332](https://tools.ietf.org/rfc/rfc3332.txt): Obsolted by 4666
- [M2UA RFC 3331](https://tools.ietf.org/rfc/rfc3331.txt))
- [M2PA RFC 4165](https://tools.ietf.org/rfc/rfc4165.txt))

## SCCP Address

## [GT (Global Title)](https://en.wikipedia.org/wiki/Global_title)
- Global title format
The format parameter indicates the available formats are in use. Each format can include any of the subsequent parameters. A variety of formats are defined in separate standards. 

- Numbering plan indicator
The numbering plan indicator (NPI) describes which numbering plan will be used for the global title. The chosen numbering plan will aid the routing system in determining the correct network system to direct the message.

- Type of number
The type of number (TON) or Nature of Address Indicator (NAI) indicates the scope of the address value, such as whether it is an international number (i.e. including the country code), a "national" or domestic number (i.e. without country code), and other formats such as "local" format (e.g. in the U.S., without an area code). It could be relevance to E.164 (regular telephone) numbers. 

- Translation type
The translation type (TT) is used in a network to indicate the preferred method of global title analysis. Normally in European networks, this parameter is set to 0 (the default) value. In North American mobile networks, different translation types are used for analysis of the IMSI and for messages between telephone systems. This parameter is valuable in complex routing problems, where the same number has to be routed differently depending on the circumstances.

## [PC (PointCode)](https://en.wikipedia.org/wiki/Point_code)
An SS7 point code is similar to an IP address in an IP network. It is a unique address for a node (Signaling Point, or SP), used in MTP layer 3 to identify the destination of a message signal unit (MSU):
- OPC (Originating Point Code) 
- DPC (Destination Point Code)
- ISPC International Signaling Point Code

Depending on the network, a point code can be 24 bits (North America, China), 16 bits (Japan), or 14 bits (ITU standard, International SS7 network and most countries) in length:
- ANSI point codes use 24 bits, mostly in 8-8-8 format
- ITU point codes use 14 bits and are written in 3-8-3 format

## M3UA Format
```
M3UA:
      0                   1                   2                   3
      0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |    Version    |   Reserved    | Message Class | Message Type  |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                        Message Length                         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      \                                                               \
      /                                                               /
   
M3UA Protocol Version: 8 bits (unsigned integer)
   The version field contains the version of the M3UA adaptation layer. The supported versions are:
         1      Release 1.0
 
Message Class: 8 bits (unsigned integer). The valid Message Type Classes:
        0     Management (MGMT) Messages
        1     Transfer Messages
        2     SS7 Signalling Network Management (SSNM) Messages
        3     ASP State Maintenance (ASPSM) Messages
        4     ASP Traffic Maintenance (ASPTM) Messages
        9     Routing Key Management (RKM) Messages
        5     Reserved for Other SIGTRAN Adaptation Layers
        6     Reserved for Other SIGTRAN Adaptation Layers
        7     Reserved for Other SIGTRAN Adaptation Layers
        8     Reserved for Other SIGTRAN Adaptation Layers
       10 to 127 Reserved by the IETF
      128 to 255 Reserved for IETF-Defined Message Class extensions

Message Type: 8 bits (unsigned integer)
      Management (MGMT) Messages
           0        Error (ERR)
           1        Notify (NTFY)
        2 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined MGMT extensions

      Transfer Messages
           0        Reserved
           1        Payload Data (DATA)
        2 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined Transfer extensions

      SS7 Signaling Network Management (SSNM) Messages 
           0        Reserved
           1        Destination Unavailable (DUNA)
           2        Destination Available (DAVA)
           3        Destination State Audit (DAUD)
           4        Signalling Congestion (SCON)
           5        Destination User Part Unavailable (DUPU)
           6        Destination Restricted (DRST)
        7 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined SSNM extensions

      ASP State Maintenance (ASPSM) Messages: Up/Down/Heartbeat: Req/Ack
           0        Reserved
           1        ASP Up (ASPUP)
           2        ASP Down (ASPDN)
           3        Heartbeat (BEAT)
           4        ASP Up Acknowledgement (ASPUP ACK)
           5        ASP Down Acknowledgement (ASPDN ACK)
           6        Heartbeat Acknowledgement (BEAT ACK)
        7 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined ASPSM extensions

      ASP Traffic Maintenance (ASPTM) Messages
           0        Reserved
           1        ASP Active (ASPAC)
           2        ASP Inactive (ASPIA)
           3        ASP Active Acknowledgement (ASPAC ACK)
           4        ASP Inactive Acknowledgement (ASPIA ACK)
        5 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined ASPTM extensions

      Routing Key Management (RKM) Messages
           0        Reserved
           1        Registration Request (REG REQ)
           2        Registration Response (REG RSP)
           3        Deregistration Request (DEREG REQ)
           4        Deregistration Response (DEREG RSP)
        5 to 127    Reserved by the IETF
      128 to 255    Reserved for IETF-Defined RKM extensions
```
### M3UA Variable-Length Parameter Format
```
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |          Parameter Tag        |       Parameter Length        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      \                                                               \
      /                       Parameter Value                         /
      \                                                               \
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

Parameter Tag: 16 bits (unsigned integer)
      The Tag field is a 16-bit identifier of the type of parameter.  It
      takes a value of 0 to 65534.  Common parameters used by adaptation
      layers are in the range of 0x00 to 0x3f.  M3UA-specific parameters
      have Tags in the range 0x0200 to 0x02ff.  
        Parameter Name                     Parameter ID
        ==============                     ============
        Reserved                              0x0000
        Not Used in M3UA                      0x0001
        Not Used in M3UA                      0x0002
        Not Used in M3UA                      0x0003
        INFO String                           0x0004
        Not Used in M3UA                      0x0005
        Routing Context                       0x0006
        Diagnostic Information                0x0007
        Not Used in M3UA                      0x0008
        Heartbeat Data                        0x0009
        Not Used in M3UA                      0x000a
        Traffic Mode Type                     0x000b
        Error Code                            0x000c
        Status                                0x000d
        Not Used in M3UA                      0x000e
        Not Used in M3UA                      0x000f
        Not Used in M3UA                      0x0010
        ASP Identifier                        0x0011
        Affected Point Code                   0x0012
        Correlation ID                        0x0013
   M3UA-Specific parameters.  
        Network Appearance                    0x0200
        Reserved                              0x0201
        Reserved                              0x0202
        Reserved                              0x0203
        User/Cause                            0x0204
        Congestion Indications                0x0205
        Concerned Destination                 0x0206
        Routing Key                           0x0207
        Registration Result                   0x0208
        Deregistration Result                 0x0209
        Local Routing Key Identifier          0x020a
        Destination Point Code                0x020b
        Service Indicators                    0x020c
        Reserved                              0x020d
        Originating Point Code List           0x020e
        Reserved                              0x020f
        Protocol Data                         0x0210
        Reserved                              0x0211
        Registration Status                   0x0212
        Deregistration Status                 0x0213
        Reserved by the IETF             0x0214 to 0xffff

Parameter Length: 16 bits (unsigned integer)
      The Parameter Length field contains the size of the parameter in
      octets, including the Parameter Tag, Parameter Length, and
      Parameter Value fields.        
```


## M3UA sample: starts with 0x01 (version1.0); 0x00(reserved); 0x??(message class); 0x??(message type); 0x??????????(length)
```
       Received 0x01000301 00000008    #ASP State Maintenance; ASP UP
link 0 stream 0 received ASPUP length=8
link 0 stream 0 sending m3ua ASPUPACK length=8
       Sending 0x01000304 00000008    #ASP State Maintenance; ASPUP ACK
       
link 0 stream 0 sending m3ua NTFY length=24 routingContext={{1}} status={type=AS-State_Change info=AS-INACTIVE}
       Sending  0x01000001 00000018; 00060008 00000001; 000D0008 00010002  
       #Management(0x00); Notify(0x01); Routing contex(0x06; value=0x01); Status(0x0Dl; value=0x00010002)
       
       Received 0x01000401 00000018 000B0008000000020006000800000087
link 0 stream 0 received ASPAC length=24 trafficModeType=2 routingContext={{135}}
link 0 stream 0 sending m3ua ASPACACK length=24 trafficModeType=2 routingContext={{135}}
       Sending 0x01000403000000180006000800000087000B000800000002
link 0 stream 0 sending m3ua NTFY length=24 routingContext={{135}} status={type=AS-State_Change info=AS-ACTIVE}
       Sending 0x01000001000000180006000800000087000D000800010003
       established M3UA connectivity/SS7 connected
```

### Payload Data Message (DATA)
```
   The DATA message contains the SS7 MTP3-User protocol data, which is
   an MTP-TRANSFER primitive, including the complete MTP3 Routing Label.
   The DATA message contains the following variable-length parameters:
        Network Appearance       Optional
        Routing Context          Conditional
        Protocol Data            Mandatory
        Correlation Id           Optional

   The following format MUST be used for the Data Message:
       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |        Tag = 0x0200           |          Length = 8           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                       Network Appearance                      |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |        Tag = 0x0006           |          Length = 8           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                        Routing Context                        |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |        Tag = 0x0210           |             Length            |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      \                                                               \
      /                        Protocol Data                          /
      \                                                               \
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |        Tag = 0x0013           |          Length = 8           |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                        Correlation Id                         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   Protocol Data: variable length
      The Protocol Data parameter contains the original SS7 MTP3
      message, including the Service Information Octet and Routing
      Label. The Protocol Data parameter contains the following fields:
         Service Indicator
         Network Indicator
         Message Priority
         Destination Point Code
         Originating Point Code
         Signalling Link Selection Code (SLS)
         User Protocol Data, which includes
            MTP3-User protocol elements (e.g., ISUP, SCCP, or TUP parameters)

   The Protocol Data parameter is encoded as follows:
        0                   1                   2                   3
        0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                     Originating Point Code                    |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |                     Destination Point Code                    |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       |       SI      |       NI      |      MP       |      SLS      |
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
       \                                                               \
       /                     User Protocol Data                        /
       \                                                               \
       +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

      Originating Point Code: 32 bits (unsigned integer)
      Destination Point Code: 32 bits (unsigned integer)

   Service Indicator: 8 bits (unsigned integer)
   Network Indicator: 8 bits (unsigned integer)
   Message Priority: 8 bits (unsigned integer)
   Signalling Link Selection: 8 bits (unsigned integer)

User Protocol Data: variable-length octet string
```

### M3UA data
```
<Message name="MAP SLR CO" packageType="0x62" acName="0.1.2.3.4.5.6.7" calledssn="145">
   <Component type="0xa1">
      <Opcode value="0x56"/>
      <ComponentID value="0x00"/>
      <Parameters tag="0x30" value="0x30700A0100302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300B0409940100000000000110800
69144871132008107022287113200F0820821436500896745F08508100C0C0C0C0C0C0C860204D2AD09800723636803F20193"/>
   </Component>
</Message>

SLR TCAP:
dialogue {
   dialogueRequest {
      protocol_version = { 0,  }
      application_context_name = { 0 1 2 3 4 5 6 7 }
   }
}

{
   begin {
      otid = 0x00000000
      dialoguePortion {
         direct_reference = { 0 0 17 773 1 1 1 }
         encoding {
            single-ASN1-type = 0x600ba109060701020304050607
         }
      }
      components[0] {
         invoke {
            invokeID = 0
            operationCode = 86
            parameter =
30 70 0a 01 00 30 2a 80 01 01 a1 08 80 06 90 21  0p...0*........!
43 53 44 f5 82 07 90 21 60 97 22 16 f2 a4 12 80  CSD....!`.".....
01 63 82 0a 53 61 74 79 61 4b 75 6d 61 72 83 01  .c..SatyaKumar..
01 30 0b 04 09 94 01 00 00 00 00 00 01 10 80 06  .0..............
91 44 87 11 32 00 81 07 02 22 87 11 32 00 f0 82  .D..2...."..2...
08 21 43 65 00 89 67 45 f0 85 08 10 0c 0c 0c 0c  .!Ce..gE........
0c 0c 0c 86 02 04 d2 ad 09 80 07 23 63 68 03 f2  ...........#ch..
01 93                                            ..
         }
      }
   }
}

SCCP UnitData mhandling=0, pclass=0, clg={ssn-routed ssn 8}, cld={ssn-routed ssn 145}, datalen=161
link 0 stream 1 sending m3ua DATA length=200 protocolData={opc=4222, dpc=4221, si=3, ni=2, mp=0, sls=0, dataLen=173}
Sending 0x01000101000000C8021000BD0000107E0000107D030200000900030507024291024208A162819E4804000000006B1A2818060700118605010101A00D600BA1090607010203040506076C7AA17802010002015630700A0100302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300B040994010000000000011080069144871132008107022287113200F0820821436500896745F08508100C0C0C0C0C0C0C860204D2AD09800723636803F20193000000

0x
01000101 000000C8 (01-01: Transfer Messages-Payload Data; length=200=0xC8) 
021000BD (protocol data:0x0210; length=00BD=189 = 173 + 4*4)
0000107E (OPC=4222) 0000107D (DPC=4221) 03(SI) 02(NI) 00(MP) 00(SLS)
0900     SCCP: 0x09=UnitData:class=00
030507024291024208A1
6281
9E
4804: Original TransID(48): 00000000; len=4
   00000000: 
6B1A: Dialog (6B); len=1A=26
   2818: External Tag: 28; len=18(24)
   060700118605
   010101A00D60
   0BA109060701
   020304050607
   
6C7A: Compoennt Portion(6C); length=7A(122)
  A178:Invoke; len=78(120)
     020100:Invoke ID(02); val=00
     020156:Local OP code: 02; val=56(86)
     3070: parameter tag(30); len=70(112)
    0A0100302A800101A10880069021435344F58207902160972216F2A412800163820A53617479614B756D6172830101300B040994010000000000011080069144871132008107022287113200F0820821436500896745F08508100C0C0C0C0C0C0C860204D2AD09800723636803F20193 000000
```
