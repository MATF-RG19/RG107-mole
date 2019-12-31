# RG107-mole

## :mushroom: Opis igre:
Radnja se odigrava na njivi. Upravljate krticom koja krade povrce od seljaka. Medjutim, kako bi je sprecili, seljaci se (nasumicno) setaju po redovima. Svaki seljak ima oblast u kojoj moze da registruje da li krtica trenutno uvlaci neko povrce pod zemlju, ukoliko se u toku uvlacenja nadjete u toj oblasti-izgubili ste. Posto se nalazi ispod zemlje, krtica, odnosno njena pozicija, predstavljena je kvadratom. Da bi povrce uvukla, prvo mora da se zakaci za njega, a zatim ga uvlaci deo po deo. Osim povrca, na njivi se nalazi i magicna pecurka, ona moze biti dobra ili losa. Ukoliko je pecurka dobra, kada je pojede krtica se krece duplo brze i povrce moze uvuci u jednom potezu (tada ne moze biti uhvacena), a inace ne moze da se pomera sve vreme trajanja efekta pecurke (10s). Vreme za kradju je ograniceno na jedan minut, kada ono istekne-izgubili ste. Jedini nacin da pobedite je da ukradete sve, pecurku nije obavezno uzeti, ona je samo za one koji vole da rizikuju (bonus ili kazna).




## :wrench: Instalacija:
1.Pomoću terminala zadati komandu za kloniranje:``` git clone https://github.com/MATF-RG19/RG107-mole.git```     
2.Pozicionirajte se u direktorijum sa nazivom ``RG107-mole``   
3.Pokrenite Makefile komandom ```make```     
4.Igricu pokrenite sa ``./mole``





## :video_game: Komande:
|Komanda   | Akcija  |
|---     |---|
| <kbd>W</kbd>  |Pomeranje na gore  |
| <kbd>S</kbd>  |Pomeranje na dole  | 
| <kbd>A</kbd>  |Pomeranje levo   |
| <kbd>D</kbd>  |Pomeranje desno   | 
| <kbd>Q</kbd>  |Pomeranje gore-levo  |
| <kbd>E</kbd>  |Pomeranje gore-desno  | 
| <kbd>Z</kbd>  |Pomeranje dole-desno   |
| <kbd>C</kbd>  |Pomeranje dole-levo   | 
||  ||
| <kbd>I</kbd>  |Kacenje za povrce |
| <kbd>U</kbd>  |Uvlacenje povrca ali samo nakon kacenja|
|| ||
| <kbd>ESC</kbd>  |Prekidanje igrice|

## :exclamation: Uputstvo:
Da biste uvukli povrce, pozicionirajte se u okolini povrca, kvadrat(krtica) ga mora dodirivati ili biti ispod njega, zatim pritisnite taster 'i', a tek onda klikovima tastera 'u' uvlacite povrce deo po deo. Sve ovo vazi i za pecurku, osim sto nakon sto se pojede pecurka dolazi do zanimljivog efekta. Kada se pojede, pored vremena do zavrsetka igre ispisuje se zeleno(ako je pecurka dobra) ili crveno(ako nije) vreme trajanja efekta. Nakon uvlacenja jednog dela povrca, iznad njega se ispisuje broj preostalih koraka potrebnih da se do kraja uvuce. Taj broj je crven ako krtica trenutno drzi to povrce, inace je beo. Sa uvlacenjem se moze prestati u nekom trenutku i kasnije se moze nastaviti bez posledica. Bitno je da seljaci nece registrovati ako je ktrica zakacena za povrce koje nije bar malo uvuceno, ako je uvuceno i zakacena je (iznad je dakle ispisan crveno broj koraka),uhvatice je.

