### GNSS Timing
========

GPS:
- GPS Time:
   - GPS Week: 10bits; 0-1023
   - TOW (Time of GPS Week): 0 ~ 604800
   - 1 h = 3600m; 1d=24*3600=86400;  1w=7*1d=604800 
   - Toe: Time of Ephemeris; in Unit of 2^4=16 seconds
      Range: [0-37800):  37800=604800/16
   - Toa: Time of Almanac: (8bits) in unit of 2^12=4096seconds
      Range: [0-256)
- GPS Timing (UTC Time <-> GPS Time)[https://www.labsat.co.uk/index.php/en/gps-time-calculator]  
- (GPS icd)[http://www.gps.gov/technical/icwg/]:(200C)[http://www.gps.gov/technical/icwg/ICD-GPS-200C.pdf]
- (Glonass icd)[http://gauss.gge.unb.ca/GLONASS.ICD-98.pdf]
- (Rinex)[ftp://igscb.jpl.nasa.gov/igscb/data/format/rinex210.txt]: 
- (RRLP)[http://www.qtc.jp/3GPP/Specs/GSM_GERAN/44031-861.pdf] :

### ECID Range Measurement
- The Range-based measurement from the cell transmit /receive antenna to the handset based on access network:
  - LTE + LPP, it is the UeRx-TxTimeDifference value from the device in units of Ts (where Ts is the basic time unit of LTE), where the reported LPP value is converted Ts as per the report mapping in 3GPP T36.133 section 9.1.9.2 [SRC_LPP]. 
  - LTE Control Plane + LPPa, it is the Timing Advance value (type 1 or type 2) from the eNodeB in units of Ts, where the reported LPPa value is converted as per the report mapping in 3GPP T36.133 section 10.3.1 [SRC_LPPa_Type1,SRC_LPPa_Type2].
  - LTE User Plane, it is the TA value as received in the ULP/ILP SUPL layer messaging, in units of 16Ts [SRC_ULP_TA]. Timing Advance (TADV) mapping is defined in TS 36.133 10.3
  - UTRAN control plane + PCAP, it is the round trip time (RTT type 1 or 2) in chip units reported from the RNC, where the reported PCAP value is converted to a measured value as per the report mapping in 3GPP 25.133 section 9.2.8.2. In this case the secondary measurement must also be set, which contains the UeRx-TxTimeDifference value [SRC_PCAP_Type1,SRC_PCAP_Type2].
  
- The Power-based measurement from the cell transmit/receive antenna to the handset(the received signal strength, and potentially signal quality) at the handset from a single cell (serving cell or neighbors)
   - LTE : RSRP and or RSRQ. The report mapping is defined in TS 36.133:
       - 9.1.4 RSRP Measurement Report Mapping to dBm
       - 9.1.7 RSRQ Measurement Report Mapping to dB
       - 9.1.8.4 Power headroom Report Mapping 
       - 9.1.9.2 Rx-Tx time difference Measurement Report mapping
       - 9.1.10.3 RSTD Measurement Report Mapping 
       - 9.1.14.3.3 CSI-RSRP measurement report mapping 
       - 9.1.17.1 RS-SINR Measurement Report Mapping 
       - 9.1.18.5.1 RSSI measurement report mapping 
   - UTRAN: CPICH RSCP amd ECNO;
  
