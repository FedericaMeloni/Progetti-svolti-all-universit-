
%l'utente in serisce tre numeri

a= input('inserisci il numero a: \n');
b= input('inserisci il numero b: \n');
c= input('inserisci il numero c: \n');



a=round(a,3 ,'significant');
b=round(b, 3, 'significant');
c=round(c, 3, 'significant');

% (a + b) + c con operazioni macchina
d1=round( round(a+b, 3, 'significant')+c, 3, 'significant');

% a + (b + c) con operazioni macchina
d2=round(round(b+c, 3, 'significant')+a, 3, 'significant');


%stampiamo i valori ottenuti
disp(' ');
disp("d1 = (a + b) + c = " + d1);
disp("d2 = a + (b + c) = " + d2);



%errori relativi r1 e r2  differenza tra il valore misurato e il valore
%esatto divisi valore atteso

r1= abs(d1 - ( (a + b) + c)) / abs( (a + b) + c);
r2= abs(d2 - (  a + (b + c) )) / abs(  a + (b + c) );

disp(' ');
disp("errori relativi calcolati su d1 e d2 rispettivamente r1 e r2");
disp(" r1: "+r1+"    r2: " +r2);
disp(' ');



