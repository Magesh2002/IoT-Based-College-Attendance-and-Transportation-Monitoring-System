<?php

include("connection.php");
    

    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    
    $split = explode("!",$loc);
    $lat0 = $split[2];
    echo"<p>Long: $lat0</p>";;
    

?>