%effetua dei test sulla risoluzione di un equazione
%nonlineare. Il test dovrà usare i dati presenti nelle tabelle 
% 7.1, 7.2, 7.3 e 7.4 del libro di testo

%funzioni da risolvere
fun1=@(x) x.^(2)-2;
fun2=@(x) exp(x)-2;
fun3=@(x) (1./x)-3;
fun4=@(x)(x-3).^3;

%derivate delle funzioni 
m1 = @(x) 2.*x;
m2 = @(x) exp(x);
m3 = @(x) -x.^(-2);
m4 = @(x) 3.*(x-3).^2;

%soluzione delle funzioni da usare per il calcolo dell'errore
a1 = sqrt(2);
a2 = log(2);
a3 = 1/3;
a4 = 3;

%tabella 7.1 Metodo delle bisecanti
kmax=100; %massimo iterazioni
tol=1e-8; %tolleranza

%bisec(fun,a,b,tol,kmax)
%fun è la funzione da risolvere, a e b gli estremi dell'intervallo, tol la
%tolleranza e kmax il massimo di iterazioni

fprintf("\n- Metodo di Bisezione:\n");
a = 0; b = 2; %intervallo 

%e = abs(x-a1) è il calcolo dell'errore

[x,k] = bisec(fun1, a, b, tol, kmax);
e = abs(x-a1);
fprintf('Prima funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k] = bisec(fun2, a, b, tol, kmax);
e = abs(x-a2);
fprintf('Seconda funzione     radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k] = bisec(fun3, a, b, tol, kmax);
e = abs(x-a3);
fprintf('Terza funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k] = bisec(fun4, 4/3, 10/3, tol, kmax);
e = abs(x-a4);
fprintf('Quarta funzione      radice:  %f     passi: %d     errore: %e\n', x,k,e);


%tabella 7.2 Metodo di Newton
kmax=100;

% newton(fun,fund,x0,tol,kmax)
%fun è la funzione da risolvere, fund coefficente angolare di fun, x0, tol la
%tolleranza e kmax il massimo di iterazioni

fprintf("\n- Metodo di Newton:\n");

[x,k]=newton(fun1,m1,200,tol,kmax);
e = abs(x-a1);
fprintf('Prima funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=newton(fun2,m2,200,tol,kmax);
e = abs(x-a2);
fprintf('Seconda funzione     radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=newton(fun3,m3,0.1,tol,kmax);
e = abs(x-a3);
fprintf('Terza funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=newton(fun4,m4,2.9,tol,kmax);
e = abs(x-a4);
fprintf('Quarta funzione      radice:  %f     passi: %d     errore: %e\n', x,k,e);


%tabella 7.3
%corde(fun,m,x0,tol,kmax)
%fun è la funzione da risolvere, m coefficente angolare di fun, x0, tol la
%tolleranza e kmax il massimo di iterazioni

fprintf("\n- Metodo delle Corde:\n");

kmax=2000; %iterazioni massime

[x,k]=corde(fun1,m1,200,tol,kmax);
e = abs(x-a1);
fprintf('Prima funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=corde(fun2,m2,200,tol,kmax);
e = abs(x-a2);
fprintf('Seconda funzione     radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=corde(fun3,m3,0.1,tol,kmax);
e = abs(x-a3);
fprintf('Terza funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=corde(fun4,m4,2.9,tol,kmax);
e = abs(x-a4);
fprintf('Quarta funzione      radice:  %f     passi: %d     errore: %e\n', x,k,e);


%tabella 7.4
%secanti(fun,x0,x1,tolx,kmax)
%fun è la funzione da risolvere, m coefficente angolare di fun, x0, tol la
%tolleranza e kmax il massimo di iterazioni
kmax=100;

fprintf("\n- Metodo delle Secanti:\n");

[x,k]=secanti(fun1,1,2,tol,kmax);
e = abs(x-a1);
fprintf('Prima funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=secanti(fun2,2,3,tol,kmax);
e = abs(x-a2);
fprintf('Seconda funzione     radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=secanti(fun3,2,3,tol,kmax);
e = abs(x-a3);
fprintf('Terza funzione       radice:  %f     passi: %d     errore: %e\n', x,k,e);

[x,k]=secanti(fun4,1,2,tol,kmax);
e = abs(x-a4);
fprintf('Quarta funzione      radice:  %f     passi: %d     errore: %e\n', x,k,e);
