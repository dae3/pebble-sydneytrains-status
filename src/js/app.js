const APPMSGTYPE_REFRESH = 0;
const APPMSGTYPE_STATUS = 1;
const APPMSGTYPE_LINESTATUS = 2;
const APPMSGTYPE_PKJSREADY = 3;

var tfnswapi = require('./tfnswapi.js');
var pkjs_ready = false;

Pebble.addEventListener('ready', function(eventType, payload) {
    console.log('ready event');
    pkjs_ready = true;
    Pebble.sendAppMessage({"APPMSGKEY_MSGTYPE" : APPMSGTYPE_PKJSREADY},null, null);
    tfnswapi.api();
});

Pebble.addEventListener('appmessage', function(e) {
    console.log('appmessage event');
    var dict = e.payload;
    //var dict = payload;
    if (!('APPMSGKEY_MSGTYPE' in dict)) {
	console.log('appmsg with no MSGTYPE');
    } else {
	switch (dict['APPMSGKEY_MSGTYPE']) {
	case APPMSGTYPE_REFRESH:
	    console.log('appmsg refresh');
	    sendLineStatusToWatch();
	    break;

	default:
	    console.log('appmsg not refresh');
	    break;
	}
    }
});

function sendOneLineToWatch(status, index) {
    line_names = Object.keys(status);
    
    Pebble.sendAppMessage(
    	{
    	    "APPMSGKEY_MSGTYPE" : APPMSGTYPE_LINESTATUS,
    	    "APPMSGKEY_LINENAME" : line_names[index],
    	    "APPMSGKEY_LINESTATUS" : status[line_names[index]]
    	},
    	function(d) {
	    console.log('linestatus appmsg sent: ' + line_names[index]);
	    if (++index < line_names.length) { sendOneLineToWatch(status, index); }
	},
    	function(d, e) {
	    console.log('linestatus appmsg not sent');
	    // TODO: check syntax - this is erroring at runtime
	    setTimeout(sendOneLineToWatch(status, index), 1000);
	}
    );
}

function sendLineStatusToWatch() {

    status = dummyLineStatusProvider();
    nl = Object.keys(status).length;
    console.log('sendLinestatustowatch ' + nl);
    Pebble.sendAppMessage(
	{ "APPMSGKEY_MSGTYPE" : APPMSGTYPE_REFRESH,
	  "APPMSGKEY_NUMLINES" : nl },
	function(d) {
	    console.log('sendLinestatustowatch OK');
	    sendOneLineToWatch(status, 0);
	},
	function(d, e) {
	    // refresh message failed
	    console.log('sendLinestatustowatch failed ' + e);
	});

}

function dummyLineStatusProvider() {
    var status = {
	line1 : 'Good service',
	line2 : 'Trackwork',
	line3 : 'Delays',
	line4 : 'Major delays'
    };

    return status;
}

function cityrailinfoScreenScraperLineStatusProvider() {
    
}

function gtfsLineStatusProvider() {

}
