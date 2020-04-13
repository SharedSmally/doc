# Wireless WANS (Long Range): 30% 
- licensed/unlicened spectrum
- LTE-M
- NB-IoT (LPWA)
- EC-GSM-IoT
- LoRaWAN
- SigFox

## LTE-M vs NB-IoT
## Reference
- [LTE-M vs NB-IoT](https://www.iotforall.com/cellular-iot-explained-nb-iot-vs-lte-m/): From release 13
    - Cat-1: 
    - Cat-0: Optimizes for cost ( eliminated features to support high data rate for Cat-1)
    - Cat-M1/Cat-M/LTE-M: second generation of LTE chips built for IoT, Compatible with the existing LTE network.
    - NB-IoT/Cat-M2: Uses DSSS modulation instead of LTE radio, potentially less expensive option
    - EC-GSM (EC-EGPRS): the IoT-optimized GSM network
    
![diagram](https://cdn-images-1.medium.com/max/800/1*NElcQqs2kIB_OLC56es04w.jpeg)
    

## [Chipset Vendors](http://www.codeplayon.com/2019/03/narrow-band-nb-iot-modem-chip-vendors-2/)
- Qualcomm: [MDM 9207(CAT1)/9206(Cat-M1)/9205(Cheap)](https://rethinkresearch.biz/articles/qualcomms-latest-iot-modem-chipset-covers-nearly-all-the-3gpp-bases/)
    - [DeveloperNetwork](https://developer.qualcomm.com/project/)
    - [OS-IoT C Library for BG96/MDM9206 in ThreadX](https://os-iot.org/c-library/)
    - [Cellular IoT-mdm9206](https://developer.qualcomm.com/blog/cellular-iot-mdm9206-modem-and-new-lte-iot-sdk)
- HiSilicom: Balong
- Samsung: Exynos
- Sequans: Monarch/Monarch-N
- Altair: ALT1250
- MediaTek: MT2625 SoC
- Nordic Semiconductor: nRF91xx(9160): $25; DK(DevKit:$150); https://devzone.nordicsemi.com
- u-blox: SARA R410M; C030 Application board
- SaneChips: RoseFinch7100
- Riot Micro: RM1000 

## Distributor
- Telit: xE910: ME910G1/ME910C1 (from QM)
- Quectel: BG96/BC95 (from HiSilicom)

# Local networks (Short Range): 70%
- Bluetooth LE
- WiFi 802.11ah
- IEEE 802.15.4
- ZigBee
- XBee
- Z-Wave

## BlueTooth
- NORDIC SEMICONDUCTOR: nRF 5340

## Sensors
- $2 for 10PCBs: https://jlcpcb.com (Gerber)

## IoT Projects
- https://openthread.io/
