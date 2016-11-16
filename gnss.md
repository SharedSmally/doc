GNSS Timing
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

