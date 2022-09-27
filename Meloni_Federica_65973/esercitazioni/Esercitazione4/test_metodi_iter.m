
%reallochiamo il vettore err che conterrà gli errori delle 10 matrici
%un arrai per gauss - seidel  e uno per jacobi.
errG= zeros(10,1);
errJ= zeros(10,1);
i=0;

fprintf("\nTabella che contiene raggio spettrale della matrice di iterazione per entrambi i metodi, dimensione della matrice e errore relativo calcolato col metodo Gauss-Seidel e Jacobi\n");

%crea 10 matrici di dimensione tra 100 e 1000 con passo 100
for n= 100:100:1000
    i=i+1;
    A=6*rand(n);
   
    %renderla streattamente diagonalmente dominante
    % S= diag(A);
    %A=A+diag(100*S);
    
    A = A - diag(diag(A)); %ottengo una matrice con elementi in diagonale nulli
    S = abs(A)*ones(n,1); 
    A = A+6*diag(S); %matrice strettamente diagonalmente dominante
  

%imporre una soluzione x di elementi uguali a uno e
%creare il vettore dei termini noti b
x=ones(n,1);
b=A.*x;

% chiamare le funzioni jacobi.m e gs.m
%per ottenere le approssimazioni della soluzione xj e xgs
 
tol= 1e-6; % impostiamo la tolleranza 
kmax=200; %massimo di iterazioni 

x0 = zeros(n,1);%vettore iniziale 

[xj,kj] = jacobi(A,b,tol,kmax,x0);
[xgs,kgs]= gs(A,b,tol,kmax,x0);

%calcolare gli errori relativi tra la soluzione
%vera x e quelle approssimate
errJ(i)=norm(x-xj)/norm(x);
errG(i)=norm(x-xgs)/norm(x);

%Si stampi a video con il comando fprintf, una tabella
%che stampi per ogni valore della dimensione della matrice, l%errore relativo e il raggio
%spettrale della matrice di iterazione per ognuno dei due metodi.

fprintf("\ndimensione matrice: %d         \nerrore relativo(Gauss-Seidel): %3.3e    passi(Gauss_Seidel): %d   \nerrore relativo(Jacobi): %3.3e          passi(Jacobi):%d \n\n ", n,errG(i),kgs,errJ(i),kj);
 
end