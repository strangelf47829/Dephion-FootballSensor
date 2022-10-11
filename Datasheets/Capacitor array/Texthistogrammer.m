clc
s = 2;
siz = 11000;
files = zeros(s,siz);

resolution = 50;
minimum = 50;
maximum = 4000;



for c=1:s
   fi = readmatrix("measurements_ball_" + c + ".txt");
   files(c, 1:size(fi,2)) = fi;
end

figure
hold on
for c=1:s
    
    gig = files(c,:);
    indicies = gig<minimum | gig > maximum;
    gig(indicies) = [];
    histogram(gig,round(max(gig)/resolution))


end

title("Histogram of raw sensor data (" + minimum + " -> " + maximum + ")")
xlabel("Raw Sensor Data Bin")
ylabel("Count per bin")
legend('Shot data', 'Move data', 'Fast', 'Mixed');