<!DOCTYPE html>

<?php 

session_start();
include("connection.php");

date_default_timezone_set("Asia/Kolkata");
$date = date("d/m/Y");
$my = date("m/y");
$day = date("d");
$time =  date("H:i a");

$uplo = "SELECT * FROM `SBll` ORDER BY `id` DESC";
$resultuplo = mysqli_query($con, $uplo);
$uplorow = mysqli_fetch_array($resultuplo);
$loc = $uplorow['loc'];
$split = explode("!",$loc);
$lat0 = $split[1];
$lng0 = $split[2];
$locf = $lat0."!".$lng0;

?>

<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>FingerPrint</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">
        <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.10.0/css/all.min.css" rel="stylesheet">
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.4/jquery.min.js" integrity="sha512-pumBsjNRGGqkPzKHndZMaAG+bir374sORyzM3uulLV14lN5LyykqNk8eEeUlUkB3U0M4FApyaHraT65ihJhDpQ==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>
    </head>
<style>
    input{
        width:50%;
        margin-left:25%;
        padding:5px;
    }
    label{
        width:50%;
        margin-left:15%;
    }
    button{
        width:10%;
        margin-left:45%;
        padding:2px;
        font-weight:bold;
        color:white;
        background:green;
    }
</style>
<body>

<div style="width:75%; margin-left:12.5%;">
    <br>
    <br>
    <br>
    <br>
    
        <h1 style='text-align:center;'>Staff In / Out</h1>
        <br>
        <form method="POST">
        <input style="color:red; border:none; text-align:center; font-weight:bolder; font-size:200%;" id="itag" name="itag" type="text" value="" readonly>
        <br>
        <br><br>
        <label>Bus No</label>
        <br>
        <input type="number" name="bnum" required>
        <br>
        <br>
        <button name="submit" style='width:10%; margin-left:45%; background:green; padding:3px; color:white;text-align:center;'>Log</button>
        </form>
        <br>
        <h4 style='color:red; text-align:center;'>Please place your left thumb on the scanner.</h4>
        <br>
        <a href='#' name='submit' style='width:10%; margin-left:45%; background:green; padding:3px; color:white;'>Get Fingerprint</a>
        <br>
    
<?php

if(isset($_POST['submit'])){
    
    
    $fid = $_POST['itag'];
    $bnum = $_POST['bnum'];
    
    
    if($bnum == "1947"){
        
        $_SESSION['sid']=$bnum;
        header('Location: adashboard');
        
    }else{
    
    
    date_default_timezone_set('Asia/Kolkata');
                
    $up2 = "SELECT * FROM `SBstudents` WHERE `fid`='$fid'";
    $resultup2 = mysqli_query($con, $up2);
        
    $count2 = mysqli_num_rows($resultup2);
    
    $up1 = "SELECT * FROM `SBstaff` WHERE `fid`='$fid'";
    $resultup1 = mysqli_query($con, $up1);
        
    $count1 = mysqli_num_rows($resultup1);

    if($count2 != ""){
        
        echo"<br><p style='color:red; font-weight:bold; text-align:center;'>Staffs Only !</p>";
        
    }elseif($count1 != ""){
        
    $rowd1 = mysqli_fetch_array($resultup1);
    $staffid = $rowd1['staffid'];
    
    date_default_timezone_set("Asia/Kolkata");
    $datein = date("d/m/Y");
    
    $tname = $bnum."_".$datein;
    
    echo"<script>alert($date)</script>";
    
     $table2 = "CREATE TABLE `$tname` (
        `id` int(11) AUTO_INCREMENT PRIMARY KEY,
        `uid` VARCHAR(255),
        `who` VARCHAR(255),
        `time` VARCHAR(255),
        `loc` VARCHAR(255),
        `sts` VARCHAR(255))";
            
      $result2 = mysqli_query($con, $table2);
      if(!$result2){
      echo"('Invalid query: '.mysqli_error($con))";
      }else{
          
        $in = "INSERT INTO `SBbus` (`bus`, `date`, `time`, `staff`) VALUE ('$tname', '$datein', '$time', '$staffid')";
        $resultin = mysqli_query($con, $in);
            
            if($resultin){
    
            $in2 = "INSERT INTO `$tname` (`uid`, `who`, `time`, `loc`, `sts`) VALUE ('$staffid', 'staff', '$time', '$locf', 'in')";
            $resultin2 = mysqli_query($con, $in2);
            
                if($resultin2){
        
                $_SESSION['sid']=$staffid;
                header('Location: staffdashboard');
                    
                }else{
                    echo"<span style='color:red; font-weight:bold;'>Unable to register !</span>";
                }
                
            }else{
                echo"<span style='color:red; font-weight:bold;'>Unable to register !</span>";
            }
            
      }
            
    }else{
        echo"<br><p style='color:red; font-weight:bold; text-align:center;'>No such Fingerprint found, <a href='register.php'>enrolled Now</a> !</p>";
    }
}
}

?>

</div>

<script>

setInterval(function(){
$.ajax({
  url: 'ajax.php',
  success: function(data) {
    $('#itag').val(data);
  }
});
},1000);
</script>
</body>

</html>
