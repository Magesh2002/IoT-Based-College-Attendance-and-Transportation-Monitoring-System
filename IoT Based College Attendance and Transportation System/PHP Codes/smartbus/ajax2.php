<?php

include("connection.php");

$id = $_POST['data'];

if($id != ""){
    
$split = explode("!",$id);
$speed = $split[0];
$lat0 = $split[1];
$lng0 = $split[2];
$locf = $speed."!".$lat0."!".$lng0;

if($speed < "50"){
    $op = "no";
}else{
    $op = "yes";
}

$ss = "INSERT INTO `SBll` (`loc`, `op`) VALUE('$locf', '$op')";
$qss = mysqli_query($con, $ss);

if($qss){
    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    
    echo"$loc";
    
}else{
    echo"error";
}
}else{
    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    
    echo"$loc";
}
?>