
%prende in input un numero

x= input('inserire un numero fra 0 e 50: \n');

%se il numero è all'interno del range calcola e stampa la sua radice
%quadrata
%verifica che il numero inserito abbia un valore tra 0 e 50
if(x>0 & x<50)
   y=sqrt(x);
   disp("radice del numero inserito: " +y);
   
else
    %se il numero inserito è al di fuori del range stampa un avviso
   disp('il numero inserito è al di fuori del range (0 - 50)');
end
