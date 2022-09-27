function [L,U] = gauss_lu(A)

%questa funzione rende la fattorizzazione A=LU di una matrice senza struttura
%l'input e' la matrice da fattorizzare
%gli output sono le matrici L e U tali che A = L*U

format rat

[m,n] = size(A);

if (m~=n)
    error('Matrice non quadrata!')
end

if (abs(det(A)) < 1e-14)
    error('Determinante molto piccolo')
end

L = zeros(n);
L = L + diag(ones(n,1));

%stesso risultato se L = eye(n);

for k = 1:n-1
    for i = k+1:n
    	m = A(i,k)/A(k,k);
    	A(i,:) = A(i,:) - m*A(k,:);
    	L(i,k) = m;
    end
    %pause
end

U=A;


