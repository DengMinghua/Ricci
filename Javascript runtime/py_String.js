'use strict'

var print = console.log;		// define for debug

// String

var String_Py = {
	return_an_instance : function(_str) {
		var string_instance = {};
		string_instance.value = _str;
		return string_instance;
	},

	opt_capitalize : function(_str) {
		var _ret = _str.value[0].toUpperCase() + _str.value.slice(1).toLowerCase();
		return this.return_an_instance(_ret);
	},

	opt_casefold : function() {
		// TODO();
	},

	opt_center : function() {
		// TODO();
	},

	opt_count : function() {
		// TODO();
	},

	opt_encode : function() {
		// TODO();
	},

	opt_endswith : function() {
		// TODO();
	},
	
	opt_expandtabs : function() {
		// TODO();
	},

	opt_find : function() {
		// If not find, return -1
		// TODO();
	},
	opt_format : function() {
		// TODO();
	},
	opt_format_map : function() {
		// TODO();
	},
	opt_index : function() {
		// If not find, throw Error
		// TODO();
	},
	opt_isalnum : function(_str) {
		return /^[A-Za-z0-9]+$/g.test(_str.value);
	},
	opt_isalpha : function(_str) {
		return /^[A-Za-z]+$/g.test(_str.value);
	},
	opt_isdecimal : function(_str) {
		return this.opt_isdigit(_str);
	},
	opt_isdigit : function(_str) {
		return /^\d+$/g.test(_str.value);
	},

	opt_isidentifier : function() {
		// TODO();
	},

	opt_islower : function(_str) {
		return /^[a-z]+$/g.test(_str.value);
	},

	opt_isnumeric : function(_str) {
		return this.opt_isdigit(_str);
	},

	opt_isprintable : function() {
		// TODO();
	},

	opt_isspace : function(_str) {
		return /^\s+$/g.test(_str.value);
	},

	opt_istitle : function(_str) {
		var _str_arr = _str.value.split(/[^A-Za-z]+/g);
		var _hit = false;
		if (!_str_arr[0]) _str_arr.splice(0, 1);
		var _back = _str_arr.pop();
		if (_back) _str_arr.push(_back);
		for (var i in _str_arr) {
		    if (!/^[A-Z][a-z]*$/g.test(_str_arr[i])) {
		        return false;
		    } else if (!_hit) {
		        _hit = true;
		    }
		}
		return _hit;
		// return /^.+[[A-Z][a-z]+[^A-Za-z]+]+$/g.test(_str.value);
	},
	opt_isupper : function(_str) {
		return /^[A-Z]+$/g.test(_str.value);
	},
	opt_join : function() {
		// TODO();
	},
	opt_ljust : function() {
		// TODO();
	},
	opt_lower : function(_str) {
		return this.return_an_instance(_str.value.toLowerCase());
	},
	opt_lstrip : function(_str) {
		return this.return_an_instance(_str.value.replace(/^\s+/g, ""));
	},
	opt_maketrans : function() {
		// TODO();
	},
	opt_partition : function() {
		// TODO();
	},
	opt_replace : function() {
		// TODO();
	},
	opt_rindex : function() {
		// TODO();
	},
	opt_rjust : function() {
		// TODO();
	},
	opt_rpartition : function() {
		// TODO();
	},
	opt_rsplit : function() {
		// TODO();
	},
	opt_rstrip : function(_str) {
		return this.return_an_instance(_str.value.replace(/\s+$/g,""));
	},
	opt_split : function() {
		// TODO();
	},
	opt_splitlines : function() {
		// TODO();
	},
	opt_startswith : function() {
		// TODO();
	},

	opt_strip : function(_str) {
		return this.return_an_instance(_str.value.replace(/^\s+|\s+$/g,""));
	},

	opt_swapcase : function() {
		// TODO();
	},
	opt_title : function() {
		// TODO();
	},
	opt_translate : function() {
		// TODO();
	},

	opt_upper : function(_str) {
		return this.return_an_instance(_str.value.toUpperCase());
	},

	opt_zfill : function() {
		// TODO();
	},

};


///////////////////////////////////////////////////
// --------------------------------------------- //
//                    Testing.                   //
// --------------------------------------------- //
/////////////////////////////////////////////////// 


var s1 = String_Py.return_an_instance(" hello, world ! ");
var s2 = String_Py.return_an_instance("aBcDe");
var s3 = String_Py.return_an_instance("121351");
var s4 = String_Py.return_an_instance("1234abc");
var s5 = String_Py.return_an_instance("12 34");
var s6 = String_Py.return_an_instance("abc de");
var s7 = String_Py.return_an_instance("  \n \t ");
var s8 = String_Py.return_an_instance("I Am A Man..Adsdfsf123Gsd...A");
var s9 = String_Py.return_an_instance("ImA Man");
var s10 = String_Py.return_an_instance("..Im A Man..");
var s11 = String_Py.return_an_instance("riDIcUloUs");

var test_list = [
	"[" + String_Py.opt_strip(s1).value + "]",
	"[" + String_Py.opt_rstrip(s1).value + "]",
	"[" + String_Py.opt_lstrip(s1).value + "]",
	String_Py.opt_upper(s2),
	String_Py.opt_lower(s2),
	String_Py.opt_isdigit(s3),
	String_Py.opt_isdigit(s4),
	String_Py.opt_isalpha(s2),
	String_Py.opt_isalpha(s4),
	String_Py.opt_isspace(s7),
	String_Py.opt_isspace(s6),

	String_Py.opt_istitle(s8),
	String_Py.opt_istitle(s9),
	String_Py.opt_istitle(s10),

	String_Py.opt_capitalize(s11),
];

for (var i of test_list) {
	print(i);
}