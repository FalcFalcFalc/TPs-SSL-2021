#Punto a, b y c
sed 's/\. */\.\n/g' breve_historia.txt > breve_historia_1.5.txt

sed '/^$/d' breve_historia_1.5.txt > breve_historia_2.txt

#Punto d

printf "Listando oraciones con la palabra 'Guerra':\n\n"

grep -Eo "[A-Z]+([^\.]|[A-Z]\.)*(g|G)+(u|U)+(e|E)+(r|R){2}+(a|A)[^\.]*" breve_historia.txt | sed 's/^/- /'

#Punto e

printf "\n===============================================================\n"
printf "\nListando lineas que empiecen con 'A' y terminen con 's' o 's.':\n\n"

grep -o -E "^A.*(s\.|s)$" breve_historia.txt

#Punto f

printf "\n===============================================================\n"
printf "Cuantas veces aparece la palabra 'peronismo': "

grep -o "peronismo" breve_historia.txt | grep -c .

PRINTF "\n"

grep -Eo "([^\. ]* ){0,5}peronismo([^\. ]* ){0,5}" breve_historia.txt | sed 's/^/\(\.\.\.\) /;s/$/ \(\.\.\.\)/;s/peronismo/\* PERONISMO \*/'

#Punto g

printf "\n===============================================================\n"
printf "\nCuantas oraciones tienen 'Sarmiento' y 'Rosas': "

 grep -oP "[A-Z]([^\.]|[A-Z]\.)*((Sarmiento.*?Rosas)|(Rosas.*?Sarmiento?))[^\.]*\." breve_historia.txt | grep -c .

 grep -oP "[A-Z]([^\.]|[A-Z]\.)*((Sarmiento.*?Rosas)|(Rosas.*?Sarmiento?))[^\.]*\." breve_historia.txt

#Punto h

printf "\n===============================================================\n"
printf "\nListando oraciones con fechas del siglo XIX:\n\n"

grep -o -E "[A-Z]+([^\.]|[A-Z]\.)*+18[0-9]{2}+[^\.]*\." breve_historia.txt | sed 's/^/- /'


#Punto i

 sed 's/^[^ ]*\b //' breve_historia.txt > breve_historia_3.txt

#Punto j

printf "\n===============================================================\n"
printf "\nListando archivos de extensión .txt: "

ls | grep "[^\.]*\.txt"

#FINAL

printf "\n===============================================================\n"
read -p 'Presione Enter para Salir.'