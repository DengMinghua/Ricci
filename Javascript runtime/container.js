'use strict'

// Python built-in Type Class

var print = console.log;		// define for debug

// Container for Sequence Types -- list, tuple, range
//       and for Unordered Types -- set, dict ;

// *************************************************
// warning :  sets do not support indexing, slicing, 
// 			  or other sequence-like behavior.


// ----------------------------------------------
// Do now.
// ----------------------------------------------

// class Container
var Container = {
	create_Container : function() {
		var py_container = {};
		// Void...
		return py_container;
	},
};

// class Sequence
var Sequence = {
	create_Sequence : function(_len) {
		var py_sequence = new Array(_len);
		return py_sequence;
	},

	opt_in : function(_element, _arr) {
		// Make sure arguments' types
		if (Array.isArray(_element)) {
			_element = [_arr, _arr = _element][0];	// Swap inline
		}

		var _ret = _arr.indexOf(_element) !== -1;
		return _ret;
	},

	opt_not_in : function(_element, _value) {
		return !Sequence.opt_in(_element, _value);
	},

	opt_add : function(_value1, _value2) {
		return _value1.concat(_value2);
	},

	opt_mul : function(_value1, _value2) {
		// Make sure that _value1 is a number and _value2 is an array.
		if (Array.isArray(_value1)) {
			_value1 = [_value2, _value2 = _value1][0];	// Swap inline
		}
		
		var _ret = [];
		for (var i = 0; i < _value1; i++) {
			_ret = _ret.concat(_value2);
		}
		return _ret;
	},

	opt_item : function(_arr, _index) {
		return _arr[_index];
	},

	opt_slice : function(_arr, _left, _right) {
		return _arr.slice(_left, _right);
	},

	opt_index : function(_arr, _element, _left, _right) {
		var _tmpArr = Sequence.opt_slice(_arr, _left, _right);
		var _index = _tmpArr.indexOf(_element) + _left;
		return _index;
	},

	opt_slice_step : function(_value, _value1, _value2, _step) {
		// _step cannot be zero
		var _ret = [];

		if ((_value2 - _value1) * _step < 0) return _ret;
		
		if (_step > 0) {
			for (var i = _value1; i < _value2; i += _step) {
				_ret.push(_value[i]);
			}
		} else if (_step < 0) {
			for (var i = _value1; i > _value2; i += _step) {
				_ret.push(_value[i]);
			}
		}
		return _ret;
	},

	opt_len : function(_value) {
		return _value.length;
	},

	opt_min : function(_arr) {
		var _min = _arr[0];
		for (var i = 1; i < _arr.length; i++) {
			if (_min > _arr[i]) _min = _arr[i];
		}
		return _min;
	},

	opt_max : function(_arr) {
		var _max = _arr[0];
		for (var i = 1; i < _arr.length; i++) {
			if (_max < _arr[i]) _max = _arr[i];
		}
		return _max;
	},

	opt_count : function(_arr, _value) {
		var _ret = 0;
		for (var i in _arr) {
			if (_arr[i] === _value) ++_ret;
		}
		return _ret;
	},
};

// class Unordered_Container
var Unordered_Container = {
	create_Unordered_Container : function() {
		var py_unordered_container = Container.create_Container();
		// TODO();
		return py_unordered_container;
	},
};

// class Mutable_Sequence
var Mutable_Sequence = {
	create_Mutable_Sequence : function() {
		var py_mutable_sequence = Sequence.create_Sequence();
		return py_mutable_sequence;
	},


};

// class Immutable_Sequence
var Immutable_Sequence = {
	create_Immutable_Sequence : function() {
		// TODO();
	},
};

// class List
var List = {
	create_List : function() {
		// TODO();
	},
};

// class Tuple
var Tuple = {
	create_Tuple : function() {
		// TODO();
	},
};

// class Range
var Range = {
	create_Range : function() {
		// TODO();
	},
};

// class Set
var Set = {
	create_Set : function() {
		// TODO();
	},
};

// class Frozenset
var Frozenset = {
	create_Frozenset : function() {
		// TODO();
	},
};

// class Dict
var Dict = {
	create_Dict : function() {
		// TODO();
	},
};

// ----------------------------------------------
// Additional Types -- string, bytes, bytearray
// ----------------------------------------------

// class String
var String = {
	create_String : function() {
		// TODO();
	},
};

// class Bytes
var Bytes = {
	create_Bytes : function() {
		// TODO();
	},
};

// class Bytearry
var Bytearry = {
	create_Bytearry : function() {
		// TODO();
	},
};

// ----------------------------------------------
// Testing.
// ----------------------------------------------

var test_list = [
	"-------------- create function -------------",
	Container.create_Container(),
	Sequence.create_Sequence(),
	Unordered_Container.create_Unordered_Container(),
	Mutable_Sequence.create_Mutable_Sequence(),
	Immutable_Sequence.create_Immutable_Sequence(),
	List.create_List(),
	Tuple.create_Tuple(),
	Range.create_Range(),
	Dict.create_Dict(),
	String.create_String(),

	"-------------- Sequence function -------------",
	Sequence.opt_in(2, [0, 1, 2, 5]),	// true
	Sequence.opt_in([0, 1, 2, 5], 0),	// true
	Sequence.opt_in(3, [0, 1, 2, 5]),	// false

	Sequence.opt_not_in(3, [0, 1, 2, 5]),	// true
	Sequence.opt_add([1, 2], [3, 4]),	// [1, 2, 3, 4]
	Sequence.opt_len([1, 2, 3]),		// 3

	Sequence.opt_mul(3, [1, 2, 3]),		// [1, 2, 3, 1, 2, 3, 1, 2, 3]
	Sequence.opt_mul([1, 2, 3], 3),		// [1, 2, 3, 1, 2, 3, 1, 2, 3]

	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 1, 4, 2),	// [1, 3]
	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 1, 4, -1),	// []
	Sequence.opt_slice_step([0, 1, 2, 3, 4, 5], 4, 0, -1),	// [4, 3, 2]

	Sequence.opt_count([2, 3, 2, 2, 6, 5, 6], 2),	// 3
	Sequence.opt_index([1, 2, 3, 4, 5], 3, 1, 3),	// 2
	Sequence.opt_index([1, 2, 3, 4, 5], 3, 1),		// 2

	Sequence.opt_min([2, 3, 2, 1, 9, 6, 5, 6]),		// 1
	Sequence.opt_max([2, 3, 2, 1, 9, 6, 5, 6]),		// 9	
];

for (var i in test_list) {
	print(test_list[i]);
}