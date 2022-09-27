function yy = canint(x,y,xx)

%help

%facciamo in modo che x e y siano vettori colonna
x = x(:);
y = y(:);

%quanti elementi sono contenuti in x e y
n = size(x,1);

%costruiamo la matrice di vandermont
X = zeros(n);

for j = 1:n %per tutte le colonne della matrice
    X(:,j) = x.^(j-1); 
end

a = X\y;

m = size(xx,1);
yy = zeros(m,1);


%p = a0*x^0 + a1*x^1 + ... + an*x^n in teoria
%p = a1*x^0 + a2*x^1 + ... + a(n)*x^(n-1) su Matlab

for j = 1:m
    s = 0;
    for i = 1:n
        s = s + a(i)*(xx(j)^(i-1));
    end
    yy(j) = s;
end

%stampa punti in coordinate x e y e poi una serie di punti con
%coordinate xx e yy uniti da una linea
plot(x,y,'or',xx,yy,'b-')

%legenda
legend('dati da interpolare','polinomio interpolante')








