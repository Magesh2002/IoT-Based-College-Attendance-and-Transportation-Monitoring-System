<html lang="en">
<?php
session_start();

include("connection.php");
$session = $_SESSION['sid'];
if($session == ""){

    header("location:login.php");
    exit;
    
}else{
    
$getid = "SELECT * FROM SBstaff WHERE staffid='$session'";
$q_getid = mysqli_query($con, $getid);

$dataid=mysqli_fetch_array($q_getid);
$name = $dataid['name'];

date_default_timezone_set("Asia/Kolkata");
$date = date("d/m/Y");
$my = date("m/y");
$time =  date("H:i a");

$gbus = $_GET['no'];

$gett = "SELECT * FROM SBbus WHERE bus='$gbus'";
$q_gett = mysqli_query($con, $gett);
$busr = mysqli_fetch_array($q_gett);
    $bdate = $busr['date'];
    $btm = $busr['time'];
    $bb =$busr['bus'];
    $sp = explode("_", $bb);
    $bx = $sp['0'];
    $bt = $sp['1'];
        
?>
<head>
	<meta charset="utf-8">
	<meta content="IE=edge" http-equiv="X-UA-Compatible">
	<meta content="width=device-width, initial-scale=1" name="viewport">
	<title>Bus Details</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">

  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

</head>
<style>
    #flot{
        position: fixed;
        top:5%;
        right:5%;
        width:15%;
        height:15%;
    }
