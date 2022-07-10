# Busmaster_CANSocket
 Busmaster komunikacija/ BUSMASTER-CANSocket (RPi)
 
## Ciljevi zadatka
- uspostavljanje komunikacije između BUSMASTER programa i Slave uređaja (u našem slučaju to je RPi)
- smještanje primljenih podataka u određene datoteke 
- razumijevanje pojmova DBC i DBF
- koncept konverzije 


## BUSMASTER - Software

Busmaster je prvenstveno namijenje za prenos podataka ili prijem istih, tako da on predstavlja softverski paket koji može slati određene frejmove, generisati neke vrste signala, što je i prikazano u ovom zadatku, a takođe prima podatke, odnosno u tom slučaju predstavlja _slave_ uređaj. Takođe ovaj program može da detektuje razne vrste grešaka. U okviru ovog programa, korisnik može da nadgleda CAN i LIN poruke, u zavisnosti interfejsa i okruženja koje koristi.
Postoje četri osnovna koraka, koja je potrebno ispuniti kako bi konfigurisali željeni okvir:

1. Odabir drajvera (u našem slučaju USB-Peak)
2. Konfiguracija parametara (kao što je Baudrate)
3. Database konfiguracija
4. Monitoring okvira i poruka koji se šalju/primaju

Kada je u pitanju slanje i generisanje frejmova, na veoma jednostavan način uz pomoć softverskog okruženja možemo generisati CAN frejm, sa svim parametrima koje čine ovu komunikaciju jedinstvenom. Nama su od interesa Transmissed message, gdje je prije svega potrebno napraviti jedan DBF fajl na osnovu kojeg ćemo generisati, konfigurisati i poslati podatak. 
Database (`.dbf`) je standardna biblioteka podataka koju koriste aplikacije za upravljanje bazama podataka. One zapravo organizuju podatke u više zapisa sa poljima, koje čuvaju u odgovarajućem nizu podataka. Ovaj tip baze je kompatabilan i sa drugim vrstama podataka, a ovaj program omogućava njihvu konverziju u drugi tip (na primjer `.dbc`) ili obrnuto, iz neke druge vrste podatak u .dbf fajl. Obično, ova vrsta podataka je više dostupna čitaocima, te je na taj način jasnije za razumijevanje poruka, pa samim tim i detekciju grešaka.
Pored Transmissed message, možemo generisati neku vrstu signala, a zatim je poslati nekom udaljenom čvoru (u našem slučaju slave uređadj je RPi). 
Naravno, osim slanja moguće je i logovanje/prijem poruka, to jeste da naš softver bude slave uređaj.
Ovaj program, u posljednjim ažuriranjima ima opciju da preko GUIa na jednostavan način generišete _Node simulaciju_. Klasa podataka kojoj pristupate za ovaj vid komunikacije je prikazana na sledećoj slici:

![Screenshot_1](https://user-images.githubusercontent.com/73527927/178165789-c2ca62f4-a61e-4d91-b1e8-bfe37558c6ab.png)Na 

Na ovaj način možemo jednostavno deklasirisati poruke koje šaljemo.
Sve ovo je detaljnije objašnjeno, sa jasno definisanim koracima u PDF fajlu [help.pdf](https://raw.githubusercontent.com/rbei-etas/busmaster-documents/master/help.pdf)


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
 
 ```dtparam=spi=on
dtoverlay=mcp2515-can2,oscillator=10000000,spimaxfrequency=1000000,interrupt=25```

ako se radi o verziji Linux kernela >= 4.4.x, 

```dtparam=spi=on
dtoverlay=mcp2515-can2-overlay,oscillator=10000000,spimaxfrequency=1000000,interrupt=25
dtoverlay=spi-bcm2835-overlay```

Važno je napomenuti da prilikom kroskompajliranja bilo koje aplikacije koja sadrži _<math.h>_ biblioteku  na Linux platformi, prilikom linkovanja mora dodati ekstenzija `-lm`.



