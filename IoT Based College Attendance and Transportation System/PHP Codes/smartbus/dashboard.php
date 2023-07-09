<html lang="en">
<?php
session_start();

include("connection.php");
$session = $_SESSION['sid'];
if($session == ""){

    header("location:login.php");
    exit;
    
}else{
    
$getid = "SELECT * FROM students WHERE studentid='$session'";
$q_getid = mysqli_query($con, $getid);

$dataid=mysqli_fetch_array($q_getid);
$name = $dataid['name'];

date_default_timezone_set("Asia/Kolkata");
$date = date("d/m/Y");
$time =  date("H:i a");
?>
<head>
	<meta charset="utf-8">
	<meta content="IE=edge" http-equiv="X-UA-Compatible">
	<meta content="width=device-width, initial-scale=1" name="viewport">
	<title>Attendance System</title>

  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>



</head>
<style>
    textarea{
        width:75%;
        margin-left:12.5%;
        padding:5px;
    }
    button{
        width:7%;
        margin-left:46.5%;
        padding:5px;
        font-weight:bold;
        color:white;
        background:green;
    }
</style>
<body>
    <h1 style="text-align:center;">Student Dashboard</h1>
    <h3 style="padding-left:7.5%;">Hai <span style="color:green; font-size:160%;"><?php echo"$name";?></span> !<span style="position:absolute; top:10%; right:10%; color:red; font-size:80%;" onclick="javascript:location.href='logout'">LOGOUT</span></h3>
    
    <br>
    <h2 style="padding-left:7.5%;">Have a Doubt ?</h2>
    <form method="POST">
    <textarea type="text" name="data" required placeholder="Feel feel to clear your doubts. Type-in your doubt and ask now." rows="5"></textarea>
        <br>
        <br>
    <button name="submit">Ask</button>
    </form>
    
    <?php
    
    if(isset($_POST['submit'])){
    
    $data = $_POST['data'];
    
     $in = "INSERT INTO `doubt` (`studentid`, `date`, `time`, `data`) VALUE ('$session', '$date', '$time', '$data')";
        $resultin = mysqli_query($con, $in);
        
        if($resultin){
            echo"<p style='color:green; text-align:center;'>Your doubt has been successfully submitted</p>";
        }else{
            echo"<p style='color:indianred; text-align:center;'>Can't submit your doubt, try again after few minutes!</p>";
        }
            
    
    }
    ?>
    
    <div style="display:block; height:40%; width:85%; margin-left:7.5%; border:2px solid black; overflow:scroll;">
        <?php
        
        $getdbt = "SELECT * FROM doubt WHERE studentid='$session' and date='$date' ORDER BY id DESC";
        $q_getdbt = mysqli_query($con, $getdbt);
        
        $nos = mysqli_num_rows($q_getdbt);
        
        if($nos == "0"){
            echo"
                <h6 style='width:100%; text-align:center; margin-top:10%; color:indianred;'>No doubtes asked yet!</h6>
            ";
        }else{
            while($datas = mysqli_fetch_array($q_getdbt)){
            $dataa = $datas['data'];
            $reply = $datas['reply'];
            $when = $datas['date']."-".$datas['time'];
            
            if($reply == ""){
                
            echo"
                <p style='width:90%; text-align:start; margin-top:1%; margin-left:5%;'><span style='color:red; font-size:70%; font-weight:bolder;'>($when) --> </span> $dataa</p>
                <hr style='border:1px solid black; background-color:black; margin:2%; width:96%;'>
            ";
            
            }else{
                
                
            echo"
                <p style='width:90%; text-align:start; margin-top:1%; color:black; margin-left:5%;'><span style='font-size:70%; font-weight:bolder; color:green;'>($when) --> </span> $dataa</p>
                <p style='width:80%; text-align:start; margin-top:1%; color:yellow; margin-left:10%; background-color:black;'>$reply</p>
                <hr style='border:1px solid black; background-color:black; margin:2%; width:96%;'>
            ";
            
            }
            }
        }
        
        ?>
        
    </div>

</body>
<script>

//   setInterval(function(){
//         $('#orders').load("ind.php").fadeIn('slow');
//     },1000);
  
//  setInterval(function(){
//         $('#orderm').load("ind2.php").fadeIn('slow');
//     },1000);

</script>
</html>
<?php } ?>