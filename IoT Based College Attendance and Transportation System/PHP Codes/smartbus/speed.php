<?php

include("connection.php");
    

    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    $op = $row['op'];
    
    $split = explode("!",$loc);
    $lat0 = $split[0];
    if($op == "no"){
    echo"<p>Speed: <span style='color:green;'>$lat0</span> KM/H</p>";
    }else{
    echo"<p>Speed: <span style='color:red;'>$lat0</span> KM/H</p>";
    }
    

?>