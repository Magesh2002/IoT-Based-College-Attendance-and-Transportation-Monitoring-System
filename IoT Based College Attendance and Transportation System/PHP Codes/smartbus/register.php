<!DOCTYPE html>

<?php 

include("connection.php");

?>

<html lang="en">
    <head>
        <meta charset="utf-8">
        <title>Smart Bus</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">
        <link href="https://cdnjs.cloudflare.com/ajax/libs/font-awesome/5.10.0/css/all.min.css" rel="stylesheet">
<script src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.6.4/jquery.min.js" integrity="sha512-pumBsjNRGGqkPzKHndZMaAG+bir374sORyzM3uulLV14lN5LyykqNk8eEeUlUkB3U0M4FApyaHraT65ihJhDpQ==" crossorigin="anonymous" referrerpolicy="no-referrer"></script>

    </head>
<style>
    input{
        width:50%;
        margin-left:25%;
        padding:5px;
    }
    label{
        width:50%;
        margin-left:15%;
    }
    button{
        width:10%;
        margin-left:45%;
        padding:2px;
        font-weight:bold;
        color:white;
        background:green;
    }
</style>
<body>

<div style="width:75%; margin-left:12.5%;">
<br>
<h1 style="text-align:center;">Fingerprint Enrollment</h1>

<form method="POST">

<input style="color:red; border:none; text-align:center; font-weight:bolder; font-size:200%;" type="text" name="fid" id="itag" readonly required>
<br>
<input type="radio" id="stud" name="what" value="stud" style="width:auto; margin-left:35%;">
<label for="stud" style="width:auto; margin:0%;">Student</label>
<input type="radio" id="staff" name="what" value="staff" style="width:auto; margin-left:15%;">
<label for="staff" style="width:auto; margin:0%;">Staff</label>
<br>
<br>
<label>Name</label>
<br>
<input type="text" name="name" required>
<br>
<br>
<label>Department</label>
<br>
<input type="text" name="dept" required>
<br>
<br>
<label>Register No</label>
<br>
<input type="text" name="rno">
<br>
<br>
<label>Parent's Mobile No</label>
<br>
<input type="number" name="pno">
<br>
<br><p style='color:red; text-align:center;'>Please place your left thumb on the scanner.
<a href=''>Get Fingerprint</a></p>";
<br>
<br>
<button name="submit">register</button>
<br>

<?php



if(isset($_POST['submit'])){

    $name = $_POST['name'];
    $rno = $_POST['rno'];
    $pno = $_POST['pno'];
    $dept = $_POST['dept'];
    $finger = $_POST['fid'];
    $what = $_POST['what'];
    $stuid = "sb-".rand(0, 1000);
                
    if($what == "stud"){
                
    $up2 = "SELECT * FROM `SBstudents` WHERE `fid`='$finger''";
    $resultup2 = mysqli_query($con, $up2);
        
    $count2 = mysqli_num_rows($resultup2);

    if($count2 == ''){
        $in = "INSERT INTO `SBstudents` (`name`, `rno`, `pno`, `dept`, `fid`, `studentid`) VALUE ('$name', '$rno', '$pno', '$dept', '$finger', '$stuid')";
        $resultin = mysqli_query($con, $in);
        
        if($resultin){
            
            $_SESSION['sid']=$stuid;
            header('Location: login.php');
            
        }else{
        echo"<span style='color:red; font-weight:bold;'>Unable to register !</span>";
        }
        
    }else{
        echo"<span style='color:red; font-weight:bold;'>User already enrolled, Try <a href='login.php'>login</a> !</span>";
    }
    
    }else{
        
        $up2 = "SELECT * FROM `SBstaff` WHERE `fid`='$finger'";
        $resultup2 = mysqli_query($con, $up2);
            
        $count2 = mysqli_num_rows($resultup2);
    
        if($count2 == ''){
            $in = "INSERT INTO `SBstaff` (`name`, `dept`, `fid`, `staffid`, `contact`) VALUE ('$name', '$dept', '$finger', '$stuid', '$pno')";
            $resultin = mysqli_query($con, $in);
            
            if($resultin){
                
                $_SESSION['sid']=$stuid;
                header('Location: staffdashboard');
                
            }else{
            echo"<span style='color:red; font-weight:bold;'>Unable to register !</span>";
            }
            
        }else{
            echo"<span style='color:red; font-weight:bold;'>User already enrolled, Try <a href='login.php'>login</a> !</span>";
        }
        
    }
}


?>

</form>
</div>
<script>
//   setInterval(function(){
//         $('#op').load("ajax").fadeIn('slow');
//     },1000);

setInterval(function(){
$.ajax({
  url: 'ajax.php',
  success: function(data) {
    $('#itag').val(data);
  }
});
},1000);
</script>
</body>

</html>
