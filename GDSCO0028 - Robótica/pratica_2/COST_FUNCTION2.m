function [J]=COST_FUNCTION2(SRx,SRy,SRteta,SRv,SRw,U,Xref,Yref,PHIref,N1,N2,Nu,L1,L2,L3)
sum_x = 0;
sum_y = 0;
sum_teta = 0;
t=0.01;
for i=N1:1:N2
    if (i <= Nu)
        v = U(1,i);
        w = U(2,i);
    else
        v = U(1,Nu);
        w = U(2,Nu);
    end

    for j = 1:1:4

        cteta = cos(SRteta);
        steta = sin(SRteta);

        if SRteta > pi
            SRteta = SRteta - 2*pi;
        end

        SRteta = SRteta + t*w;
        SRx = SRx + t*(v*cteta);
        SRy = SRy + t*(v*steta);
    end

    sum_x = sum_x + ((Xref(i)-SRx)*(Xref(i)-SRx));
    sum_y = sum_y + ((Yref(i)-SRy)*(Yref(i)-SRy));
    sum_teta = sum_teta+DiffAngle(PHIref(i),SRteta)*DiffAngle(PHIref(i),SRteta);

end

dU = (SRv-U(1,1))^2 + (SRw-U(2,1))^2;
A = L1*(sum_x + sum_y);
B = L2*sum_teta;
U = L3*(dU);
J= A+B+U;
end
