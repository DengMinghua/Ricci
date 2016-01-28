'use strict'

var print = console.log;		// define for debug

// Real
var py_Real = {
	return_an_instance : function(_value) {
		var real_instance = new Number(_value);
		return real_instance;
	},

	add : function(_value1, _value2) {
		return this.return_an_instance(_value1 + _value2);
	},

	sub : function(_value1, _value2) {
		return this.return_an_instance(_value1 - _value2);
	}, 

	mul : function(_value1, _value2) {
		return this.return_an_instance(_value1 * _value2);
	},

	div : function(_value1, _value2) {
		return this.return_an_instance(_value1 / _value2);
	},

	floordiv : function(_value1, _value2) {
		return this.return_an_instance(Math.floor(_value1 / _value2));
	},

	mod : function(_value1, _value2) {
		return this.return_an_instance(_value1 % _value2);
	},

	pow : function(_value1, _value2) {
		return this.return_an_instance(Math.pow(_value1, _value2));
	},

	neg : function(_value) {
		return this.return_an_instance(-_value);
	},

	abs : function(_value) {
		return this.return_an_instance(Math.abs(_value));
	},

	divmod : function(_value1, _value2) {
		var _ret1 = this.div(_value1, _value2);
		var _ret2 = this.mod(_value1, _value2);
		return [_ret1, _ret2];
	},
};

// Int
var py_Int = Object.create(py_Real);

// Float
var py_Float = Object.create(py_Real);



///////////////////////////////////////////////////////
// For the Precision Limit :
//   99999999999999999 === 10000000000000000000	// true
//
// Arbitrary Precision Arithmetic for Int
py_Int.apa_add = function(_value1, _value2) {
	// TODO();
};

py_Int.apa_sub = function(_value1, _value2) {
	// TODO();
};

py_Int.apa_mul = function(_value1, _value2) {
	// TODO();
};

py_Int.apa_div = function(_value1, _value2) {
	// TODO();
};

////////////////////////////////////////////
// For the Precision Loss :
//   0.1 + 0.2 = 0.300000000000000004 
// 	 11 * 22.9 != 251.9
//
// Arbitrary Precision Arithmetic for Float
py_Float.apa_add = function(_value1, _value2) {
	var _v1 = 0, _v2 = 0;
	try {_v1 = _value1.toString().split(".")[1].length} catch(e) {}
	try {_v2 = _value2.toString().split(".")[1].length} catch(e) {}
	var _index = Math.pow(10, Math.max(_v1, _v2));
	return (_value1 * _index + _value2 * _index) / _index;
};

py_Float.apa_sub = function(_value1, _value2) {
	var _v1 = 0, _v2 = 0;
	try {_v1 = _value1.toString().split(".")[1].length} catch(e) {}
	try {_v2 = _value2.toString().split(".")[1].length} catch(e) {}
	var _fix = Math.max(_v1, _v2);
	var _index = Math.pow(10, _fix);
	var _ret = (_value1 * _index + _value2 * _index) / _index;
	return parseFloat(_ret.toFixed(_fix));
};

py_Float.apa_mul = function(_value1, _value2) {
	var _index = 0, _s1 = _value1.toString(), _s2 = _value2.toString();
	try {_index += _s1.split(".")[1].length} catch(e) {}
	try {_index += _s2.split(".")[1].length} catch(e) {}
	_s1 = _s1.replace(".", "");
	_s2 = _s2.replace(".", "");
	return Number(_s1) * Number(_s2) / Math.pow(10, _index);
};

py_Float.apa_div = function(_value1, _value2) {
	var _v1 = 0, _v2 = 0;
	try {_v1 = _value1.toString().split(".")[1].length} catch(e) {}
	try {_v2 = _value2.toString().split(".")[1].length} catch(e) {}
	var _s1 = _value1.toString().replace(".", "");
	var _s2 = _value2.toString().replace(".", "");
	return Number(_s1) / Number(_s2) * Math.pow(10, _v2 - _v1);
};

// ------------------------ Testing ----------------------------

var print = console.log;

var test_list = [

	// py_Int test
	py_Int.add(3, 4),
	py_Int.sub(3, 4),
	py_Int.neg(py_Int.mul(3, 4)),
	py_Int.floordiv(-3, 2),
	py_Int.return_an_instance(12450),

	// py_Float test
	py_Float.mod(10, 7),
	py_Float.pow(2, 5),
	py_Float.div(4, 3),
	py_Float.abs(-3.14),
	py_Float.return_an_instance(10086),

	py_Float.apa_add(0.1, 0.2),
	py_Float.apa_sub(0.4, 0.1),
	py_Float.apa_mul(11, 22.9),
	py_Float.apa_div(123.5, 3),
	py_Float.apa_sub(1, 2 / 3),
	py_Float.apa_sub(1, py_Float.apa_div(2, 3)),
];


// Display the test list.
for (var i of test_list) {
	print(i);
}


