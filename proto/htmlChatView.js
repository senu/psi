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


/** Part is almost filled template with %message% keyword,
 * messageBody is value of this keyword*/
function psi_appendNextMessage(messagePart, messageBody) {
    try {
        chatElement = document.getElementById('Chat');
        insertDiv = document.getElementById('insert');

        if(insertDiv != null) //could be removed by appendEvent
            insertDiv.parentNode.removeChild(insertDiv);
		
        newNode = document.createElement('div');
        newNode.innerHTML=psi_setMessageBody(messagePart, messageBody);
        psi_appendChilds(chatElement, newNode);
    }
    catch(e) {
        alert(e);
    }
}

/** Part is almost filled template with %message% keyword,
 * messageBody is value of this keyword*/
function psi_appendConsecutiveMessage(messagePart, messageBody) {
    try {	
        insertDiv = document.getElementById('insert');
    }
    catch(e) {
        alert('1 ' + e);
    }
    try {
        parentNode = insertDiv.parentNode;
        newNode = document.createElement('span'); //TODO 
        newNode.innerHTML=psi_setMessageBody(messagePart, messageBody);
        parentNode.replaceChild(newNode, insertDiv);
    }
    catch(e) {
        alert('2 ' + e);
    }
}

function psi_appendEvent(eventPart) {
    psi_appendNextMessage(eventPart);
}

allowed = [
    "background-color", "color", "font-family", "font-size", "font-style",
    "font-weight", "margin-left", "margin-right", "text-align", "text-decoration", 
    "margin-left-value", "margin-right-value", //GECKO
];


/** Takes String and returns DOM element (<span>) with validated CSS */
function dfs(element) {	
    if(element.nodeType == Node.ELEMENT_NODE) {
        //		alert(element.tagName);
        //check style
        var prevProperty = ''; 
        for(var j=0; j<element.style.length; j++) {
            var cssProperty = element.style.item(j);
            if(allowed.indexOf(cssProperty) == -1 && prevProperty != cssProperty) {
                //				alert(cssProperty + ' - not allowed');
                prevValue = element.style.removeProperty(cssProperty);
                //				alert(cssProperty+' -> '+prevValue);
                j--;
            }
            prevProperty = cssProperty;
        }
		
        //check children
        for(var i=0; i<element.childNodes.length; i++) {
            dfs(element.childNodes[i]);
        }
    }
}

/** Replaces %message% keyword with CSS-validated messageBody */
function psi_setMessageBody(messagePart, messageBody) {
    return messagePart.replace("%message%", psi_validateCSS(messageBody));
}

function psi_validateCSS(elementString) {
    returned = document.createElement('span');	
    returned.innerHTML = elementString;

    dfs(returned);
    return returned.innerHTML;
}

function psi_removeSpaces(string) {
    tstring = "";
    string = '' + string;
    splitstring = string.split(" ");
    for(i = 0; i < splitstring.length; i++)
	tstring += splitstring[i];
    return tstring;
}

function runTests() {
    results = document.getElementById('Chat');

    title = document.createElement('h1');
    title.appendChild(document.createTextNode("Results:"));
    results.appendChild(title);

    e1 =     '<div><strong style="color:red; margin-left: 300px;">strong</strong>y<br style="position:   absolute"/>yyy'+
        '<em style="color:blue;">zzz</em><em style=" border: solid 1px ;   color:green;">aaa</em></div>';
    ve1Str = '<div><strong style="color:red; margin-left: 300px;">strong</strong>y<br style="">yyy'+
        '<em style="color:blue;">zzz</em><em style="border-color: initial; color: green;">aaa</em></div>';


    pe1Str = psi_validateCSS(e1);
    output = document.createElement('p');
    output.innerHTML = pe1Str;

    if(psi_removeSpaces(pe1Str) == psi_removeSpaces(ve1Str)) {
        results.appendChild(document.createTextNode("1 -> OK"));
    }
    else {
        results.appendChild(document.createTextNode("1 -> FAILED"));	
    }

    results.appendChild(output);
	
//    alert(pe1Str.replace(' ', '')+'\n'+ve1Str.replace(' ', ''));
	
		
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
        
 //       runTests();
    }
    catch(e) {
        alert(e);
    }
}
