<?php
	$descricao=null;
	$status=null;
	if(isset($_POST['descricao']))
		$descricao=$_POST['descricao'];
	if(isset($_POST['status']))
		$status=$_POST['status'];

	$servidor = 'localhost';
	$usuario = 'root';
	$senha = '';
	$banco = 'dados';
	$mysqli = new mysqli($servidor, $usuario, $senha, $banco);

	if (mysqli_connect_errno()) trigger_error(mysqli_connect_error());

	$mysqli->query("UPDATE acao SET status='$status' WHERE descricao='$descricao'");
	
	$mysqli->close();
?>