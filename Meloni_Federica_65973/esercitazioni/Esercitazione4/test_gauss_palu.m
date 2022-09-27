
%reallochiamo il vettore err
err= zeros(10,1);
i=0;

%crea 10 matrici di dimensione tra 100 e 1000 con passo 100
for n= 100:100:1000
    i=i+1;
    A=rand(n);


%imporre una soluzione x di elementi pari a uno
%e creare il vettore dei termini noti b
x=ones(n,1);
b=A*x;
 
%chiamare la funzione gauss_palu.m per ottenere le matrici L e U e P
%ottenere la soluzione x1
[P,L,U]=gauss_palu(A);
Pb=P*b;
y=L\Pb;
x1= U\y;

%calcola errore relativo
err(i)=norm(x1-x)/norm(x1);

%Si stampi a video con il comando fprintf, per
%ogni valore della dimensione della matrice, l%errore relativo e il 
% condizionamento della %matrice A


fprintf('dimensione matrice: %d      errore relativo: %e     condizionamento: %f\n',n,err(i),cond(A));

end