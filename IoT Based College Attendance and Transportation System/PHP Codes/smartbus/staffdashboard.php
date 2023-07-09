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


?>
<head>
	<meta charset="utf-8">
	<meta content="IE=edge" http-equiv="X-UA-Compatible">
	<meta content="width=device-width, initial-scale=1" name="viewport">
	<title>Staff Dashboard</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">

  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

</head>

<body>
    <br>
    <h1 style="text-align:center;">Staff Dashboard</h1>
    <br>
    <h3 style="padding-left:7.5%;">Hai 
    <span style="color:green; font-size:120%;">
        <?php echo"$name";?>
    </span> !
    </h3>
    
    <span style="position:absolute; top:10%; right:10%; color:red; font-size:80%;" onclick="javascript:location.href='logout'">
        LOGOUT
    </span>
    <br>
    <div class="container">
        
        <h5 style="text-align:center;">Your Buses</h5>
        
    <div class="row">
        <?php
            
        $gett = "SELECT * FROM SBbus WHERE staff='$session'";
        $q_gett = mysqli_query($con, $gett);
        while($busr = mysqli_fetch_array($q_gett)){
            $bdate = $busr['date'];
            $btm = $busr['time'];
            $bb =$busr['bus'];
            $sp = explode("_", $bb);
            $bx = $sp['0'];
            $bt = $sp['1'];
            echo"
            <div class='col-3' style='width:98%; border:1px solid white; padding:0%; background-color:rgba(0,0,0,0.3);'>
                <p style='width:90%; margin-left:5%; margin-bottom:3px;'>Bus: $bx <br> $bdate <br> $btm</p>
                <button style='width:75%; margin-left:12.5%; margin-bottom:5%;' class='btn btn-success open' id='$bb'>Open</button>
            </div>";
        }
        ?>
   </div>
   </div>
   
   <script>
   $(document).ready(function(){
  $(".open").click(function(){
    var bus = this.id;
    window.location.href="bus?no="+bus;
  });
});
       
   </script>
   
</body>
</html>
<?php } ?>