# Busmaster_CANSocket
 Busmaster komunikacija/ BUSMASTER-CANSocket (RPi)
 
## Ciljevi zadatka
- uspostavljanje komunikacije između BUSMASTER programa i Slave uređaja (u našem slučaju to je RPi)
- smještanje primljenih podataka u određene datoteke 
- razumijevanje pojmova DBC i DBF
- koncept konverzije 

## Priprema za izvršavanje zadatka

### BUSMASTER

Da bi uspostavili komunikaciju, zatim vršili prenos poruka, potrebno je prije svega da se skine softver (https://rbei-etas.github.io/busmaster/). 
Nakon toga, u zavisnosti operativnog sistema gdje je instaliran BUSMASTER, te u zavisnosti interfejsa (kod nas je USB-PEAK), konfiguriše se odgovarajući drajver, kako bi se sama komunikacija odvijala (link za drajver: (https://www.peak-system.com/PCAN-USB.199.0.html?&L=1&gclid=Cj0KCQjwzLCVBhD3ARIsAPKYTcStBVBsB5PcaRnTnB-Twuo1CKX8zmqqc7mUmLVB26Rk_ZyrzPyfxC4aAmo9EALw_wcB)).

### Preuzimanje i instalacija za razvojnu platformu

Da bi se na adekvatan način instalirala _can-utils_ biblioteka na ciljnoj platformi, potrebno je ispratiti korake na sledećem linku (https://github.com/knezicm/ikm-labs/tree/master/lab7#readme), odnosno odjeljak pod nazivom `Preuzimanje i instalacija can-utils softverskog paketa (radi se na razvojnoj platformi)`.


### Konfigurisanje CAN drajvera na RPI

Da bi mogao da se koristi CAN interefejs na Raspberry Pi platformi, neophodno je obezbijediti odgovarajući hardverski modul koji je povezan na jedan od interfejsa.  U našem slučaju, koristićemo modul CAN SPI click proizvođača Mikroelektronika. Ovaj modul sadrži CAN kontroler MCP2515 i CAN transiver MCP2551, koji omogućavaju povezivanje mikrokontrolera CAN mrežom preko interfejsa.

Ovaj fajl treba editovati komandom:

`sudo nano /boot/config.txt`
 zatim unijeti sledeće linije:
 
 `dtparam=spi=on
dtoverlay=mcp2515-can2,oscillator=10000000,spimaxfrequency=1000000,interrupt=25`

ako se radi o verziji Linux kernela >= 4.4.x, 

`dtparam=spi=on
dtoverlay=mcp2515-can2-overlay,oscillator=10000000,spimaxfrequency=1000000,interrupt=25
dtoverlay=spi-bcm2835-overlay`



