%The Boundary Co-ordinates of water body which is to be analyzed is marked.
x = [76.898800 76.898800 76.899000 76.899000 76.898800];
y = [10.906520 10.906120 10.906120 10.906520 10.906520];

k1 = ge_plot(x,y,...
    'lineWidth', 1,...
             'lineColor','FF000000');         
kml = 'Boundary.kml';
ge_output(kml,k1,...
              'name',kml);
          winopen(kml);
%% Data Extraction, Preparation & Analyze

% The below source code extract the random data from the data base and
% analyze the corresopnding lattitude and longitude co-ordinate of each data.

x2 = [76.898850, 76.898950];
y2 = [10.906220, 10.906420];    

data = load('Temp.txt');
ph = data(:,1);
lat = data(:, 3);
lon = data(:, 4);
%% This is to estimate the range of Co-ordinates

% To determint the end points of the co-ordinates
lat_max = max(lat);
lon_max = max(lon);
lat_min = min(lat);
lon_min = min(lon);

%% Here we assign each data to its corresponding grid points. 

lat_ascending = lat;
lon_ascending = lon;

for l1 = 1 :size(lat,1)
    if lat_ascending(l1) > lat_ascending(l1+1)
        
            temp = lat(l1);
            lat_ascending(l1) = lat_ascending(l1+1);
            lat_ascending(l1+1) = temp;
            
    end
end

for l2 = 1 :size(lon,1)
    if lon_ascending(l2) > lon_ascending(l2+1)
        
            temp = lat(l2);
            lat_ascending(l2) = lat_ascending(l2+1);
            lat_ascending(l2+1) = temp;
            
    end
end
    
l1 = 1;

while l1 < size(lon,1);
for l2 = 1 : size(lon,1)
        if lon_ascending(l1) == lon(l2) 
            ph_new(l1) = ph(l2);
            l1 = l1+1;           
        end 
end
end         


 j = 1;
for i = 1 : size(ph_new)
    
    tagged_data(j, 1) = ph_new(i);
    j = j+1;
    
end

m = 1;
for k =1 : 34
    for l = 1 : 17
        y(k,l) = tagged_data(m);
        m = m+1;
    end
end

%% Limit scaling  

% This is the last stage, where we just simply display color for the small
% grids containing datas. This is what a choro pleth map is and it is done
% in order to provide meaninful interpretation from the raw data for the
% third party viewers( Users)



cLimLow = 31;
cLimHigh = 32;
% Make the coustom colormap
cmap = [0,0,1;0,1,0;1,0,0];
alphaMatrix = ones(size(data))*0.1;

kml2 = 'monitoring.kml';
output = ge_imagesc(x2,y2,y, 'cLimLow', cLimLow, 'cLimHigh', cLimHigh);
ge_output(kml2,output);
winopen(kml2);


