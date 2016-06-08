const APPMSGTYPE_REFRESH = 0;
const APPMSGTYPE_STATUS = 1;
const APPMSGTYPE_LINESTATUS = 2;

Pebble.addEventListener('ready', function(eventType, payload) {
    console.log('ready event');
    sendLineStatusToWatch();
});

Pebble.addEventListener('appmessage', function(eventType, payload) {
    console.log('appmessage event');

});




function sendLineStatusToWatch() {
    status = dummyLineStatusProvider();
    Pebble.sendAppMessage(
	{ "APPMSGKEY_MSGTYPE" : APPMSGTYPE_REFRESH, "APPMSGKEY_NUMLINES" : Object.keys(status).length },
	function(d) { console.log('linenum appmsg sent'); },
	function(d, e) { console.log('linenum appmsg not sent: ' + e); }
    );

    Object.keys(status).forEach(
	function(k, i) {
    	    Pebble.sendAppMessage(
    	    	{
    	    	    "APPMSGKEY_MSGTYPE" : APPMSGTYPE_LINESTATUS,
    	    	    "APPMSGKEY_LINENAME" : k,
    	    	    "APPMSGKEY_LINESTATUS" : status[k]
    	    	},
    	    	function(d) { console.log('linestatus appmsg sent: ' + k); },
    	    	function(d, e) { console.log('linestatus appmsg not sent'); }
	    )
	}
    );
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
