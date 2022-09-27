
%La function deve prendere in input la funzione fun, il valore
%m della pendenza della retta, il valore iniziale x0, la tolleranza tol e il numero massimo
%di iterazioni kmax. La function deve restituire come output l%approssimazione x della
%radice e il numero di iterazioni k effettuate.



function [x,k]=corde(fun,m,x0,tol,kmax)


% I parametri della funzione sono:
%       x0 -> valore iniziale
%       m -> il coefficiente angolare che verrà mantenuto costante durante
%            tutto l'algoritmo
%       fun -> funzione di cui valutare uno zero
%       tol -> tolleranza per la radice
%       kmax -> limite superiore al numero di iterazioni
%
%   I valori di ritorno sono:
%       x -> la soluzione trovata
%       k -> il numero di iterazioni impiegate per ottenere la soluzione
%      



k = 0;
f0 = fun(x0); %valore assunto dalla funzione

if (abs(f0) < 1e-10) %se il valore assoluto di f0 si avvicina a 0 da sinistra
    x = x0; %il valore iniziale è la radice
    return
end

fd = m(x0); %valore derivata in x0
%  Denominatore di   x k-esimo - f(x)/m k-esimo

if (abs(fd)<1e-10) %se il valore assoluto di f0 si avvicina a 0 daq sinistra
    warning('La derivata si annulla in x0! Cambia punto di partenza');
end
   
k = 1;
x_new = x0 - (f0/fd); %prima iterazione

flag = 1;
while flag %flag è un indicatore d'arresto
    k = k+1; %numero di iterazioni 
    x0 = x_new; %punto di partenza per l'iterazione seguente
    f0 = fun(x0); %valore assunto dalla funzione nel nuovo punto
   
    if (abs(fd)<1e-10)
        warning('La derivata si annulla nel punto! Cambia x0');
    end  
    x_new = x0 - (f0/fd); %risultato dell'iterazione

    %si controlla che il valore non si avvicini troppo alla tolleranza e
    %che non sia raggiunto il numero massimo di iterazioni
    flag = (abs(x_new-x0)>tol*abs(x0)) && (k<kmax) && (abs(fun(x_new))>1e-10); 
end

if (k>=kmax) %numero massimo di iterazioni raggiunto
    warning('N. massimo di iterazioni raggiunto');
    x = inf;
else
    x = x_new;
end
    