</style>
<body>
    
    <div id="flot">
        <p id="spd"></p>
        <p id="lat"></p>
        <p id="lng"></p>
    </div>
    
    <h1 style="text-align:center;"> 
    <span style="color:green; font-size:100%;">
        <?php echo"$bx";?>
    </span>
    Bus Details</h1>
    <form method="POST">
        <input style="width:100%; color:red; border:none; text-align:center; font-weight:bolder; font-size:200%;" id="itag" name="itag" type="text" value="" readonly>
        <br>
        <input style="width:100%; color:black; border:none; text-align:center; font-weight:bold; font-size:100%;" id="ltag" name="ltag" type="text" value="" readonly hidden>
        <br>
        <div class="container">
            <div class="row" style="justify-content: space-evenly;">
                <button name="submit" class="col-4 btn btn-success">Log</button>
                <button class="col-4 btn btn-success"><a href='location' style="color:white;">Location</a></button>
            </div>
        </div>
        <?php
        if(isset($_POST['submit'])){
    
        $fid = $_POST['itag'];
        $locf = $_POST['ltag'];
        $split = explode("!",$locf);
        $speed = $split[0];
        $lat0 = $split[1];
        $lng0 = $split[2];
        $floc = $lat0."!".$lng0;
        
        $up2 = "SELECT * FROM `SBstudents` WHERE `fid`='$fid'";
        $resultup2 = mysqli_query($con, $up2);
            
        $count2 = mysqli_num_rows($resultup2);
        
        $up1 = "SELECT * FROM `SBstaff` WHERE `fid`='$fid'";
        $resultup1 = mysqli_query($con, $up1);
            
        $count1 = mysqli_num_rows($resultup1);
    
        if($count2 != ""){
            
        $rowd2 = mysqli_fetch_array($resultup2);
        $stuid = $rowd2['studentid'];
        $pnum = $rowd2['pno'];
        
            $up01 = "SELECT * FROM `$gbus` WHERE `uid`='$stuid'";
            $resultup01 = mysqli_query($con, $up01);
                
            $count01 = mysqli_num_rows($resultup01);
            if($count01 == "2"){
                echo"<br><p style='width:100%; text-align:center; color:red;'>Your travel has been finished already</p>";
            }elseif($count01 == "1"){
                
                $in01 = "INSERT INTO `$gbus` (`uid`, `who`, `time`, `loc`, `sts`) VALUE ('$stuid', 'stud', '$time', '$floc', 'out')";
                $resultin01 = mysqli_query($con, $in01);
                
            }else{
            
                $in01 = "INSERT INTO `$gbus` (`uid`, `who`, `time`, `loc`, `sts`) VALUE ('$stuid', 'stud', '$time', '$floc', 'in')";
                $resultin01 = mysqli_query($con, $in01);
                if($resultin01){
                    header("location:https://wa.me/91$pnum?text=http://projectoutput.co.in/smartbus/bus?no=$gbus");
                }
                
            }
            
        }elseif($count1 != ""){
            
        $rowd1 = mysqli_fetch_array($resultup1);
        $staffid = $rowd1['staffid'];
        
         $up02 = "SELECT * FROM `$gbus` WHERE `uid`='$staffid'";
            $resultup02 = mysqli_query($con, $up02);
                
            $count02 = mysqli_num_rows($resultup02);
            if($count02 == "2"){
                echo"<br><p style='width:100%; text-align:center; color:red;'>Your travel has been finished already</p>";
            }elseif($count02 == "1"){
                
                $in02 = "INSERT INTO `$gbus` (`uid`, `who`, `time`, `loc`, `sts`) VALUE ('$staffid', 'staff', '$time', '$floc', 'out')";
                $resultin02 = mysqli_query($con, $in02);
                
            }else{
            
                $in02 = "INSERT INTO `$gbus` (`uid`, `who`, `time`, `loc`, `sts`) VALUE ('$staffid', 'staff', '$time', '$floc', 'in')";
                $resultin02 = mysqli_query($con, $in02);
                
            }
        
        }else{
            echo"No User Found";
        }
        }
        ?>
        </form>
        <br>
        <h4 style='color:red; text-align:center;'>Please place your left thumb on the scanner.</h4>
    <br>
    <div class="container-fluid">
        
        <div class="row">
            
        <div class="col-md-6" style="height:500px; min-height:500px; overflow:scroll; background-color:rgba(0,100,0,0.3);">
          
        <h5 style="text-align:center; margin-top:2%; margin-bottom:3%;">In Details</h5>
            
        <style>
            table,th,td{
                border:1px solid black;
                padding:0.7%;
            }
        </style>
            
        <table style="width:100%;">
            <tr>
                <th style="text-align:center;">Name</th>
                <th style="text-align:center;">Time</th>
                <th style="text-align:center;">Location</th>
            </tr>
        
        <?php

        $gettt = "SELECT * FROM `$gbus` WHERE `who`='staff' and `sts`='in'";
        $q_gettt = mysqli_query($con, $gettt);
        while($busin = mysqli_fetch_array($q_gettt)){
            $uid = $busin['uid'];
            $inloc = $busin['loc'];
            $intime = $busin['time'];
            
            $inl = explode("!", $inloc);
            $inlat = $inl['0'];
            $inlng = $inl['1'];
            
            $gets = "SELECT * FROM `SBstaff` WHERE `staffid`='$uid'";
            $q_gets = mysqli_query($con, $gets);
            
            $datas=mysqli_fetch_array($q_gets);
            $names = $datas['name'];
            
            echo"
            <tr>
                <td style='text-align:center; color:green; font-weight:bold;'>$names</td>
                <td style='text-align:center;'>$intime</td>
                <td style='text-align:center;'><a href='https://www.google.com/maps/search/?api=1&query=$inlat,$inlng'>Open</a></td>
            </tr>
            ";
            
        }
        ?>
        
        <?php

        $gettt = "SELECT * FROM `$gbus` WHERE `who`='stud' and `sts`='in'";
        $q_gettt = mysqli_query($con, $gettt);
        while($busin = mysqli_fetch_array($q_gettt)){
            $uid = $busin['uid'];
            $inloc = $busin['loc'];
            $intime = $busin['time'];
            
            $inl = explode("!", $inloc);
            $inlat = $inl['0'];
            $inlng = $inl['1'];
            
            $gets = "SELECT * FROM `SBstudents` WHERE `studentid`='$uid'";
            $q_gets = mysqli_query($con, $gets);
            
            $datas=mysqli_fetch_array($q_gets);
            $names = $datas['name'];
            
            echo"
            <tr>
                <td style='text-align:center;'>$names</td>
                <td style='text-align:center;'>$intime</td>
                <td style='text-align:center;'><a href='https://www.google.com/maps/search/?api=1&query=$inlat,$inlng'>Open</a></td>
            </tr>
            ";
            
        }
        ?>
        
        </table>
   </div>
   
     <div class="col-md-6" style="height:500px; min-height:500px; overflow:scroll; background-color:rgba(100,0,0,0.3);">
            
        <h5 style="text-align:center; margin-top:2%; margin-bottom:3%;">Out Details</h5>
            
        <table style="width:100%;">
            <tr>
                <th style="text-align:center;">Name</th>
                <th style="text-align:center;">Time</th>
                <th style="text-align:center;">Location</th>
            </tr>
        
        <?php

        $gettt = "SELECT * FROM `$gbus` WHERE `who`='staff' and `sts`='out'";
        $q_gettt = mysqli_query($con, $gettt);
        while($busin = mysqli_fetch_array($q_gettt)){
            $uid = $busin['uid'];
            $inloc = $busin['loc'];
            $intime = $busin['time'];
            
            $inl = explode("!", $inloc);
            $inlat = $inl['0'];
            $inlng = $inl['1'];
            
            $gets2 = "SELECT * FROM `SBstaff` WHERE `staffid`='$uid'";
            $q_gets2 = mysqli_query($con, $gets2);
            
            $datas2=mysqli_fetch_array($q_gets2);
            $names2 = $datas2['name'];
            
            echo"
            <tr>
                <td style='text-align:center; color:green; font-weight:bold;'>$names2</td>
                <td style='text-align:center;'>$intime</td>
                <td style='text-align:center;'><a href='https://www.google.com/maps/search/?api=1&query=$inlat,$inlng'>Open</a></td>
            </tr>
            ";
            
        }
        ?>
        
        <?php

        $gettt = "SELECT * FROM `$gbus` WHERE `who`='stud' and `sts`='out'";
        $q_gettt = mysqli_query($con, $gettt);
        while($busin = mysqli_fetch_array($q_gettt)){
            $uid = $busin['uid'];
            $inloc = $busin['loc'];
            $intime = $busin['time'];
            
            $inl = explode("!", $inloc);
            $inlat = $inl['0'];
            $inlng = $inl['1'];
            
            $gets = "SELECT * FROM `SBstudents` WHERE `studentid`='$uid'";
            $q_gets = mysqli_query($con, $gets);
            
            $datas=mysqli_fetch_array($q_gets);
            $names = $datas['name'];
            
            echo"
            <tr>
                <td style='text-align:center;'>$names</td>
                <td style='text-align:center;'>$intime</td>
                <td style='text-align:center;'><a href='https://www.google.com/maps/search/?api=1&query=$inlat,$inlng'>Open</a></td>
            </tr>
            ";
            
        }
        ?>
        
        </table>
   </div>
   </div>
   
   
   <div class="row">
       <div class="col-md-12" id="hazard" style="background-color:indianred;">
           
       </div>
   </div>
   
   
   </div>
</body>
<script>

setInterval(function(){
$.ajax({
  url: 'ajax',
  success: function(data) {
    $('#itag').val(data);
  }
});
},1000);


setInterval(function(){
$.ajax({
  url: 'ajax2',
  success: function(data) {
    $('#ltag').val(data);
  }
});
},1000);


setInterval(function(){
$("#lat").load("lat");
},1000);

setInterval(function(){
$("#lng").load("lng");
},1000);

setInterval(function(){
$("#spd").load("speed");
},1000);

setInterval(function(){
    var bus = '<?php echo"$gbus";?>';
$("#hazard").load("hazard", {bus:bus});
},1000);

</script>
</html>
<?php } ?>