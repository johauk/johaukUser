#!/usr/bin/perl -w

# script to generate cutflow table in HTML format
# from TrigReports with statistical errors
#
# pipe output to htm file with command " cutFlow.pl > output.htm "
#
# You have to configure the first variables in the script to your needs:
#  - target lumi: luminosity of the data, mc is normalized to this
#  - textfiles containing the TrigReport cutflows, real data has to be last
#  - weights: for MC samples -> length of list is one shorter than 
#    file list if real data are included
#  - modules: names of the modules which's passed evt number you want
#    to appear in the table

# integrated luminosity of data in /pb
my $lumi = 1091.0;

# input files (last file is for data)
my @files = (#"mc/qcd.txt",
             #"mc/singletopS.txt",
	     #"mc/singletopT.txt",
	     #"mc/singletopTw.txt",
	     "mc/ttbar.txt",
	     #"mc/wmunu.txt",
	     #"mc/wtaunu.txt",
	     #"mc/ww.txt",
	     #"mc/wz.txt",
	     #"mc/zz.txt",
	     #"mc/ztautau.txt",
	     ##"mc/zmumu.txt",
	     "mc/zmumuUdsc.txt",
	     "mc/zmumuB.txt",
	     "data/allData.txt",
	    );

# cross section over number of events	    
my @weights = (#$lumi*296600.*0.2855/29434562.,
               #$lumi*4.6/494967.,
	       #$lumi*64.6/489417.,
	       #$lumi*10.6/484060.,
	       $lumi*157.5/3581947.,
	       #$lumi*10438./5038640.,
	       #$lumi*10438./4773750.,
	       #$lumi*4.51/110000.,
	       #$lumi*0.61/110000.,
	       #$lumi*7.4/2108608.,
	       #$lumi*3048./2329439.,
	       ##$lumi*3048./2329439.,
	       $lumi*3048./36277961.,
	       $lumi*3048./36277961.,
	      ); #for data no weight is needed so 
	         #weight array is 1 shorter then files array	    

# modules which you want to appear in cutflow
my @modules = ("EventCounterStep0",
	       "EventCounterStep1a",
	       "EventCounterStep1b",
	       "EventCounterStep1",
	       "EventCounterStep2a",
	       "EventCounterStep2b",
	       "EventCounterStep2c",
	       "EventCounterStep2d",
	       "EventCounterStep2e",
	       "EventCounterStep2f",
	       "EventCounterStep2g",
	       "EventCounterStep2",
	       "EventCounterStep3a",
	       "EventCounterStep3b",
	       "EventCounterStep3c",
	       "EventCounterStep3d",
	       "EventCounterStep3e",
	       "EventCounterStep3",
	       "EventCounterStep4a",
	       "EventCounterStep4b",
	       "EventCounterStep4c",
	       "EventCounterStep4d",
	       "EventCounterStep4",
	       "EventCounterStep5",
	       "EventCounterStep6a",
	       "EventCounterStep6",
	       "EventCounterStep7a",
	       "EventCounterStep7b",
	       "EventCounterStep7c",
	       "EventCounterStep7",
	       
	       "EventCounterStepZVetoLow3",
	       "EventCounterStepZVetoLow4a",
	       "EventCounterStepZVetoLow4b",
	       "EventCounterStepZVetoLow4c",
	       "EventCounterStepZVetoLow4d",
	       "EventCounterStepZVetoLow4",
	       "EventCounterStepZVetoLow5",
	       "EventCounterStepZVetoLow6a",
	       "EventCounterStepZVetoLow6",
	       "EventCounterStepZVetoLow7a",
	       "EventCounterStepZVetoLow7b",
	       "EventCounterStepZVetoLow7c",
	       "EventCounterStepZVetoLow7",
	       "EventCounterStepZVetoHigh3",
	       "EventCounterStepZVetoHigh4a",
	       "EventCounterStepZVetoHigh4b",
	       "EventCounterStepZVetoHigh4c",
	       "EventCounterStepZVetoHigh4d",
	       "EventCounterStepZVetoHigh4",
	       "EventCounterStepZVetoHigh5",
	       "EventCounterStepZVetoHigh6a",
	       "EventCounterStepZVetoHigh6",
	       "EventCounterStepZVetoHigh7a",
	       "EventCounterStepZVetoHigh7b",
	       "EventCounterStepZVetoHigh7c",
	       "EventCounterStepZVetoHigh7",
	       
	       "EventCounterStepNoMet7a",
	       "EventCounterStepNoMet7b",
	       "EventCounterStepNoMet7c",
	       "EventCounterStepNoMet7",
	       
	       "EventCounterStepZVetoLowNoMet7a",
	       "EventCounterStepZVetoLowNoMet7b",
	       "EventCounterStepZVetoLowNoMet7c",
	       "EventCounterStepZVetoLowNoMet7",
	       "EventCounterStepZVetoHighNoMet7a",
	       "EventCounterStepZVetoHighNoMet7b",
	       "EventCounterStepZVetoHighNoMet7c",
	       "EventCounterStepZVetoHighNoMet7",
	       
	       "EventCounterStepOneBSsvHeMJet7a",
	       "EventCounterStepOneBSsvHpTJet7a",
	       "EventCounterStepZVetoLowOneBSsvHeMJet7a",
	       "EventCounterStepZVetoLowOneBSsvHpTJet7a",
	       "EventCounterStepZVetoHighOneBSsvHeMJet7a",
	       "EventCounterStepZVetoHighOneBSsvHpTJet7a",
	       
	       "EventCounterStepNoMetOneBSsvHeMJet7a",
	       "EventCounterStepNoMetOneBSsvHpTJet7a",
	       "EventCounterStepZVetoLowNoMetOneBSsvHeMJet7a",
	       "EventCounterStepZVetoLowNoMetOneBSsvHpTJet7a",
	       "EventCounterStepZVetoHighNoMetOneBSsvHeMJet7a",
	       "EventCounterStepZVetoHighNoMetOneBSsvHpTJet7a",
              );
	      	      	    
