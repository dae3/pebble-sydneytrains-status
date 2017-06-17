// TFNSW API constants
// https://opendata.transport.nsw.gov.au
const TFNSW_APIKEY = 'XXX';
const TFNSW_APISS = 'YYY';
const TFNSW_HOST = 'https://api.transport.nsw.gov.au';
const TFNSW_AUTHPATH = '/auth/oauth/v2/token';
const TFNSW_AUTHPARAMS = 'grant_type=client_credentials&scope=user';
const TFNSW_PATH = '/v1/gtfs/alerts/sydneytrains';
const TFNSW_TIMEOUT = 10000;

var req;
var tfnswToken;
var Pbf = require('./pbf.js');
var FeedMessage = require('./gtfs.js').FeedMessage;
var Entity = require('./gtfs.js').Entity;
var Alert = require('./gtfs.js').Alert;


function tfnswLogin() {
    req = new XMLHttpRequest();
    req.addEventListener('load',  function() {
	if (this.readyState == 4 && this.status == 200) {
	    tfnswToken = JSON.parse(this.responseText).access_token;
	    console.log('got tfnsw token: ' + tfnswToken);
	    getRealtimeAlerts();
	} else {
	    console.log('xhr tfnsw login failed.');
	}
    });
    req.addEventListener('error', function() {
	console.log(this.statusText);
    });
    req.open('POST', TFNSW_HOST + TFNSW_AUTHPATH);
    req.setRequestHeader("Authorization", 'Basic ' + Base64.encode(TFNSW_APIKEY + ':' + TFNSW_APISS));
    req.timeout = TFNSW_TIMEOUT;
    req.send(TFNSW_AUTHPARAMS);
}

function getTfnswReq(loadProc, errorProc, debug) {
    req = new XMLHttpRequest();
    //req.open('GET', TFNSW_HOST + TFNSW_PATH + '?debug=true');
    req.open('GET', TFNSW_HOST + TFNSW_PATH);
    req.setRequestHeader('Authorization', 'Bearer ' + tfnswToken);
    req.timeout = TFNSW_TIMEOUT;
    req.addEventListener('load', loadProc);
    req.addEventListener('error', errorProc);
    req.responseType = 'arraybuffer';
    if (debug) {
 	req.onreadystatechange = function() {
	    console.log('readystate change to ' + this.readyState);
	};
    }
    console.log(tfnswToken);
    return req;
}

function getRealtimeAlerts() {
    req = getTfnswReq(
	function() {
	    if (this.readyState == 4 && this.status == 200) {
		console.log('load OK');
		var pbf = new Pbf(this.response);
		var fm = FeedMessage.read(pbf);
		for (i in fm.entity) {
		    console.log(fm.entity[i].alert.header_text.translation[0].text);
		}
	    } else {
		console.log('load readystate ' + this.readyState + '  status ' + this.status + ' ' + this.statusText);
		console.log(this.responseText);
	    }
	},
	function() {
	    console.log('error: ' + this.responseText);
	},
	true
    );

    req.send();
    console.log('sent');
}


function tfnswapiLineStatusProvider() {
    var status = {
	line1 : 'Good service',
	line2 : 'Trackwork',
	line3 : 'Delays',
	line4 : 'Major delays'
    };

    console.log('aaa');

    return status;
}

module.exports.login = tfnswLogin;

/* from http://stackoverflow.com/questions/6965107/converting-between-strings-and-arraybuffers */


function str2ab(str) {
  var buf = new ArrayBuffer(str.length*2); // 2 bytes for each char
  var bufView = new Uint16Array(buf);
  for (var i=0, strLen=str.length; i<strLen; i++) {
    bufView[i] = str.charCodeAt(i);
  }
  return buf;
}


/**
*
*  Base64 encode / decode
*  http://www.webtoolkit.info/
*
**/
var Base64 = {
    // private property
    _keyStr : "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=",
    // public method for encoding
    encode : function (input) {
        var output = "";
        var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
        var i = 0;
        input = Base64._utf8_encode(input);
        while (i < input.length) {
            chr1 = input.charCodeAt(i++);
            chr2 = input.charCodeAt(i++);
            chr3 = input.charCodeAt(i++);
            enc1 = chr1 >> 2;
            enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
            enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
            enc4 = chr3 & 63;
            if (isNaN(chr2)) {
                enc3 = enc4 = 64;
            } else if (isNaN(chr3)) {
                enc4 = 64;
            }
            output = output +
            this._keyStr.charAt(enc1) + this._keyStr.charAt(enc2) +
            this._keyStr.charAt(enc3) + this._keyStr.charAt(enc4);
        }
        return output;
    },
    // public method for decoding
    decode : function (input) {
        var output = "";
        var chr1, chr2, chr3;
        var enc1, enc2, enc3, enc4;
        var i = 0;
        input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");
        while (i < input.length) {
            enc1 = this._keyStr.indexOf(input.charAt(i++));
            enc2 = this._keyStr.indexOf(input.charAt(i++));
            enc3 = this._keyStr.indexOf(input.charAt(i++));
            enc4 = this._keyStr.indexOf(input.charAt(i++));
            chr1 = (enc1 << 2) | (enc2 >> 4);
            chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
            chr3 = ((enc3 & 3) << 6) | enc4;
            output = output + String.fromCharCode(chr1);
            if (enc3 != 64) {
                output = output + String.fromCharCode(chr2);
            }
            if (enc4 != 64) {
                output = output + String.fromCharCode(chr3);
            }
        }
        output = Base64._utf8_decode(output);
        return output;
    },
    // private method for UTF-8 encoding
    _utf8_encode : function (string) {
        string = string.replace(/\r\n/g,"\n");
        var utftext = "";
        for (var n = 0; n < string.length; n++) {
            var c = string.charCodeAt(n);
            if (c < 128) {
                utftext += String.fromCharCode(c);
            }
            else if((c > 127) && (c < 2048)) {
                utftext += String.fromCharCode((c >> 6) | 192);
                utftext += String.fromCharCode((c & 63) | 128);
            }
            else {
                utftext += String.fromCharCode((c >> 12) | 224);
                utftext += String.fromCharCode(((c >> 6) & 63) | 128);
                utftext += String.fromCharCode((c & 63) | 128);
            }
        }
        return utftext;
    },
    // private method for UTF-8 decoding
    _utf8_decode : function (utftext) {
        var string = "";
        var i = 0;
        var c = c1 = c2 = 0;
        while ( i < utftext.length ) {
            c = utftext.charCodeAt(i);
            if (c < 128) {
                string += String.fromCharCode(c);
                i++;
            }
            else if((c > 191) && (c < 224)) {
                c2 = utftext.charCodeAt(i+1);
                string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
                i += 2;
            }
            else {
                c2 = utftext.charCodeAt(i+1);
                c3 = utftext.charCodeAt(i+2);
                string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
                i += 3;
            }
        }
        return string;
    }
};
