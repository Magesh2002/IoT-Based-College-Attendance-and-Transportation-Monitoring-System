<!DOCTYPE html>

<?php 

include("connection.php");

$fid = $_POST['data'];

if($fid == ""){
    echo"unknown $fid";
}else{

$ss = "INSERT INTO `puvan` (`userid`) VALUE('$fid')";
$qss = mysqli_query($con, $ss);

if($qss){
    echo"updated";
}else{
    echo"error";
}
}
?>

<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>FingerPrint</title>  
        
	<script src="//cdnjs.cloudflare.com/ajax/libs/jquery/3.2.1/jquery.min.js"></script>
	<script
	src="https://code.jquery.com/jquery-3.6.0.js"
	integrity="sha256-H+K7U5CnXl1h5ywQfKtSj8PCmoN9aaq30gDh27Xc0jk="
	crossorigin="anonymous"></script>
	
    </head>

<body>

<h1>Finger print data</h1>
<h1 id="op"></h1>

<script>
  setInterval(function(){
        $('#op').load("ajax").fadeIn('slow');
    },1000);
</script>
</body>

</html>
