clc
clear all
close all

% simple polygon
% x = [1.5 5 2.0 4.0 1.5 1.5 5.0 5.0];
% y = [0.5 0.5 1.0 3.0 3.5 0.5 2.0 0.5];

% complex polygon

S = 1; Nx = 100; Ny = 60;
Nv = 3;
x = [4.5 7.5 6 4.5];
y = [1.5 1.5 4.5 1.5];

%for i = 1:length(x)
plot(x,y,'*-')
hold on
%end
%X = [0 Nx*S Nx*S 0];
%Y = [0 0 Ny*S Ny*S];
hold on
count = 0;
yc = zeros(Nx*Ny,1);
xc = yc;
for i = 0:Nx % number of cells
    for j = 0:Ny % number of cells
        xx = i * S;
        yy = j * S;
        count = count + 1;
        xc(count) = xx;
        yc(count) = yy;
    end
end
plot(xc,yc,'kd');
xlabel('x');
ylabel('y');
axis image
axis([0 Nx 0 Ny])