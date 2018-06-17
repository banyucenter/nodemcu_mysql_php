<!DOCTYPE html>
<html>
<head>
	<meta charset="utf-8">
	<title>NodeMCU + Mysql + Php</title>
</head>
<body>
	<form action="" method="post">
		<input type="date" name="form_data">
		<input type="submit" name="submit" value="Pesquisar">
	</form>
	<?php
	include "conexao.php";
	if($_SERVER['REQUEST_METHOD'] == "POST"){
		$data = $_POST['form_data'];
	}else{
		$data = date('Y-m');
	}
	$sql ="SELECT * from tbdados WHERE data_hora LIKE '%$data%' ";
	$select = $conn->prepare($sql);

	$select->execute();
	?><table border="1px">
		<tr>
			<th>Sensor1</th>
			<th>Sensor2</th>
			<th>Sensor3</th>
			<th>Data/Hora</th>
		</tr>
		<?php
		while ($linhas = $select->fetch(PDO::FETCH_OBJ)) {
			?>	
			<tr>
				<td><?php echo $linhas->sensor1; ?></td>
				<td><?php echo $linhas->sensor2; ?></td>
				<td><?php echo $linhas->sensor3; ?></td>
				<td><?php echo $linhas->data_hora; ?></td>
			</tr>
			<?php
		}
		?>	
	</table>
</body>
</html>