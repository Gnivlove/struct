# Data structure

Repositories consist of tasks (programs) by which I analyze and learn the performance of basic data types and structures: arrays and arrays, stack, row, single and double linked lists, trees, binary trees, balanced binary trees, hash tables, sets, and charts. I used sorting and retrieval techniques, scattering, memory waste collection, and memory usage control, and apply basic knowledge of algorithm complexity.

# Language
- C


# Lab Title: [Insert title here]

## Challenge Answers

- **Challenge 1:** [Insert answer here, i.e., a Chuck Norris fact]
- **Challenge 2:** [Insert answer here, i.e., a `password` to unlock the next lab]

## Other Relevant Information

[Insert here, if applicable]
  
## Lab Prep Questions and Answers

1. What is the _Address Resolution Protocol (ARP)_, and what is its role in a network?
- ARP je protokol na mrežnoj razini koji se koristi za povezivanje logičkih adresa (npr. IP adresa) sa fizičkim adresama (npr. MAC adresa) na lokalnoj mreži. Bitan je jer omogućava računalima na mreži da komuniciraju međusobno i da znaju kako pronaći druga računala. Bez ARP-a, računala na mreži ne bi bila u stanju razmjenjivati podatke ili uspostaviti bilo kakvu vrstu veze.

1. What is the _Address Resolution Protocol (ARP)_, and what is its role in a network?
- ARP je protokol na mrežnoj razini koji se koristi za povezivanje logičkih adresa (npr. IP adresa) sa fizičkim adresama (npr. MAC adresa) na lokalnoj mreži. Bitan je jer omogućava računalima na mreži da komuniciraju međusobno i da znaju kako pronaći druga računala. Bez ARP-a, računala na mreži ne bi bila u stanju razmjenjivati podatke ili uspostaviti bilo kakvu vrstu veze.
  
2. What is a _Man-in-the-Middle (MitM)_ attack, and how does ARP spoofing enable it?
- MitM napad je vrsta napada u kojoj napadač između dvije komunikacijske strane ubaci sebe kao posrednika i prati i/ili mijenja komunikaciju između njih bez njihova znanja. ARP spoofing (ili ARP trojan) je tehnika koja omogućuje napadaču da izvrši MitM napad tako što lažno predstavlja svoju MAC adresu kao MAC adresu legitimnog uređaja u mreži. Kada se to dogodi, svi mrežni promet koji je namijenjen legitimnom uređaju u stvarnosti ide prema napadaču, koji može pregledavati, mijenjati ili čak blokirati komunikaciju.

3. How does an attacker use ARP spoofing to intercept network traffic?
- Napadač može koristiti ARP spoofing za presretanje mrežnog prometa tako da pošalje lažne ARP odgovore u mrežu s lažnom MAC adresom koja se predstavlja kao MAC adresa legitimnog uređaja u mreži. Kada druge računala u mreži pošalju ARP upit za tu IP adresu, umjesto da dobiju pravu MAC adresu legitimnog uređaja, dobivaju lažnu MAC adresu napadača. Kada se to dogodi, sav promet koji je namijenjen legitimnom uređaju u stvarnosti ide prema napadaču. Napadač tada može pregledavati, mijenjati ili čak blokirati komunikaciju između dva računala bez njihova znanja.
  
4. How is the _cookie_ used to derive the encryption/decryption key?
- Kolačići nisu direktno korišteni za stvaranje enkripcijskih ključeva, ali mogu se upotrijebiti za pohranu identifikatora sesije. Identifikator sesije se koristi za stvaranje jedinstvenog ključa za enkripciju za svaku sesiju. Ovaj ključ se obično generira pomoću funkcije za izvođenje ključa. Nakon što je ključ generiran, koristi se za šifriranje i dešifriranje podataka koji se razmjenjuju između klijenta i servera.

5. What REST API request do you need to send to the _crypto oracle_ the secret cookie?
- Potrebno je poslati HTTP zahtjev tipa POST s tijelom zahtjeva koji sadrži tajni kolačić (secret cookie) na REST API adresu kripto orakla.U slučaju autentifikacije putem REST API-ja, korisnik bi trebao pružiti autentifikacijski ključ ili token.
  
6. How do you obtain the authentication token?
- Autentifikacijski token za API ili uslugu se obično dobiva tako da se korisnik se  mora registrirati i generirati API vjerodajnice poput ključeva ili tokena. Nakon autentifikacije, API ili usluga izdaju autentifikacijski token koji se koristi za slanje naknadnih zahtjeva. Koraci variraju ovisno o API-ju ili usluzi, a dokumentacija bi trebala pružiti specifične upute.
  
7. How do you use the authentication token to obtain the cookie?
- Upotreba autentifikacijskog tokena za stjecanje kolačića ovisi o API-ju ili usluzi koju koristite. Obično se koristi kako bi se autentificirali s API-jem i omogućilo slanje zahtjeva za kolačićem. Točan postupak varira ovisno o specifičnom API-ju ili usluzi koju koristite, stoga je važno provjeriti dokumentaciju kako biste dobili specifične upute.

8. What encryption mode is used to encrypt the challenge in this lab?
- U ovom laboratorijskom zadatku se koristi CBC modus šifriranja (Cipher Block Chaining) za osiguravanje povjerljivosti i integriteta poruke kod blokovskih šifri. CBC modus koristi XOR operaciju između prethodnog bloka šifratexta i otvorenog teksta prije nego što se blok šifratexta šifrira, kako bi se osigurala ovisnost o svim prethodnim blokovima otvorenog teksta za svaki blok šifratexta. ICV (integrity check value) se dodaje na kraj šifra-teksta kako bi se spriječila manipulacija porukom. CBC modus je popularan za blokovske šifre.
9. What tool can you use to capture network traffic on a local network interface?
- Postoji nekoliko besplatnih i open-source alata za snimanje mrežnog prometa na lokalnom mrežnom sučelju. Među njima je popularan Wireshark, koji omogućuje snimanje i analizu mrežnog prometa u stvarnom vremenu. Wireshark podržava širok raspon protokola i snimanje prometa s različitih žičanih i bežičnih sučelja. Osim toga, postoje i drugi alati poput tcpdump-a, Microsoft Network Monitor i NetWitness koji imaju slične mogućnosti i koji se također mogu koristiti za ovu svrhu.


