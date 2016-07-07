!function(t){if("object"==typeof exports&&"undefined"!=typeof module)module.exports=t();else if("function"==typeof define&&define.amd)define([],t);else{var i;i="undefined"!=typeof window?window:"undefined"!=typeof global?global:"undefined"!=typeof self?self:this,i.Pbf=t()}}(function(){return function t(i,e,r){function n(o,a){if(!e[o]){if(!i[o]){var h="function"==typeof require&&require;if(!a&&h)return h(o,!0);if(s)return s(o,!0);var u=new Error("Cannot find module '"+o+"'");throw u.code="MODULE_NOT_FOUND",u}var f=e[o]={exports:{}};i[o][0].call(f.exports,function(t){var e=i[o][1][t];return n(e?e:t)},f,f.exports,t,i,e,r)}return e[o].exports}for(var s="function"==typeof require&&require,o=0;o<r.length;o++)n(r[o]);return n}({1:[function(t,i,e){"use strict";function r(t){var i;t&&t.length&&(i=t,t=i.length);var e=new Uint8Array(t||0);return i&&e.set(i),e.readUInt32LE=s.readUInt32LE,e.writeUInt32LE=s.writeUInt32LE,e.readInt32LE=s.readInt32LE,e.writeInt32LE=s.writeInt32LE,e.readFloatLE=s.readFloatLE,e.writeFloatLE=s.writeFloatLE,e.readDoubleLE=s.readDoubleLE,e.writeDoubleLE=s.writeDoubleLE,e.toString=s.toString,e.write=s.write,e.slice=s.slice,e.copy=s.copy,e._isBuffer=!0,e}function n(t){for(var i,e,r=t.length,n=[],s=0;r>s;s++){if(i=t.charCodeAt(s),i>55295&&57344>i){if(!e){i>56319||s+1===r?n.push(239,191,189):e=i;continue}if(56320>i){n.push(239,191,189),e=i;continue}i=e-55296<<10|i-56320|65536,e=null}else e&&(n.push(239,191,189),e=null);128>i?n.push(i):2048>i?n.push(i>>6|192,63&i|128):65536>i?n.push(i>>12|224,i>>6&63|128,63&i|128):n.push(i>>18|240,i>>12&63|128,i>>6&63|128,63&i|128)}return n}i.exports=r;var s,o,a,h=t("ieee754");s={readUInt32LE:function(t){return(this[t]|this[t+1]<<8|this[t+2]<<16)+16777216*this[t+3]},writeUInt32LE:function(t,i){this[i]=t,this[i+1]=t>>>8,this[i+2]=t>>>16,this[i+3]=t>>>24},readInt32LE:function(t){return(this[t]|this[t+1]<<8|this[t+2]<<16)+(this[t+3]<<24)},readFloatLE:function(t){return h.read(this,t,!0,23,4)},readDoubleLE:function(t){return h.read(this,t,!0,52,8)},writeFloatLE:function(t,i){return h.write(this,t,i,!0,23,4)},writeDoubleLE:function(t,i){return h.write(this,t,i,!0,52,8)},toString:function(t,i,e){var r="",n="";i=i||0,e=Math.min(this.length,e||this.length);for(var s=i;e>s;s++){var o=this[s];127>=o?(r+=decodeURIComponent(n)+String.fromCharCode(o),n=""):n+="%"+o.toString(16)}return r+=decodeURIComponent(n)},write:function(t,i){for(var e=t===o?a:n(t),r=0;r<e.length;r++)this[i+r]=e[r]},slice:function(t,i){return this.subarray(t,i)},copy:function(t,i){i=i||0;for(var e=0;e<this.length;e++)t[i+e]=this[e]}},s.writeInt32LE=s.writeUInt32LE,r.byteLength=function(t){return o=t,a=n(t),a.length},r.isBuffer=function(t){return!(!t||!t._isBuffer)}},{ieee754:3}],2:[function(t,i,e){(function(e){"use strict";function r(t){this.buf=F.isBuffer(t)?t:new F(t||0),this.pos=0,this.length=this.buf.length}function n(t,i){var e,r=i.buf;if(e=r[i.pos++],t+=268435456*(127&e),128>e)return t;if(e=r[i.pos++],t+=34359738368*(127&e),128>e)return t;if(e=r[i.pos++],t+=4398046511104*(127&e),128>e)return t;if(e=r[i.pos++],t+=562949953421312*(127&e),128>e)return t;if(e=r[i.pos++],t+=72057594037927940*(127&e),128>e)return t;if(e=r[i.pos++],t+=0x8000000000000000*(127&e),128>e)return t;throw new Error("Expected varint not more than 10 bytes")}function s(t,i){i.realloc(10);for(var e=i.pos+10;t>=1;){if(i.pos>=e)throw new Error("Given varint doesn't fit into 10 bytes");var r=255&t;i.buf[i.pos++]=r|(t>=128?128:0),t/=128}}function o(t,i,e){var r=16383>=i?1:2097151>=i?2:268435455>=i?3:Math.ceil(Math.log(i)/(7*Math.LN2));e.realloc(r);for(var n=e.pos-1;n>=t;n--)e.buf[n+r]=e.buf[n]}function a(t,i){for(var e=0;e<t.length;e++)i.writeVarint(t[e])}function h(t,i){for(var e=0;e<t.length;e++)i.writeSVarint(t[e])}function u(t,i){for(var e=0;e<t.length;e++)i.writeFloat(t[e])}function f(t,i){for(var e=0;e<t.length;e++)i.writeDouble(t[e])}function d(t,i){for(var e=0;e<t.length;e++)i.writeBoolean(t[e])}function c(t,i){for(var e=0;e<t.length;e++)i.writeFixed32(t[e])}function p(t,i){for(var e=0;e<t.length;e++)i.writeSFixed32(t[e])}function l(t,i){for(var e=0;e<t.length;e++)i.writeFixed64(t[e])}function w(t,i){for(var e=0;e<t.length;e++)i.writeSFixed64(t[e])}i.exports=r;var F=e.Buffer||t("./buffer");r.Varint=0,r.Fixed64=1,r.Bytes=2,r.Fixed32=5;var g=4294967296,v=1/g,b=Math.pow(2,63);r.prototype={destroy:function(){this.buf=null},readFields:function(t,i,e){for(e=e||this.length;this.pos<e;){var r=this.readVarint(),n=r>>3,s=this.pos;t(n,i,this),this.pos===s&&this.skip(r)}return i},readMessage:function(t,i){return this.readFields(t,i,this.readVarint()+this.pos)},readFixed32:function(){var t=this.buf.readUInt32LE(this.pos);return this.pos+=4,t},readSFixed32:function(){var t=this.buf.readInt32LE(this.pos);return this.pos+=4,t},readFixed64:function(){var t=this.buf.readUInt32LE(this.pos)+this.buf.readUInt32LE(this.pos+4)*g;return this.pos+=8,t},readSFixed64:function(){var t=this.buf.readUInt32LE(this.pos)+this.buf.readInt32LE(this.pos+4)*g;return this.pos+=8,t},readFloat:function(){var t=this.buf.readFloatLE(this.pos);return this.pos+=4,t},readDouble:function(){var t=this.buf.readDoubleLE(this.pos);return this.pos+=8,t},readVarint:function(){var t,i,e=this.buf;return i=e[this.pos++],t=127&i,128>i?t:(i=e[this.pos++],t|=(127&i)<<7,128>i?t:(i=e[this.pos++],t|=(127&i)<<14,128>i?t:(i=e[this.pos++],t|=(127&i)<<21,128>i?t:n(t,this))))},readVarint64:function(){var t=this.pos,i=this.readVarint();if(b>i)return i;for(var e=this.pos-2;255===this.buf[e];)e--;t>e&&(e=t),i=0;for(var r=0;e-t+1>r;r++){var n=127&~this.buf[t+r];i+=4>r?n<<7*r:n*Math.pow(2,7*r)}return-i-1},readSVarint:function(){var t=this.readVarint();return t%2===1?(t+1)/-2:t/2},readBoolean:function(){return Boolean(this.readVarint())},readString:function(){var t=this.readVarint()+this.pos,i=this.buf.toString("utf8",this.pos,t);return this.pos=t,i},readBytes:function(){var t=this.readVarint()+this.pos,i=this.buf.slice(this.pos,t);return this.pos=t,i},readPackedVarint:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readVarint());return i},readPackedSVarint:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readSVarint());return i},readPackedBoolean:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readBoolean());return i},readPackedFloat:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readFloat());return i},readPackedDouble:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readDouble());return i},readPackedFixed32:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readFixed32());return i},readPackedSFixed32:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readSFixed32());return i},readPackedFixed64:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readFixed64());return i},readPackedSFixed64:function(){for(var t=this.readVarint()+this.pos,i=[];this.pos<t;)i.push(this.readSFixed64());return i},skip:function(t){var i=7&t;if(i===r.Varint)for(;this.buf[this.pos++]>127;);else if(i===r.Bytes)this.pos=this.readVarint()+this.pos;else if(i===r.Fixed32)this.pos+=4;else{if(i!==r.Fixed64)throw new Error("Unimplemented type: "+i);this.pos+=8}},writeTag:function(t,i){this.writeVarint(t<<3|i)},realloc:function(t){for(var i=this.length||16;i<this.pos+t;)i*=2;if(i!==this.length){var e=new F(i);this.buf.copy(e),this.buf=e,this.length=i}},finish:function(){return this.length=this.pos,this.pos=0,this.buf.slice(0,this.length)},writeFixed32:function(t){this.realloc(4),this.buf.writeUInt32LE(t,this.pos),this.pos+=4},writeSFixed32:function(t){this.realloc(4),this.buf.writeInt32LE(t,this.pos),this.pos+=4},writeFixed64:function(t){this.realloc(8),this.buf.writeInt32LE(-1&t,this.pos),this.buf.writeUInt32LE(Math.floor(t*v),this.pos+4),this.pos+=8},writeSFixed64:function(t){this.realloc(8),this.buf.writeInt32LE(-1&t,this.pos),this.buf.writeInt32LE(Math.floor(t*v),this.pos+4),this.pos+=8},writeVarint:function(t){return t=+t,t>268435455?void s(t,this):(this.realloc(4),this.buf[this.pos++]=127&t|(t>127?128:0),void(127>=t||(this.buf[this.pos++]=127&(t>>>=7)|(t>127?128:0),127>=t||(this.buf[this.pos++]=127&(t>>>=7)|(t>127?128:0),127>=t||(this.buf[this.pos++]=t>>>7&127)))))},writeSVarint:function(t){this.writeVarint(0>t?2*-t-1:2*t)},writeBoolean:function(t){this.writeVarint(Boolean(t))},writeString:function(t){t=String(t);var i=F.byteLength(t);this.writeVarint(i),this.realloc(i),this.buf.write(t,this.pos),this.pos+=i},writeFloat:function(t){this.realloc(4),this.buf.writeFloatLE(t,this.pos),this.pos+=4},writeDouble:function(t){this.realloc(8),this.buf.writeDoubleLE(t,this.pos),this.pos+=8},writeBytes:function(t){var i=t.length;this.writeVarint(i),this.realloc(i);for(var e=0;i>e;e++)this.buf[this.pos++]=t[e]},writeRawMessage:function(t,i){this.pos++;var e=this.pos;t(i,this);var r=this.pos-e;r>=128&&o(e,r,this),this.pos=e-1,this.writeVarint(r),this.pos+=r},writeMessage:function(t,i,e){this.writeTag(t,r.Bytes),this.writeRawMessage(i,e)},writePackedVarint:function(t,i){this.writeMessage(t,a,i)},writePackedSVarint:function(t,i){this.writeMessage(t,h,i)},writePackedBoolean:function(t,i){this.writeMessage(t,d,i)},writePackedFloat:function(t,i){this.writeMessage(t,u,i)},writePackedDouble:function(t,i){this.writeMessage(t,f,i)},writePackedFixed32:function(t,i){this.writeMessage(t,c,i)},writePackedSFixed32:function(t,i){this.writeMessage(t,p,i)},writePackedFixed64:function(t,i){this.writeMessage(t,l,i)},writePackedSFixed64:function(t,i){this.writeMessage(t,w,i)},writeBytesField:function(t,i){this.writeTag(t,r.Bytes),this.writeBytes(i)},writeFixed32Field:function(t,i){this.writeTag(t,r.Fixed32),this.writeFixed32(i)},writeSFixed32Field:function(t,i){this.writeTag(t,r.Fixed32),this.writeSFixed32(i)},writeFixed64Field:function(t,i){this.writeTag(t,r.Fixed64),this.writeFixed64(i)},writeSFixed64Field:function(t,i){this.writeTag(t,r.Fixed64),this.writeSFixed64(i)},writeVarintField:function(t,i){this.writeTag(t,r.Varint),this.writeVarint(i)},writeSVarintField:function(t,i){this.writeTag(t,r.Varint),this.writeSVarint(i)},writeStringField:function(t,i){this.writeTag(t,r.Bytes),this.writeString(i)},writeFloatField:function(t,i){this.writeTag(t,r.Fixed32),this.writeFloat(i)},writeDoubleField:function(t,i){this.writeTag(t,r.Fixed64),this.writeDouble(i)},writeBooleanField:function(t,i){this.writeVarintField(t,Boolean(i))}}}).call(this,"undefined"!=typeof global?global:"undefined"!=typeof self?self:"undefined"!=typeof window?window:{})},{"./buffer":1}],3:[function(t,i,e){e.read=function(t,i,e,r,n){var s,o,a=8*n-r-1,h=(1<<a)-1,u=h>>1,f=-7,d=e?n-1:0,c=e?-1:1,p=t[i+d];for(d+=c,s=p&(1<<-f)-1,p>>=-f,f+=a;f>0;s=256*s+t[i+d],d+=c,f-=8);for(o=s&(1<<-f)-1,s>>=-f,f+=r;f>0;o=256*o+t[i+d],d+=c,f-=8);if(0===s)s=1-u;else{if(s===h)return o?NaN:(p?-1:1)*(1/0);o+=Math.pow(2,r),s-=u}return(p?-1:1)*o*Math.pow(2,s-r)},e.write=function(t,i,e,r,n,s){var o,a,h,u=8*s-n-1,f=(1<<u)-1,d=f>>1,c=23===n?Math.pow(2,-24)-Math.pow(2,-77):0,p=r?0:s-1,l=r?1:-1,w=0>i||0===i&&0>1/i?1:0;for(i=Math.abs(i),isNaN(i)||i===1/0?(a=isNaN(i)?1:0,o=f):(o=Math.floor(Math.log(i)/Math.LN2),i*(h=Math.pow(2,-o))<1&&(o--,h*=2),i+=o+d>=1?c/h:c*Math.pow(2,1-d),i*h>=2&&(o++,h/=2),o+d>=f?(a=0,o=f):o+d>=1?(a=(i*h-1)*Math.pow(2,n),o+=d):(a=i*Math.pow(2,d-1)*Math.pow(2,n),o=0));n>=8;t[e+p]=255&a,p+=l,a/=256,n-=8);for(o=o<<n|a,u+=n;u>0;t[e+p]=255&o,p+=l,o/=256,u-=8);t[e+p-l]|=128*w}},{}]},{},[2])(2)});