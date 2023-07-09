<?php

include("connection.php");

$id = $_POST['data'];

if($id != ""){

$ss = "INSERT INTO `SBfp` (`userid`) VALUE('$id')";
$qss = mysqli_query($con, $ss);

if($qss){
    $in = "SELECT * FROM `SBfp` ORDER BY id DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $finger = $row['userid'];
    
    echo"$finger";
    
}else{
    echo"error";
}
}else{
   
    $in = "SELECT * FROM `SBfp` ORDER BY id DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $finger = $row['userid'];
    
    echo"$finger";
}
?>