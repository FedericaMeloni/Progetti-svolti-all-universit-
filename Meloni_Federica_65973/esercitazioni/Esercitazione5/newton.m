function [x,k] = newton(fun,fund,x0,tol,kmax)

%help
% fun -< funzione
%fund-> derivata
% x0-> punto di partenza
% tol -> tolleranza
%kmax -> numero max di operaqzioni

%output: x soluzione e k numero iterazioni

k = 0;
f0 = fun(x0);

if (abs(f0) < 1e-10) %se il valore assoluto di f0 si avvicina a 0 daq sinistra
    x = x0;
    return
end

fd = fund(x0); %valore derivata in x0, Denominatore di   x k-esimo - f(x)/'f(x)

if (abs(fd)<1e-10) %se il valore assoluto di f0 si avvicina a 0 daq sinistra
    warning('La derivata si annulla in x0! Cambia punto di partenza');
end
   
k = 1;
x_new = x0 - (f0/fd);

flag = 1;
while flag %flag è un indicatore d'arresto
    k = k+1;
    x0 = x_new;
    f0 = fun(x0);
    fd = fund(x0);  %valore derivata in x0, Denominatore di   x k-esimo - f(x)/'f(x)
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
    
