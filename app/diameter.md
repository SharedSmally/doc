# Diameter
The Diameter base protocol is defined by RFC 6733 and defines the minimum requirements for an AAA protocol. 

## [Protocol](https://en.wikipedia.org/wiki/Diameter_(protocol))
- Diameter base - [RFC 6733](https://tools.ietf.org/html/rfc6733) (Obsoletes: [RFC 3588](https://tools.ietf.org/html/rfc3588))
    - CER/CEA  Capabilities-Exchange-Request/Answer  	
    - DWR/DWA  Device-Watchdog-Request/Answer	
    - DPR/DPA  Disconnect-Peer-Request/DPA
    - RAR/RAA  Re-Auth-Request/Answer
    - STR/STA  Session-Termination-Request/Answer
    - ASR/ASA  Abort-Session-Request/Answer
    - ACR/ACA  Accounting-Request
- SIP Application - [RFC 4740](https://tools.ietf.org/html/rfc4740)
    - UAR/UAA  User-Authorization-Request/Answer
    - SAR/SAA  Server-Assignment-Request/Answer
    - LIR/LIA  Location-Info-Request/Answer
    - MAR/MAA  Multimedia-Auth-Request/Answer
    - RTR/RTA  Registration-Termination-Request/Answer
    - PPR/PPA  Push-Profile-Request/Answer
- Mobile IPv4 - [RFC 4004](https://tools.ietf.org/html/rfc4004) for IPv4, and [RFC 5447](https://tools.ietf.org/html/rfc5447) for IPv6
    - AMR/AMA  AA-Mobile-Node-Request/Answer	
    - HAR/HAA  Home-Agent-MIP-Request/Answer
- Credit-Control Application - [RFC 8506](https://tools.ietf.org/html/rfc8506) (Obsoletes [RFC 4006](https://tools.ietf.org/html/rfc4006))
    - CCR/CCA  Credit-Control-Request/Answer	
- EAP(Extensible Authentication Protocol) Application - [RFC 4072](https://tools.ietf.org/html/rfc4072)
    - DER/DEA  Diameter-EAP-Request/Answer
- NAS(Network Access Server) Application - [RFC 7155](https://tools.ietf.org/html/rfc7155)
    - AAR/AAR  AA-Request/Answer
- 3GPP Diameter base - [RFC 3589](https://tools.ietf.org/html/rfc3589) for Release 5
    - UAR/UAA  User-Authorization-Request/Answer
    - SAR/SAA  Server-Assignment-Request/Answer
    - LIR/LIA  Location-Info-Request/Answer
    - MAR/MAA  Multimedia-Auth-Request/Answer
    - RTR/RTA  Registration-Termination-Request/Answer
    - PPR/PPA  Push-Profile-Request/Answer
    - UDR/UDA  User-Data-Request/Answer
    - PUR/PUA  Profile-Update-Request/Answer
    - SNR/SNA  Subscribe-Notifications-Request/Answer
    - PNR/PNA  Push-Notification-Request/Answer
    - BIR/BIA  Bootstrapping-Info-Request/Answer
    - MPR/MPA  Message-Process-Request/Answer
- 3GPP TS 29.272 - [RFC 5516](https://tools.ietf.org/html/rfc5516) for EPS
    - ULR/ULA  Update-Location-Request/Answer
    - CLR/CLA  Cancel-Location-Request/Answer
    - AIR/AIA  Authentication-Information-Request/Answer
    - IDR/IDA  Insert-Subscriber-Data-Request/Answer
    - DSR/DSA  Delete-Subscriber-Data-Request/Answer
    - PER/PEA  Purge-UE-Request/Answer
    - NR/NA    Notify-Request/Answer
- 3GPP TS 29.172 SLg
    - PLR/PLA: Provide-Location-Request/Answer
- 3GPP TS 29.173 SLh
    - RIR/RIA: Routing-Info-Request/Answer
- 3GPP TS 29.336 S6t
    - CIR/CIA  Configuration-Information-Request/Answer
    - RIR/RIA  Reporting-Information-Request/Answer
    - NIR/NIA  NIDD-Information-Request/Answer
    
## 3GPP Diameter: TS 29.230

## Message Flow 
!(message flow)[https://en.wikipedia.org/wiki/File:Diameter_message_flow.png]
