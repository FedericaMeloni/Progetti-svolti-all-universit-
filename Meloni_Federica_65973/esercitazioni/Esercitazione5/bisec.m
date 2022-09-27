function [x,k] = bisec(fun,a,b,tol,kmax)

%help
% fun -< funzione
% a e b estremi intervallo
% tol -> tolleranza
%kmax -> numero max di operaqzioni

%output: x soluzione e k numero iterazioni

fa = fun(a);
fb = fun(b);

%controlla se il segno cambia negli estremi
if (fa*fb > 0)
    error('Intervallo sbagliato!')
end

k = 1;
%calcola punto medio fra gli estremi a e b;
c = (a+b)/2;
fc = fun(c); %valore della funzione nel punto medio

if (abs(fc) < 1e-10) % controlla che il valore assoluto di f di c si avvicina a 0
    x = c; %la radice è c, esci dalla funzione
    return
end

flag = 1;
while (flag~=0)     
    k = k+1;
    if (fa*fc < 0) %se i segni sono discordi
        b = c;
        fb = fc;
    else
        a = c;
        fa = fc;
    end
    c = (a+b)/2; %calcolo il punto medio degli estremi
    fc = fun(c);
    

    %ciclo while, va avanti finchè l'intervallo non non è 
    %più piccolo della tolleranza e non si sono superate
    %il numero massimo di iterazioni
    %controlla che il valore assoluto di f di c sia maggiore di 0
    
    flag = (abs(b-a) > tol) && (k<kmax) && (abs(fc)>1e-10);
end

if (k>=kmax) %numero massimo di terazioni raggiunto
    warning('N. massimo di terazioni raggiunto')
    x = inf;
elseif (abs(fc)<=1e-10) % f di c è molto vicino a 0
    x = c;
else
    x = (a+b)/2;
end


    
    
    


