% ��Ӧ����⺯�������������ʣ�
% ����һ������洢ÿ���������Ӧ�ȣ��͸ô���Ⱥ�������Ӧ��

function [obj , maxobj, average] = Objfunc(pop)
    Ctime = [1040 656 656 584 808 808 736 808 736 968 808 504];   %����Ϣ����ʱ������
    tmp = [0 0 0 0 0 0 0 0];                                                              %��ʱ������飬���ԱȽ�
    Stmp = [0 0 0 0 0 0 0 0];
    SumCtime = 15120;
    SUM = 0;
    [row,col,popsize] = size(pop);                                                    %pop����ĸ�ά����
    for i = 1 : popsize          %ÿ��40������
        SUM = 0;
        num = [8 8 8 8 8 8 8 8];   
        for j = 1 : col-1             %ѭ����
            for k =1 : row
                if pop(k,j,i)==0
                    tmp(k) = 0;
                    num(j) = num(j) - 1;
                else
                    tmp(k) = Ctime( pop(k,j,i) );
                end
            end
            [MAX,Index] = max(tmp);   %MAX�Ǹ��е����ֵ��Index������
            Stmp(j) = MAX;                   %�Ѹ��д����п����� 
        end
        for z = 5 : col-1
            SUM =  SUM + Stmp(z) * num(z);
        end
        obj(i) = SumCtime / SUM + 3;        %��Ӧ�Ⱥ����㶨
    end
        maxobj = max(obj);
        average = sum(obj) / 40.0;
end
