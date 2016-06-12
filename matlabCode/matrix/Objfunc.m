% 适应度求解函数（带宽利用率）
% 返回一个数组存储每个个体的适应度，和该代种群的最大适应度

function [obj , maxobj, average] = Objfunc(pop)
    Ctime = [1040 656 656 584 808 808 736 808 736 968 808 504];   %各消息传输时间数组
    tmp = [0 0 0 0 0 0 0 0];                                                              %暂时存放数组，用以比较
    Stmp = [0 0 0 0 0 0 0 0];
    SumCtime = 15120;
    SUM = 0;
    [row,col,popsize] = size(pop);                                                    %pop数组的各维长度
    for i = 1 : popsize          %每代40个个体
        SUM = 0;
        num = [8 8 8 8 8 8 8 8];   
        for j = 1 : col-1             %循环列
            for k =1 : row
                if pop(k,j,i)==0
                    tmp(k) = 0;
                    num(j) = num(j) - 1;
                else
                    tmp(k) = Ctime( pop(k,j,i) );
                end
            end
            [MAX,Index] = max(tmp);   %MAX是该列的最大值，Index是索引
            Stmp(j) = MAX;                   %把该列存入列宽数组 
        end
        for z = 5 : col-1
            SUM =  SUM + Stmp(z) * num(z);
        end
        obj(i) = SumCtime / SUM + 3;        %适应度函数搞定
    end
        maxobj = max(obj);
        average = sum(obj) / 40.0;
end
