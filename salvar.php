<?php 
include "conexao.php";
$sensor1 = $_GET['sensor1'];
$sensor2 = $_GET['sensor2'];
$sensor3 = $_GET['sensor3'];

$sql = "INSERT INTO tbdados (sensor1,sensor2,sensor3) values(?,?,?)";

$insert = $conn->prepare($sql)->execute(
	array(
		$sensor1,
		$sensor2,
		$sensor3));
if($insert){
	echo "salvo_com_sucesso";
}else{
	echo "erro_ao_salvar";
}
?>