
%chiede in input all'utente una dimensione e la salvi nella variabile n
n= input('inserisci n dimensione matrice:\n');

%crea una matrice quadrata S di dimensione n 
% con elementi pseudo-casuali interi tra 10 e 20

S=randi([10,20],n,n );
fprintf("\n Matrice S: \n");
disp(S);

%verificare se S è simmetrica altrimenti renderla tale
if true==issymmetric(S)
    disp(S);
    fprintf('\n\nLa matrice S di dimensione %d è simmetrica\n', n);
else
    fprintf('La matrice S di dimensione %d non è simmetrica.\n', n);
    S= (S+transpose(S))/2; %rendiamo S simmetrica
    S=round(double(S)); %rendiamo la matrice intera
 
    fprintf(" Stampa della matrice S dopo essere stata resa simmetrica:\n");
    disp(S);
end    

fprintf("Autovalori della matrice S\n");
%autovalori matrice memorizzari nel vettore d
d=eig(S);
disp(d);

%calcola la norma con indice 1, 2 e ∞ del vettore d
fprintf(" Norme con indice 1, 2 e infinito del vettore d (il vettore d contiene gli autovalori della matrice): \n");
disp(norm(d,1));
disp(norm(d));
disp(norm(d,inf));
