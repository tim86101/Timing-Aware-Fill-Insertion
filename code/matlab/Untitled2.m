clear
clf
[ID,x1,y1,x2,y2,i1,i2,i3]=textread('test1.fill','%d%d%d%d%d%d%d%s');
width=x2-x1;
height=y2-y1;
a=[x1,y1,width,height];
for i = 1 : length(x1)
    rectangle('Position',a(i,:))
end
print('-dpng','«Ó­ô')