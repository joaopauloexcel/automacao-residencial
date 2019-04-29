<?php
	$servidor = 'localhost';
	$usuario = 'root';
	$senha = '';
	$banco = 'dados';
	$mysqli = new mysqli($servidor, $usuario, $senha, $banco);

	if (mysqli_connect_errno()) trigger_error(mysqli_connect_error());

	$sql = "SELECT descricao, valor FROM temperatura";

	$query = $mysqli->query($sql);
	$mysqli->close();
	$mString="{";
	while ($dados = $query->fetch_array()) {
		$mString=$mString.'"'.$dados['descricao'].'":"'.$dados['valor'].'",';
	}
	$mString=substr($mString, 0, -1);
	$mString=$mString."}";
	header("Content-type:application/json"); 
	$mString=json_encode($mString, JSON_UNESCAPED_UNICODE);
	echo $mString;
?>