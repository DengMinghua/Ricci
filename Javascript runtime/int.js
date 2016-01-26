var py_Int = {
	return_a_int_instance : function(_value) {
		var py_int_instance = {};
		py_int_instance.value = _value || 0;
		return py_int_instance;
	},

	add : function(_value1, _value2) {
		return this.return_a_int_instance(_value1 + _value2);
	},

	sub : function(_value1, _value2) {
		return this.return_a_int_instance(_value1 - _value2);
	},

	mul : function(_value1, _value2) {
		return this.return_a_int_instance(_value1 * _value2);
	},

	div : function(_value1, _value2) {
		return this.return_a_int_instance(_value1 / _value2);
	},

	floordiv : function(_value1, _value2) {
		return this.return_a_int_instance(Math.floor(_value1 / _value2));
	},

	mod : function(_value1, _value2) {
		return this.return_a_int_instance(_value1 % _value2);
	},

	pow : function(_value1, _value2) {
		return this.return_a_int_instance(Math.pow(_value1, _value2));
	},

	neg : function(_value) {
		return this.return_a_int_instance(-_value);
	},

	abs : function(_value) {
		return this.return_a_int_instance(Math.abs(_value));
	},

	divmod : function(_value1, _value2) {
		// TODO();
	},
};
