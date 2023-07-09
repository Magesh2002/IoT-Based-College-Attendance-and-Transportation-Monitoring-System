<?php

include("connection.php");

$bus = $_POST['bus'];
    
    $in = "SELECT * FROM `$bus` WHERE `sts`='in'";
    $qin = mysqli_query($con, $in);
    $inr = mysqli_num_rows($qin);
    
    
    $out = "SELECT * FROM `$bus` WHERE `sts`='out'";
    $qout = mysqli_query($con, $out);
    $outr = mysqli_num_rows($qout);
    
    if($inr != $outr){
        $l = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
        $ql = mysqli_query($con, $l);
        $rowl = mysqli_fetch_array($ql);
        
        $loc = $rowl['loc'];
        $opl = $rowl['op'];
        
        if($opl == "yes"){
            
            $split = explode("!",$loc);
            $speed = $split[0];
            $lat0 = $split[1];
            $lng0 = $split[2];
            $locc = $lat0."!".$lng0;
            
            $ss = "INSERT INTO `hazard` (`busid`, `loc`, `details`) VALUE('$bus', '$locc', 'Over Speed - $speed')";
            $qss = mysqli_query($con, $ss);
            
            if($qss){
                 $e1 = "SELECT * FROM `hazard` WHERE `busid`='$bus' and `details`!='Crashed' ORDER BY `id` DESC";
                $qe1 = mysqli_query($con, $e1);
                while($e1r = mysqli_fetch_array($qe1)){
                    $sloc = $e1r['loc'];
                    $ssplit = explode("!",$sloc);
                    $inlats = $ssplit[0];
                    $inlngs = $ssplit[1];
                    
                    $sdet = $e1r['details'];
                    
                    echo"<p>$sdet - <a href='https://www.google.com/maps/search/?api=1&query=$inlats,$inlngs'>open</a></p>";
                    
                }
            }
            
        }
        
        
        $f = "SELECT * FROM `SBfo` ORDER BY `id` DESC LIMIT 1";
        $qf = mysqli_query($con, $f);
        $rowf = mysqli_fetch_array($qf);
        
        $fo = $rowf['fo'];
        $opf = $rowf['op'];
        $latf = $rowf['lat'];
        $lngf = $rowf['lng'];
        $locf = $latf."!".$lngf;
        
        if($opf == "yes"){
            
            $ssf = "INSERT INTO `hazard` (`busid`, `loc`, `details`) VALUE('$bus', '$locf', 'Crashed')";
            $qssf = mysqli_query($con, $ssf);
            
            if($qssf){
                $e2 = "SELECT * FROM `hazard` WHERE `busid`='$bus' and `details`='Crashed' ORDER BY `id` DESC";
                $qe2 = mysqli_query($con, $e2);
                while($e2r = mysqli_fetch_array($qe2)){
                    $gloc = $e2r['loc'];
                    $splitt = explode("!",$gloc);
                    $inlat = $splitt[0];
                    $inlng = $splitt[1];
                    
                    $cdet = $e2r['details'];
                    
                    echo"<p>Crashed - <a href='https://www.google.com/maps/search/?api=1&query=$inlat,$inlng'>open</a></p>";
                    
                }
            }
            
        }
        
    }
    
    
    $e = "SELECT * FROM `hazard` WHERE `busid`='$bus' ORDER BY `id` DESC";
                $qe = mysqli_query($con, $e);
                while($er = mysqli_fetch_array($qe)){
                    $eloc = $er['loc'];
                    $splite = explode("!",$eloc);
                    $einlat = $splite[0];
                    $einlng = $splite[1];
                    
                    $cdet = $er['details'];
                    
                    echo"<p>$cdet - <a href='https://www.google.com/maps/search/?api=1&query=$einlat,$einlng'>open</a></p>";
                }
    

?>