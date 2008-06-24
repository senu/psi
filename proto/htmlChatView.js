function x() {
	document.getElementById('senu').innerHTML='yyy ddd';
} 

function psi_appendNextMessage(messagePart) {
	try {
		chatElement = document.getElementById('Chat');
		insertDiv = document.getElementById('insert');
		insertDiv.parentNode.removeChild(insertDiv);
		
		newNode = document.createElement('div');
		newNode.innerHTML=messagePart;
		chatElement.appendChild(newNode.children[0]);
	}
	catch(e) {
		alert(e);
	}
}

function psi_appendConsecutiveMessage(messagePart) {
	try {	
		insertDiv = document.getElementById('insert');
	}
	catch(e) {
		alert('1 ' + e);
	}
	try {
		parentNode = insertDiv.parentNode;
		newNode = document.createElement('span');
		newNode.innerHTML=messagePart;
		parentNode.replaceChild(newNode, insertDiv);
	}
	catch(e) {
		alert('2 ' + e);
	}
}


