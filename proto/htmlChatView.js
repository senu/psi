//internal 
/** Append all what childs to where*/
function psi_appendChilds(where, what) {
	try {
	    while(what.hasChildNodes()) {
		    'app'+where.appendChild(what.firstChild);
	    }
		
	   // where.innerHTML += what.innerHTML; //WTF?
		//TODO ctso: appending link-rel doesnt work? [pro style]
	}
	catch(e) {
		alert('ac'+e);
    }
}


function psi_appendNextMessage(messagePart) {
	try {
		chatElement = document.getElementById('Chat');
		insertDiv = document.getElementById('insert');

		if(insertDiv != null) //could be removed by appendEvent
			insertDiv.parentNode.removeChild(insertDiv);
		
		newNode = document.createElement('div');
		newNode.innerHTML=messagePart;
		psi_appendChilds(chatElement, newNode);
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
		newNode = document.createElement('span'); //TODO 
		newNode.innerHTML=messagePart;
		parentNode.replaceChild(newNode, insertDiv);
	}
	catch(e) {
		alert('2 ' + e);
	}
}

function psi_appendEvent(eventPart) {
	psi_appendNextMessage(eventPart);
}


function psi_initDocument(header, footer) {
	try {
		chatElement = document.createElement("div");
		chatElement.setAttribute("id", "Chat");

		footerElement = document.createElement("span"); //TODO documentFragment?
		headerElement = document.createElement("span"); 
	
		footerElement.innerHTML = footer;
		headerElement.innerHTML = header;
//		alert(document.baseURI);

        psi_appendChilds(document.body, headerElement);
        document.body.appendChild(chatElement);
        psi_appendChilds(document.body, footerElement);
	}
	catch(e) {
		alert(e);
    }
}
