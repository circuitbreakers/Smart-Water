%boundary plots

x = [80.225640 80.225740 80.225740 80.225640 80.225640];
y = [12.910630 12.910630 12.910570 12.910570 12.910630];


k1 = ge_plot(x,y,...
    'lineWidth', 1,...
             'lineColor','FF000000');
         
         mahin = 'swimming pool.kml';
ge_output(mahin,k1,...
              'name',mahin);
          winopen(mahin);
          
          
%% data part
            
x2 = [80.225665, 80.225715];
y2 = [12.910585, 12.910615];    

data = load('temperature_tech_mahindra.txt');
ph = data(:,1);


 j = 1;
for i = 1 : 2 : size(ph)
    gh(j, 1) = ph(i);
    j = j+1;
    
end


m = 1;

for k =1 : 34
    for l = 1 : 17
        y(k,l) = gh(m);
        m = m+1;
    end
end

%% Limit scaling  
cLimLow = 27;
cLimHigh = 30;





% make the custom colormap
cmap = [0,0,1;0,1,0;1,0,0];
%cmap = 'winter';
alphaMatrix = ones(size(data))*0.1;



kml22 = 'part.kml';
output = ge_imagesc(x2,y2,y, 'cLimLow', cLimLow, 'cLimHigh', cLimHigh);


ge_output(kml22,output);

winopen(kml22);

