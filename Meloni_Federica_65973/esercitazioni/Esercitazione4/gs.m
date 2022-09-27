% calcola l'approssimazione di x tramite l’algoritmo iterativo di Gauss-Seidel


%La funzione accetta in input la matrice dei
%coefficienti A, il vettore dei termini noti b, la tolleranza tol, il numero massimo di
%iterazioni kmax e il vettore iniziale x0. Rende in uscita il vettore soluzione x
%e il numero di iterazioni effettuate k.


function [x,k]= gs(A,b,tol,kmax,x0)


%creiamo la matrice diagonale D e le matrici E e ed F che sono matrici
%diagonali cambiate di segno

D = diag(diag(A)); %matrice che contiene la diagonale di A
E = -tril(A,-1); %matrice che contiene la parte triangolare inferiore di A cambiata di segno e senza diagonale
F = -triu(A,1);%matrice che contiene la parte triangolare superiore di A cambiata di segno e senza diagonale

Bg = (D-E)\F; %calcolo di Bg matrice di iterazione e vettore f
f = (D-E)\b;
rho = max(abs(eig(Bg))); %raggio spettrale
fprintf('Raggio spettrale della matrice di iterazione Bgs: %f', rho);

x_old = x0;
x_new = Bg.*x_old + f;

k = 1; %conta le iterazioni

%il ciclo continua finchè non avviene la convergenza con la tolleranza
%o si raggiunge il numero massimo di iterazioni
while (norm(x_new-x_old)>tol*norm(x_old)) && (k<kmax)
    k = k+1;
    x_old = x_new;
    x_new = Bg.*x_old + f;
end

%è stato raggiunto il numero massimo di iterazioni
if (k>=kmax)
    warning('Raggiunto il numero massimo di iterazioni')
end

x = x_new; %soluzione trovata



