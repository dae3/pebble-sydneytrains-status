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
	    setTimeout(sendOneLineToWatch(status, index), 1000);
	}
    );
}

function sendLineStatusToWatch() {
    status = dummyLineStatusProvider();
    sendOneLineToWatch(status, 0);
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
