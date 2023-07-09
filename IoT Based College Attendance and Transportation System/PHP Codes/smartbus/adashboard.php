<html lang="en">
<?php
session_start();

include("connection.php");
$session = $_SESSION['sid'];
if($session == ""){

    header("location:login.php");
    exit;
    
}else{
?>
<head>
	<meta charset="utf-8">
	<meta content="IE=edge" http-equiv="X-UA-Compatible">
	<meta content="width=device-width, initial-scale=1" name="viewport">
	<title>Admin Dashboard</title>
        <link href="https://stackpath.bootstrapcdn.com/bootstrap/4.4.1/css/bootstrap.min.css" rel="stylesheet">

  <script src="https://ajax.googleapis.com/ajax/libs/jquery/3.5.1/jquery.min.js"></script>

</head>
<style>
    table,th,td{
        text-align:center;
        border:1px solid black;
    }
</style>
<body>
    <br>
    <h1 style="text-align:center;">Admin Dashboard</h1>
    <br>
    <span style="position:absolute; top:10%; right:10%; color:red; font-size:80%;" onclick="javascript:location.href='logout'">
        LOGOUT
    </span>
    <div class="container">
        
        <h5 style="text-align:center;">Staff Details</h5>
        <br>
        
    <div class="row">
        <table style="width:100%;">
            <tr>
                <th>Name</th>
                <th>Dept</th>
                <th>Contact</th>
                <th>Bus</th>
            </tr>
        <?php
        include("connection.php");
        $gett = "SELECT * FROM `SBstaff` ORDER BY `id` DESC";
        $q_gett = mysqli_query($con, $gett);
        while($busr = mysqli_fetch_array($q_gett)){
            $name = $busr['name'];
            $uid = $busr['staffid'];
            $contact =$busr['contact'];
            $dept =$busr['dept'];
            echo"
            <tr>
                <td>$name</td>
                <td>$dept</td>
                <td>Contact</td>
                <td class='btn btn-success open' id='$uid'>Open</td>
            </tr>
            ";
        }
        ?>
        
        </table>
   </div>
   </div>
   
   <script>
$(document).ready(function(){
  $(".open").click(function(){
    var bus = this.id;
    window.location.href="staff?no="+bus;
  });
});
       
   </script>
   
</body>
</html>
<?php }?>