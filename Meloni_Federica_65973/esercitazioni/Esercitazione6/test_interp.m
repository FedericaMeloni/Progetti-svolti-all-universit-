%il test con le due forme diverse del polinomio interpolante
%(forma canonica e forma di Lagrange), con due modi diversi di scegliere le ascisse di interpolazione (punti equispaziati o zeri del polinomio di Chebychev) e due diverse funzioni
%da interpolare:



%funzioni da risolvere
f1=@(x) 1./(1+25.*x.^2);
f2= @(x) sin(2.*pi.*x);

%---------------------------------

n=30; %numero di punti
m=100; %numero di ascisse per disegnare il grafico
k = [0:1:n]'; % vettore riga con entrate da 0 a n trasposto con passo 1

%inserire su che funzione eseguire il test

fprintf("\nPer selezionare il test da eseguire verrà chiesto prima se usare punti equidistanti o \nnodi di interpolazione di Chebychev, poi su quale delle due funzioni eseguire il test" + ...
    "\ne infine se usare il metodo di Lagrange o la forma Canonica\n\n");

a = input('\nPer usare i punti equidistanti inserire 1       per usare nodi di interpolazione di Chebychev 2 o un qualsiasi altro numero:');

switch a
    case 1
       fprintf("\n- Punti Equidistanti\n");  
       x=linspace(-pi,pi,n)'; %campionamento del segmento da -p1 a pi prendendo n punti, utilizzo del metodo dei punti equidistanti
       b = input('\nInserisci 1 per eseguire il test sulla prima funzione, un qualsiasi altro numero per eseguirlo sulla funzione due: ');

    otherwise
        fprintf("\n- Polinomio di Chebychev\n"); 
        x=cos(((2*k+1)*pi)./(2*n+2)); %zeri del polinomio di Chebychev
        b = input('\nInserisci 1 per eseguire il test sulla prima funzione, un qualsiasi altro numero per eseguirlo sulla funzione due: ');     
  
end

switch b
   case 1
      fprintf("\n- Prima funzione\n"); 
      y = f1(x); %ricavo il valore della prima funzione in x
      xx=linspace(x(1),x(end),m)';
      z= input("\nInserisci 1 per effettuare il test con l'interpolazione nella forma canonica, un altro numero per eseguirlo con l'interpolazione nella forma di lagrange:");
  
    otherwise 
       fprintf("\n- Seconda funzione\n");  
       y = f2(x); %ricavo il valore della seconda funzione in x
       xx=linspace(x(1),x(end),m)';
       z= input("\nInserisci 1 per effettuare il test con l'interpolazione nella forma canonica, un altro numero per eseguirlo con l'interpolazione nella forma di lagrange:");
end   

if(z==1)
    fprintf("\n- Forma Canonica\n");
    yy = canint(x,y,xx); %test con la forma canonica
else
    fprintf("\n- Forma di Lagrange\n");
    yy = lagrint(x,y,xx); %test con la forma di lagrange
end        


