function yy = lagrint(x,y,xx)

%help

%Lj(x) = ((x-x1)/(xj-x1))*((x-x2)/(xj-x2))*...*((x-xn)/(xj-xn))
%p(x) = y(1)*L0(x) + y(2)*L1(x) + ... + y(n)*Ln-1(x)

x = x(:);
y = y(:);


%quanti elementi sono contenuti in x e y
n = size(x,1);
%denominatore polinomio caratteristico di lagrange
den = zeros(n,1);

for j = 1:n %creare i denominatori
    den(j) = prod(x(j) - x([1:j-1,j+1:end]));
end

%prendere dimensione della xx
m = size(xx,1);
yy = zeros(m,1);

for i=1:m %
    num = prod(xx(i)-x)./(xx(i)-x); %calcola numeratore
    L = num./den; %elemento del polinomio
    yy(i) = y'*L; 
end

%stampa punti in coordinate x e y e poi una serie di punti con
%coordinate xx e yy uniti da una linea
plot(x,y,'or',xx,yy,'b-')

%legenda
legend('dati da interpolare','polinomio interpolante')




