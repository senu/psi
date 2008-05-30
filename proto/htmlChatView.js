function x() {
	document.getElementById('senu').innerHTML='yyy ddd';
} 

function psi_appendNextMessage() {
	try {
		chatElement = document.getElementById('Chat');
		insertDiv = document.getElementById('insert');
		insertDiv.parentNode.removeChild(insertDiv);
		
		newNode = document.createElement('div');
		newNode.innerHTML='<div class="out content"><div class="nameheader"><div class="name"><nobr>%sender%</nobr></div><div class="protocol"><nobr>%service%</nobr></div></div>        <div class="spacer"></div>       <div class="buddyicon"><img src="%userIconPath%" /></div>        <div class="messagecontainer">                <div class="messagetop">                        <div class="messagetopleft"></div><div class="messagetopright"></div>                </div>                <div class="messagetextcontainer">                        <div class="message">                                <p><span class="messagetime">%time%</span>SENU TU BYL TEZ</p>                                <div id="insert"></div>                        </div>                </div>        </div>        <div class="spacer"></div></div>';

		chatElement.appendChild(newNode.children[0]);
	}
	catch(e) {
		alert(e);
	}
}

function psi_appendConsecutiveMessage() {
	try {	
		insertDiv = document.getElementById('insert');
	}
	catch(e) {
		alert('1 ' + e);
	}
	try {
		parentNode = insertDiv.parentNode;
		newNode = document.createElement('span');
		newNode.innerHTML='<div class="nextmessageline"></div><p><span class="messagetime consecutive">%time%</span>senu tu byl</p><div id="insert"></div>';
		parentNode.replaceChild(newNode, insertDiv);
	}
	catch(e) {
		alert('2 ' + e);
	}
}


