## PC (Point Code)
- An SS7 point code is similar to an IP address in an IP network. It is a unique address for a node (Signaling Point, or SP), used in MTP layer 3 to identify the destination of a message signal unit (MSU).
- An OPC (Originating Point Code) and a DPC (Destination Point Code) is in the message, sometime they are refered as ISPC (International Signaling Point Code). 
- Depending on the network, a point code can be 24 bits (North America, China), 16 bits (Japan), or 14 bits (ITU standard, International SS7 network and most countries) in length.
- ANSI point codes use 24 bits, mostly in 8-8-8 format.[1] ITU point codes use 14 bits and are written in 3-8-3 format.[2]
- Fourteen bit point codes can be written in a number of formats. The most common formats are decimal number, hexadecimal number, or 3-8-3 format (3 most significant bits, 8 middle bits, 3 least significant bits).
- Twenty-four bit point codes may be written in decimal, hexadecimal, or 8-8-8 format.
- Examples:    
   - 24 bits:  12345(Dec) = 3039(Hex) = 0-48-57    (8-8-8)
   - 14 bits:  1234(Dec)  = 4D2(Hex)  = 9-82(7-7)  (3-8-3; 7-7; 4-3-4-3; 7-7; 6-8)

## [SSN](https://en.wikipedia.org/wiki/Subsystem_number) (Subsystem number)
 In GSM and UMTS, subsystem numbers is used between PLMNs in which case they are taken from the globally standardized range (1 - 31) or the part of the national network range (129 - 150) reserved for GSM/UMTS use between PLMNs. For use within a PLMN, numbers are taken from the part of the national network range (32 - 128 & 151 - 254) not reserved for GSM/UMTS use between PLMNs.

The following globally standardized subsystem numbers have been allocated for use by GSM/UMTS:
```
 0  Not used/Unknown
 1  SCCP MG
 6  HLR (MAP)
 7  VLR (MAP)
 8  MSC (MAP)
 9  EIR (MAP)
 10 is allocated for evolution (possible Authentication Centre).
 ```
The following national network subsystem numbers have been allocated for use within GSM/UMTS networks:
```
 249  PCAP
 250  BSC (BSSAP-LE)
 251  MSC (BSSAP-LE)
 252  SMLC (BSSAP-LE)
 253  BSS O&M (A interface)
 254  BSSAP (A interface)
```
The following national network subsystem numbers have been allocated for use within and between GSM/UMTS networks:
```
 142  RANAP
 143  RNSAP
 145  GMLC (MAP)
 146  CAP
 147  gsmSCF (MAP) or IM-SSF (MAP)
 148  SIWF (MAP)
 149  SGSN (MAP)
 150  GGSN (MAP)
 241  INAP
```

North American (ANSI) SSNs
```
 232  CNAM (Calling Name)
 247  LNP
 248  800 number translation (AIN0.1)
 254  800 number translation (TCAP)
```

## [GT](https://en.wikipedia.org/wiki/Global_title) (Global Title)
A global title (GT) is an address used in the SCCP protocol for routing signaling messages on telecommunications networks.The GT structure is officially defined in ITU-T Recommendation [Q.713](), and further extended in the supporting numbering plan standards

- Global title format
A global title can be in a variety of formats, most of which are each defined in separate standards. The format parameter indicates which of the available formats are in use. Each format can include any of the subsequent parameters.

- Numbering plan indicator
The numbering plan indicator (NPI) describes which numbering plan will be used for the global title. The chosen numbering plan will aid the routing system in determining the correct network system to direct the message.

- Type of number
The type of number (TON) or Nature of Address Indicator (NAI) parameter, which is of relevance to E.164 (regular telephone) numbers for example, indicates the scope of the address value, such as whether it is an international number (i.e. including the country code), a "national" or domestic number (i.e. without country code), and other formats such as "local" format (e.g. in the U.S., without an area code).

- Translation type
The translation type (TT) parameter is used in a network to indicate the preferred method of global title analysis (see below). Normally in European networks, this parameter is set to 0 (the default) value. In North American mobile networks, different translation types are used for analysis of the IMSI and for messages between telephone systems. This parameter is valuable in complex routing problems, where the same number has to be routed differently depending on the circumstances, such as those introduced by number portability resolution.

## SCCP Address()
```
struct GTT0100{
    short tt;
    short numplan;
    short natureofaddr;
    bool present;
};

struct SSN{
    int value;
    bool present;
};

struct PointCode{
    int  value;
    bool present;
};

struct SCCPAddr {
    int indicator;  // 0---routing by PC+SSN;  >1---routing by GTT;                     
    union {
        GTT0100 gtt0100;
    } gtt;
    SSN     ssn;
    PointCode pc;
};
```
