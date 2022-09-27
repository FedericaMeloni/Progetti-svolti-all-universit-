
%chiede in input all'utente una dimensione e la salvi nella variabile n
n= input('inserisci dimensione matrice: \n');

%crea una matrice quadrata A di dimensione n contenente solo elementi uguali a 0
R=rand(n);

%estrae diagonale di R e la inserisce nel vettore x
x=diag(R);

%crea una matrice D che contiene il vettore x come diagonale
D=diag(x,0); %0 rappresenta la diagonale principale

%estrarre la parte triangolare superiore e inferiore  di R 
U=tril(R);
L=triu(R);

fprintf("\nMatrice D:\n");
disp(D);

%verifichi  se D è diagonale, questo è vero se, isdiag(D) è pari a 1:

if isdiag( D )==1
     disp('D è diagonale');
    
else %isdiag(D) ritorna 0 quindi D non è una matrice diagonale
     disp('D non è diagonale');
end 


%U è triangolare superiore se istril(U) è pari a 1, se è pari a 0 non lo è
if istril(U)
    disp('U è triangolare superiore');
else 
    disp('U non è triangolare superiore');
end    

%L è triangolare INFERIORE se istriu(L) è pari a 1, se è pari a 0 non lo è
if istriu(L)
    disp('L è triangolare inferiore');
else 
    disp('L non è triangolare inferiore');
end 


