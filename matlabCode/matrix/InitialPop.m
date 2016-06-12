% 初始化种群
% pop_size:      population size
% BC  :             basic circle
% T  :                matrix Time
% row :             line numbers
% col :               column numbers
function pop = InitialPop (row , col , pop_size)
    pop = zeros ( row , col , pop_size);
    for p = 1 : pop_size
        times = [0 0 4 0 4 2 0 2 4 1 2 1] ;
        gap =    [1 1 2 1 2 4 1 4 2 8 4 8];
        for i=1:8
            pop(i,1,p) = 1;
            pop(i,2,p) = 2;
            pop(i,3,p) = 4;
            pop(i,4,p) = 7;
        end
    %    f = [0 0 0 0 0 0 0 0 0 0 0 0];
        for j = 5 : col - 1
             recol = 0;
             ferror = 0;
             flag = [0 0 0 0 0 0 0 0];
             f = [0 0 0 0 0 0 0 0 0 0 0 0];
             while Judgement(times,recol) == 1
              %   if judge == 0
              %       break;
              %   end
                 mes  = randsrc(1,1,[3 5 6 8 9 10 11 12]);
                 
                 if times(mes) > 0 && times(mes) <= (row-recol)    %判断第一行从何开始
                     for k=1:8
                         if flag(k) == 0
                             i = k;
                             break;
                         end
                     end
                 else
                     continue;
                 end
                 
                 if gap(mes) * (times(mes) - 1) + i > row
                     f(mes) = f(mes) +1;
                     for c=1:12
                         if f(c) >= 100
                             ferror = 1;
                         end
                     end
                     if ferror == 1
                         break;
                     else
                         continue;
                     end
                 end
                 
                 while times(mes) > 0
                     pop(i,j,p) = mes;
                     recol = recol+1;
                     times(mes) = times(mes)-1;
                     flag(i) =1 ;
                     i = i+gap(mes);
                 end
             end
        end
    end
end
                 
function  judge = Judgement(times,num)    %判断函数
    judge = 0;
    Curmes = [8 8 4 8 4 2 8 2 4 1 2 1];
    for i = 1:12
        if times(i) > 0 && Curmes(i) <= 8 - num
            judge = 1;
        end
    end
end
                 
          
                 