# counter for summed stats	     
my @countSum;
my @countSumErrorSquare;
# initiate all couters with zero
foreach (@modules){
  push(@countSum,0);
  push(@countSumErrorSquare,0);  
}
	     
#print header for html
print "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01//EN\"";
print " \"http://www.w3.org/TR/html4/strict.dtd\">\n";
print "<html>\n";
print "<head>\n";
print "<title>Cutflow Table</title>\n";
print "<meta http-equiv=\"content-type\" content=\"text/html; charset=ISO-8859-1\">\n";
print "<style type=\"text/css\">\n";
print "  body  { background-color:#bfbfff;}\n";
print "  table { background-color:#dfdfff; border:1px solid #000; width:100%;text-align:right;}\n";
print "  th    { border:1px solid #000; width:250px; white-space:nowrap; background-color:#ffff7f;}\n";
print "  td    { border:1px solid #000; white-space:nowrap; }\n";
print "  #ttbarmumu  { background-color:#CC0000;}\n";
print "  #ttbartaumu { background-color:#CC0000;}\n";
print "  #ttbarbg    { background-color:#CC6666;}\n";
print "  #singletops { background-color:#990099;}\n";
print "  #singletopt { background-color:#990099;}\n";
print "  #singletoptw{ background-color:#FF00FF;}\n";
print "  #vvjets     { background-color:#FFFFFF;}\n";
print "  #ztautau_mad{ background-color:#33CCFF;}\n";
print "  #ztautau_pyt{ background-color:#33CCFF;}\n";
print "  #zmumu_mad  { background-color:#3366FF;}\n";
print "  #zmumu_pyt  { background-color:#3366FF;}\n";
print "  #dymumu     { background-color:#3366FF;}\n";
print "  #wjets      { background-color:#33CC33;}\n";
print "  #qcd        { background-color:#FFFF00;}\n";
print "  #mcsum      { background-color:#ffff7f;}\n";
print "  #data       { background-color:#ffff7f;}\n";
print "</style>\n";
print "</head>\n";
print "<body>\n";
print "<h1>Cutflow</h1>\n";
print "<h3>integrated lumi = ", $lumi, " pb<sup>-1</sup></h3>\n";
print "<table>\n";
print "<tr>\n  <th></th>";  

# print table header
foreach my $module (@modules) {
  print "  <th>$module</th>";
}; # end loop over modules    
print "</tr>\n";

# loop over all files
for( my $i=0; $i<@files-1; $i++) { #files-1 because it is not looped over datafile 

  my $file = $files[$i];  
  #skip if file does not exist
  if(!-e $file) {next;}  
  open(IN,$file);
    
  # get event weight for file i from array
  my $weight = $weights[$i];
  
  # print filelabel into first column  
  my $filelabel = substr($file,0,index($file,"."));
  print "<tr id=\"$filelabel\">\n  <td>$filelabel</td>";  
  
  # loop over all modules  
  for( my $j=0; $j<@modules; $j++) {

    my $module = $modules[$j];    
  
    # find lines in summary table
    my @modline = `grep TrigReport $file | grep -w $module`;
    # extract number from line
    if($modline[0] =~ /TrigReport\s+\d+\s+\d+\s+\d+\s+(\d+).*/) {
      my $passed = $1;
      if($passed>0){    
        #statistical error is just squareroot        
        my $staterror = sqrt($passed);
        #weight eventnumbers and statistic errors
        $passed *= $weight;
        $staterror *= $weight;
	
	$countSum[$j] += $passed;
	$countSumErrorSquare[$j] += $weight*$passed;
      
        print "  <td>";
        printf("%.2f", $passed);
        print " +- ";
        printf("%.2f", $staterror);
        print "</td>";
      }
      else{ # if event number is zero
        print "  <td>-</td>";       
      }
    } else {
      print "  <td>ERROR: didn't find module $module from $file</td>";
    };         
  }; # end loop over modules    
  close IN;
  print "\n</tr>\n";
}; # end loop over files


# table line for added stats
print "<tr id=\"mcsum\">\n  <td>Sum</td>";
for( my $i=0; $i<@modules; $i++) {
  print "  <td>";
  printf("%.2f", $countSum[$i]);
  print " +- ";
  printf("%.2f", sqrt($countSumErrorSquare[$i]));
  print "</td>";
}; # end loop over modules    
print "</tr>\n";

# table line for real data
print "<tr id=\"data\">\n  <td>Data</td>";

if(-e $files[-1]){
  my $file = $files[-1];
  open(IN,$file);
  
  for( my $i=0; $i<@modules; $i++) {
    my $module = $modules[$i];      
    # find lines in summary table
    my @modline = `grep TrigReport $file | grep -w $module`;
    # extract number from line
    if($modline[0] =~ /TrigReport\s+\d+\s+\d+\s+\d+\s+(\d+).*/) {
      my $passed = $1;
      if($passed>0){           
        my $staterror = sqrt($passed);       
        print "  <td>";
        printf("%.2f", $passed);
        print " +- ";
        printf("%.2f", $staterror);
        print "</td>";
      }
      else{ # if event number is zero
        print "  <td>-</td>";       
      }
    } else {
      print "  <td>ERROR: didn't find module $module from $file</td>";
    };  
  }; # end loop over modules    
print "</tr>\n";
}

# close table
print "</table>\n";
print "</html>\n";

exit;
