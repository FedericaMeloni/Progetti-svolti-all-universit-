function [x,k] = jacobi(A,b,tol,kmax,x0)

%questa funzione calcola l'approssimazione di x tramite l'algoritmo di
%Jacobi

%gli input sono :
% A : matrice dei coefficienti
% b : vettore termini noti
% tol : tolleranza 
% kmax : numero massimo di iterazioni
% x0 : vettore iniziale 
%
%gli output sono :
% x : vettore soluzione
% k : numero di iterazioni 


%Calcoliamo le matrici D,E,F per poi ottenere la matrice di itearzion Bj e
%il vetrtore f
D = diag(diag(A));
E = -tril(A,-1);
F = -triu(A,1);

Bj = D\(E+F); %matrice di iterazione
f = D\b; %vettore f
rho = max(abs(eig(Bj))); %raggio spettrale della matrice di iterazione di Jacobi
fprintf('Raggio spettrale della matrice di iterazione Bj: %f\n', rho);

x_old = x0;
x_new = Bj*x_old + f; %prima iterazione del metodo

k = 1;
while (norm(x_new-x_old)>tol*norm(x_old)) && (k<kmax)
    k = k+1; %svolgimento di una nuova iterazione finchè le condizioni del while vengono rispettate
    x_old = x_new; %aggiornamento del vettore
    x_new = Bj*x_old + f;
end

if (k>=kmax) %si è raggiunto numero massimo di iterazioni
    warning('Raggiunto il numero massimo di iterazioni')
end

x = x_new; %soluzione




