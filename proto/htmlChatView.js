//internal 
/** Append all what childs to where*/
function psi_appendChilds(where, what) {
    try {
        while(what.hasChildNodes()) {
            'app'+where.appendChild(what.firstChild);
        }
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
    jsNotifier.appendFinished();
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
    jsNotifier.appendFinished();
}

function psi_appendEvent(eventPart) {
    psi_appendNextMessage(eventPart);
}

allowed = [
    "background-color", "color", "font-family", "font-size", "font-style",
    "font-weight", "margin-left", "margin-right", "text-align", "text-decoration", 
];


function psi_dfs(element) {	
    if(element.nodeType == Node.ELEMENT_NODE) {
        
        //check style
        var prevProperty = ''; 
        for(var j=0; j<element.style.length; j++) {
            var cssProperty = element.style.item(j);
            if(allowed.indexOf(cssProperty) == -1 && prevProperty != cssProperty) {
                prevValue = element.style.removeProperty(cssProperty);
                j--;
            }
            prevProperty = cssProperty;
        }

        //check children
        for(var i=0; i<element.childNodes.length; i++) {
            psi_dfs(element.childNodes[i]);
        }
    }
}

/** Replaces %message% keyword with CSS-validated messageBody */
function psi_setMessageBody(messagePart, messageBody) {
    return messagePart.replace("%message%", psi_validateCSS(messageBody));
}

/** Takes String and returns DOM element (<span>) with validated CSS */
function psi_validateCSS(elementString) {
    returned = document.createElement('span');	
    returned.innerHTML = elementString;

    psi_dfs(returned);
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


function psi_runTests() {
    results = document.getElementById('results');

    title = document.createElement('h1');
    title.appendChild(document.createTextNode("Results:"));
    results.appendChild(title);

    inp = '<div><strong style="color:red; margin-left: 300px;">strong</strong>y<br style="position:   absolute"/>yyy'+
        '<em style="color:blue;">zzz</em><em style=" border: solid 1px ;   color:green;">aaa</em></div>';
    out = '<div><strong style="color:red; margin-left: 300px;">strong</strong>y<br style="">yyy'+
        '<em style="color:blue;">zzz</em><em style="border-color: initial; color: green;">aaa</em></div>';

    psi_cssRunTest("1. sample test", inp, out, results);

    inp = '';
    out = '';
   
    psi_cssRunTest("2. empty string", inp, out, results);
    
    inp = '<div style=""></div>';
    out = '<div style=""></div>';
   
    psi_cssRunTest("3. empty style attr", inp, out, results);
    
    inp = '<div style=""><strong style="clear: both;">xxx</strong></div>';
    out = '<div style=""><strong style="">xxx</strong></div>';
   
    psi_cssRunTest("4. single bad style prop.", inp, out, results);
    
    
    inp = '<div style="">a<strong style="cle%ar: b;:o=th; color:red">xxx</strong></div>';
    out = '<div style="">a<strong style="cle%ar: b;:o=th; color:red">xxx</strong></div>';

    //NOTICE imho webkit output is invalid, but it displays test proper way
    psi_cssRunTest("5. invalid style attribute", inp, out, results);


    inp = '<div style=""><strong style="clear: both; text-align:right;   dispaly:none">xxx</strong></div>';
    out = '<div style=""><strong style="text-align:right;">xxx</strong></div>';
   
    psi_cssRunTest("6. bad; good; bad; prop.", inp, out, results);
    
    inp = '<div style=""><strong style="clear: both; cursor: corsshair;  dispaly:none">xxx</strong></div>';
    out = '<div style=""><strong style="">xxx</strong></div>';
   
    psi_cssRunTest("6. bad; bad; bad; prop.", inp, out, results);
    



}

function psi_cssRunTest(name, input, validOutput, results) {
    pe1Str = psi_validateCSS(input);
    output = document.createElement('p');
    output.innerHTML = pe1Str;
    
    pe1Str = psi_removeSpaces(pe1Str);
    validOutput =  psi_removeSpaces(validOutput);

    summary = document.createElement('strong');
   
    if(pe1Str == validOutput) {
        summary.innerHTML = name + ' -> <span style="color: darkgreen">OK</span>';
        results.appendChild(summary);
    }
    else {
        summary.innerHTML = name + ' -> <span style="color: red">FAILED</span>';
        results.appendChild(summary);

        results.appendChild(document.createElement('br'));
        results.appendChild(document.createElement('br'));
        results.appendChild(document.createTextNode(validOutput));
        results.appendChild(document.createElement('br'));

        results.appendChild(document.createTextNode(pe1Str));
        //results.innerHTML += psi_validateCSS(input);
    }

   
    results.appendChild(document.createElement('br'));
}


function psi_initDocument(header, footer) {
    try {
        chatElement = document.createElement("div");
        chatElement.setAttribute("id", "Chat");

        footerElement = document.createElement("span");
        headerElement = document.createElement("span"); 

        footerElement.innerHTML = footer;
        headerElement.innerHTML = header;
        //		alert(document.baseURI);

        psi_appendChilds(document.body, headerElement);
        document.body.appendChild(chatElement);
        psi_appendChilds(document.body, footerElement);

        //       runTests();
        jsNotifier.initFinished();
    }
    catch(e) {
        alert(e);
    }
}

//removes messages from ChatView
function psi_clearMessages() {
    chatElement = document.getElementById('Chat');
    chatElement.innerHTML = "";
}
