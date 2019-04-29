<?php
	$descricao='principal';
	$valor=null;

	if(isset($_GET['valor']))
		$valor=$_GET['valor'];

	$servidor = 'localhost';
	$usuario = 'root';
	$senha = '';
	$banco = 'dados';
	$mysqli = new mysqli($servidor, $usuario, $senha, $banco);

	if (mysqli_connect_errno()) trigger_error(mysqli_connect_error());

	$mysqli->query("UPDATE temperatura SET valor='$valor' WHERE descricao='$descricao'");
	
	$mysqli->close();
?>