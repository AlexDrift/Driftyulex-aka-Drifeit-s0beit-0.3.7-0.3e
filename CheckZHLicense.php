<?php
$f = file('Serials.txt');
$search = $_GET['serial'];
foreach ($f as $v) {
$v = trim($v);
if($v==$search) { echo 'RakSAMPClient'; break; }
}
?>