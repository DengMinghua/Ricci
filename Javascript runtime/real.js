'use strict'
var py_Real = {
	return_a_real_instance : function(_value) {
		var py_real_instance = new Number(_value);
		return py_real_instance;
	},

	add : function(_value1, _value2) {
		return this.return_a_real_instance(_value1 + _value2);
	},

	sub : function(_value1, _value2) {
		return this.return_a_real_instance(_value1 - _value2);
	}, 

	mul : function(_value1, _value2) {
		return this.return_a_real_instance(_value1 * _value2);
	},

	div : function(_value1, _value2) {
		return this.return_a_real_instance(_value1 / _value2);
	},

	floordiv : function(_value1, _value2) {
		return this.return_a_real_instance(Math.floor(_value1 / _value2));
	},

	mod : function(_value1, _value2) {
		return this.return_a_real_instance(_value1 % _value2);
	},

	pow : function(_value1, _value2) {
		return this.return_a_real_instance(Math.pow(_value1, _value2));
	},

	neg : function(_value) {
		return this.return_a_real_instance(-_value);
	},

	abs : function(_value) {
		return this.return_a_real_instance(Math.abs(_value));
	},

	divmod : function(_value1, _value2) {
		// TODO();
	},
};

var py_Int = Object.create(py_Real);
var py_Float = Object.create(py_Real);

py_Int.return_a_int_instance = py_Real.return_a_real_instance;
py_Float.return_a_float_instance = py_Real.return_a_real_instance;

// ------------------------ Testing ----------------------------

var print = console.log;

var test_list = [

	// py_Int test
	py_Int.add(3, 4),
	py_Int.sub(3, 4),
	py_Int.neg(py_Int.mul(3, 4)),
	py_Int.floordiv(-3, 2),
	py_Int.return_a_int_instance(12450),

	// py_Float test
	py_Float.mod(10, 7),
	py_Float.pow(2, 5),
	py_Float.div(4, 3),
	py_Float.abs(-3.14),
	py_Float.return_a_float_instance(10086),

];

for (var i of test_list) {
	print(i);
}
/*
print(py_Real.__proto__);
print(py_Int.__proto__);
print(py_Float.__proto__);
print('\n');
print(py_Int.return_a_int_instance().__proto__);
print(py_Int.hasOwnProperty('return_a_int_instance'));
print(py_Int.return_a_real_instance === py_Float.return_a_real_instance);
*/