<?php

include("connection.php");

$id = $_POST['data'];

if($id != ""){
    
    if($id < 30){
        $op="no";
    }else{
        $op="yes";
    }
    
    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    $split = explode("!",$loc);
    $speed = $split[0];
    $lat0 = $split[1];
    $lng0 = $split[2];

$ss = "INSERT INTO `SBfo` (`fo`, `op`, `lat`, `lng`) VALUE('$id', '$op', '$lat0', '$lng0')";
$qss = mysqli_query($con, $ss);

if($qss){
    $in = "SELECT * FROM `SBfo` ORDER BY id DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $fo = $row['fo'];
    
    echo"$fo";
    
}else{
    echo"error";
}
}else{
   
    $in = "SELECT * FROM `SBfo` ORDER BY id DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $fo = $row['fo'];
    
    echo"$fo";
}
?>