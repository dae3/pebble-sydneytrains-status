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
    line_names = Object.keys(status);

    Pebble.sendAppMessage(
	{ "APPMSGKEY_MSGTYPE" : APPMSGTYPE_REFRESH, "APPMSGKEY_NUMLINES" : line_names.length },
	function(d) { console.log('linenum appmsg sent'); },
	function(d, e) { console.log('linenum appmsg not sent: ' + e); }
    );

    for (i = 0; i < line_names.length; ) {
    	    Pebble.sendAppMessage(
    	    	{
    	    	    "APPMSGKEY_MSGTYPE" : APPMSGTYPE_LINESTATUS,
    	    	    "APPMSGKEY_LINENAME" : line_names[i],
    	    	    "APPMSGKEY_LINESTATUS" : status[line_names[i]]
    	    	},
    	    	function(d) { i++; console.log('linestatus appmsg sent: ' + line_names[i]);  },
    	    	function(d, e) { console.log('linestatus appmsg not sent'); sleep(2000); }
    	    );
    }
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
