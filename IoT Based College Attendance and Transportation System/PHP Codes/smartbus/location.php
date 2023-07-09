<?php

include("connection.php");


    $in = "SELECT * FROM `SBll` ORDER BY `id` DESC LIMIT 1";
    $qin = mysqli_query($con, $in);
    $row = mysqli_fetch_array($qin);
    
    $loc = $row['loc'];
    
        $split = explode("!",$loc);
        $speed = $split[0];
        $lat0 = $split[1];
        $lng0 = $split[2];
        
        echo"<script>window.location = 'https://www.google.com/maps/search/?api=1&query=$lat0,$lng0';</script>";

?>