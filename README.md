# LSP_md_dir

Uzdevums: uzrakstīt programmu md3, kas apstaigā direktoriju koku un atrod tos failus kas ir duplikāti, respektīvi, atrodami vairākos eksemplāros.

Apstaigāšana jāsāk no tās direktorijas, kurā programma izpildās (t.i. direktorijas ar nosaukumu ".").

Faili tiek uzskatīti par vienādiem, ja tiem ir vienāds izmērs un faila vārds, izņemot MD5 režīmā, kad failu vienādību nosaka MD5 vērtības.

Saites (symbolic links, t.i. "vājās" saites) jāignorē. Divas vājās saites, vai arī fails un vājā saite uz to nav jāsalīdzina.

Vārds un izmērs jāpārbauda vienmēr, izņemot MD5 režīmu. Papildus pārbaudes nosaka parametri:

md3 -d      pārbauda arī faila satura izmaiņu datumu (st_mtime) sakritību
md3 -m      aprēķina un salīdzina MD5 vērtību faila saturam (bez vārda un datuma). 
md3 -h      izvada palīga tekstu par parametriem

Izdrukas formāts (uz stdout):

=== date size filename1
path1/filename1 
path2/filename1 
...

=== date size filename2
path1/filename2 
path2/filename2 
...

Datuma formāts ir tāds pat kā ls -l: (yyyy-mm-dd hh:mm). Piemēram: 2010-09-25 21:45 

Piemēri:

Darbinām md3, salīdzinām arī datumus, izvadam rezultātus log failā.
md3 -d > log

Salīdzinām failus tikai pēc vārdiem
md3

Salīdzinām failus pēc vārdiem un izmaiņu datumiem
md3 -d

Salīdzinām failus pēc satura
md3 -m

Salīdzinām failus pēc satura, vārdiem un datumiem. Izvadam tikai tos, kam visi vienādi.
md3 -d -m
