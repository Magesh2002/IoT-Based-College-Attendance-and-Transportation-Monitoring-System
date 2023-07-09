<?php
$con=mysqli_connect("localhost", "PUVAN", "crisisgonepuv", "negan");
if (!$con) {
    die("Error Connecting to DB".mysqli_connect_error());
}

try{
    if($con = mysqli_connect("localhost", "PUVAN", "crisisgonepuv", "negan")){
        if(!$con){
            die("error".mysqli_connect_error());
        }
    }else{
        throw new Exception('unable to connect');
    }
}
catch(Exception $e){
    echo $e-> getMessage();
}
?>