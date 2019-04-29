function gravaLampadas(x,y) {
	$.ajax({
	url: "grava_lampadas.php",
	type: 'POST',
	data: { descricao: x, status: y, },
	success: function(data) {
		console.log(data)
	}
	});
}


$(document).on('click','#div-lampada',function() {
	if(document.getElementById('checkbox_lampada').checked==true)
	{
		document.getElementById('checkbox_lampada').checked = false
		document.getElementById('lampada').src="img/"+document.getElementById('paginaAtual').value+"_desligada.png"
		gravaLampadas(document.getElementById('paginaAtual').value,0);
	}
	else
	{
		document.getElementById('checkbox_lampada').checked = true;
		document.getElementById('lampada').src="img/"+document.getElementById('paginaAtual').value+"_ligada.png"
		gravaLampadas(document.getElementById('paginaAtual').value,1);
	}		
})

function setaLampadas(x)
{
	if(x==1)
	{
		document.getElementById('checkbox_lampada').checked = true;
		document.getElementById('lampada').src="img/"+document.getElementById('paginaAtual').value+"_ligada.png"
	}
	else
	{
		document.getElementById('checkbox_lampada').checked = false;
		document.getElementById('lampada').src="img/"+document.getElementById('paginaAtual').value+"_desligada.png"
	}
}
function atualizaTodasLampadas() {
	$.ajax({
		url: "atualiza_lampadas.php",
		type: 'POST',
		success: function(data) {
			data = JSON.parse(data)
			for (item in data) {
				if((data[item])==1)
				{
					document.getElementById(item).src="img/"+item+"_ligada.png"
				}
				else
				{
					document.getElementById(item).src="img/"+item+"_desligada.png"
				}
			}
		}
	});
}




function atualizar(){
	if (document.getElementById('paginaAtual').value=="principal") {
		atualizaTodasLampadas()
		atualizaTemperatura("principal")
	}else{
		atualizaUmalampada(document.getElementById('paginaAtual').value)
	}
}
function setTime() {
	atualizar()
   	setTimeout(setTime, 1000)
}

function atualizaUmalampada(x) {
	$.ajax({
		url: "atualiza_lampadas.php",
		type: 'POST',
		success: function(data) {
			data = JSON.parse(data)
			setaLampadas(data[x])
		}
	});
}
function atualizaTemperatura(x) {
	$.ajax({
		url: "atualiza_temperatura.php",
		type: 'POST',
		success: function(data) {
			data = JSON.parse(data)
			document.getElementById('temperatura').innerHTML=(data[x]+"°C")
		}
	});
}
$(document).ready(function(){
	setTime()
})