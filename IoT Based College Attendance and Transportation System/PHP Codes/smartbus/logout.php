<?php
session_start();

include("connection.php");


$session = $_SESSION['sid'];

   
date_default_timezone_set("Asia/Kolkata");
$date = date("d/m/Y");
$my = date("m/y");
$day = date("d");
$time =  date("H:i a");
    
$getid = "SELECT * FROM students WHERE studentid='$session'";
$q_getid = mysqli_query($con, $getid);

$nos = mysqli_num_rows($q_getid);

if($nos == ""){
    
    session_destroy();
    header('Location: login');
        
}else{
    
    $s2 = "SELECT * FROM `daily` WHERE `date`='$date' and `sts`='OUT'";
        $resultus2 = mysqli_query($con, $s2);
        $ocnos = mysqli_num_rows($resultus2);
        if($ocnos == ""){
            $ocnt = 0;
        }else{
            $orow = mysqli_fetch_array($resultus2);
            $ocnt = $orow['count'];
        }
        
    $in = "INSERT INTO `loginS` (`studentid`, `date`, `time`, `sts`) VALUE ('$session', '$date', '$time', 'OUT')";
    $resultin = mysqli_query($con, $in);
        
    if($resultin){
            
         $s1 = "SELECT * FROM `loginS` WHERE `studentid`='$session' and `date`='$date' and `sts`='OUT'";
        $resultus1 = mysqli_query($con, $s1);
        
        $nos2 = mysqli_num_rows($resultus1);
        
            if($nos2 == "1"){
                
                $ncnt = $ocnt + 1 ;
                
                if($ocnos == ""){
                    
                $inn = "INSERT INTO `daily` (`date`, `count`, `sts`, `day`, `my`) VALUE ('$date', '$ncnt', 'OUT', '$day', '$my')";
                $resultinn = mysqli_query($con, $inn);
                
                if($resultinn){
                    
                session_destroy();
                header('Location: logout');
                
                }else{
                    echo"<span style='color:red; font-weight:bold;'>Unable to Update daily !</span>";
                }
                
                }else{
                    
                $inn = "UPDATE `daily` SET `count`='$ncnt' WHERE `date`='$date' and `sts`='OUT'";
                $resultinn = mysqli_query($con, $inn);
                
                if($resultinn){
                    
                session_destroy();
                header('Location: logout');
                
                }else{
                    echo"<span style='color:red; font-weight:bold;'>Unable to Update daily !</span>";
                }
                
                }
                
                
            }else{
            
            session_destroy();
            header('Location: logout');
            
            }
            
    }else{
    echo"<span style='color:red; font-weight:bold;'>Unable to Logout !</span>";
    }
    
}
    

?>