

%chiede in input all'utente una dimensione e la salvi nella variabile n
n= input('inserisci dimensione n: \n');

%crea matrice quadrata A di dimensione n contenente solo elementi uguali a 0
A= zeros(n);

fprintf("\nMatrice A:\n\n");
disp(A);

%crea una matrice quadrata B di dimensione n contenente solo elementi uguali a 1
B= ones(n);

fprintf("\nMatrice B:\n\n");
disp(B);

%crea un vettore colonna z di lunghezza n contenente elementi uguali a 2;
Z=ones(n)*2;%creiamo prima la matrice contenente elementi pari a 2 
z=Z(:,n); %estraiamo il vettore

fprintf("\nVettore z:\n\n");
disp(z);


%prodotto fra matrice A e vettore z
b=A*z;
fprintf("\nStampa vettore b pari al prodotto fra matrice A e vettore z:\n\n");
disp(b);

%prodotto fra vettore trasposto z e matrice B
c=transpose(z)*B;
fprintf("\nStampa vettore c pari al prodotto fra vettore trasposto z e matrice B:\n\n");
disp(c);
