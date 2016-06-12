function  Judge(num)    %ÅÐ¶Ïº¯Êý
global judge;
    Curmes = [4 4 2 2 4 1 2 1];
    for i = 1:8
        if Curmes(i) ~= 0 && Curmes(i) < 8 - num
            judge = 1;
        else
             judge =  0;
        end
    end
end