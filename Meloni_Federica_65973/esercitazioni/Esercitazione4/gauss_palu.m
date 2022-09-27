function [P,L,U] = gauss_palu(A)

%questa funzione rende la fattorizzazione PA=LU di una matrice senza struttura
%l'input e' la matrice da fattorizzare
%gli output sono le matrici P, L e U tali che P*A = L*U

[m,n] = size(A);

if (m~=n)
    error('Matrice non quadrata!')
end

if (abs(det(A)) < 1e-14)
    error('Determinante molto piccolo')
end

L = zeros(n);
P = eye(n);

for k = 1:n-1
    [~,pos] = max(abs(A(k:n,k)));
    r = pos + k - 1;
    A([k r],:) = A([r k],:);
    P([k r],:) = P([r k],:);
    L([k r],:) = L([r k],:);
    for i = k+1:n
    	m = A(i,k)/A(k,k);
    	A(i,:) = A(i,:) - m*A(k,:);
    	L(i,k) = m;
    end
    %pause
end

U=A;
L = L + diag(ones(n,1));